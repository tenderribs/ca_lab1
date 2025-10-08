import pandas as pd
import matplotlib.pyplot as plt

csv_path = "bench/inputs_custom_*.x.csv"

config_cols = [
    "policy",
    "icache_cap",
    "icache_ways",
    "icache_blsz",
    "dcache_cap",
    "dcache_ways",
    "dcache_blsz",
]


def find_best_for_test(df, test_name):
    """Find the best IPC configurations for a specific test"""
    # Filter rows based on column: 'input'
    filtered_df = df[
        df["input"].str.contains(test_name, regex=False, na=False, case=False)
    ]

    if filtered_df.empty:
        print(f"No data found for test: {test_name}")
        return None

    # Sort by columns: 'ipc' (descending), 'icache_cap' (ascending), 'dcache_cap' (ascending)
    sorted_df = filtered_df.sort_values(
        ["cycles", "icache_cap", "dcache_cap"], ascending=[True, True, True]
    )

    # Get the least cycles value
    least_cycles = sorted_df["cycles"].iloc[0]

    # Get all configurations with least cycles
    best_configs = sorted_df[sorted_df["cycles"] == least_cycles]

    # print(f"\n=== Best configurations for {test_name} (IPC = {least_cycles}) ===")
    # print(best_configs.head())
    return best_configs


def find_common_best_configs(df, input_tests):
    """Find configurations that work well across all tests"""
    print(f"Checking {df.shape} configurations")
    # Get the best configurations for each test
    best_configs_by_test = {}
    for test in input_tests:
        best_configs = find_best_for_test(df, test)
        if best_configs is not None:
            best_configs_by_test[test] = best_configs

    # Start with the best configs from the first test
    first_test = list(best_configs_by_test.keys())[0]
    common_configs = best_configs_by_test[first_test][config_cols].drop_duplicates()

    # Merge with best configs from each subsequent test
    for test, configs in best_configs_by_test.items():
        common_configs = pd.merge(
            common_configs,
            configs[config_cols].drop_duplicates(),
            how="inner",
            on=config_cols,
        )

    return common_configs


# find the parameter set that achieves the max score on all benchmarks
def best_overall():
    input_tests = [
        "pointer_chase",
        "strided_access",
        "primes",
        "random1",
        "repmovs",
        "test1",
    ]

    df = pd.read_csv(csv_path)

    # best configs are those that got the best IPC score on all tests
    best = find_common_best_configs(df, input_tests)

    # find smallest caches that permit achieved best score
    # sort by what is most interesting
    best = best.sort_values(
        ["icache_cap", "dcache_cap", "dcache_blsz", "policy"],
        ascending=[True, True, False, False],
    )

    best.to_csv("bench/best_overall.csv", index=False)


def best_strided():
    # disinclude the stride test because this favours impractically large data caches + block sizes
    input_tests = [
        "pointer_chase",
        # "strided_access",
        "primes",
        "random1",
        "repmovs",
        "test1",
    ]

    # find best performing configs on tests excluding the strided access
    df = pd.read_csv(csv_path)

    best = find_common_best_configs(df, input_tests)
    best = best.sort_values(
        ["icache_cap", "dcache_cap", "dcache_blsz", "policy"],
        ascending=[True, True, False, False],
    )

    # for these best configs, look for the least cycles used within the pointer_chase results
    pc_results = df[df["input"] == "inputs/custom/strided_access.x"]
    best_sa_res = pd.merge(pc_results, best, how="right", on=config_cols)
    best_sa_res = best_sa_res.sort_values(
        ["cycles", "icache_cap", "dcache_cap", "dcache_blsz", "policy"],
        ascending=[True, True, True, False, False],
    )
    best_sa_res.to_csv("bench/best_strided.csv", index=False)


def best_practical():
    # disinclude the stride test because this favours impractically large data caches + block sizes
    input_tests = [
        "pointer_chase",
        "strided_access",
        "primes",
        "random1",
        "repmovs",
        "test1",
    ]

    df = pd.read_csv(csv_path)

    # L1 caches over 64KB very expensive IRL, so only search within this space
    df = df[df["dcache_cap"] <= 64 * 1024]
    df = df[df["icache_cap"] <= 64 * 1024]

    # additionally restrict
    df = df[df["icache_blsz"] <= 64]
    df = df[df["dcache_blsz"] <= 64]
    best = find_common_best_configs(df, input_tests)
    best = best.sort_values(
        ["icache_cap", "dcache_cap", "dcache_blsz", "policy"],
        ascending=[True, True, False, False],
    )

    best.to_csv("bench/best_practical.csv", index=False)


# Effect of Cache Size on Performance (LRU, 32B blocks)
def analyze_cache_size_effect():
    print("\n\n\n============ analyze_cache_size_effect ============")
    df = df = pd.read_csv(csv_path)

    # Filter for baseline configuration
    df = df[
        (df["policy"] == "lru")
        & (df["icache_ways"] == 4)
        & (df["dcache_ways"] == 8)
        & (df["icache_blsz"] == 32)
        & (df["dcache_blsz"] == 32)
    ]

    # here everything has same results, so just show random25k
    icache_test = "inputs/custom/looped_random_1k.x"

    # tests with interesting results, all others are equal
    dcache_tests = [
        "inputs/custom/strided_access.x",
        "inputs/custom/primes.x",
    ]

    # Instruction cache size effect with 64KB dcache
    test_data = df[(df["input"] == icache_test) & (df["dcache_cap"] == 64 * 1024)]
    test_data = test_data.sort_values(by=["icache_cap"])
    print(f"\ninst cache {icache_test}")
    print(test_data)

    # Data cache size effect
    for idx, test in enumerate(dcache_tests):
        # with 2KB icache
        test_data = df[(df["input"] == test) & (df["icache_cap"] == 2 * 1024)]
        print(f"\ndata cache {test}")
        print(test_data)
    return


# Effect of Block Size on Performance (LRU, 32B blocks)
def analyze_block_size_effect():
    print("\n\n\n============ analyze_block_size_effect ============")
    df = df = pd.read_csv(csv_path)

    # Filter for baseline configuration
    df = df[
        (df["policy"] == "lru")
        & (df["icache_ways"] == 4)
        & (df["dcache_ways"] == 8)
        & (df["icache_cap"] == 2 * 1024)
        & (df["dcache_cap"] == 64 * 1024)
    ]

    # all tests are interesting here
    tests = df["input"].unique()

    for idx, test in enumerate(tests):
        test_data = df[(df["input"] == test)]
        print(f"\ninst cache {test}")
        print(test_data)


# Effect of Block Size on Performance (LRU, 32B blocks)
def analyze_associativity_effect():
    print("\n\n\n============ analyze_associativity_effect ============")
    df = df = pd.read_csv(csv_path)

    # Filter for baseline configuration
    df = df[
        (df["policy"] == "lru")
        & (df["icache_blsz"] == 64)
        & (df["dcache_blsz"] == 64)
        & (df["icache_cap"] == 2 * 1024)
        & (df["dcache_cap"] == 64 * 1024)
    ]

    # all tests are interesting here
    tests = df["input"].unique()

    for idx, test in enumerate(tests):
        test_data = df[(df["input"] == test)]
        print(f"\ninst cache {test}")
        print(test_data)


if __name__ == "__main__":
    # best_overall()
    # best_strided()
    # best_practical()
    analyze_cache_size_effect()
    analyze_block_size_effect()
    analyze_associativity_effect()
