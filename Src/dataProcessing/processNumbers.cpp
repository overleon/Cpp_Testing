#include "../../Inc/processNumbers.h"
#include <string.h>
#include <unistd.h>

void* pthreadProcessNumber(void *arg);


CProcessNumber::CProcessNumber(){

    for(uint8_t index = 0; index < 100; index++){
        block[index].clearBlock();
        block[index].setMinimumNumber(UINT32_MAX);
    }
    blockIndex = 0;
    
    primeNumbersHandler.storePrimeNumbers();

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


CBlock::CBlock(){
    clearBlock();
}

void CBlock::resetFirstNumberStatus(void){
    firstNumberStatus = 0;
}   

uint8_t CBlock::getFirstNumberStatus(void){
    return firstNumberStatus;
}   

void CBlock::setMaximumNumber(uint32_t number){
    block.max_number = number;    
}   

void CBlock::setMinimumNumber(uint32_t number){
    block.min_number = number;    

}

void CBlock::setFirstNumber(uint32_t number){
    block.first_number = number;    
    firstNumberStatus = 1;

}

void CBlock::setLastNumber(uint32_t number){
    block.last_number = number;    

}

void CBlock::increaseOnePrimeNumbers(void){
    block.number_of_prime_numbers++;
}

void CBlock::increaseOneEvenNumbers(void){
    block.number_of_even_numbers++;
}

void CBlock::increaseOneOddNumbers(void){
    block.number_of_odd_numbers++;
}

uint32_t CBlock::getMaximumNumber(void){
    return block.max_number;
}

uint32_t CBlock::getMinimumNumber(void){
    return block.min_number;
}

uint32_t CBlock::getFirstNumber(void){
    return block.first_number;
}

uint32_t CBlock::getLastNumber(void){
    return block.last_number;
}

uint16_t CBlock::getNumberOfPrimes(void){
    return block.number_of_prime_numbers;
}

uint16_t CBlock::getNumberOfEvens(void){
    return block.number_of_even_numbers;
}

uint16_t CBlock::getNumberOfOdds(void){
    return block.number_of_odd_numbers;
}

void CBlock::clearBlock(void){
    memset(&block, 0x00, sizeof(block));
}
