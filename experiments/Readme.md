## Experiment Design for mmcso

### 1. Experimental Setup
- Hardware Platforms:
    + SuperMUC-NG (SNG): 
        + Dual-socket (NUMA), 24 cores per socket, 48 cores in total
        + Interconnect: Intel Omni-Path
    + HAWK in Stuttgart
        + AMD EPYC node architecture, 8 NUMA domains???
        + Interconnect: ???

- Software Stack:
    + MPI (e.g., Intel MPI, Open MPI)
    + Compiler versions, thread libraries (i.e., OpenMP)
    + libmmc.so integration mode (LD_PRELOAD)

- Benchmarks and Applications:
    + Synthetic microbenchmarks for intra/inter communiation, and adjustable workloads
    + Realistic application: Cardiac Electrophysiology Simulation

### 2. Intra- and Inter-Node Communication Performance
- Intra-Communication: NUMA 0 <-> NUMA 1 (same node)
- Inter-Communication: UMA 0 (node A) <-> NUMA 0 (node B), and NUMA 1 (node A) <-> NUMA 1 (node B)
- Goal: Assess baseline communication performance and how libmmc.so handles thread-aware traffic across NUMA and node boundaries.
- Experiment Detail:
    + For workload 0 100 10000 1000000
        + For varied message sizes (small, medium, large)
    + 2 figures: one with intel mpi on intel node; one with cray mpi on amd node (Line charts with message size on X, overhead/overlap_percentage on Y). Subplots for intra-node vs inter-node
- Discussion:
    + Highlight how libmmc.so affects contention on intra-node communication
    + How offloading performs across networked nodes under NUMA isolation

### 3. Strong and Weak Scaling Across Nodes
- Strong and Weak Scaling Across Nodes: increase the number of processes
- Goal: Show that libmmc.so maintains scalability as we increase the number of processes across nodes (use max. threads as well as max. cores).
- Weak Scaling:
    + Increase total workload proportionally with compute resources
- Strong Scaling:
    Fixed total workload; increase the number of MPI processes
- Evaluattion results on SNG and HAWK

### 4. Use case: Realistic Application-Level Speedup
- Goal: Demonstrate end-to-end benefits in realistic workloads.
- Use case: Cardiac Electrophysiology Simulation