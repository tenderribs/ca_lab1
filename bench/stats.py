import pandas as pd

input_tests = [
    "pointer_chase",
    # "strided_access",
    "primes",
    "random1",
    "repmovs",
    "test1",
]

config_cols = [
    "policy",
    "icache_cap",
    "icache_ways",
    "icache_blsz",
    "dcache_cap",
    "dcache_ways",
    "dcache_blsz",
]


def find_best_ipc_for_test(df, test_name):
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
        ["ipc", "icache_cap", "dcache_cap"], ascending=[False, True, True]
    )

    # Get the best IPC value
    best_ipc = sorted_df["ipc"].iloc[0]

    # Get all configurations with this best IPC
    best_configs = sorted_df[sorted_df["ipc"] == best_ipc]

    # print(f"\n=== Best configurations for {test_name} (IPC = {best_ipc}) ===")
    # print(best_configs.head())

    return best_configs


def find_common_best_configs(df):
    """Find configurations that work well across all tests"""
    print(f"Checking {df.shape} configurations")
    # Get the best configurations for each test
    best_configs_by_test = {}
    for test in input_tests:
        best_configs = find_best_ipc_for_test(df, test)
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

        print(
            f"After merging with {test}, found {common_configs.shape[0]} common configurations"
        )

    print(f"\nFinal common best configurations across all tests:")
    print(common_configs)

    return common_configs


if __name__ == "__main__":
    csv_path = "bench/inputs_custom_*.x.csv"

    df = pd.read_csv(csv_path)

    # best configs are those that got the best IPC score on all tests
    best = find_common_best_configs(df)

    # find smallest caches that permit achieved best score
    best = best.sort_values(["icache_cap", "dcache_cap"], ascending=[True, True])
    print(best.head())

    best.to_csv("bench/best.csv")
