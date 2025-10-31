# build programs first with build.sh

OUTFILE = "task2_out.csv"

import subprocess as sp
import re
import csv
import os

def gen_params():
    params = []




    # inp_sizes = [24, 48]  # in MB
    # dpu_cnts = [8]
    # tasklets_cnts = [1] + [i + 4 for i in range(0, 24, 4)]
    # dtypes = ["INT32", "INT64", "FLOAT", "DOUBLE", "CHAR", "SHORT"]

    inp_sizes = [24]  # in MB
    dpu_cnts = [32]
    tasklets_cnts = [i + 1 for i in range(0, 24, 1)]
    dtypes = ["INT32"]

    for inp_size in inp_sizes:
        for n_dpus in dpu_cnts:
            for dtype in dtypes:
                for n_tasklets in tasklets_cnts:
                    params.append(
                        {
                            "inp_size": inp_size,
                            "n_dpus": n_dpus,
                            "dtype": dtype,
                            "n_tsklts": n_tasklets,
                        }
                    )
    return params


def run(params_list):
    results = []

    for idx, p in enumerate(params_list):
        print(f"[{idx+1}/{len(params_list)}] {p}")

        # Run the program with specified parameters
        env = {
            **os.environ,
            "NR_DPUS": str(p["n_dpus"]),
            "NR_TASKLETS": str(p["n_tsklts"]),
            "BLOCK": "8",
            "TYPE": p["dtype"],
            "TRANSFER": "PARALLEL",
            "PERF": "INSTRUCTIONS",
        }
        sp.run(["make", "clean"], check=True, capture_output=True, text=True, timeout=120)
        sp.run(["make"], env=env, check=True, capture_output=True, text=True, timeout=120)
        result = sp.run(
            ["./bin/host_code", "-w", "2", "-e", "10", "-i", str(p["inp_size"] * 131072), "-a", "20"],
            capture_output=True, text=True, timeout=120
        )
        stdout = result.stdout

        assert "Outputs are equal" in stdout

        cpu_dpu_match = re.search(r"CPU-DPU Time \(ms\):\s+([\d.]+)", stdout)
        dpu_cpu_match = re.search(r"DPU-CPU Time \(ms\):\s+([\d.]+)", stdout)
        dpu_kernel_match = re.search(r"DPU Kernel Time \(ms\):\s+([\d.]+)", stdout)
        dpu_inst_match = re.search(r"DPU instructions\s*=\s*([0-9.+-eE]+)", stdout)

        assert cpu_dpu_match and dpu_cpu_match and dpu_kernel_match and dpu_inst_match

        perf = {
            "cpu_dpu": float(cpu_dpu_match.group(1)),
            "dpu_cpu": float(dpu_cpu_match.group(1)),
            "dpu_kernel_time": float(dpu_kernel_match.group(1)),
            "dpu_instr_cnt": float(dpu_inst_match.group(1)),
        }
        results.append({**perf, **p})

    return results


if __name__ == "__main__":
    results = run(gen_params())
    print("DONE")

    # save results to disk
    if results:
        with open(OUTFILE, "w", newline="") as f:
            writer = csv.DictWriter(f, fieldnames=results[0].keys())
            writer.writeheader()
            writer.writerows(results)
