make clean && make TRANSFER=SERIAL && mv bin/host_code host_code_serial
make clean && make TRANSFER=BROADCAST && mv bin/host_code host_code_broadcast
make clean && make TRANSFER=PARALLEL && mv bin/host_code host_code_parallel