/* 
 * File:   Power.h
 * Author: dthedens
 *
 * Created on June 6, 2014, 11:41 AM
 */

#ifndef POWER_H
#define	POWER_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef enum _POWERSTATE
{
  POWER_OFF = 0,
  POWER_ON
} PowerState_t;


extern void PowerManager(PowerState_t state);


#ifdef	__cplusplus
}
#endif

#endif	/* POWER_H */

