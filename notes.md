How does HW Thread relate to logical cores? ChatGPT says that they are the same thing. "top-1" also suggests that this is the case since when HW Threads are all even numbered, even numbered logical cores are busy.
One thing that boggles my mind is that I cannot set cpuset larger than 28 threads since likwid API says that I have 28 HW Threads in total, so I cannot use more than 28 HW Threads. However, my server has 56 cores, meanng that it should accommodate 56 threads with hyperthreading disabled.

# How to build

```
g++ -DLIKWID_PERFMON main.cpp -fopenmp -llikwid
```

If you omit ```LIKWID_PERFMON```, the Marker API calls resolve to an empty string causing no overhead.

# How to run

```
likwid-perfctr -C S0:0-27 -g L3 -m ./a.out
```

This command invokes likwid-perfctr to invoke our executable and run it in parallel across 28 threads.

# Available event groups (performance groups)

```
[root@du01 likwid_demo]# likwid-perfctr -a
    Group name  Description
--------------------------------------------------------------------------------
        BRANCH  Branch prediction miss rate/ratio
        CACHES  Cache bandwidth in MBytes/s
         CLOCK  Power and Energy consumption
CYCLE_ACTIVITY  Cycle Activities
  CYCLE_STALLS  Cycle Activities (Stalls)
          DATA  Load to store ratio
        DIVIDE  Divide unit information
        ENERGY  Power and Energy consumption
     FLOPS_AVX  Packed AVX MFLOP/s
      FLOPS_DP  Double Precision MFLOP/s
      FLOPS_SP  Single Precision MFLOP/s
            L2  L2 cache bandwidth in MBytes/s
       L2CACHE  L2 cache miss rate/ratio
            L3  L3 cache bandwidth in MBytes/s
       L3CACHE  L3 cache miss rate/ratio
           MEM  Main memory bandwidth in MBytes/s
        MEM_DP  Overview of arithmetic and main memory performance
        MEM_SP  Overview of arithmetic and main memory performance
           PMM  Intel Optane DC bandwidth in MBytes/s
      TLB_DATA  L2 data TLB miss rate/ratio
     TLB_INSTR  L1 Instruction TLB miss rate/ratio
           TMA  Top down cycle allocation
     UOPS_EXEC  UOPs execution
    UOPS_ISSUE  UOPs issueing
   UOPS_RETIRE  UOPs retirement
           UPI  UPI data traffic
```