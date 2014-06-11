/* 
 * File:   main.c
 * Author: dthedens
 *
 * Created on June 6, 2014, 10:57 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pps.h"

#include "Pin.h"
#include "LedPins.h"
#include "Switch.h"
#include "Timer.h"

#include "Power.h"

unsigned int Activity;

#define TIMER1_PERIOD 0x8ff;

// JTAG/Code Protect/Write Protect/Clip-on Emulation mode/
// Watchdog Timer/ICD pins select
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx1)

// Enable CLK switch, Disable CLK monitor, OSCO or Fosc/2,
// Primary Oscillator Mode: Disabled, Internal Fast RC oscillator
_CONFIG2(FCKSM_CSECMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)

_CONFIG3(SOSCSEL_IO &  WPDIS_WPDIS)

_CONFIG4(RTCOSC_LPRC & DSWDTOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)

// we need to set RP16 - RP19 to be PWM outputs
void InitPWMPins()
{
    PPSOutput(PPS_RP16, PPS_OC1);
    PPSOutput(PPS_RP17, PPS_OC2);
    PPSOutput(PPS_RP18, PPS_OC3);
    PPSOutput(PPS_RP19, PPS_OC4);
}

void InitPWM()
{

}

// timer 1 is the switch bebouncer and sampling
// timer 2 is used as the inactivity sleep counter
// timer 3 may be used as a heartbeat LED
void InitTimers()
{
    Timer1.Set(&Timer1, TxCON, 0);
    Timer1.Set(&Timer1, TxPERIOD, 0x8ff);

}



void Initialize()
{
    InitLeds();
    InitSwitches();
    InitTimers();
    InitPWM();
}

void Execute()
{
    Timer1.Execute(&Timer1, TxSTART);
    while(1)
    {
        // main loop
    }

}
/*
 * 
 */
int main()
{

    AD1PCFGL = 0xFFFF;  /*Ensure AN pins are digital for ICD 2 debugging*/

    InitPWMPins();

    // Disable Watch Dog Timer
    RCONbits.SWDTEN = 0;

    // Clock switch to incorporate PLL
    // Initiate Clock Switch to FRC with PLL (NOSC=0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01); // Start clock switching

    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001) ;

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1) ;

    PowerManager(POWER_ON);



    Initialize();
    Execute();

	// just in case we return from execute(), power down
    PowerManager(POWER_OFF);
	while(1)
            ;

    return (EXIT_SUCCESS);
}

