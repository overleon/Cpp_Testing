#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H


#include <stdint.h>
#include <iostream>
#include <string>


class CSystemTimer{
    private:
        uint64_t time_ms;
        struct timeval ti, tf;
    public:
        CSystemTimer(){}
        void startTimer(void);
        void restartTimer(void);
        uint64_t getTimeTimerInMilliseconds(void);
        bool hasPassedXTime(uint64_t time);

};      

#endif