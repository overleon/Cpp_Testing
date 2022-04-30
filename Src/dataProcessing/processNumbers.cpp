#include "../../Inc/processNumbers.h"
#include <string.h>
#include <unistd.h>

void* pthreadProcessNumber(void *arg);

inline void CProcessNumber::createProcessNumberThread(){
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, pthreadProcessNumber, (void*)this);
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
    cout<<"Parsing data Thread created\n";
} 

CProcessNumber::CProcessNumber(){
    
    memset(block, 0x00, sizeof(block));
    for(uint8_t index = 0; index < 100; index++){
        block[index].min_number = UINT32_MAX;
        firstNumber[index] = 0;
    }
    blockIndex = 0;
    
    primeNumbersHandler.storePrimeNumbers();

    createProcessNumberThread();
}

void CProcessNumber::checkMaximumNumber(uint32_t number){
    if(block[blockIndex].max_number < number){
        block[blockIndex].max_number = number;
    }
}

void CProcessNumber::checkMinimumNumber(uint32_t number){
    if(block[blockIndex].min_number > number){
        block[blockIndex].min_number = number;
    }
}

void CProcessNumber::checkFirstNumber(uint32_t number){
    if(!firstNumber[blockIndex]){
        block[blockIndex].first_number = number;
        firstNumber[blockIndex] = 1;
    }
}

void CProcessNumber::checkPrimeNumber(uint32_t number){
    if(!primeNumbersHandler.checkIfNumberIsPrime(number)){
        block[blockIndex].number_of_prime_numbers++;
    }

}

void CProcessNumber::checkEvenOddNumber(uint32_t number){
    if ( number % 2 == 0){
        block[blockIndex].number_of_even_numbers++;
    }else{
        block[blockIndex].number_of_odd_numbers++;
    }
}

void CProcessNumber::setLastNumber(uint32_t number){
    block[blockIndex].last_number = number;
}

void CProcessNumber::clearBlocks(void){
    memset(&block, 0x00, sizeof(block));
    for(uint8_t index = 0; index < 100; index++){
        block[index].min_number = UINT32_MAX;
        firstNumber[index] = 0;
    }
}



void CProcessNumber::checkBlockIndex(void){
    if(blockIndex == 100){
        blockIndex = 0;
    }
}

void CProcessNumber::passToNextBlock(void){
    blockIndex++;
}

void CProcessNumber::processNumber(uint32_t number){
    checkBlockIndex();
    checkMaximumNumber(number);
    checkMinimumNumber(number);
    checkFirstNumber(number);
    setLastNumber(number);
    checkEvenOddNumber(number);
    checkPrimeNumber(number);
    passToNextBlock();
}


uint32_t CProcessNumber::assembleNextNumberFromBuffer(void){
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
    CProcessNumber *handler = (CProcessNumber*)arg;
    while(1){

        while(handler->numbersBuffer.isBufferFull()){
            uint32_t number = handler->assembleNextNumberFromBuffer();
            handler->processNumber(number);
            // cout<<"Number: "<<number<<endl;
        }
    }
    pthread_exit(NULL);
}



void CProcessNumber::showBlocksResult(void){
	for(uint8_t index = 0; index < 100; index++){
		cout<<"Maximum number: 	"<<block[index].max_number<<endl;
		cout<<"Minimum number: 	"<<block[index].min_number<<endl;
		cout<<"First number:   	"<<block[index].first_number<<endl;
		cout<<"Last number:    	"<<block[index].last_number<<endl;
		cout<<"Number of primes: 	"<<block[index].number_of_prime_numbers<<endl;
		cout<<"Number of evens: 	"<<block[index].number_of_even_numbers<<endl;
		cout<<"Number of odds: 	"<<block[index].number_of_odd_numbers<<endl;
		cout<<"-----------------------------------------------"<<endl;
	}
	clearBlocks();	
}
