
// power system is a switch which turns on a FET or enables SHDWN on a LDO
// to sustatin power.
// CPU then sets a bit which drives another FET to keep power enabled.
// after some period of inactivity, the program will drive the pin low which will
// remove bias or cause SHDWN to go low.
// the only power draw will be the power FET or LDO leakage current.


// define power bus pin
// unfortunately this must be defined/declared in Pin.h and Pin.c otherwise we have to duplicate code
// PIN const PowerPin = {BIT2, &LATC, SetMode, Set, Get};

#include "Pin.h"
#include "Power.h"

void PowerManager(PowerState_t state)
{
    PowerPin.SetMode(&PowerPin, PIN_OUTPUT);
    if(state == POWER_ON)
        PowerPin.Set(&PowerPin, PIN_HIGH);
    else
        PowerPin.Set(&PowerPin, PIN_LOW);
}
