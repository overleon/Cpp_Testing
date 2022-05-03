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

void* pthreadGetBValues(void *arg);
void* pthreadProcessNumber(void *arg);

pthread_mutex_t systemBufferMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t numberBufferMutex = PTHREAD_MUTEX_INITIALIZER;

CDataProcessing::CDataProcessing(){
    blockHandler = new CBlockHandler(mblock, 100);    
    blockHandler->clearAllTheBlocks();
} 

void CDataProcessing::createParsingThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadGetBValues, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Thread: Parsing data --- Created\n";
} 

void CDataProcessing::createProcessNumberThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadProcessNumber, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Thread: Processing numbers --- created\n";
} 

void* pthreadProcessNumber(void *arg){
    CDataProcessing *handler = (CDataProcessing*)arg;
    while(1){
        while(handler->numbersBufferHasDatas()){
            uint32_t number = handler->numberBufferGetData();
            handler->processNumber(number, handler->getCurrentBlock());
            handler->passToNextBlock();
        }
        usleep(100);
    }
    pthread_exit(NULL);
}

void* pthreadGetBValues(void *arg) {
    CDataProcessing *handler = (CDataProcessing*)arg;
    static volatile uint32_t bCounter = 0;
    uint8_t BNumberInString[10] = {0};
    uint8_t ANumberInString[3] = {0};
    while(1){
        while(handler->systemBufferHasDatas()){
            uint8_t character = handler->systemBufferGetData();    
            if(character == 'b'){
                character = handler->systemBufferGetData();//---- "
                character = handler->systemBufferGetData();//---- "
                character = handler->systemBufferGetData();//---- "
                character = handler->systemBufferGetData();//---- "
                unsigned char index = 0;//Variable to protect the system againt an infinity loop
                while((character >= '0' && character <= '9') && index < 10){
                    BNumberInString[index] = character; 
                    character = handler->systemBufferGetData();
                    index++;
                }
                if( BNumberInString[0] >= '0' && BNumberInString[0] <= '9'){
                    uint32_t number = (uint32_t)strtoul((const char*)BNumberInString, NULL, 0 );
                    handler->numberBufferSaveData( number );
                    memset(BNumberInString, 0x00, 11);
                    bCounter++;
                    cout<<"Number: "<<bCounter<<endl;
                }
            }
        }
        usleep(100);
    }
    pthread_exit(NULL);
}

void CDataProcessing::showAllTheBlocksResult(void){
    blockHandler->showBlocksResult();
}

CBlock* CDataProcessing::getCurrentBlock(void){
    return &mblock[blockHandler->getIndex()];
}

void CDataProcessing::clearAllTheBlocks(void){
    blockHandler->clearAllTheBlocks();
}

void CDataProcessing::passToNextBlock(void){
    blockHandler->passToNextBlock();
}
void CDataProcessing::processNumber(uint32_t number, CBlock* block){
    mprocessNumber.processNumber(number, block);
}

bool CDataProcessing::systemBufferHasDatas(void){
    if(systemBuffer.empty()){
        return false;
    }else{
        return true;
    }
}

void CDataProcessing::systemBufferSaveData(uint32_t lenght, uint8_t* data){
    if(lenght == 0 || data == NULL){
        return;
    }
    pthread_mutex_lock(&systemBufferMutex);
    for(uint32_t index = 0; index < lenght; index++){
        systemBuffer.push(data[index]);
    }
    pthread_mutex_unlock(&systemBufferMutex);
}

uint8_t CDataProcessing::systemBufferGetData(void){
    if(systemBuffer.empty()){
        return 0;
    }
    pthread_mutex_lock(&systemBufferMutex);
    uint8_t number = systemBuffer.front();
    systemBuffer.pop();
    pthread_mutex_unlock(&systemBufferMutex);
    return number;
}


bool CDataProcessing::numbersBufferHasDatas(void){
    if(numberBuffer.empty()){
        return false;
    }else{
        return true;
    }
}

void CDataProcessing::numberBufferSaveData(uint32_t number){
    pthread_mutex_lock(&numberBufferMutex);
    numberBuffer.push(number);
    pthread_mutex_unlock(&numberBufferMutex);
}

uint32_t CDataProcessing::numberBufferGetData(void){
    if(numberBuffer.empty()){
        return 0;
    }
    pthread_mutex_lock(&numberBufferMutex);
    uint32_t number = numberBuffer.front();
    numberBuffer.pop();
    pthread_mutex_unlock(&numberBufferMutex);
    return number;

}
