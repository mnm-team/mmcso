#!/bin/bash

# The Tiny suite is intended to target a single or few nodes using between 1 and 256 ranks. It uses a maximum of 60GB of memory per benchmark.

# The Small suite is intended to target a single larger node or a small cluster of nodes using between 64 and 1024 ranks. It uses a maximum of 480GB of memory per benchmark.
# (4-1024 nodes)

# The Medium suite is intended to target a mid-sized cluster of nodes using between 256 and 4096 ranks. It uses a maximum of 4TB of memory per benchmark.
# (16-1024 nodes)

# The Larger suite is intended to target a larger cluster of nodes using between 2048 and 32,768 ranks. It uses a maximum of 14.5TB of memory per benchmark.
# (128-1024 nodes)

# qsub -N $JOBNAME -o $JOBNAME.stdout -e $JOBNAME.stderr -v BENCH=$BENCH -l select=$NNODES:node_type=rome:ncpus=128 -l walltime=00:01:00 test-nodes.pbs

# Tiny: (1-1024 nodes), basetime 6 minutes

# BENCH, BASETIME, istart iend
submit_jobs()
{
	BENCH=$1
	BASETIME=$2

	for n in $(seq $3 $4); do
		NNODES=$((2 ** $n))
		JOBNAME=$BENCH-nodes-$NNODES
		WTIME=$(($BASETIME / $NNODES))
		if [ "$WTIME" -lt "10" ]; then
			WTIME="10"
		fi
		#qsub -N $JOBNAME -o $JOBNAME.stdout -e $JOBNAME.stderr -v BENCH=$BENCH -l select=$NNODES:node_type=rome:ncpus=128 -l walltime=$(date -d@$((60*$WTIME)) -u +%H:%M:%S) -q test hpgmgfv.pbs
		qsub -N $JOBNAME -o $JOBNAME.stdout -e $JOBNAME.stderr -v BENCH=$BENCH -l select=$NNODES:node_type=rome:ncpus=128 -l walltime=00:25:00 -q test hpgmgfv.pbs
		sleep 1
	done
}

#submit_jobs 534.hpgmgfv_t $((2 * 6 * 12)) 5 5 # 1-128 nodes
submit_jobs 634.hpgmgfv_s $((4 * 4 * 2 * 6 * 12)) 5 5 # 4-512 nodes
#submit_jobs 734.hpgmgfv_m $((4 * 16 * 2 * 6 * 12)) 4 10 # 16-1024 nodes
#submit_jobs 834.hpgmgfv_l $((16 * 16 * 2 * 6 * 12)) 7 7 # 128-1024 nodes

