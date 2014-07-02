/*
 * Timer.h
 *
 * The Timer object is a const (in flash) structure member rather than allocating
 * the object from the heap.  One concern would be that the callback list would have
 * to be static globals within the scope of this object rather than a member variable.
 * we only use 16 bit timers.
 * The stupid timer registers order is all messed up which makes the object
 * larger
 */

#ifndef __TIMER_OBJECT_H_
#define __TIMER_OBJECT_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
struct _TIMER;
typedef struct _TIMER const Timer_t;
typedef Timer_t const * pTimer_t;

typedef enum _TIMERREG { TCON = 0, TPERIOD, TTIME, TISR, TISRPRIORITY } TimerReg_t;
typedef enum _TIMEREXE { TSTART = 0, TSTOP} TimerExecute_t;
typedef bool (*T_Set) (pTimer_t This, TimerReg_t timerReg, unsigned int val);
typedef unsigned int (*T_Get) (pTimer_t This, TimerReg_t timerReg);
typedef void (*T_Execute) (pTimer_t This, TimerExecute_t timerexe);
typedef void (*T_CallBack)(void const * instance);

typedef struct _CallBackList
{
  T_CallBack CallBack;
  void const * instance;
} CallBackList_t;

// timer register address order is all messed up, so we need many members
struct _TIMER {
  volatile unsigned int * TimerBase;
  volatile unsigned int * Period;
  volatile unsigned int * Time;
  volatile unsigned int * interruptEnable;
  unsigned int mask;
  T_Set Set;
  T_Get Get;
  T_Execute Execute;
 };

extern Timer_t Timer1;
extern Timer_t Timer2;
extern Timer_t Timer3;
extern Timer_t Timer4;
extern Timer_t Timer5;


#endif

