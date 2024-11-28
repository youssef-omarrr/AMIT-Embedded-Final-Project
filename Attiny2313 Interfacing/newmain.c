#include <xc.h>
#include "tiny2313_dio.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void) {

    setAllPortBDirection(1);
//    setAllPortBState(1);
    while (1) {
        setPinBState(PB2,STATE_HIGH);
        _delay_ms(1000);
        setPinBState(PB2,STATE_LOW);
        _delay_ms(1000);
    }
    return 0;
}
