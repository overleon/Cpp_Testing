#ifndef SYSTEMTHREADS_H
#define SYSTEMTHREADS_H


#include <stdint.h>
#include <iostream>
#include <string>
#include "../nio/userBuffer.h"
#include "primeNumbers.h"
#include "processNumbers.h"
#include "blocks.h"
#include <queue>

class CDataProcessing{
	private:
		CUserBuffer mSystemBuffer;
		// CUserBuffer mNumbersBuffer;
		queue<uint32_t> numberBuffer;
		CProcessNumber 	mprocessNumber;
		CBlock mblock[100];
		CBlockHandler *blockHandler;
		
	public:
		void createParsingThread();
		void createProcessNumberThread();
		CDataProcessing();
		virtual ~CDataProcessing(){}

		bool systemBufferHasDatas(void);
		void systemBufferSaveData(uint32_t lenght, uint8_t* data);
		uint8_t systemBufferGetData(void);

		bool numbersBufferHasDatas(void);
		void numberBufferSaveData(uint32_t number);
		uint32_t numberBufferGetData(void);

		void processNumber(uint32_t number, CBlock* block);

		uint32_t assembleNumber(void);

		CBlock* getCurrentBlock(void); 
		void passToNextBlock(void); 
		void showAllTheBlocksResult(void);
		void clearAllTheBlocks(void);
};


#endif