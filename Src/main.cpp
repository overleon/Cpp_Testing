#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "../Inc/proccessData.h"
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

// void showAllBlocks(void){
// 	cout<<"-----------------------------------------------"<<endl;
// 	for(uint8_t index = 0; index < 100; index++){
// 		cout<<"Maximum number: 	"<<proccesNumber->block[index].max_number<<endl;
// 		cout<<"Minimum number: 	"<<proccesNumber->block[index].min_number<<endl;
// 		cout<<"First number:   	"<<proccesNumber->block[index].first_number<<endl;
// 		cout<<"Last number:    	"<<proccesNumber->block[index].last_number<<endl;
// 		cout<<"Number of primes: 	"<<proccesNumber->block[index].number_of_prime_numbers<<endl;
// 		cout<<"Number of evens: 	"<<proccesNumber->block[index].number_of_even_numbers<<endl;
// 		cout<<"Number of odds: 	"<<proccesNumber->block[index].number_of_odd_numbers<<endl;
// 		cout<<"-----------------------------------------------"<<endl;
// 	}
// 	proccesNumber->clearBlocks();	
// }

uint8_t var[] = "{\"a\": 1234566, \"b\": 680929}";

int main () {
	// CProcessPrimeNumber *processPrimeNumber = new CProcessPrimeNumber();
	// processPrimeNumber->storePrimeNumbers();
	// for (uint32_t index = 0; index < UINT32_MAX; index++){
	// 	processPrimeNumber->checkIfNumberIsPrime(index);

	CUserBuffer *userBuffer = new CUserBuffer();
	UserParsePacket *userParsePacket = new UserParsePacket(*userBuffer);	

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
		userBuffer->sendDatatoBuffer(len, (uint8_t*)msg);
		// for(volatile uint16_t timeout = 0; timeout < 1000; timeout++);
		// userBuffer->sendDatatoBuffer(sizeof(var)-1, var);
		// break;
		// printf("%s\n", msg);	
		if(counter++ == (6300)){
			gettimeofday(&tf, NULL);   // Instante final
			tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
			printf("Has tardado: %g milisegundos\n", tiempo);

			while(userBuffer->mBufferLenght);
			while(userParsePacket->getNumbersBufferLenght());
			cout<<"Finished"<<endl;
			userParsePacket->showBlocksResult();
			// showAllBlocks();
			counter = 0;
		}
	}
	websockh_close_connection(ws);
	SSL_CTX_free(ssl_ctx);
	pthread_exit(NULL);
	return 0;
}


