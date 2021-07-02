#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"
#include <sys/resource.h>


int x[5] = {1,2,3,4,5};

float UserTime(struct rusage *start, struct rusage *end)
{
  return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) + 1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}
float SystemTime(struct rusage *start, struct rusage *end)
{
  return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) + 1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}

void allocate()
{
    int i;
    int *p;
    for(i =1 ; i<1000000 ; i++)
    {
      p = malloc(500 * sizeof(int));
      if(func(i)) { free (p);}
    }
}

void allocate1()
{
  int i;
  int *p;
  for (i=1 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    if(i & 1)
      free (p);
  }
}

void allocate2()
{
  int i;
  int *p;
  for (i=1 ; i<300000 ; i++)
  {
    p = malloc(10000 * sizeof(int));
    free (p);
  }
}


int main(int argc, char const *argv[]) {
  struct rusage start, end;
  int i;

  int *p;
  printf("Executing the code ......\n");
  getrusage(RUSAGE_SELF, &start);
  allocate();

  for (i=0 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    free (p);
  }
  getrusage(RUSAGE_SELF,&end);
  printf("Program execution successfull\n");
  printf("CPU TIME: %.06f seconds user, %.06f seconds system\n",UserTime(&start,&end),SystemTime(&start, &end));

  return 0;
}

/*REFERENCE: https://www.delftstack.com/howto/c/getrusage-example-in-c/ */

