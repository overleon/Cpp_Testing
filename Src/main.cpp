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
	queue<uint32_t> systemQueue;
	CDataProcessing *dataProcessing = new CDataProcessing();	
	// forward_list<uint32_t> myList;
	// myList.
	// dataProcessing->createProcessNumberThread();
	// dataProcessing->numberBufferSaveData(1);
	// dataProcessing->numberBufferSaveData(2);
	// dataProcessing->numberBufferSaveData(3);
	
	// cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
	// cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
	// cout<<"number: "<<dataProcessing->numberBufferGetData()<<endl;
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
		// printf("%s\n", msg);
		dataProcessing->systemBufferSaveData(len, (uint8_t*)msg);

		double timeMilliseconds = systemTimer.getTimeTimerInMilliseconds();
		if(timeMilliseconds >= 60000){
			while(dataProcessing->systemBufferHasDatas());
			while(dataProcessing->bNumberBufferHasDatas());
			dataProcessing->showAllTheBlocksResult();
			dataProcessing->clearAllTheBlocks();
			printf("Time milliseconds: %g \n", timeMilliseconds);
			systemTimer.restartTimer();
		}
	}
	websockh_close_connection(ws);
	pthread_exit(NULL);
	return 0;
}