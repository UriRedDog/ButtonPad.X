/* 
 * File:   Switch.h
 * Author: dthedens
 *
 * Switches for the 4x4 pad have a row and a column.
 * It is helpful to print the schematic and then rotate it 90 degrees.
 * the rows are ;ab;ed SWT-GND[1-4], the columns are SWITCH[1-4]E
 * the column is a duplicated in the switch objects, but it is only a small amount of code.
 * The controller will activate a column and scan the rows
 * then move to the next column.  Since the switches might be bouncy, we
 * will need to maintain some state to determine the switch status.
 *
 * This object must expose a timer callback so that the timer ISR can periodicaly
 * call the switch routines
 *
 *
 *
 *
 *
 * http://www.dribin.org/dave/keyboard/one_html/
 *
 * Created on June 4, 2014, 3:39 PM
 */

#ifndef SWITCH_H
#define	SWITCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Pin.h"

typedef enum _SwitchState {SWITCH_ON = 0, SWITCH_OFF, SWITCH_BOUNCE } SwitchState_t;
struct _SWITCH;
typedef struct _SWITCH const Switch_t;
typedef Switch_t const * pSwitch_t;

typedef void (*S_Sample)(pSwitch_t This);
typedef SwitchState_t (*S_GetState)(pSwitch_t This);

struct _SWITCH {
  pPin_t row;
  pPin_t col;
  unsigned int * bounceCount;
  S_Sample Sample;
  S_GetState GetState;
};

extern Switch_t switchR1C1;
extern Switch_t switchR2C1;
extern Switch_t switchR3C1;
extern Switch_t switchR4C1;

extern Switch_t switchR1C2;
extern Switch_t switchR2C2;
extern Switch_t switchR3C2;
extern Switch_t switchR4C2;

extern Switch_t switchR1C3;
extern Switch_t switchR2C3;
extern Switch_t switchR3C3;
extern Switch_t switchR4C3;

extern Switch_t switchR1C4;
extern Switch_t switchR2C4;
extern Switch_t switchR3C4;
extern Switch_t switchR4C4;

//extern pSwitch_t SwitchArray[];

extern void InitSwitches(void);
extern void SampleSwitches(void const * instance);

#ifdef	__cplusplus
}
#endif

#endif	/* SWITCH_H */

