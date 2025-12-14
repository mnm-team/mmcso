#!/bin/bash

set_mmcso_thread_affinity()
{
	echo Placing MMCSO Offload Threads in $1 MPI processes on each $2th Core of each Node with total $3 Cores
	a=$(for i in $(seq 0 $(($1 - 1))); do echo $i:$(( ((($i+1)*$2) - 1) % $3 )); done)
	export MMCSO_THREAD_AFFINITY=$(echo $a | sed -e 's/\s\+/,/g')
}

# exports a string that defines the thread affinity of the offload thread

# number of processes, core stride, cores per node
set_mmcso_thread_affinity $1 $2 $3
