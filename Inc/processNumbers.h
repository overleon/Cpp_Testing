#ifndef PROCESSNUMBER_H
#define PROCESSNUMBER_H

#include <iostream>
#include "userBuffer.h"
#include "primeNumbers.h"
#include "blocks.h"

using namespace std;

class CProcessNumber{
    private:    
    public:
        CProcessNumber();

		CProcessPrimeNumber primeNumbersHandler;

		void checkMaximumNumber(uint32_t, CBlock*);
		void checkMinimumNumber(uint32_t, CBlock*);
		void checkFirstNumber(uint32_t, CBlock*);
		void setLastNumber(uint32_t, CBlock*);
		void checkPrimeNumber(uint32_t, CBlock*);
		void checkEvenOddNumber(uint32_t, CBlock*);

		void processNumber(uint32_t number, CBlock *block);


};

#endif




