#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H


#include <stdint.h>
#include <iostream>
#include <string>


class CSystemTimer{
    private:
        double time_ms;
        struct timeval ti, tf;
    public:
        CSystemTimer(){}
        void startTimer(void);
        void restartTimer(void);
        double getTimeTimerInMilliseconds(void);

};      

#endif