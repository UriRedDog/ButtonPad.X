/* 
 * File:   LedPins.h
 * Author: dthedens
 *
 * Created on June 4, 2014, 2:29 PM
 */

#ifndef LEDPINS_H
#define	LEDPINS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Pin.h"
struct _LED;
typedef struct _LED const LED_t;
typedef LED_t const * pLED_t;
typedef enum _LEDSTATE { LED_ON = 0, LED_OFF } LEDState_t;
typedef void (*L_Set)(pLED_t This, LEDState_t newState);

struct _LED
{
    pPin_t anode;
    L_Set Set;
};

extern LED_t Red1;
extern LED_t Blue1;
extern LED_t Green1;

extern LED_t Red2;
extern LED_t Blue2;
extern LED_t Green2;

extern LED_t Red3;
extern LED_t Blue3;
extern LED_t Green3;

extern LED_t Red4;
extern LED_t Blue4;
extern LED_t Green4;

extern void InitLeds();

#ifdef	__cplusplus
}
#endif

#endif	/* LEDPINS_H */

