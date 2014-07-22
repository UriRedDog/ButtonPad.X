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
typedef void (*L_Output)(pLED_t This);

struct _LED
{
    LEDState_t * state;
    pPin_t anode;
    L_Set Set;
    L_Output Output;
};

// 48 LEDs in total
extern LED_t Red1C1;
extern LED_t Red1C2;
extern LED_t Red1C3;
extern LED_t Red1C4;

extern LED_t Blue1C1;
extern LED_t Blue1C2;
extern LED_t Blue1C3;
extern LED_t Blue1C4;

extern LED_t Green1C1;
extern LED_t Green1C2;
extern LED_t Green1C3;
extern LED_t Green1C4;

extern LED_t Red2C1;
extern LED_t Red2C2;
extern LED_t Red2C3;
extern LED_t Red2C4;

extern LED_t Blue2C1;
extern LED_t Blue2C2;
extern LED_t Blue2C3;
extern LED_t Blue2C4;

extern LED_t Green2C1;
extern LED_t Green2C2;
extern LED_t Green2C3;
extern LED_t Green2C4;

extern LED_t Red3C1;
extern LED_t Red3C2;
extern LED_t Red3C3;
extern LED_t Red3C4;

extern LED_t Blue3C1;
extern LED_t Blue3C2;
extern LED_t Blue3C3;
extern LED_t Blue3C4;

extern LED_t Green3C1;
extern LED_t Green3C2;
extern LED_t Green3C3;
extern LED_t Green3C4;

extern LED_t Red4C1;
extern LED_t Red4C2;
extern LED_t Red4C3;
extern LED_t Red4C4;

extern LED_t Blue4C1;
extern LED_t Blue4C2;
extern LED_t Blue4C3;
extern LED_t Blue4C4;

extern LED_t Green4C1;
extern LED_t Green4C2;
extern LED_t Green4C3;
extern LED_t Green4C4;

extern void InitLeds();

extern pLED_t LedColum1[12];
extern pLED_t LedColum2[12];
extern pLED_t LedColum3[12];
extern pLED_t LedColum4[12];

#ifdef	__cplusplus
}
#endif

#endif	/* LEDPINS_H */

