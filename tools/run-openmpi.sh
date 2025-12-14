#!/bin/bash

export OMP_PROC_BIND=CLOSE OMP_PLACES=CORES OMP_DISPLAY_AFFINITY=TRUE
export COMMOFF_THREAD_CPU_ID=0:23,1:23,2:47,3:47
export OMP_DISPLAY_AFFINITY=true
export OMP_NUM_THREADS=23

PREFIX=openmpi

CSV_OFFLOAD=${PREFIX}/offload.csv
CSV_NATIVE=${PREFIX}/native.csv

CSV_HEADER=nthreads,thread,rep,work,msg_size,post_time,wait_time,comp_time,comm_time

echo ${CSV_HEADER} > ${CSV_OFFLOAD}
echo ${CSV_HEADER} > ${CSV_NATIVE}

for t in 2 12 23; do
        export OMP_NUM_THREADS=$t
	BENCH="mpiexec -display-map -x OMP_DISPLAY_AFFINITY=true -x OMP_NUM_THREADS=${t} -x OMP_PLACES=cores -n 4 --map-by node:PE=24 --bind-to core lib/mt_overlap"
	echo $BENCH
        for work in 0 100 10000 1000000; do
                for msg in 100 300 1000 3000; do
                        LD_PRELOAD=${PREFIX}/libmmc.so ${BENCH} -m ${msg} -w ${work} -f ${CSV_OFFLOAD} -r 1000
			${BENCH} -m ${msg} -w ${work} -f ${CSV_NATIVE} -r 1000
                done

                for msg in 10000 30000; do
                        LD_PRELOAD=${PREFIX}/libmmc.so ${BENCH} -m ${msg} -w ${work} -f ${CSV_OFFLOAD} -r 100
                        ${BENCH} -m ${msg} -w ${work} -f ${CSV_NATIVE} -r 100
                done

                for msg in 100000 300000 1000000 3000000 10000000; do
                        LD_PRELOAD=${PREFIX}/libmmc.so ${BENCH} -m ${msg} -w ${work} -f ${CSV_OFFLOAD} -r 10
                        ${BENCH} -m ${msg} -w ${work} -f ${CSV_NATIVE} -r 10
                done
        done
done
