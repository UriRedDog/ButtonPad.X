/* 
 * File:   main.c
 * Author: dthedens
 *
 * Created on June 6, 2014, 10:57 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "p24fxxxx.h"

#include "Pin.h"
#include "LedPins.h"
#include "Switch.h"

#include "Power.h"


// JTAG/Code Protect/Write Protect/Clip-on Emulation mode/
// Watchdog Timer/ICD pins select
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx1)

// Enable CLK switch, Disable CLK monitor, OSCO or Fosc/2,
// Primary Oscillator Mode: Disabled, Internal Fast RC oscillator
_CONFIG2(FCKSM_CSECMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)

_CONFIG3(SOSCSEL_IO &  WPDIS_WPDIS)

_CONFIG4(RTCOSC_LPRC & DSWDTOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF)

void Initialize()
{
    InitLeds();
    InitSwitches();
}

void Execute()
{

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
    return 0;
    InitPins();
    InitSwitches();


    return (EXIT_SUCCESS);
}

