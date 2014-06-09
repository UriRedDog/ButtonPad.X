/* 
 * File:   PWM.h
 * Author: dthedens
 *
 * Created on June 6, 2014, 2:33 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum _PWM_REGISTER { OCCON1 = 0, OCCON2, OCRS, OCR, OCTMR } PwmReg_t;
struct _PWM;
typedef struct _PWM const Pwm_t;
typedef Pwm_t const * pPwm_t ;


typedef void (*P_Set)(pPwm_t This, PwmReg_t reg, unsigned int value);
typedef unsigned int (*P_Get)(pPwm_t This, PwmReg_t reg);


struct _PIN {
  volatile unsigned int *base;
  P_Set Set;
  P_Get Get;
};


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

