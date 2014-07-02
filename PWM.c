
 /*
  * PWM.c
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
  *
  * object for pulse with modulation.
 */
#include <xc.h>
#include "BitOperations.h"
#include "PWM.h"
#include "UnitTest.h"

static void Set(pPwm_t This, PwmReg_t reg, unsigned int value)
{
    switch(reg)
    {
        case OCCON1:
            *This->base = value;
            break;
        case OCCON2 :
            *(This->base +1) = value;
            break;
        case OCRS :
            *(This->base +2) = value;
            break;
        case OCR :
            *(This->base +3) = value;
            break;
        case OCTMR :
            // this is read only
            break;
        case OCISR:
            // set or clear the interrupt enable, 0 == clear
            if (value == 0)
                *(This->interruptEnable) &= ~This->bitMask;
            else
                *(This->interruptEnable) |= This->bitMask;
            break;
    }
}


static unsigned int Get(pPwm_t This, PwmReg_t reg)
{
    unsigned int retValue = ~0;
    switch(reg)
    {
        case OCCON1:
            retValue = *This->base;
            break;
        case OCCON2 :
            retValue = *(This->base +1);
            break;
        case OCRS :
            retValue = *(This->base +2);
            break;
        case OCR :
            retValue = *(This->base +3);
            break;
        case OCTMR :
            retValue = *(This->base +4);
            break;
        case OCISR :
            retValue = *(This->interruptEnable) & This->bitMask;
            retValue = (retValue) ? 1 : 0;
            break;
    }
    return retValue;
}


Pwm_t pwm1 = {&OC1CON1, &IEC0, BIT(2), &Set, &Get};
Pwm_t pwm2 = {&OC2CON1, &IEC0, BIT(6), &Set, &Get};
Pwm_t pwm3 = {&OC3CON1, &IEC1, BIT(9), &Set, &Get};
Pwm_t pwm4 = {&OC4CON1, &IEC1, BIT(10), &Set, &Get};
//Pwm_t pwm5 = {&OC5CON1, &IEC2, BIT(9), &Set, &Get};  // we do not need 5



void __attribute__((__interrupt__, no_auto_psv)) _OC1Interrupt(void)
{
  _OC1IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _OC2Interrupt(void)
{
  _OC2IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _OC3Interrupt(void)
{
  _OC3IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _OC4Interrupt(void)
{
  _OC4IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _OC5Interrupt(void)
{
  _OC5IF = 0;
}


#if UNIT_TESTS == 1




UnitTestResult_t UnitTestPwmRegisters()
{
    // test setting registers
    unsigned int setValue;
    unsigned int getValue;

    setValue = 1000;
    pwm1.Set(&pwm1, OCCON1, setValue);
    getValue = pwm1.Get(&pwm1, OCCON1);
    if(setValue != getValue)
        return UnitTestFail;

    pwm1.Set(&pwm1, OCCON2, setValue);
    getValue = pwm1.Get(&pwm1, OCCON2);
    if(setValue != getValue)
        return UnitTestFail;

    pwm1.Set(&pwm1, OCRS, setValue);
    getValue = pwm1.Get(&pwm1, OCRS);
    if(setValue != getValue)
        return UnitTestFail;

    pwm1.Set(&pwm1, OCR, setValue);
    getValue = pwm1.Get(&pwm1, OCR);
    if(setValue != getValue)
        return UnitTestFail;

    pwm1.Set(&pwm1, OCTMR, setValue);
    getValue = pwm1.Get(&pwm1, OCTMR);
    if(setValue != getValue)
        return UnitTestFail;

    setValue = 1;
    pwm1.Set(&pwm1, OCISR, setValue);
    getValue = pwm1.Get(&pwm1, OCISR);
    if(setValue != getValue)
        return UnitTestFail;
    pwm1.Set(&pwm1, OCISR, 0);

    return UnitTestSuccess;
}

void DoAllPwmTests()
{
    UnitTestResult_t didFail;

    didFail = UnitTestPwmRegisters();
    if(didFail == UnitTestFail)
        while(1)
            Nop(); // some instruction to set break point

    // TODO add more tests
}


#endif
