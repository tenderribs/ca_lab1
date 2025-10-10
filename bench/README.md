Step 1: Compile the sim with different replacement policies
```sh
# select different flag in src/cache.h
make sim
```
Then save the executables as sim_lru, sim_rand, sim_rrip respectively in the workspace root folder. Make sure only one policy flag is uncommented at one time.

Step 2:

Run the benchmarking python script in the workspace root directory. Can change the input file globstring and select policies to test. Will output a CSV file with params and corresponding results. The custom folder in inputs contains selected tests designed to trigger different types of cache misses.

```sh
python3 bench/bench.py
```

Plot stuff with 

```sh
python3 bench/stats.py
```