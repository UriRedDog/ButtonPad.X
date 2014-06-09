/* 
 * File:   Pin.h
 * Author: dthedens
 *
 * Created on June 4, 2014, 2:22 PM
 */

#ifndef PIN_H
#define	PIN_H

#ifdef	__cplusplus
extern "C" {
#endif



typedef enum _PIN_MODE { PIN_OUTPUT = 0, PIN_INPUT, PIN_INPUT_PULLUP } PinMode_t;
typedef enum _PIN_STATE { PIN_LOW = 0, PIN_HIGH } PinState_t;
struct _PIN;
typedef struct _PIN const Pin_t;
typedef Pin_t const * pPin_t ;


typedef void (*P_SetMode)(pPin_t This, PinMode_t newMode);
typedef PinState_t (*P_Get)(pPin_t This);
typedef void (*P_Set)(pPin_t This, PinState_t newState);

struct _PIN {
  unsigned int mMask;
  volatile unsigned int *mpLat;
  P_SetMode SetMode;
  P_Set Set;
  P_Get Get;
};

// pins for LEDs
extern Pin_t Cathode1;
extern Pin_t Cathode1;
extern Pin_t Cathode1;
extern Pin_t Cathode1;

extern Pin_t AnodeRed1;
extern Pin_t AnodeGreen1;
extern Pin_t AnodeBlue1;

extern Pin_t AnodeRed2;
extern Pin_t AnodeGreen2;
extern Pin_t AnodeBlue2;

extern Pin_t AnodeRed3;
extern Pin_t AnodeGreen3;
extern Pin_t AnodeBlue3;

extern Pin_t AnodeRed4;
extern Pin_t AnodeGreen4;
extern Pin_t AnodeBlue4;

// pins for switches
extern Pin_t Row1;
extern Pin_t Row2;
extern Pin_t Row3;
extern Pin_t Row4;
extern Pin_t Col1;
extern Pin_t Col2;
extern Pin_t Col3;
extern Pin_t Col4;

extern Pin_t PowerPin;

extern void InitPins();

#ifdef	__cplusplus
}
#endif

#endif	/* PIN_H */

