#ifndef PROCESSNUMBER_H
#define PROCESSNUMBER_H

#include <iostream>
#include "userBuffer.h"
#include "primeNumbers.h"

using namespace std;



class CBlocks{
	private:
		struct{
			uint32_t max_number;
			uint32_t min_number;
			uint32_t first_number;
			uint32_t last_number;
			uint16_t number_of_prime_numbers;
			uint16_t number_of_even_numbers;
			uint16_t number_of_odd_numbers;
		}block;
		uint8_t firstNumberStatus;
	public:
		CBlocks();
		~CBlocks(){}

		uint8_t getFirstNumberStatus(void);
		void resetFirstNumberStatus(void);

		void setMaximumNumber(uint32_t);
		void setMinimumNumber(uint32_t);
		void setFirstNumber(uint32_t);
		void setLastNumber(uint32_t);
		void increaseOnePrimeNumbers(void);
		void increaseOneEvenNumbers(void);
		void increaseOneOddNumbers(void);

		uint32_t getMaximumNumber(void);
		uint32_t getMinimumNumber(void);
		uint32_t getFirstNumber(void);
		uint32_t getLastNumber(void);
		uint16_t getNumberOfPrimes(void);
		uint16_t getNumberOfEvens(void);
		uint16_t getNumberOfOdds(void);

		void clearBlock(void);
};

class CProcessNumber{
    private:    
		uint8_t blockIndex;
    public:

		inline void createProcessNumberThread();
        CProcessNumber();

		CUserBuffer numbersBuffer;
		CProcessPrimeNumber primeNumbersHandler;
		CBlocks block[100];

		void checkMaximumNumber(uint32_t);
		void checkMinimumNumber(uint32_t);
		void checkFirstNumber(uint32_t);
		void setLastNumber(uint32_t);
		void checkPrimeNumber(uint32_t);
		void checkEvenOddNumber(uint32_t);

		uint32_t assembleNextNumberFromBuffer(void);
		void processNumber(uint32_t number);

		void clearAllTheBlocks(void);
		void checkBlockIndex(void);
		void passToNextBlock(void);
		void showBlocksResult(void);

};

// class CBlocks{
// 	private:
// 	public:
// }

#endif




