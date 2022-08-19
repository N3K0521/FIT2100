#include <stdio.h>      /* standard I/O routines */
#include <pthread.h>    /* pthread functions and data structures */
#include <unistd.h>     /* we will use sleep() later on in prac */
#include <stdlib.h>     /* needed for exit() function */

int sum; //global integer varaible sum

/* This function is to be executed by the new thread */
void* print_hello(void* data){
	int t = *(int *)data; /* data received by thread */
	sum += t; //increment the sum global varaible by t
	
	printf("Hello from thread (%ld) - I was created in iteration %ld. Current sum: %d\n", pthread_self(), t, sum);
	
	pthread_exit(NULL); /* terminate the thread */
}

int main(int argc, char* argv[]){
	int rc; /* value returned from thread creation */
	pthread_t thread_id; /* thread's ID (a long unsigned integer)*/
	int t; /* data passed to the new thread */
	int x; //takes in an integer value x as an argument from the command line
	
	//argc == 2 when the program is run with one command-line argument
	if (argc != 2){
		printf("Error: please enter one command line argument for x\n");
		return -1;
	}
	
	x = atoi(argv[1]);
	
	for (int i = 0; i < x; i++){
		t = i + 1;
		/* create a new thread that will execute 'print_hello()' */
  		rc = pthread_create(&thread_id, NULL, print_hello, &t);
		
		if(rc) {    /* could not create thread */
    		printf("\n ERROR: return code from pthread_create is %d \n", rc);
    		exit(1);
  		}
		else{
			printf("I am thread %lu, Created new thread (%lu) in iteration %ld. Current sum: %d\n", pthread_self(), thread_id, t, sum);
		}
		
		if ((i > 0) && (i % 4 == 0))
			sleep(1);
			
	}
	pthread_exit(NULL);     /* terminate the thread */
}
