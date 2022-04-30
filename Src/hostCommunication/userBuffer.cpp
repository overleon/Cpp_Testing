#include "../../Inc/userBuffer.h"
#include "../../Inc/processBuffer.h"

#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <list>
#include <string.h>

using namespace std;
typedef void * (*THREADFUNCPTR)(void *);

CUserBuffer::CUserBuffer(){
    mBufferHead = new Node();
    mBufferHead->next = NULL;
    mBufferHead->data = 0;
}

void CUserBuffer::clearBuffer(void){
    if(mBufferHead->next != NULL){
        Node *c = mBufferHead;
        Node *n = mBufferHead->next;
        while (c != NULL) {
            delete c;
            c = n;
            n = n->next;
        }
    }
}

void CUserBuffer::printBuffer(void)
{
    if(mBufferHead->next != NULL){
        Node *n = mBufferHead;
        int counter = 0;
        while (n != NULL) {
            cout<<n->data;
            counter++;
            n = n->next;
        }
    }else{
        cout<<"Not datas in buffer\n";
    }
}



void CUserBuffer::sendDatatoBuffer(uint32_t lenght, uint8_t *data){
    Node *auxiliarData[lenght] = {NULL};
    for (size_t index = 0; index < lenght; index++)
    {
        auxiliarData[index] = new Node();
    }

    size_t index = 0;
    if(mBufferHead->next == NULL){
        mBufferHead->data = data[0];
        mBufferHead->next = auxiliarData[0];
        for(index = 0; index < (lenght - 1); index++){
            auxiliarData[index]->data = data[index+1];
            auxiliarData[index]->next = auxiliarData[index+1]; 
        }
    }else{
        mBufferTail->next = auxiliarData[0];
        for(index = 0; index < lenght; index++){
            auxiliarData[index]->data = data[index];
            auxiliarData[index]->next = auxiliarData[index+1]; 
        }
    }
    auxiliarData[index-1]->next = NULL;
    mBufferTail = auxiliarData[index-1];
    mBufferLenght += lenght;
}

uint32_t CUserBuffer::isBufferFull(void){
    return mBufferLenght;
}
uint8_t CUserBuffer::getDataFromBuffer(void){
    if(mBufferLenght){
        if(mBufferHead->next != NULL){
            Node *temp = mBufferHead; 
            char data = mBufferHead->data;
            mBufferHead = mBufferHead->next; 
            delete temp;
            mBufferLenght--;
            return data;
        }
        else{
            mBufferLenght--;
            return mBufferHead->data; // Return the last value
        }
    }
    return 0;
}
