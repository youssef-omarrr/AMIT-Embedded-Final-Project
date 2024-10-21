#include <xc.h>
#include "tiny4313_dio.h"

int main(void)
{

    setPortBDirection(0xFF, 1);
    setPinBState(PORTB5, STATE_HIGH);
    while (1)
    {
    }
    return 0;
}
