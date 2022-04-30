#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "../Inc/processBuffer.h"
#include "../Inc/userBuffer.h"
#include <ctime> 
#include <sys/time.h> 
#include <string.h>
#include <iostream>
#include "../Inc/main.h"
#include "../Inc/primeNumbers.h"
#include "../Inc/processNumbers.h"

#define NUM_THREADS 1
extern "C" {
    #include "../Inc/websockh.h"
}

uint8_t var[] = "{\"a\": 1234566, \"b\": 680929}";

int main () {
	// CProcessPrimeNumber *processPrimeNumber = new CProcessPrimeNumber();
	// for (uint32_t index = 0; index < UINT32_MAX; index++){
	// 	processPrimeNumber->checkIfNumberIsPrime(index);

	CDataProcessing *dataProcessing = new CDataProcessing();	

	SSL_CTX *ssl_ctx = websockh_init_ssl_ctx();
	websockh ws = websockh_create_connection("209.126.82.146", 8080, "/", NULL);
	uint32_t counter = 0;
	if (ws == NULL) return  1;
	struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);   // Instante inicial
	while (1){
		uint64_t len;
		uint8_t opcode;
		char *msg = (char *)websockh_recv(ws, &len, &opcode);
		// cout<<"lenght: "<<len<<endl;
		// systemBuffer->sendDatatoBuffer(len, (uint8_t*)msg);
		dataProcessing->systemBuffer.sendDatatoBuffer(len, (uint8_t*)msg);
		// cout<<"counter: "<<counter++<<endl;
		// systemBuffer->sendDatatoBuffer(0, (uint8_t*)var);
		if(counter++ == (6300)){

			while(dataProcessing->systemBuffer.isBufferFull());
			while(dataProcessing->processNumber.numbersBuffer.isBufferFull());
			dataProcessing->processNumber.showBlocksResult();
			gettimeofday(&tf, NULL);   // Instante final
			tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
			printf("Has tardado: %g milisegundos\n", tiempo);
			counter = 0;
		}
	}
	websockh_close_connection(ws);
	SSL_CTX_free(ssl_ctx);
	pthread_exit(NULL);
	return 0;
}


