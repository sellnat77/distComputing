/* Lab 5 - Producers and consumers 
 * Grade A+
 * 
 * Russell Tan
 * ID: 011529945
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef int buffer_item;
#define NUMBER_OF_CHOPSTICKS 5

//Global variables
buffer_item buffer[NUMBER_OF_CHOPSTICKS];
pthread_mutex_t mutex;
sem_t full,empty;//Two semaphors for empty and full buffer
int bufferCounter;//Used for insert and remove

//Method declarations
void initialize_buffer();
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

//For pthreads
void *producer(void *param);
void *consumer(void *param);

//Main method
int main(int argc, char *argv[]){
	srand(time(NULL));
	int timeOut;
	int producers;
	int consumers;
	s
	int k;
	
	if (argc < 2){
		printf("\n Error\n");
		exit(1);
	}
	else{
		timeOut = atoi(argv[1]);
		producers =atoi(argv[2]);
		consumers =atoi(argv[3]);
	}
	//Create thread arrays based on cl args
	pthread_t producerThreads[producers];
	pthread_t consumerThreads[consumers];
	
	printf("TimeOut = %2d producers = %2d consumers = %2d\n\n",timeOut,producers,consumers);
	
	//Initialize the global values and buffer
	initialize_buffer();
	
	//Create the threads
	for(k = 0; k < producers; k++){

		pthread_create(&producerThreads[k],NULL,producer,NULL);
	}
	for(k = 0; k < consumers; k++){
		pthread_create(&consumerThreads[k],NULL,consumer,NULL);
	}
	
	sleep(timeOut);
	printf("\n\n\n");
	
	exit(0);
}

void *producer(void *param){
	buffer_item item;
	
	while(1){
		sleep(1);
		item = rand()%201-100;
		
		//Grab lock and dec. empty because 
		//there's 1 less empty spot in buffer
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		
		if(insert_item(item)){
			printf("Producer ERROR");
		}
		else{
			printf("\n\tProducer produced %3d",item);
		}
		//Release lock and increment full because
		//there's 1 more value in the buffer
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	
}

void *consumer(void *param){
	buffer_item item;
	
	while(1){
		sleep(2);
		item = rand()%201-100;
		
		//Grab lock and dec. full because
		//there's 1 less item in the buffer
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
				
		if(remove_item(&item)){
			printf("Consumer ERROR");
		}
		else{
			printf("\n\t\t\t\tConsumer consumed %3d",item);
		}
		
		//Release lock and inc.empty because
		//there's 1 more empty spot in the buffer
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

int insert_item(buffer_item item){
	//If current index is not at the end of the buffer
	//insert value at end and move index forward
	if(bufferCounter < NUMBER_OF_CHOPSTICKS){
		buffer[bufferCounter] = item;
		bufferCounter++;
		return 0;
	}
	else{
		return -1;
	}
}

int remove_item(buffer_item *item){
	//If index is not at beginning, set the current value to the 
	//previous value and move the index backwards
	if(bufferCounter > 0){
		*item = buffer[(bufferCounter-1)];
		bufferCounter--;
		return 0;
	}
	else{
		return -1;
	}
}

void initialize_buffer(){
	pthread_mutex_init(&mutex,NULL);
	
	//Full starts at 0 because there are 0 taken spots in the buffer 
	sem_init(&full,0,0);
	
	//Empty starts at BUFFER SIZE because there are BUFFER SIZE
	//empty spots in the buffer
	sem_init(&empty,0,NUMBER_OF_CHOPSTICKS);
	
	bufferCounter = 0;
	
	int k; 
	for(k = 0; k < NUMBER_OF_CHOPSTICKS; k++){
		buffer[k] = 0;
	}
}
