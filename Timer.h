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

typedef enum _TIMERSET { TxCON = 0, TxPERIOD, TxTIME, TxISR, TxISRPRIORITY } TimerSet_t;
typedef enum _TIMEREXE { TxSTART = 0, TxSTOP} TimerExecute_t;
typedef bool (*T_Set) (pTimer_t This, TimerSet_t timerset, unsigned int val);
typedef unsigned int (*T_Get) (pTimer_t This, TimerSet_t timerset);
typedef void (*T_Execute) (pTimer_t This, TimerExecute_t timerexe);
typedef void (*T_CallBack)(void const * instance);

typedef struct _CallBackList
{
  T_CallBack CallBack;
  void const * instance;
} CallBackList;

struct _TIMER {
  volatile unsigned int * TimerBase;
  volatile unsigned int * Period;
  volatile unsigned int * Time;
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

