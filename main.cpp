#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>
// This block enables compilation of the code with and without LIKWID in place
#ifdef LIKWID_PERFMON
#include <likwid-marker.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif

#define N 100000

int main(int argc, char* argv[])
{
    int i;
    double data[N];
    LIKWID_MARKER_INIT;
#pragma omp parallel
{
    LIKWID_MARKER_REGISTER("foo");
}
#pragma omp parallel 
{
    #pragma omp single
    {
        std::cout << "thread count: " << omp_get_num_threads()  << std::endl;
    }
    #pragma omp critical
    {
        std::cout << "thread num: " << omp_get_thread_num() << std::endl;
    }
    
    LIKWID_MARKER_START("foo");
    #pragma omp for
    for(i = 0; i < N; i++)
    {
        for(int j = 0; j < N; ++j)
        {
            data[j] = omp_get_thread_num();
        }
    }
    LIKWID_MARKER_STOP("foo");
}
    LIKWID_MARKER_CLOSE;
    return 0;
}