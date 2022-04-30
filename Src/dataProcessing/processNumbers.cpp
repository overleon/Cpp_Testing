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

    for(uint8_t index = 0; index < 100; index++){
        block[index].clearBlock();
        block[index].setMinimumNumber(UINT32_MAX);
    }
    blockIndex = 0;
    
    primeNumbersHandler.storePrimeNumbers();

    createProcessNumberThread();
}

void CProcessNumber::checkMaximumNumber(uint32_t number){
    if(block[blockIndex].getMaximumNumber() < number){
        block[blockIndex].setMaximumNumber(number);
    }
}

void CProcessNumber::checkMinimumNumber(uint32_t number){
    if(block[blockIndex].getMinimumNumber() > number){
        block[blockIndex].setMinimumNumber(number);
    }
}

void CProcessNumber::checkFirstNumber(uint32_t number){
    if(!block[blockIndex].getFirstNumberStatus()){
        block[blockIndex].setFirstNumber(number);
    }
}

void CProcessNumber::checkPrimeNumber(uint32_t number){
    if(!primeNumbersHandler.checkIfNumberIsPrime(number)){
        block[blockIndex].increaseOnePrimeNumbers();
    }
}

void CProcessNumber::checkEvenOddNumber(uint32_t number){
    if ( number % 2 == 0){
        block[blockIndex].increaseOneEvenNumbers();
    }else{
        block[blockIndex].increaseOneOddNumbers();
    }
}

void CProcessNumber::setLastNumber(uint32_t number){
    block[blockIndex].setLastNumber(number);
}

void CProcessNumber::clearAllTheBlocks(void){
    for(uint8_t index = 0; index < 100; index++){
        block[index].clearBlock();
        block[index].setMinimumNumber(UINT32_MAX);
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
		cout<<"Maximum number: 	"<<block[index].getMaximumNumber()<<endl;
		cout<<"Minimum number: 	"<<block[index].getMinimumNumber()<<endl;
		cout<<"First number:   	"<<block[index].getFirstNumber()<<endl;
		cout<<"Last number:    	"<<block[index].getLastNumber()<<endl;
		cout<<"Number of primes: 	"<<block[index].getNumberOfPrimes()<<endl;
		cout<<"Number of evens: 	"<<block[index].getNumberOfEvens()<<endl;
		cout<<"Number of odds: 	"<<block[index].getNumberOfOdds()<<endl;
		cout<<"-----------------------------------------------"<<endl;
	}
	clearAllTheBlocks();	
}


CBlocks::CBlocks(){
    clearBlock();
}

void CBlocks::resetFirstNumberStatus(void){
    firstNumberStatus = 0;
}   

uint8_t CBlocks::getFirstNumberStatus(void){
    return firstNumberStatus;
}   

void CBlocks::setMaximumNumber(uint32_t number){
    block.max_number = number;    
}   

void CBlocks::setMinimumNumber(uint32_t number){
    block.min_number = number;    

}

void CBlocks::setFirstNumber(uint32_t number){
    block.first_number = number;    
    firstNumberStatus = 1;

}

void CBlocks::setLastNumber(uint32_t number){
    block.last_number = number;    

}

void CBlocks::increaseOnePrimeNumbers(void){
    block.number_of_prime_numbers++;
}

void CBlocks::increaseOneEvenNumbers(void){
    block.number_of_even_numbers++;
}

void CBlocks::increaseOneOddNumbers(void){
    block.number_of_odd_numbers++;
}

uint32_t CBlocks::getMaximumNumber(void){
    return block.max_number;
}

uint32_t CBlocks::getMinimumNumber(void){
    return block.min_number;
}

uint32_t CBlocks::getFirstNumber(void){
    return block.first_number;
}

uint32_t CBlocks::getLastNumber(void){
    return block.last_number;
}

uint16_t CBlocks::getNumberOfPrimes(void){
    return block.number_of_prime_numbers;
}

uint16_t CBlocks::getNumberOfEvens(void){
    return block.number_of_even_numbers;
}

uint16_t CBlocks::getNumberOfOdds(void){
    return block.number_of_odd_numbers;
}

void CBlocks::clearBlock(void){
    memset(&block, 0x00, sizeof(block));
}
