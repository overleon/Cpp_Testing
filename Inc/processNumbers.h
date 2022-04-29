#ifndef PROCESSNUMBER_H
#define PROCESSNUMBER_H

#include <iostream>
#include "observerPattern.h"
#include "primeNumbers.h"
#include "userBuffer.h"
#include "proccessData.h"
#include "proccessData.h"
#include "primeNumbers.h"

using namespace std;

class ProccesNumber{
    private:    
		uint8_t firstNumber[100];
		CProcessPrimeNumber *primeNumbersHandler;
        UserParsePacket *userParsePacket;
    public:

		CUserBuffer *numbersBuffer;
        uint8_t blockIndex;
		block_t block[100];
        uint32_t mNumber;
		uint8_t threadRunning;

		void storePrimeNumbers(void);
		void checkMaximumNumber(uint32_t);
		void checkMinimumNumber(uint32_t);
		void checkFirstNumber(uint32_t);
		void setLastNumber(uint32_t);
		void checkPrimeNumber(uint32_t);
		void checkEvenOddNumber(uint32_t);

        ProccesNumber(CUserBuffer &subject);
        void passNumber(uint32_t number);



		void clearBlocks(void);

};

#endif




