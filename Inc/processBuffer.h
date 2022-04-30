#ifndef PROCESSBUFFER_H
#define PROCESSBUFFER_H


#include <stdint.h>
#include <iostream>
#include <string>
#include "userBuffer.h"
#include "primeNumbers.h"
#include "processNumbers.h"


class CDataProcessing : public IObserver{
 public:
	CDataProcessing(CUserBuffer &subject);
	virtual ~CDataProcessing(){
		std::cout << "Goodbye, I was the Observer\n";
	}
	void Update(const std::string &message_from_subject);
	void RemoveMeFromTheList();

	uint8_t getNextDataFromBuffer(void);
	uint32_t getSystemBufferLenght(void);
	uint32_t getNumbersBufferLenght(void);
	void sendNumberToNumbersBuffer(uint32_t number);
	void showBlocksResult(void);
 private:
	ProccesNumber *processNumber;
	CUserBuffer &subject_;
	int parseThreadRunningStatus;
	std::string message_from_subject_;
};


#endif