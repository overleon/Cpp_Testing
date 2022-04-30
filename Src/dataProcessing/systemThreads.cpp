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


uint32_t CDataProcessing::assembleNumber(void){
    uint32_t number = 0;
    uint32_t firstPart =     (uint32_t)mNumbersBuffer.getDataFromBuffer();
    uint32_t secondPart =    (uint32_t)mNumbersBuffer.getDataFromBuffer();
    uint32_t thirdPart =     (uint32_t)mNumbersBuffer.getDataFromBuffer();
    uint32_t fourthPart =    (uint32_t)mNumbersBuffer.getDataFromBuffer();
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
        while(handler->numbersBufferHasDatas()){
            uint32_t number = handler->assembleNumber();
            handler->processNumber(number, handler->getCurrentBlock());
            handler->passToNextBlock();
            // cout<<"Number: "<<handler->numbersBuffer.getLenght()<<endl;
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
                    handler->numberBufferSaveData( sizeof(uint32_t), (uint8_t*)&number);
                    memset(BNumberInString, 0x00, 11);
                    bCounter++;
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
    if(mSystemBuffer.getLenght()){
        return true;
    }else{
        return false;
    }
}

void CDataProcessing::systemBufferSaveData(uint32_t lenght, uint8_t* data){
    mSystemBuffer.saveData(lenght, data);
}

uint8_t CDataProcessing::systemBufferGetData(void){
    return mSystemBuffer.getDataFromBuffer();
}


bool CDataProcessing::numbersBufferHasDatas(void){
    if(mNumbersBuffer.getLenght()){
        return true;
    }else{
        return false;
    }
}

void CDataProcessing::numberBufferSaveData(uint32_t lenght, uint8_t* data){
    mNumbersBuffer.saveData(lenght, data);
}

uint8_t CDataProcessing::numberBufferGetData(void){
    return mNumbersBuffer.getDataFromBuffer();
}
