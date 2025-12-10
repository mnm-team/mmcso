#!/bin/bash

python3 hawk/plot_speedup_hawk.py
mv hawk/speedup_microbench_hawk.pdf .

python3 sng/plot_speedup_sng.py
mv sng/speedup_microbench_sng.pdf .

python3 plot_overhead_hawk_sng.py

