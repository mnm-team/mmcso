#!/bin/bash

cd $PBS_O_WORKDIR

export MMCSO_DISPLAY_AFFINITY=1
export LD_LIBRARY_PATH=$HOME/mmcso/build/lib:$LD_LIBRARY_PATH
export MPI_DSM_VERBOSE=1
#export MPI_DSM_CPULIST=0-127:0-127

for i in $(seq 126); do
	mpiexec_mpt -ppn 1 -n 2 dplace -s1 ./osu_latency_mt-default -t $i:$i > osu_latency_mt_2nodes-default/$i.txt
	mpiexec_mpt -ppn 1 -n 2 dplace -s1 ./osu_latency_mt-offload -t $i:$i > osu_latency_mt_2nodes-offload/$i.txt
done

