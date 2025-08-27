#!/bin/bash

benchmarks="534.hpgmgfv_t 634.hpgmgfv_s 734.hpgmgfv_m"

for b in $benchmarks; do
	runhpc -c sng-funneled --define model=omp --define label=sng-funneled --action=build $b
	runhpc -c sng-multiple --define model=omp --define label=sng-multiple --action=build $b
done


