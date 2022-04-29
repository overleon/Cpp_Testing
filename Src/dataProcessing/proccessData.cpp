#include "../../Inc/proccessData.h"
#include "../../Inc/primeNumbers.h"
#include "../../Inc/processNumbers.h"

#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <list>
#include <string.h>
#include <sys/time.h>

using namespace std;

extern ProccesNumber *proccesNumber;

UserParsePacket::UserParsePacket(CUserBuffer &subject):subject_(subject){
    this->subject_.Attach(this);
}
void* UserParsePacket::pthreadGetBValues(void *arg) {
    UserParsePacket *handler = (UserParsePacket*)arg;
    static volatile uint32_t bCounter = 0;
    uint8_t numberInString[10] = {0};
    while(1){
        while(handler->subject_.isBufferFull()){
            char character = (char)handler->subject_.getDataFromBuffer();    
            if(character == 'b'){
                character = handler->subject_.getDataFromBuffer();//---- "
                character = handler->subject_.getDataFromBuffer();//---- :
                character = handler->subject_.getDataFromBuffer();//---- space
                character = handler->subject_.getDataFromBuffer();//---- firstNumber
                unsigned char index = 0;//Variable to protect the system againt an infinity loop
                while((character >= '0' && character <= '9') && index < 10){
                    numberInString[index] = character; 
                    character = handler->subject_.getDataFromBuffer();
                    index++;
                }
                if( numberInString[0] >= '0' && numberInString[0] <= '9'){
                    uint32_t number = (uint32_t)strtoul((const char*)numberInString, NULL, 0 );
                    proccesNumber->passNumber(number);
                    memset(numberInString, 0x00, 11);
                    bCounter++;
                }
            }
            // cout<<"Number: "<<handler->isBufferFull()<<endl;
        }
    }
    handler->parseThreadRunningStatus = 0;
    pthread_exit(NULL);
}

void UserParsePacket::Update(const std::string &message_from_subject) {
    if(!parseThreadRunningStatus){
        cout<<"Thread created 2\n";
        pthread_t thread;
        int rc = pthread_create(&thread, NULL, pthreadGetBValues, (void*)this);
        parseThreadRunningStatus = 1;
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
}

void UserParsePacket::RemoveMeFromTheList() {
	subject_.Detach(this);
}

