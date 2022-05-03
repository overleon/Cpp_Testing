#include "../../Inc/dataProcessing/systemThreads.h"
#include "../../Inc/dataProcessing/primeNumbers.h"
#include "../../Inc/dataProcessing/processNumbers.h"
#include "../../Inc/dataProcessing/blocks.h"

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

void* pthreadGetBAndAValues(void *arg);
void* pthreadProcessNumber(void *arg);

CSystemHandler::CSystemHandler(){
    blockHandler = new CBlockHandler(mblock, 100);    
    blockHandler->clearAllTheBlocks();
} 

void CSystemHandler::createParsingThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadGetBAndAValues, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Thread: Parsing data --- Created\n";
} 

void CSystemHandler::createProcessNumberThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadProcessNumber, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Thread: Processing numbers --- created\n";
} 

void* pthreadProcessNumber(void *arg){
    CSystemHandler *handler = (CSystemHandler*)arg;
    static volatile uint32_t bCounter = 0;
    static volatile uint32_t aCounter = 0;
    while(1){
        while(handler->bNumberQueueHasDatas() && handler->aNumberQueueHasDatas()){
            uint32_t aNumber = handler->aNumberQueueGetData();
            uint32_t bNumber = handler->bNumberQueueGetData();
            handler->processNumber(bNumber, handler->getBlock(aNumber));
        }
        usleep(100);
    }
    pthread_exit(NULL);
}

uint64_t CSystemHandler::getNumber(void){
    uint8_t numberInString[10] = {0};
    uint8_t character = systemQueueGetData();//---- "
    uint32_t number;
    character = systemQueueGetData();//---- "
    character = systemQueueGetData();//---- "
    character = systemQueueGetData();//---- "
    unsigned char index = 0;//Variable to protect the system againt an infinity loop
    while((character >= '0' && character <= '9') && index < 10){
        numberInString[index] = character; 
        character = systemQueueGetData();
        index++;
    }
    if( numberInString[0] >= '0' && numberInString[0] <= '9'){
        number = (uint32_t)strtoul((const char*)numberInString, NULL, 0 );
        return number;
    }
    number = UINT32_MAX + 1; 
    return number;
}

void* pthreadGetBAndAValues(void *arg) {
    CSystemHandler *handler = (CSystemHandler*)arg;
    uint32_t bCounter = 0;
    uint32_t aCounter = 0;

    uint32_t aNumber = 0;
    uint64_t bNumber = 0;
    
    uint8_t searchingForNumber = 0;
    uint8_t maximumCharactersForB = 0;
    uint64_t numberNotFound = UINT32_MAX + 1;
    while(1){
        while(handler->systemQueueHasDatas()){
            uint8_t character = handler->systemQueueGetData();    
            if(character == 'a' && searchingForNumber == 0){
                aNumber = handler->getNumber();
                if(aNumber > 0 && aNumber<=100){
                    searchingForNumber = 1;
                    maximumCharactersForB = 0; 
                    aCounter++;
                }
            }
            if(character == 'b' && searchingForNumber == 1){
                bNumber = handler->getNumber();
                if(bNumber == numberNotFound){
                }else{
                    handler->aNumberQueueHasDatas( --aNumber );
                    handler->bNumberQueueHasDatas( (uint32_t)bNumber );
                    bCounter++;
                }
                searchingForNumber = 0;
            }
            if(searchingForNumber == 1 && ++maximumCharactersForB == 6){
                searchingForNumber = 0;
            }
        }
        usleep(100);
    }
    pthread_exit(NULL);
}

void CSystemHandler::showAllTheBlocksResult(void){
    blockHandler->showBlocksResult();
}

void CSystemHandler::clearAllTheBlocks(void){
    blockHandler->clearAllTheBlocks();
}

CBlock* CSystemHandler::getBlock(uint8_t numberBlock){
    return &mblock[numberBlock];
}

void CSystemHandler::processNumber(uint32_t number, CBlock* block){
    mProcessNumber.processNumber(number, block);
}

bool CSystemHandler::systemQueueHasDatas(void){
    if(systemQueue.empty()){
        return false;
    }else{
        return true;
    }
}

void CSystemHandler::systemQueueHasDatas(uint32_t lenght, uint8_t* data){
    if(lenght == 0 || data == NULL){
        return;
    }
    pthread_mutex_lock(&systemQueueMutex);
    for(uint32_t index = 0; index < lenght; index++){
        systemQueue.push(data[index]);
    }
    pthread_mutex_unlock(&systemQueueMutex);
}

uint8_t CSystemHandler::systemQueueGetData(void){
    if(systemQueue.empty()){
        return 0;
    }
    pthread_mutex_lock(&systemQueueMutex);
    uint8_t number = systemQueue.front();
    systemQueue.pop();
    pthread_mutex_unlock(&systemQueueMutex);
    return number;
}


bool CSystemHandler::bNumberQueueHasDatas(void){
    if(bNumberQueue.empty()){
        return false;
    }else{
        return true;
    }
}

void CSystemHandler::bNumberQueueHasDatas(uint32_t number){
    pthread_mutex_lock(&bNumberQueueMutex);
    bNumberQueue.push(number);
    pthread_mutex_unlock(&bNumberQueueMutex);
}

uint32_t CSystemHandler::bNumberQueueGetData(void){
    if(bNumberQueue.empty()){
        return 0;
    }
    pthread_mutex_lock(&bNumberQueueMutex);
    uint32_t number = bNumberQueue.front();
    bNumberQueue.pop();
    pthread_mutex_unlock(&bNumberQueueMutex);
    return number;
}

bool CSystemHandler::aNumberQueueHasDatas(void){
    if(aNumberQueue.empty()){
        return false;
    }else{
        return true;
    }
}

void CSystemHandler::aNumberQueueHasDatas(uint32_t number){
    pthread_mutex_lock(&aNumberQueueMutex);
    aNumberQueue.push(number);
    pthread_mutex_unlock(&aNumberQueueMutex);
}

uint32_t CSystemHandler::aNumberQueueGetData(void){
    if(aNumberQueue.empty()){
        return 0;
    }
    pthread_mutex_lock(&aNumberQueueMutex);
    uint32_t number = aNumberQueue.front();
    aNumberQueue.pop();
    pthread_mutex_unlock(&aNumberQueueMutex);
    return number;
}
