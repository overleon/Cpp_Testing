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
#include <forward_list>

#define NUM_THREADS 1
extern "C" {
    #include "../Inc/websocket/websockh.h"
}

const uint64_t TIME_TO_SHOW_BLOCKS = 60000;

int main () {
	websockh ws = websockh_create_connection("209.126.82.146", 8080, "/", NULL);
	if (ws == NULL) return  1;

	CSystemHandler *systemHandler = new CSystemHandler();	
	systemHandler->createProcessNumberThread();
	systemHandler->createParsingThread();	

	CSystemTimer systemTimer;
	systemTimer.startTimer();

	while (1){
		uint64_t len;
		uint8_t opcode;
		char *msg = (char *)websockh_recv(ws, &len, &opcode);
		// printf("%s\n", msg);
		systemHandler->systemQueueHasDatas(len, (uint8_t*)msg);

		if(systemTimer.hasPassedXTime(TIME_TO_SHOW_BLOCKS) == true){
			while(systemHandler->systemQueueHasDatas());
			while(systemHandler->bNumberQueueHasDatas() && systemHandler->aNumberQueueHasDatas());
			systemHandler->showAllTheBlocksResult();
			systemHandler->clearAllTheBlocks();
			printf("Time milliseconds: %ld \n", systemTimer.getTimeTimerInMilliseconds());
			systemTimer.restartTimer();
		}
	}
	websockh_close_connection(ws);
	pthread_exit(NULL);
	return 0;
}