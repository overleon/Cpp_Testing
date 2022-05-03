#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <ctime> 
#include <sys/time.h> 
#include <string.h>
#include <iostream>

#include "../Inc/dataProcessing/systemThreads.h"
#include "../Inc/nio/userBuffer.h"
#include "../Inc/main.h"
#include "../Inc/dataProcessing/primeNumbers.h"
#include "../Inc/dataProcessing/processNumbers.h"
#include "../Inc/dataProcessing/blocks.h"
#include "../Inc/timer/systemTimer.h"

#define NUM_THREADS 1
extern "C" {
    #include "../Inc/websocket/websockh.h"
}

#include <forward_list>
void function(void){
	queue<uint32_t> systemBuffer;
	CDataProcessing *dataProcessing = new CDataProcessing();	
	// forward_list<uint32_t> myList;
	// myList.
	dataProcessing->createProcessNumberThread();
	dataProcessing->numberBufferSaveData(1);
	dataProcessing->numberBufferSaveData(2);
	dataProcessing->numberBufferSaveData(3);
	
	cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
	cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
	cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
}

int main () {
	// function();
	websockh ws = websockh_create_connection("209.126.82.146", 8080, "/", NULL);
	if (ws == NULL) return  1;

	CDataProcessing *dataProcessing = new CDataProcessing();	
	dataProcessing->createProcessNumberThread();
	dataProcessing->createParsingThread();

	CSystemTimer systemTimer;
	systemTimer.startTimer();

	while (1){
		uint64_t len;
		uint8_t opcode;
		char *msg = (char *)websockh_recv(ws, &len, &opcode);
		dataProcessing->systemBufferSaveData(len, (uint8_t*)msg);

		double timeMilliseconds = systemTimer.getTimeTimerInMilliseconds();
		if(timeMilliseconds >= 5000){
			while(dataProcessing->systemBufferHasDatas());
			while(dataProcessing->numbersBufferHasDatas());
			dataProcessing->showAllTheBlocksResult();
			dataProcessing->clearAllTheBlocks();
			printf("Time milliseconds: %g \n", timeMilliseconds);
			systemTimer.restartTimer();
			break;
		}
	}
	websockh_close_connection(ws);
	pthread_exit(NULL);
	return 0;
}


// #include <stdio.h>
// #include <iostream>
// #include <unistd.h>
// #include <ctime> 
// #include <sys/time.h> 
// #include <string.h>
// #include <iostream>

// pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
// void *function1(void *arg){
// 	pthread_mutex_lock(&mutex_1);
// 	while(1){
// 		printf("function 1\n");
// 		sleep(1);
// 	}
// 	pthread_mutex_unlock(&mutex_1);
// }

// void *function2(void *arg){
// 	pthread_mutex_lock(&mutex_1);
// 	while(1){
// 		printf("function 2\n");
// 		sleep(1);
// 	}
// 	pthread_mutex_unlock(&mutex_1);

// }

// void *function3(void *arg){
// 	pthread_mutex_lock(&mutex_2);
// 	while(1){
// 		printf("function 3\n");
// 		sleep(1);
// 	}
// 	pthread_mutex_unlock(&mutex_2);

// }

// void *function4(void *arg){
// 	pthread_mutex_lock(&mutex_2);
// 	while(1){
// 		printf("function 4\n");
// 		sleep(1);
// 	}
// 	pthread_mutex_unlock(&mutex_2);

// }

// int main(void){
// 	pthread_t thread[4];
//     int rc = pthread_create(&thread[0], NULL, function1, NULL);
//     	rc = pthread_create(&thread[1], NULL, function2, NULL);
//     	rc = pthread_create(&thread[2], NULL, function3, NULL);
//     	rc = pthread_create(&thread[3], NULL, function4, NULL);
// 	pthread_exit(NULL);
// }
