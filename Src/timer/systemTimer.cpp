#include "../../Inc/systemTimer.h"
#include <sys/time.h> 

void  CSystemTimer::startTimer(void){
    gettimeofday(&ti, NULL);   // Instante inicial
}

void  CSystemTimer::restartTimer(void){
    gettimeofday(&ti, NULL);   // Instante inicial
}

double CSystemTimer::getTimeTimerInMilliseconds(void){
    gettimeofday(&tf, NULL);   // Instante final
	time_ms = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
	return time_ms;
}

