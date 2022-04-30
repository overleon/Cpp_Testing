#include "../../Inc/dataProcessing/processNumbers.h"
#include "../../Inc/dataProcessing/blocks.h"
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
