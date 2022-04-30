#ifndef PROCESSBUFFER_H
#define PROCESSBUFFER_H


#include <stdint.h>
#include <iostream>
#include <string>
#include "userBuffer.h"
#include "primeNumbers.h"
#include "processNumbers.h"


class CDataProcessing{
	private:
		
	public:
		inline void createParsingThread();
		inline void createProcessNumberThread();
		CDataProcessing();
		virtual ~CDataProcessing(){}
		uint32_t assembleNumber(void);
		CUserBuffer systemBuffer;
		CUserBuffer numbersBuffer;
		CProcessNumber 	processNumber;
		CBlock block[100];
		CBlockHandler *blockHandler;

};


#endif