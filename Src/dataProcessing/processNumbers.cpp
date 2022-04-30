#include "../../Inc/processNumbers.h"
#include <string.h>
#include <unistd.h>

void* pthreadProcessNumber(void *arg);


CProcessNumber::CProcessNumber(){
    primeNumbersHandler.storePrimeNumbers();
}

void CProcessNumber::checkMaximumNumber(uint32_t number, CBlock *block){
    if(block->getMaximumNumber() < number){
        block->setMaximumNumber(number);
    }
}

void CProcessNumber::checkMinimumNumber(uint32_t number, CBlock *block){
    if(block->getMinimumNumber() > number){
        block->setMinimumNumber(number);
    }
}

void CProcessNumber::checkFirstNumber(uint32_t number, CBlock *block){
    if(!block->getFirstNumberStatus()){
        block->setFirstNumber(number);
    }
}

void CProcessNumber::checkPrimeNumber(uint32_t number, CBlock *block){
    if(!primeNumbersHandler.checkIfNumberIsPrime(number)){
        block->increaseOnePrimeNumbers();
    }
}

void CProcessNumber::checkEvenOddNumber(uint32_t number, CBlock *block){
    if ( number % 2 == 0){
        block->increaseOneEvenNumbers();
    }else{
        block->increaseOneOddNumbers();
    }
}

void CProcessNumber::setLastNumber(uint32_t number, CBlock *block){
    block->setLastNumber(number);
}

void CProcessNumber::processNumber(uint32_t number, CBlock *block){
    checkMaximumNumber(number, block);
    checkMinimumNumber(number, block);
    checkFirstNumber(number, block);
    setLastNumber(number, block);
    checkEvenOddNumber(number, block);
    checkPrimeNumber(number, block);
}

CBlockHandler::CBlockHandler(CBlock *blocks, uint32_t size){
    handler = blocks;
    this->size = size;
    blockIndex = 0;
}

void CBlockHandler::showBlocksResult(void){
	for(uint8_t index = 0; index < 100; index++){
		cout<<"Maximum number: 	"<<handler[index].getMaximumNumber()<<endl;
		cout<<"Minimum number: 	"<<handler[index].getMinimumNumber()<<endl;
		cout<<"First number:   	"<<handler[index].getFirstNumber()<<endl;
		cout<<"Last number:    	"<<handler[index].getLastNumber()<<endl;
		cout<<"Number of primes: 	"<<handler[index].getNumberOfPrimes()<<endl;
		cout<<"Number of evens: 	"<<handler[index].getNumberOfEvens()<<endl;
		cout<<"Number of odds: 	"<<handler[index].getNumberOfOdds()<<endl;
		cout<<"-----------------------------------------------"<<endl;
	}
}

void CBlockHandler::passToNextBlock(void){
    blockIndex++;
}

void CBlockHandler::clearAllTheBlocks(void){
    for(uint8_t index = 0; index < size; index++){
        handler[index].clearBlock();
        handler[index].setMinimumNumber(UINT32_MAX);
        handler[index].resetFirstNumberStatus();
    }
}

uint32_t CBlockHandler::getIndex(void){
    return blockIndex;
}

void CBlockHandler::checkBlockIndex(void){
    if(blockIndex == size){
        blockIndex = 0;
    }
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
