#!/usr/bin/python3

# Chris Fallin, 2012
# Yoongu Kim, 2013
# Juan Gomez Luna, 2017
# Minesh Patel, 2020

import sys, os, subprocess, re, glob, argparse, csv

ref = "./basesim_original"
sim = "./sim"

bold = "\033[1m"
green = "\033[0;32m"
red = "\033[0;31m"
normal = "\033[0m"


def main(sweep):
    all_inputs = glob.glob("inputs/long/*.x")

    parser = argparse.ArgumentParser()
    parser.add_argument("inputs", nargs="*", default=all_inputs)
    parser = parser.parse_args()

    results = []

    for in_idx, i in enumerate(parser.inputs):
        if not os.path.exists(i):
            print(red + "ERROR -- input file (*.x) not found: " + i + normal)
            continue

        print(bold + "Testing: " + normal + i)

        for p_idx, params in enumerate(sweep):
            # run the simulator
            sim_out = run(i, params)

            # parse sim output
            sim_out = sim_out.split("\n")
            ipc = -1
            cycles = -1
            for line in sim_out:
                if line.startswith("Cycles:"):
                    cycles = int(line.split(":")[1].strip())
                elif line.startswith("IPC:"):
                    ipc = float(line.split(":")[1].strip())

            results.append(
                {
                    "input": i,
                    "block_size": params[0],
                    "icache_size": params[1],
                    "icache_ways": params[2],
                    "dcache_size": params[3],
                    "dcache_ways": params[4],
                    "cycles": cycles,
                    "ipc": ipc,
                }
            )

            print(
                f"T({in_idx+1}/{len(parser.inputs)}) P({p_idx+1}/{len(sweep)}) bs={params[0]}, [IC: {params[1]/1024}KB, {params[2]}W], [DC: {params[3]/1024}KB, {params[4]}W] [cyc={cycles},IPC={ipc}]"
            )

    print("DONE")
    return results


def run(i, params):
    global ref, sim

    simproc = subprocess.Popen(
        [sim, i],
        executable=sim,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

    cmds = b""
    cmdfile = os.path.splitext(i)[0] + ".cmd"
    if os.path.exists(cmdfile):
        cmds += open(cmdfile).read().encode("utf-8")

    # Send bench command followed by the cache parameters
    cmds += b"\nbench\n"
    param_str = f"{params[0]} {params[1]} {params[2]} {params[3]} {params[4]}\n"
    cmds += param_str.encode("utf-8")
    cmds += b"rdump\nquit\n"
    (s, s_err) = simproc.communicate(input=cmds)

    return filter_stats(s.decode("utf-8"))


def filter_stats(out):
    lines = out.split("\n")
    regex = re.compile(
        "^(HI:)|(LO:)|(R\d+:)|(PC:)|(Cycles:)|(Fetched\w+:)|(Retired\w+:)|(IPC:)|(Flushes:).*$"
    )
    out = []
    for l in lines:
        if regex.match(l):
            out.append(l)

    return "\n".join(out)


def gen_param_sweep():
    block_sizes = [8, 32, 64]
    cache_sizes = [1024 * (2**exp) for exp in range(0, 7)]  # 1KB to 2^xKB
    ways = [1, 2, 4, 8, 16]

    possible_params = []
    for cache_sz in cache_sizes:
        for way in ways:
            possible_params.append((cache_sz, way))

    sweep = []
    for bs in block_sizes:
        for icache in range(len(possible_params)):
            for dcache in range(len(possible_params)):
                sweep.append(
                    (
                        bs,  # block size
                        possible_params[icache][0],  # icache_size
                        possible_params[icache][1],  # icache_ways
                        possible_params[dcache][0],  # dcache_size
                        possible_params[dcache][1],  # dcache_ways
                    )
                )
    return sweep


def save_results(results):
    output_file = "OUT.csv"
    with open(output_file, "w", newline="") as csvfile:
        fieldnames = results[0].keys()
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(results)

    print(green + f"Results saved to {output_file}" + normal)


if __name__ == "__main__":
    sweep = gen_param_sweep()

    results = main(sweep)

    if results:
        save_results(results)
