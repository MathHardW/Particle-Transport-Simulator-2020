#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int numThreads, tid;

#pragma omp parallel private(numThreads, tid)
 {
   tid = omp_get_thread_num();
   printf("Hello World from thread number %d\n", tid);

	   if (tid == 0)
     {
       numThreads = omp_get_num_threads();
       printf("Number of threads is %d\n", numThreads);
     }
 }
 return 0;
}


