
 /*
 *
 */
#include <xc.h>

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
            *(This->base +4) = value;
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
    }
    return retValue;
}


Pwm_t pwm1 = {&OC1CON1, &Set, &Get};
Pwm_t pwm2 = {&OC2CON1, &Set, &Get};
Pwm_t pwm3 = {&OC3CON1, &Set, &Get};
Pwm_t pwm4 = {&OC4CON1, &Set, &Get};

#if 0
  #define  PWM_PERIOD 62500
  void
  PwmInit(
      void
     )
  {
      /* Unmap RP31(RF13) */
      RPOR15bits.RP31R = 0;

      /* Drive RF13 low and make it an output */
      LATFbits.LATF13 = 0;
      TRISFbits.TRISF13 = 0;
      Nop();

      /* Reset PWM */
      OC1CON1 = 0x0000;
      OC1CON2 = 0x0000;

      /* set PWM duty cycle to 50% */
      OC1R    = PWM_PERIOD >> 1; /* set the duty cycle tp 50% */
      OC1RS   = PWM_PERIOD - 1;  /* set the period */

      /* configure PWM */
      OC1CON2 = 0x001F;   /* Sync with This OC module                               */
      OC1CON1 = 0x1C08;   /* Clock sourc Fcyc, trigger mode 1, Mode 0 (disable OC1) */

      /* enable the PWM */
      OC1CON1 = OC1CON1 | 0x0006;   /* Mode 6, Edge-aligned PWM Mode */

      /* Make pin RP31(RF13) OC1 (PWM output) */
      RPOR15bits.RP31R = 18;

  }


#endif

