#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

#include <iostream>

class CProcessPrimeNumber{
    private:
        static const uint32_t CProcessPrimeNumberArraySize = 203280221;
        uint32_t primeNumbersArray[CProcessPrimeNumberArraySize]; 
    public:
        ~CProcessPrimeNumber(){};
        CProcessPrimeNumber(){};
        uint32_t binarySearch(uint32_t array[], uint32_t x, uint32_t low, uint32_t high);
        uint8_t checkIfNumberIsPrime(uint32_t numberToSearch);
        void storePrimeNumbers(void);
};

#endif




