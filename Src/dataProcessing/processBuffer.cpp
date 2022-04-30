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
void* pthreadProcessNumber(void *arg);

inline void CDataProcessing::createParsingThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadGetBValues, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Parsing data Thread created\n";
} 

inline void CDataProcessing::createProcessNumberThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadProcessNumber, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Parsing data Thread created\n";
} 

CDataProcessing::CDataProcessing(){
    createParsingThread();
    createProcessNumberThread();
    blockHandler = new CBlockHandler(block, 100);    
    blockHandler->clearAllTheBlocks();
} 



uint32_t CDataProcessing::assembleNumber(void){
    uint32_t number = 0;
    uint32_t firstPart =     (uint32_t)numbersBuffer.getDataFromBuffer();
    uint32_t secondPart =    (uint32_t)numbersBuffer.getDataFromBuffer();
    uint32_t thirdPart =     (uint32_t)numbersBuffer.getDataFromBuffer();
    uint32_t fourthPart =    (uint32_t)numbersBuffer.getDataFromBuffer();
    number = number|fourthPart;
    number = number<<8;
    number = number|thirdPart;
    number = number<<8;
    number = number|secondPart;
    number = number<<8;
    number = number|firstPart;
    return number;
}

void* pthreadProcessNumber(void *arg){
    CDataProcessing *handler = (CDataProcessing*)arg;
    while(1){
        while(handler->numbersBuffer.isBufferFull()){
            handler->blockHandler->checkBlockIndex();
            uint32_t number = handler->assembleNumber();
            handler->processNumber.processNumber(number, &handler->block[handler->blockHandler->getIndex()]);
            handler->blockHandler->passToNextBlock();
            // cout<<"Number: "<<number<<endl;
            // cout<<"Number: "<<handler->numbersBuffer.isBufferFull()<<endl;
        }
    }
    pthread_exit(NULL);
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
                    handler->numbersBuffer.sendDatatoBuffer( sizeof(uint32_t), (uint8_t*)&number);
                    memset(numberInString, 0x00, 11);
                    // cout<<"Number: "<<number<<endl;
                    bCounter++;
                }
            }
        }
    }
    pthread_exit(NULL);
}
