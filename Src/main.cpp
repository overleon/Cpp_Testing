#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <ctime> 
#include <sys/time.h> 
#include <string.h>
#include <iostream>

#include "../Inc/processBuffer.h"
#include "../Inc/userBuffer.h"
#include "../Inc/main.h"
#include "../Inc/primeNumbers.h"
#include "../Inc/processNumbers.h"
#include "../Inc/blocks.h"

#define NUM_THREADS 1
extern "C" {
    #include "../Inc/websockh.h"
}

uint8_t var[] = "{\"a\": 1234566, \"b\": 680929}";

struct timeval ti, tf;

void startTimer(void){
    gettimeofday(&ti, NULL);   // Instante inicial
}

double getTimeMilliseconds(void){
    double time_ms;
	gettimeofday(&tf, NULL);   // Instante final
	time_ms = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
	return time_ms;
}

int main () {
	// CProcessPrimeNumber *processPrimeNumber = new CProcessPrimeNumber();
	// for (uint32_t index = 0; index < UINT32_MAX; index++){
	// 	processPrimeNumber->checkIfNumberIsPrime(index);
	CDataProcessing *dataProcessing = new CDataProcessing();	

	SSL_CTX *ssl_ctx = websockh_init_ssl_ctx();
	websockh ws = websockh_create_connection("209.126.82.146", 8080, "/", NULL);
	if (ws == NULL) return  1;

	startTimer();
	while (1){
		uint64_t len;
		uint8_t opcode;
		char *msg = (char *)websockh_recv(ws, &len, &opcode);
		dataProcessing->systemBuffer.saveData(len, (uint8_t*)msg);
		double timeMilliseconds = getTimeMilliseconds();
		if(timeMilliseconds >= 10000){

			while(dataProcessing->systemBuffer.getLenght());
			while(dataProcessing->numbersBuffer.getLenght());
			dataProcessing->blockHandler->showBlocksResult();
			dataProcessing->blockHandler->clearAllTheBlocks();
			printf("Time milliseconds: %g \n", timeMilliseconds);
			startTimer();	
		}
	}
	websockh_close_connection(ws);
	SSL_CTX_free(ssl_ctx);
	pthread_exit(NULL);
	return 0;
}


