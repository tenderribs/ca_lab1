#!/usr/bin/python3

# Chris Fallin, 2012
# Yoongu Kim, 2013
# Juan Gomez Luna, 2017
# Minesh Patel, 2020

import sys, os, subprocess, re, glob, argparse, csv
import multiprocessing as mp

# sim = "./sim_lru"

bold = "\033[1m"
green = "\033[0;32m"
red = "\033[0;31m"
normal = "\033[0m"


test_files = "inputs/custom/*.x"
rep_policies = ["lru", "rand", "rrip"]


def main(sweep):
    all_inputs = glob.glob(test_files)

    parser = argparse.ArgumentParser()
    parser.add_argument("inputs", nargs="*", default=all_inputs)
    parser = parser.parse_args()

    # Create a list of all tasks to run in parallel
    tasks = []
    for in_idx, i in enumerate(parser.inputs):
        if not os.path.exists(i):
            print(red + "ERROR -- input file (*.x) not found: " + i + normal)
            continue

        print(bold + "Testing: " + normal + i)

        for p_idx, params in enumerate(sweep):
            for policy in rep_policies:
                # Store all needed data for this job
                task = (i, policy, params, in_idx, p_idx)
                tasks.append(task)

    # Create process pool and run all tasks
    results = []
    with mp.Pool(processes=os.cpu_count()) as pool:
        # Use pool.imap to process results as they complete
        for result in pool.imap_unordered(process_task, tasks):
            results.append(result)
            # Print progress information from the completed task
            print(
                f"T({result['in_idx']+1}/{len(parser.inputs)}) P({result['p_idx']+1}/{len(sweep)})\t"
                f"p={result['policy']}\t"
                f"[IC: bs={result['icache_blsz']} {result['icache_cap']/1024}KB, {result['icache_ways']}W]\t"
                f"[DC: bs={result['dcache_blsz']} {result['dcache_cap']/1024}KB, {result['dcache_ways']}W]\t"
                f"[cyc={result['cycles']},IPC={result['ipc']}]"
            )

    print("DONE")
    return results


def process_task(task_data):
    """Worker function that processes a single simulation task"""
    i, policy, params, in_idx, p_idx = task_data

    # Run the simulation
    sim_out = run(i, f"./sim_{policy}", params)

    # Parse sim output
    sim_out = sim_out.split("\n")
    ipc = -1
    cycles = -1
    for line in sim_out:
        if line.startswith("Cycles:"):
            cycles = int(line.split(":")[1].strip())
        elif line.startswith("IPC:"):
            ipc = float(line.split(":")[1].strip())

    # Return a dictionary with all the results and metadata
    return {
        "input": i,
        "policy": policy,
        "icache_cap": params[0],
        "icache_ways": params[1],
        "icache_blsz": params[2],
        "dcache_cap": params[3],
        "dcache_ways": params[4],
        "dcache_blsz": params[4],
        "cycles": cycles,
        "ipc": ipc,
        "in_idx": in_idx,
        "p_idx": p_idx,
    }


def run(i, exec, params):
    simproc = subprocess.Popen(
        [exec, i],
        executable=exec,
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
    param_str = (
        f"{params[0]} {params[1]} {params[2]} {params[3]} {params[4]} {params[5]}\n"
    )
    cmds += param_str.encode("utf-8")
    cmds += b"rdump\nquit\n"
    (s, s_err) = simproc.communicate(input=cmds)

    # Check return code
    if simproc.returncode != 0:
        print(
            red
            + f"[ERROR] Simulator crashed with return code {simproc.returncode}"
            + normal
        )
        return ""

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
    block_sizes = [16, 32, 64, 128, 256, 512]
    cache_sizes = [1024 * (2**exp) for exp in range(1, 10 + 1, 1)]  # 1KB to 1MB
    ways = [1, 2, 4, 8, 16]

    possible_params = []
    for bs in block_sizes:
        for cache_sz in cache_sizes:
            for way in ways:
                if cache_sz // way < bs:
                    continue  # set smaller than block size
                possible_params.append((cache_sz, way, bs))

    sweep = []
    for icache in range(len(possible_params)):
        for dcache in range(len(possible_params)):
            sweep.append(
                (
                    possible_params[icache][0],  # icache_cap
                    possible_params[icache][1],  # icache_ways
                    possible_params[icache][2],  # icache_blsz
                    possible_params[dcache][0],  # dcache_cap
                    possible_params[dcache][1],  # dcache_ways
                    possible_params[dcache][2],  # dcache_blsz
                )
            )
    return sweep


def save_results(results):
    outfile = f"{test_files}.csv".replace("/", "_")
    with open(f"bench/{outfile}", "w", newline="") as csvfile:
        fieldnames = [f for f in results[0].keys() if f not in ["in_idx", "p_idx"]]
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        # Filter out the temporary metadata fields before saving
        filtered_results = []
        for result in results:
            filtered = {k: v for k, v in result.items() if k in fieldnames}
            filtered_results.append(filtered)
        writer.writerows(filtered_results)

    print(green + f"Results saved to {outfile}" + normal)


if __name__ == "__main__":
    sweep = gen_param_sweep()
    results = main(sweep)
    if results:
        save_results(results)
