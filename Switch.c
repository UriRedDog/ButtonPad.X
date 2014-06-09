
/*
 * Switch.c
 */

#include "p24fxxxx.h"
#include <stdlib.h>

#include "Pin.h"
#include "Switch.h"
#define BIT(a) (1 <<(a))

// using a shift in method to determine if the switch is debounced.
// if the bounce is all 1's or all 0's then the switch is debounced
unsigned int bounceArray[16];

// the state changes during a SwitchSample.  If the switch is debounced then
// the state is valid, if not, then it is still bouncing
SwitchState_t stateArray[16];

// we place the switches into a compile time array so that we can access
// all of them.
pSwitch_t SwitchArray[16] = {
&switchR1C1,
&switchR2C1,
&switchR3C1,
&switchR4C1,
&switchR1C2,
&switchR2C2,
&switchR3C2,
&switchR4C2,
&switchR1C3,
&switchR2C3,
&switchR3C3,
&switchR4C3,
&switchR1C4,
&switchR2C4,
&switchR3C4,
&switchR4C4
};


// we need a runtime method to set initial registers and some pins need to enable
// internal weak pullup.  Then we need to set up a timer
void InitSwitches()
{
    unsigned int i;
    pSwitch_t ps = SwitchArray[0];
    for (i=0; i<16;i++)
    {
        bounceArray[i] = 0;
        stateArray[i] = SWITCH_OFF;
        ps->row->SetMode(ps->row, PIN_INPUT_PULLUP);
        ps->col->SetMode(ps->col, PIN_OUTPUT);
     }
    // Timers defined in Timer.h
    //	Timer1.Set(&Timer1, TxCON, 0);
    //	Timer1.Set(&Timer1, TxPERIOD, TIMER1_PERIOD);
}


// for each col, we sample the all the rows
// we shift the sampled bit into the bounce count
static void Sample(pSwitch_t This)
{
    pPin_t row = This->row;
    pPin_t col = This->col;

}


// select the column and then read the row
static SwitchState_t GetState(pSwitch_t This)
{
    return SWITCH_ON;
}


// compile time constructors for switches
Switch_t switchR1C1 = {&Row1, &Col1, &bounceArray[0], &stateArray[0], Sample, GetState};
Switch_t switchR2C1 = {&Row2, &Col1, &bounceArray[1], &stateArray[1], Sample, GetState};
Switch_t switchR3C1 = {&Row3, &Col1, &bounceArray[2], &stateArray[2], Sample, GetState};
Switch_t switchR4C1 = {&Row4, &Col1, &bounceArray[3], &stateArray[3], Sample, GetState};

Switch_t switchR1C2 = {&Row1, &Col2, &bounceArray[4], &stateArray[4], Sample, GetState};
Switch_t switchR2C2 = {&Row2, &Col2, &bounceArray[5], &stateArray[5], Sample, GetState};
Switch_t switchR3C2 = {&Row3, &Col2, &bounceArray[6], &stateArray[6], Sample, GetState};
Switch_t switchR4C2 = {&Row4, &Col2, &bounceArray[7], &stateArray[7], Sample, GetState};

Switch_t switchR1C3 = {&Row1, &Col3, &bounceArray[8], &stateArray[8], Sample, GetState};
Switch_t switchR2C3 = {&Row2, &Col3, &bounceArray[9], &stateArray[9], Sample, GetState};
Switch_t switchR3C3 = {&Row3, &Col3, &bounceArray[10], &stateArray[10], Sample, GetState};
Switch_t switchR4C3 = {&Row4, &Col3, &bounceArray[11], &stateArray[11], Sample, GetState};

Switch_t switchR1C4 = {&Row1, &Col4, &bounceArray[12], &stateArray[12], Sample, GetState};
Switch_t switchR2C4 = {&Row2, &Col4, &bounceArray[13], &stateArray[13], Sample, GetState};
Switch_t switchR3C4 = {&Row3, &Col4, &bounceArray[14], &stateArray[14], Sample, GetState};
Switch_t switchR4C4 = {&Row4, &Col4, &bounceArray[15], &stateArray[15], Sample, GetState};

