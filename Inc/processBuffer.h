#ifndef PROCESSBUFFER_H
#define PROCESSBUFFER_H


#include <stdint.h>
#include <iostream>
#include <string>
#include "userBuffer.h"
#include "primeNumbers.h"
#include "processNumbers.h"


class CDataProcessing{
 public:
	CDataProcessing();
	virtual ~CDataProcessing(){
		std::cout << "Goodbye, I was the Observer\n";
	}
	uint8_t getNextDataFromSystemBuffer(void);
	uint32_t getSystemBufferLenght(void);
	uint32_t getNumbersBufferLenght(void);
	void sendNumberToNumbersBuffer(uint32_t number);
	void showBlocksResult(void);
	void saveData(uint32_t lenght, uint8_t *data);
	inline void createParsingThread();
	
 private:
	CUserBuffer *systemBuffer;
	ProccesNumber *processNumber;
};


#endif