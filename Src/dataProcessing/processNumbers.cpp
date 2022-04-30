#include "../../Inc/processNumbers.h"
#include <string.h>


ProccesNumber::ProccesNumber(){
    
    memset(block, 0x00, sizeof(block));
    for(uint8_t index = 0; index < 100; index++){
        block[index].min_number = UINT32_MAX;
        firstNumber[index] = 0;
    }
    threadRunning = 0;
    blockIndex = 0;
    numbersBuffer = new CUserBuffer();
    
    primeNumbersHandler = new CProcessPrimeNumber();
    // primeNumbersHandler->storePrimeNumbers();
}

void ProccesNumber::checkMaximumNumber(uint32_t number){
    if(block[blockIndex].max_number < number){
        block[blockIndex].max_number = number;
    }
}

void ProccesNumber::checkMinimumNumber(uint32_t number){
    if(block[blockIndex].min_number > number){
        block[blockIndex].min_number = number;
    }
}

void ProccesNumber::checkFirstNumber(uint32_t number){
    if(!firstNumber[blockIndex]){
        block[blockIndex].first_number = number;
        firstNumber[blockIndex] = 1;
    }
}

void ProccesNumber::checkPrimeNumber(uint32_t number){
    if(!primeNumbersHandler->checkIfNumberIsPrime(number)){
        block[blockIndex].number_of_prime_numbers++;
    }

}

void ProccesNumber::checkEvenOddNumber(uint32_t number){
    if ( number % 2 == 0){
        block[blockIndex].number_of_even_numbers++;
    }else{
        block[blockIndex].number_of_odd_numbers++;
    }
}

void ProccesNumber::setLastNumber(uint32_t number){
    block[blockIndex].last_number = number;
}

void ProccesNumber::clearBlocks(void){
    memset(&block, 0x00, sizeof(block));
    for(uint8_t index = 0; index < 100; index++){
        block[index].min_number = UINT32_MAX;
        firstNumber[index] = 0;
    }
}

uint32_t assembleNumber(ProccesNumber* handler){
    uint32_t number = 0;
    uint32_t firstPart =     (uint32_t)handler->numbersBuffer->getDataFromBuffer();
    uint32_t secondPart =    (uint32_t)handler->numbersBuffer->getDataFromBuffer();
    uint32_t thirdPart =     (uint32_t)handler->numbersBuffer->getDataFromBuffer();
    uint32_t fourthPart =    (uint32_t)handler->numbersBuffer->getDataFromBuffer();
    number = number|fourthPart;
    number = number<<8;
    number = number|thirdPart;
    number = number<<8;
    number = number|secondPart;
    number = number<<8;
    number = number|firstPart;
    return number;
}

void* process(void *arg){
    ProccesNumber *handler = (ProccesNumber*)arg;
    while(1){

        while(handler->numbersBuffer->isBufferFull()){
            if(handler->blockIndex == 100){handler->blockIndex = 0;}
            uint32_t number = assembleNumber(handler);
            handler->checkMaximumNumber(number);
            handler->checkMinimumNumber(number);
            handler->checkFirstNumber(number);
            handler->setLastNumber(number);
            handler->checkEvenOddNumber(number);
            handler->checkPrimeNumber(number);
            handler->blockIndex++;
            // cout<<"Number: "<<number<<endl;
        }
    }
    handler->threadRunning = 0;
    pthread_exit(NULL);
}

void ProccesNumber::passNumber(uint32_t number){
    number = number;
    numbersBuffer->sendDatatoBuffer(sizeof(uint32_t), (uint8_t*)&number);
    if(!threadRunning){
        cout<<"Processing Numbers Thread created\n";
        pthread_t thread;
        threadRunning = 1;
        int rc = pthread_create(&thread, NULL, process, (void*)this);
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}

