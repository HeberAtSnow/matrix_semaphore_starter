//Starter code from Heber for the 1st part of the MATRIX assignment
//Your requirement is to fix all TODO: blocks so they 'do' what is assigned
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#define MyCols 10 
char volatile line[MyCols+1];
//semaphore strctures to SIGNAL the THREAD to get a symbol
sem_t tgo[MyCols];
//semaphore structures to SIGNAL back to MAIN that the thread has gotten it's symbol
sem_t tdone[MyCols];
char validSymbols[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+={}[]?/>.<,";

typedef struct{
	int id;
} myArgs_t;
myArgs_t Tids[MyCols];


void * myThread (void * arg){
	myArgs_t * data = (myArgs_t*) arg;
	int id = data->id; //set ID from passed in arg struct
	printf("Thread %d STARTED\n",id); fflush(stdout);
	int offset=0;
	while(1){
		//TODO:
		//WAIT HERE for a SEMAPHORE signal that your 'Thread' can go
		//TODO:    hint:  &tgo[id] would be the address where this Thread's semaphore is stored at

		line[id]=validSymbols[offset];
		if(offset<strlen(validSymbols)) offset++; else offset=0; //don't go past length!

		//TODO:
		//SEND the SIGNAL to MAIN that you have gotten your character put on 'line'
		//TODO:    hint:  &tdone[id] is the address where MAIN is expecting the semaphore to be stored at

	}//loop to process every SIGNAL I receive
}
void main (){
//Initialize
	pthread_t pThreads[MyCols];
	memset((char*)line,'-',sizeof((char*)line)); line[MyCols]=0;
	for(int i=0;i<MyCols;i++){
		sem_init(&tgo[i],0,0);
		sem_init(&tdone[i],0,0);
		Tids[i].id=i; //init the thread numbers 0-MyCols
	}
//Start Threads
	for(int i=0;i<MyCols;i++){
		//start threads, and if any fail, bomb the program
		assert( pthread_create((pthread_t*)&pThreads[i], NULL, myThread, &Tids[i]) == 0);
	}
//Loop
	for(int z=0;z<100;z++){
		//WAIVE the FLAG so threads will get a character
		for(int i=0;i<MyCols;i++){
			//TODO:
			//SEND the SIGNAL to THREAD that you need it to go!
			//TODO:    hint:  &tgo[i] is the address where this Thread's semaphore is stored at
		}
		//WAIT until all threads are done -
		//I will know they are 'done' when they SIGNAL back
		for(int i=0;i<MyCols;i++){
			//TODO:
			//WAIT until all threads have signaled to me that they are ready for MAIN to go
			//TODO:     hint:  &tdone[i] is the address where I expect the signal to be sent to
		}
		//All Threads have gotten one character, I can now print the line
		printf("%s\n",line);
		fflush(stdout);//remove buffering from my console output
	}
//Cleanup
	printf("I've looped all I will.  Done!\n");
}
