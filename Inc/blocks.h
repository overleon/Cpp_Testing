#ifndef BLOCKS_H
#define BLOCKS_H

#include <iostream>
#include "userBuffer.h"
#include "primeNumbers.h"

using namespace std;

class CBlock{
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
		CBlock();
		~CBlock(){}

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

class CBlockHandler{
	private:
		uint32_t blockIndex;
		uint32_t size;
		CBlock *handler;
	public:
		CBlockHandler(CBlock *blocks, uint32_t size);
		void clearAllTheBlocks(void);
		uint32_t getIndex(void);
		void passToNextBlock(void);
		void showBlocksResult(void);
};

#endif
