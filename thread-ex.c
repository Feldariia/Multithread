#include <stdio.h>	//for I/O
#include <stdlib.h>	//for exit()
#include <unistd.h>	
#include <pthread.h>	//multi-threading support

int X = 0;		//The (global) shared data


void *thread1()		// code for thread1
{
  printf("thread1: starting...\n");
  for (int i=0; i<1000; i++)
  {
	++X;
  }
  return 0;
}

void *thread2()		// code for thread2
{
  printf("thread2: starting...\n");
  for (int i=0; i<1000; i++)
  {
	++X;
  }
  return 0;
}
int main()
{
	pthread_t thr1, thr2;		//thread control blocks

	//Create thr1 and associate its code with the function thread1
	
	if (pthread_create(&thr1,NULL,&thread1,NULL) != 0)
	{
            fprintf(stderr,"pthread_create() failed for thread1\n");
	    exit(1);
	}

	
	//Create thr2 and associate its code with the function thread2()
	if (pthread_create(&thr2,NULL,&thread2,NULL) != 0)
	{
	   fprintf(stderr, "pthread_create() failed for thread2\n");
	   exit(1);
	}

	// Coordinate the process and threads so that thr1 and thr2
	// must complete before proceeding.
	pthread_join(thr1,NULL);				//process waits for thr1 to complete
	pthread_join(thr2,NULL);				//process waits for thr2 to complete

	//thr1 and thr2 have completed, we can safely report the
	//final result and end the program.
	printf("main: X is %i\n", X);
	return 0;
}
	