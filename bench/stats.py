# Loaded variable 'df' from URI: /Users/mark/git-repos/school-repos/ca_lab1/bench/._sim_lru_inputs_custom_pointer_chase.x.csv

import pandas as pd
df = pd.read_csv(r'/Users/mark/git-repos/school-repos/ca_lab1/bench/._sim_lru_inputs_custom_pointer_chase.x.csv')

# Filter rows based on column: 'input'
df = df[df['input'].str.contains("chase", regex=False, na=False, case=False)]

# Sort by columns: 'ipc' (descending), 'icache_cap' (ascending), 'dcache_cap' (ascending)
df = df.sort_values(['ipc', 'icache_cap', 'dcache_cap'], ascending=[False, True, True])

print(df)