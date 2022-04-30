#ifndef PROCESSNUMBER_H
#define PROCESSNUMBER_H

#include <iostream>
#include "userBuffer.h"
#include "primeNumbers.h"

using namespace std;

typedef struct block_{
	uint32_t max_number;
	uint32_t min_number;
	uint32_t first_number;
	uint32_t last_number;
	uint16_t number_of_prime_numbers;
	uint16_t number_of_even_numbers;
	uint16_t number_of_odd_numbers;
}block_t;

class ProccesNumber{
    private:    
		uint8_t firstNumber[100];
		CProcessPrimeNumber *primeNumbersHandler;
    public:

        ProccesNumber();

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

        void passNumber(uint32_t number);

		void clearBlocks(void);

};

#endif




