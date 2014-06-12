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
#include "PWM.h"

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

/*
 * The goal is to have only one column of LED active at one time by providing
 * a path to ground on the LED-GND[1-4] pins.  We place a FET in the path so that
 * turning it on, causes current to flow.  We cannot use pin directly since
 * all 12 LED might be on and that amounts a lot of current.
 */
#define PWM_PERIOD 62500
void InitPWM()
{
    // turn all off
    pwm1.Set(&pwm1, OCCON1, 0);
    pwm1.Set(&pwm1, OCCON2, 0);
    pwm2.Set(&pwm2, OCCON1, 0);
    pwm2.Set(&pwm2, OCCON2, 0);
    pwm3.Set(&pwm3, OCCON1, 0);
    pwm3.Set(&pwm3, OCCON2, 0);
    pwm4.Set(&pwm4, OCCON1, 0);
    pwm4.Set(&pwm4, OCCON2, 0);


    pwm1.Set(&pwm1, OCCON2, 0x1F);  // sync with this OC module
    pwm1.Set(&pwm1, OCR, PWM_PERIOD >> 1);
    pwm1.Set(&pwm1, OCRS, PWM_PERIOD - 1);
    pwm1.Set(&pwm1, OCCON1, 0x1C08);  // Fcy source, trigger 1 mode 0

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

unsigned int LastRCON __attribute__ ((persistent));
/*
 * 
 */
int main()
{
    LastRCON = RCON;
    RCON = 0;
    AD1PCFGL = 0xFFFF;  /*Ensure AN pins are digital */

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

