#!/bin/bash
#SBATCH -J test_offload_runhpc_spec2021
#SBATCH -o ./output/test/%x.%j.out
#SBATCH -e ./output/test/%x.%j.err
#SBATCH -D ./
#SBATCH --time=00:30:00
#SBATCH --no-requeue
#SBATCH --get-user-env
#SBATCH --account=pn76bu
#SBATCH --partition=test
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2

# load spec env
# source /dss/dsshome1/0C/di35hef/mmcso/experiments/spechpc2021hpgmgfv/hpc2021-1.1.8/shrc

# specify base dirs
MMCSO_DIR=/dss/dsshome1/0C/di35hef/mmcso/build_impi/lib
MMCSO_LIB=$MMCSO_DIR/libmmc.so
BASEDIR="/dss/dsshome1/0C/di35hef/mmcso/experiments/spechpc2021hpgmgfv/hpc2021-1.1.8/benchspec/HPC"

# export mmcso lib to LD env
export LD_LIBRARY_PATH=$MMCSO_DIR:$LD_LIBRARY_PATH

export MMCSO_DISPLAY_AFFINITY=TRUE

set_mmcso_thread_affinity()
{
    # echo Placing MMCSO Threads in $1 MPI processes on each $2th Core 
    # of each Node with $3 Cores per Node 2>&1
    a=$(for i in $(seq 0 $(($1 - 1))); do echo $i:$(( ((($i+1)*$2) - 1) % $3 )); done)
    export MMCSO_THREAD_AFFINITY=$(echo $a | sed -e 's/\s\+/,/g')
    echo $MMCSO_THREAD_AFFINITY
}

# input: number of nodes, config, offloading
set_config()
{
    case $2 in
        1)
            NPROCS=$(($1 * 2))
            if [[ $3 == "1" ]]; then
                set_mmcso_thread_affinity $(($1 * 2)) 24 48
		export OMP_NUM_THREADS=23
		export LD_PRELOAD=$MMCSO_LIB
                MPIEXEC="mpiexec -ppn 2 -np $NPROCS "
            else
		export OMP_NUM_THREADS=24
                MPIEXEC="mpiexec -ppn 2 -np $NPROCS "
            fi
            ;;

        2)
            NPROCS=$(($1 * 4))
            if [[ $3 == "1" ]]; then
                set_mmcso_thread_affinity $(($1 * 4)) 32 128
                MPIEXEC="mpiexec_mpt -ppn 4 -np $NPROCS omplace -nt 31 -c 0-30,32-62,64-94,96-126"
            else
                MPIEXEC="mpiexec_mpt -ppn 4 -np $NPROCS omplace -nt 32 -c 0-31,32-63,64-95,96-127"
            fi
            ;;

        3)
            NPROCS=$(($1 * 8))
            if [[ $3 == "1" ]]; then
                set_mmcso_thread_affinity $(($1 * 8)) 16 128
                MPIEXEC="mpiexec_mpt -ppn 8 -np $NPROCS omplace -nt 15 -c 0-14,16-30,32-46,48-62,64-78,80-94,96-110,112-126"
            else
                MPIEXEC="mpiexec_mpt -ppn 8 -np $NPROCS omplace -nt 16 -c 0-15,16-31,32-47,48-63,64-79,80-95,96-111,112-127"
            fi
            ;;

        *)
            echo -n "Unknown or unsupported config!"
            ;;
    esac

}

# for testing the execution of the benchmark
BENCH="534.hpgmgfv_t"
NNODES=1
c=1
v=sng-funneled_omp
set_config $NNODES $c 1

echo "Check BASEDIR: $BASEDIR"
echo "Check BENCH: $BENCH"

ARGS=$(cat $BASEDIR/$BENCH/funneled.args.txt | xargs)
EXE="$BASEDIR/$BENCH/exe/hpgmgfv_base.$v"

echo "Check MPIEXEC: $MPIEXEC"
echo "Check EXE: $EXE"
echo "Check ARGS: $ARGS"

if ! test -f ./results/test/spectimes-test-$BENCH-$v-offload-nodes-$NNODES-conf-$c.txt; then
	$MPIEXEC ${EXE} ${ARGS}
	mv spectimes.txt ./results/test/spectimes-test-$BENCH-$v-offload-nodes-$NNODES-conf-$c.txt
fi
