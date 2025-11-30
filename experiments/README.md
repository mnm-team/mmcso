## Experiment Design for mmcso

### 1. Experimental Setup
- Hardware Platforms:
    + SuperMUC-NG (SNG):
        + Dual-socket (NUMA), 24 cores per socket, 48 cores in total
        + Interconnect: Intel Omni-Path
    + HAWK in Stuttgart
        + AMD EPYC 7742 (https://en.wikichip.org/wiki/amd/epyc/7742)
          + 64-Core Processor, 2 Sockets, 128 Cores total
          + 8 NUMA domains configured (NPS4 mode) (chiplet design, 16 Cores per Chiplet, 4 Sub-NUMA domains per Socket (CCD))
          + Private L1D and L2 caches
          + Shared L3 cache per 4 Cores (CCX), 2x CCX forms one CCD
        + Interconnect: Dual Rail InfiniBand HDR200
        + MPI: HPE MPT 2.30
        + Compiler: GCC 12.3.0
    + CoolMUC ?

- Software Stack:
    + MPI (e.g., Intel MPI, Open MPI)
    + Compiler versions, thread libraries (i.e., OpenMP)
    + libmmc.so integration mode (LD_PRELOAD)

- Benchmarks and Applications:
    + Synthetic microbenchmarks for P2P inter-node communiation, and adjustable workloads
    + Realistic application: Cardiac Electrophysiology Simulation

### 1. Inter-Node Communication Performance
- Intra-Communication: NUMA 0 <-> NUMA 1 (same node)
- Inter-Communication: NUMA 0 (node A) <-> NUMA 0 (node B), and NUMA 1 (node A) <-> NUMA 1 (node B)
- Goal: Assess baseline communication performance and how libmmc.so handles thread-aware traffic across NUMA and node boundaries.
- Experiment Detail:
    + For workload 0 100 10000 1000000
        + For varied message sizes (small, medium, large)
    + 2 figures: one with intel mpi on intel node; one with cray mpi on amd node (Line charts with message size on X, overhead/overlap_percentage on Y).
- Discussion:
    + Highlight how libmmc.so affects contention on intra-node communication
    + How offloading performs across networked nodes under NUMA isolation

### 2. OSU Latency (MT) v7.5
- Standart benchmark for (multithreaded) latency
- Hawk: 1-2 nodes, compare offload vs. default

### 3. Strong and Weak Scaling: SpecHPC 2021 HPGMG-FV benchmark
- Goal: Demonstrate end-to-end benefits in realistic workloads using MPI_THREAD_MULTIPLE vs. MPI_THREAD_FUNNELED
- Problem sizes: tiny, small, medium, large
- Compare MPI_THREAD_FUNNELED vs. MPI_THREAD_MULTIPLE + offload vs. default
- Nodes on Hawk: 1-128, 4-512, 4-512, 128-512
- Configurations on Hawk: 1 MPI proc per socket (conf1), 2 MPI proc per socket (conf2), 4 MPI proc per socket (== 1 MPI proc per sub-NUMA domain) (conf3)
