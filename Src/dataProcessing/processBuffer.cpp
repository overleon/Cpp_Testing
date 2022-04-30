#include "../../Inc/processBuffer.h"
#include "../../Inc/primeNumbers.h"
#include "../../Inc/processNumbers.h"

#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <list>
#include <string.h>
#include <sys/time.h>

using namespace std;

void* pthreadGetBValues(void *arg);

inline void CDataProcessing::createParsingThread(CDataProcessing *dataProcessing){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadGetBValues, (void*)dataProcessing);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Parsing data Thread created\n";
} 

CDataProcessing::CDataProcessing(){
    systemBuffer = new CUserBuffer();
    processNumber = new ProccesNumber();
    // createParsingThread(this);
}


void CDataProcessing::saveData(uint32_t lenght, uint8_t *data){
    systemBuffer->sendDatatoBuffer(lenght, data);
}

void* pthreadGetBValues(void *arg) {
    CDataProcessing *handler = (CDataProcessing*)arg;
    static volatile uint32_t bCounter = 0;
    uint8_t numberInString[10] = {0};
    while(1){
        while(handler->getSystemBufferLenght()){
            uint8_t character = handler->getNextDataFromSystemBuffer();    
            if(character == 'b'){
                character = handler->getNextDataFromSystemBuffer();//---- "
                character = handler->getNextDataFromSystemBuffer();//---- :
                character = handler->getNextDataFromSystemBuffer();//---- space
                character = handler->getNextDataFromSystemBuffer();//---- firstNumber
                unsigned char index = 0;//Variable to protect the system againt an infinity loop
                while((character >= '0' && character <= '9') && index < 10){
                    numberInString[index] = character; 
                    character = handler->getNextDataFromSystemBuffer();
                    index++;
                }
                if( numberInString[0] >= '0' && numberInString[0] <= '9'){
                    uint32_t number = (uint32_t)strtoul((const char*)numberInString, NULL, 0 );
                    // handler->sendNumberToNumbersBuffer(number);
                    memset(numberInString, 0x00, 11);
                    cout<<"Number: "<<number<<endl;
                    bCounter++;
                }
            }
        }
    }
    pthread_exit(NULL);
}

uint8_t CDataProcessing::getNextDataFromSystemBuffer(void){
    return systemBuffer->getDataFromBuffer();
}

uint32_t CDataProcessing::getSystemBufferLenght(void){
    return systemBuffer->isBufferFull();
}

uint32_t CDataProcessing::getNumbersBufferLenght(void){
    return processNumber->numbersBuffer->isBufferFull();
}

void CDataProcessing::sendNumberToNumbersBuffer(uint32_t number){
    processNumber->passNumber(number);
}

void CDataProcessing::showBlocksResult(void){
	for(uint8_t index = 0; index < 100; index++){
		cout<<"Maximum number: 	"<<processNumber->block[index].max_number<<endl;
		cout<<"Minimum number: 	"<<processNumber->block[index].min_number<<endl;
		cout<<"First number:   	"<<processNumber->block[index].first_number<<endl;
		cout<<"Last number:    	"<<processNumber->block[index].last_number<<endl;
		cout<<"Number of primes: 	"<<processNumber->block[index].number_of_prime_numbers<<endl;
		cout<<"Number of evens: 	"<<processNumber->block[index].number_of_even_numbers<<endl;
		cout<<"Number of odds: 	"<<processNumber->block[index].number_of_odd_numbers<<endl;
		cout<<"-----------------------------------------------"<<endl;
	}
	processNumber->clearBlocks();	
}


