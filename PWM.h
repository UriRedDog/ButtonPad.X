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

typedef enum _PWM_REGISTER { OCCON1 = 0, OCCON2, OCRS, OCR, OCTMR, OCxISR } PwmReg_t;
struct _PWM;
typedef struct _PWM const Pwm_t;
typedef Pwm_t const * pPwm_t ;


typedef void (*PW_Set)(pPwm_t This, PwmReg_t reg, unsigned int value);
typedef unsigned int (*PW_Get)(pPwm_t This, PwmReg_t reg);


struct _PWM {
  volatile unsigned int *base;
  PW_Set Set;
  PW_Get Get;
};

extern Pwm_t pwm1;
extern Pwm_t pwm2;
extern Pwm_t pwm3;
extern Pwm_t pwm4;

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

