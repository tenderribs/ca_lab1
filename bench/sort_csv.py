import pandas as pd

df = pd.read_csv("bench/inputs_custom_*.x.csv")
df = df.sort_values(["input", "icache_cap", "dcache_cap"], ascending=[True, True, True])
df.to_csv("bench/sorted_inputs_custom_*.x.csv", index=False)
