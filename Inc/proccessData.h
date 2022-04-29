#ifndef PROCESSDATA_H
#define PROCESSDATA_H


#include <stdint.h>
#include <iostream>
#include <string>
#include "userBuffer.h"
#include "primeNumbers.h"


typedef struct block_{
	uint32_t max_number;
	uint32_t min_number;
	uint32_t first_number;
	uint32_t last_number;
	uint16_t number_of_prime_numbers;
	uint16_t number_of_even_numbers;
	uint16_t number_of_odd_numbers;
}block_t;


class UserParsePacket : public IObserver{
 public:
	UserParsePacket(CUserBuffer &subject);
	virtual ~UserParsePacket(){
		std::cout << "Goodbye, I was the Observer\n";
	}
	void Update(const std::string &message_from_subject);
	void RemoveMeFromTheList();
	static void *pthreadGetBValues(void *arg);
 private:
	CUserBuffer &subject_;
	int parseThreadRunningStatus;
	std::string message_from_subject_;
};


#endif