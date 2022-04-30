#include "../../Inc/dataProcessing/primeNumbers.h"
#include "../../Inc/primesieve/primesieve.hpp"
#include <iostream>

using namespace std;

uint32_t CProcessPrimeNumber::binarySearch(uint32_t array[], uint32_t x, uint32_t low, uint32_t high) {
	uint32_t mid;
	while (low <= high) {
		mid = low + (high - low) / 2;

		if (array[mid] == x){
			return mid;
		}

		if (array[mid] < x){
			low = mid + 1;
		}else{
			high = mid - 1;
		}
	}

  return 0;
}

uint8_t CProcessPrimeNumber::checkIfNumberIsPrime(uint32_t numberToSearch){
	if(binarySearch(primeNumbersArray, numberToSearch, 0, 203280221)){
		// cout<<"Number is prime"<<endl;
		return 0;
	}else{
		// cout<<"Number is not prime"<<endl;
		return 1;
	}
}

void CProcessPrimeNumber::storePrimeNumbers(void){
	cout<<"Storing prime numbers from 0 to 2^32 ("<<UINT32_MAX<<")."<<endl;
	primesieve::iterator it; 
	uint64_t prime = 0;

	for (uint32_t index = 0; prime < UINT32_MAX; prime = it.next_prime()){
		primeNumbersArray[index++] = (uint32_t)prime;
	}
	cout<<"Finished prime numbers storing"<<endl;
}