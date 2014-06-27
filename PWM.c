
 /*
 *
 */
#include <xc.h>
#include "BitOperations.h"
#include "PWM.h"

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
        case OCxISR:
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
    unsigned int retValue = 0;
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
        case OCxISR :
            retValue = *(This->interruptEnable) & This->bitMask;
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
