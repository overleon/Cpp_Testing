#ifndef USERBUFFER_H
#define USERBUFFER_H

#include <iostream>

using namespace std;

class Node {
	public:
		uint8_t data;
		Node* next;
};

class CUserBuffer{
	private:
		Node* mBufferHead;		
		Node* mBufferTail;		
	public:
		uint32_t mBufferLenght;
		virtual ~CUserBuffer(){}
		CUserBuffer();
		void saveData(uint32_t lenght, uint8_t *data);
		void printBuffer(void);
		void clearBuffer(void);
		uint8_t getDataFromBuffer(void);
		uint32_t getLenght(void);
};

#endif




