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

inline void CDataProcessing::createParsingThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadGetBValues, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Parsing data Thread created\n";
} 

CDataProcessing::CDataProcessing(){
    createParsingThread();
}

void* pthreadGetBValues(void *arg) {
    CDataProcessing *handler = (CDataProcessing*)arg;
    static volatile uint32_t bCounter = 0;
    uint8_t numberInString[10] = {0};
    while(1){
        while(handler->systemBuffer.isBufferFull()){
            uint8_t character = handler->systemBuffer.getDataFromBuffer();    
            if(character == 'b'){
                character = handler->systemBuffer.getDataFromBuffer();//---- "
                character = handler->systemBuffer.getDataFromBuffer();//---- :
                character = handler->systemBuffer.getDataFromBuffer();//---- space
                character = handler->systemBuffer.getDataFromBuffer();//---- firstNumber
                unsigned char index = 0;//Variable to protect the system againt an infinity loop
                while((character >= '0' && character <= '9') && index < 10){
                    numberInString[index] = character; 
                    character = handler->systemBuffer.getDataFromBuffer();
                    index++;
                }
                if( numberInString[0] >= '0' && numberInString[0] <= '9'){
                    uint32_t number = (uint32_t)strtoul((const char*)numberInString, NULL, 0 );
                    handler->processNumber.numbersBuffer.sendDatatoBuffer( sizeof(uint32_t), (uint8_t*)&number);
                    memset(numberInString, 0x00, 11);
                    // cout<<"Number: "<<number<<endl;
                    bCounter++;
                }
            }
        }
    }
    pthread_exit(NULL);
}



