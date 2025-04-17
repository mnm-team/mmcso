# this pins the offloading thread on rank 0 to cpu 7 and on rank 1 to cpu 15
export MMCSO_THREAD_AFFINITY=0:7,1:15
# export MMCSO_DISPLAY_AFFINITY=TRUE

BIN=build/bench/mt_overlap
#TIME="time -p"
#VALGRIND="valgrind --tool=massif"
PERF="perf stat"
# OUTER_TOOL="perf record -T -d -d -d" # perf report -D
# INNER_TOOL="perf stat -d -d -d" # -A -x
# OUTER_TOOL="perf stat -d --table -r 10" # -A -x
OUTER_TOOL="perf stat -d -r 10"

# DISPLAY_AFFINITY="-display-map -x OMP_DISPLAY_AFFINITY=true"

echo OpenMPI + offloading using 2 ranks and 3 threads on cpu 0-5 and cpu 8-13
export LD_PRELOAD=${LD_PRELOAD}:build/lib/libmmc.so
$OUTER_TOOL mpiexec $DISPLAY_AFFINITY -x OMP_NUM_THREADS=3 -x OMP_PLACES=cores -n 2 --map-by node:PE=4 --bind-to core \
   $TIME $INNER_TOOL $BIN -m 50000 -w 200000

echo OpenMPI w/o offloading using 2 ranks and 3 threads on cpu 0-5 and cpu 8-13
export LD_PRELOAD=
$OUTER_TOOL mpiexec $DISPLAY_AFFINITY -x OMP_NUM_THREADS=3 -x OMP_PLACES=cores -n 2 --map-by node:PE=4 --bind-to core \
   $TIME $INNER_TOOL $BIN -m 50000 -w 200000
