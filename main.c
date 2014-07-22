/* 
 * File:   main.c
 * Author: dthedens
 *
 * Created on June 6, 2014, 10:57 AM
 * Copyright (c) <2014> <David Thedens, Eric Summers>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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


// we need 4 pins (RP20 - RP22) for an SPI slave
void InitSPI()
{
  PPSInput(PPS_SS1IN, PPS_RP20);
  PPSInput(PPS_SCK1IN, PPS_RP21);
  PPSInput(PPS_SDI1, PPS_RP22);
  PPSOutput(PPS_RP23, PPS_SDO1);
}

void InitCathodes()
{
  Cathode1.Set(&Cathode1,PIN_LOW);
  Cathode2.Set(&Cathode2,PIN_LOW);
  Cathode3.Set(&Cathode3,PIN_LOW);
  Cathode4.Set(&Cathode4,PIN_LOW);
}


#if 0
// we need to set RP16 - RP19 to be PWM outputs
void InitPWMPins()
{
  PPSOutput(PPS_RP16, PPS_OC1);
  PPSOutput(PPS_RP17, PPS_OC2);
  PPSOutput(PPS_RP18, PPS_OC3);
  PPSOutput(PPS_RP19, PPS_OC4);
}
#endif

/*
 * The goal is to have only one column of LED active at one time by providing
 * a path to ground on the LED-GND[1-4] pins.  We place a FET in the path so that
 * turning it on, causes current to flow.  We cannot use pin directly since
 * all 12 LED might be on and that amounts a lot of current.
 *
 * all pwm will sync off timer 2 and we want center aligned
 */
#if 0
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


  pwm1.Set(&pwm1, OCCON2, 0x8C); // sync with timer2
  pwm1.Set(&pwm1, OCR, 0x100); // on time
  pwm1.Set(&pwm1, OCRS, 0x1000); // off time
  pwm1.Set(&pwm1, OCCON1, 0x1C05); // timer2, dual compare single shot
  pwm1.Set(&pwm1, OCISR, 1);

  pwm2.Set(&pwm2, OCCON2, 0x8C); // sync with timer2
  pwm2.Set(&pwm2, OCR, 0x1000); // on time
  pwm2.Set(&pwm2, OCRS, 0x2000); // off time
  pwm2.Set(&pwm2, OCCON1, 0x1c05); // timer2, dual compare single shot
  pwm2.Set(&pwm2, OCISR, 1);

  pwm3.Set(&pwm3, OCCON2, 0x8C); // sync with timer2
  pwm3.Set(&pwm3, OCR, 0x2000); // on time
  pwm3.Set(&pwm3, OCRS, 0x3000); // off time
  pwm3.Set(&pwm3, OCCON1, 0x1c05); // timer2, dual compare single shot
  pwm3.Set(&pwm3, OCISR, 1);

  pwm4.Set(&pwm4, OCCON2, 0x8C); // sync with timer2
  pwm4.Set(&pwm4, OCR, 0x3000); // on time
  pwm4.Set(&pwm4, OCRS, 0x4000); // off time
  pwm4.Set(&pwm4, OCCON1, 0x1c05); // timer2, dual compare single shot
  pwm4.Set(&pwm4, OCISR, 1);
}
#endif

// timer 1 is the switch bebouncer and sampling
// timer 2 is used as the LED PWM
// timer 3 is used as the inactivity indicator

void InitTimers()
{

  Timer1.Set(&Timer1, TCON, 0x10); // 1:8 prescaller
  Timer1.Set(&Timer1, TPERIOD, 0x1000);

  // test timer
  TRISCbits.TRISC9 = 0;

  // period will have to be adjusted for pleasing user experience
  Timer2.Set(&Timer2, TCON, 0x10);
  Timer2.Set(&Timer2, TPERIOD, 0x1000);

  Timer3.Set(&Timer3, TCON, 0x10);
  Timer3.Set(&Timer3, TPERIOD, 0x3F0);
}

void Initialize()
{
  InitLeds();
  InitSwitches();
  InitTimers();
  //InitPWM();
  InitSPI();
}

void Execute()
{
  Timer1.Execute(&Timer1, TSTART);
  Timer1.Set(&Timer1, TISR, 1);
  Timer2.Execute(&Timer2, TSTART);
  Timer2.Set(&Timer2, TISR, 1);
  Timer3.Set(&Timer3, TISR, 1);
  TestLED();
  while (1)
  {
    // main loop
  }
}

unsigned int LastRCON __attribute__ ((persistent));
unsigned int nextColumn;
unsigned int nextRow;

/*
 * 
 */
int main()
{
  LastRCON = RCON;
  RCON = 0;
  AD1PCFGL = 0xFFFF; /*Ensure AN pins are digital */

  //InitPWMPins();

  nextColumn = 0;
  nextRow = 0;
  // Disable Watch Dog Timer
  RCONbits.SWDTEN = 0;

  // Clock switch to incorporate PLL
  // Initiate Clock Switch to FRC with PLL (NOSC=0b001)
  __builtin_write_OSCCONH(0x01);
  __builtin_write_OSCCONL(0x01); // Start clock switching

  // Wait for Clock switch to occur
  while (OSCCONbits.COSC != 0b001);

  // Wait for PLL to lock
  while (OSCCONbits.LOCK != 1);

  PowerManager(POWER_ON);



  Initialize();
  Execute();

  // just in case we return from execute(), power down
  PowerManager(POWER_OFF);
  while (1)
    ;

  return (EXIT_SUCCESS);
}



void NextLedColumn(void const * instance)
{
  switch(nextColumn)
  {
    case 0:
      Cathode4.Set(&Cathode4,PIN_LOW);
      Cathode1.Set(&Cathode1,PIN_HIGH);
      nextColumn++;
    break;
    case 1:
      Cathode1.Set(&Cathode1,PIN_LOW);
      Cathode2.Set(&Cathode2,PIN_HIGH);
      nextColumn++;
      break;
    case 2:
      Cathode2.Set(&Cathode2,PIN_LOW);
      Cathode3.Set(&Cathode3,PIN_HIGH);
      nextColumn++;
      break;
    case 3:
      Cathode3.Set(&Cathode3,PIN_LOW);
      Cathode4.Set(&Cathode4,PIN_HIGH);
      nextColumn++;
      break;
    default:
      InitCathodes();
      nextColumn = 0;
      break;
  }
}

void NextLedRow(void const * instance)
{
  pLED_t * pRow;

  switch(nextColumn)
  {
    case 0: pRow = LedColum1; break;
    case 1: pRow = LedColum2; break;
    case 2: pRow = LedColum3; break;
    case 3: pRow = LedColum4; break;
    default: pRow = LedColum1; break;
  }

  switch(nextRow)
  {
    case 0:
      nextRow++;
      break;
    case 1:
      pRow += 3;
      nextRow++;
      break;
    case 2:
      pRow += 6;
      nextRow++;
      break;
    case 3:
      pRow += 9;
      nextRow++;
      break;
    default :
      nextRow = 0;
      break;
  }

  (*pRow)->Output(*pRow);
  pRow++;
  (*pRow)->Output(*pRow);
  pRow++;
  (*pRow)->Output(*pRow);
}