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

class CSystemHandler{
	private:
		
		pthread_mutex_t systemQueueMutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_t bNumberQueueMutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_t aNumberQueueMutex = PTHREAD_MUTEX_INITIALIZER;

		queue<uint32_t> systemQueue;
		queue<uint32_t> bNumberQueue;
		queue<uint32_t> aNumberQueue;

		CProcessNumber 	mProcessNumber;

		CBlock mblock[100];
		CBlockHandler *blockHandler;
		
	public:
		void createParsingThread();
		void createProcessNumberThread();
		CSystemHandler();
		virtual ~CSystemHandler(){}

		bool systemQueueHasDatas(void);
		void systemQueueHasDatas(uint32_t lenght, uint8_t* data);
		uint8_t systemQueueGetData(void);

		bool bNumberQueueHasDatas(void);
		void bNumberQueueHasDatas(uint32_t number);
		uint32_t bNumberQueueGetData(void);

		bool aNumberQueueHasDatas(void);
		void aNumberQueueHasDatas(uint32_t number);
		uint32_t aNumberQueueGetData(void);

		uint64_t getNumber(void);

		void processNumber(uint32_t number, CBlock* block);

		CBlock* getBlock(uint8_t numberBlock); 
		void passToNextBlock(void); 
		void showAllTheBlocksResult(void);
		void clearAllTheBlocks(void);
};


#endif