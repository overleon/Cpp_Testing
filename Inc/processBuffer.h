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
		CDataProcessing();
		virtual ~CDataProcessing(){}
		CUserBuffer systemBuffer;
		CProcessNumber processNumber;	
};


#endif