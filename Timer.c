/*
 * Timer.c
 * Flash resedent Timer objects.
 * The callback list is defined as a static fixed size array
 * and is a compile time list.
 *
*/

#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Switch.h"
#include "Timer.h"

#define BIT(a) (1 <<(a))

CallBackList mListTimer1[2];
CallBackList mListTimer2[2]; 
CallBackList mListTimer3[2] = {{NULL,NULL},{NULL,NULL}};


static bool Set(pTimer_t This, TimerSet_t timerset, unsigned int val) {
//  assert (This->mTimer == &T1CON || This->mTimer == &T2CON || This->mTimer == &T3CON)

    switch (timerset) {
        case TxCON:
            *This->TimerBase = val;
            break;
        case TxPERIOD:
            *This->Period = val;
            break;
        case TxTIME:
            *This->Time = val;
            break;
        case TxISR:
            if (This->TimerBase == &T1CON)
            {
                if (val) IEC0bits.T1IE = 1;
                else IEC0bits.T1IE = 0;
            }
            else if (This->TimerBase == &T2CON)
            {
                if (val) IEC0bits.T2IE = 1;
                else IEC0bits.T2IE = 0;
            }
            else if (This->TimerBase == &T3CON)
            {
                if (val) IEC0bits.T3IE = 1;
                else IEC0bits.T3IE = 0;
            }
            else if (This->TimerBase == &T4CON)
            {
                if (val) IEC1bits.T4IE = 1;
                else IEC1bits.T4IE = 0;
            }
            else if (This->TimerBase == &T5CON)
            {
                if (val) IEC1bits.T5IE = 1;
                else IEC1bits.T5IE = 0;
            }
            else
                return false;
            break;
        case TxISRPRIORITY:
            break; // not used
    }
    return true;
}

static unsigned int Get(pTimer_t This, TimerSet_t timerset)
{
    if(timerset == TxCON)
      return *This->TimerBase;
    if(timerset == TxPERIOD)
      return *This->Period;
    if(timerset == TxTIME)
      return *This->Time;
    return 0;
}

static void Execute(pTimer_t This, TimerExecute_t timerexe)
{
  if (timerexe == TxSTART)
    *This->TimerBase |= BIT(15);
  if (timerexe == TxSTOP)
    *This->TimerBase &= ~BIT(15);
}
  
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
  CallBackList *list = mListTimer1;

  while(list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    if(list)list++;
  }
  _T1IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
  CallBackList *list = mListTimer2;

  while(list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    list++;
  }  
  _T2IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
  CallBackList *list = mListTimer3;

  while(list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    list++;
  }
  _T3IF = 0;
}

static int ShutDownCount = 0;
void ShutDown(void const * instance)
{
    extern void PowerManager(int);
    extern volatile int Activity;
    if (Activity)
    {
        Activity = 0;
        ShutDownCount = 0;
    }
    if (ShutDownCount++ == 5)
        PowerManager(0);
}

Timer_t Timer1 = {&T1CON, &PR1, &TMR1, Set, Get, Execute};
Timer_t Timer2 = {&T2CON, &PR2, &TMR2, Set, Get, Execute};
Timer_t Timer3 = {&T3CON, &PR3, &TMR3, Set, Get, Execute};
Timer_t Timer4 = {&T4CON, &PR4, &TMR4, Set, Get, Execute};
Timer_t Timer5 = {&T5CON, &PR5, &TMR5, Set, Get, Execute};

CallBackList mListTimer1[2] = {
{SampleSwitches, NULL},
{NULL,NULL}
};

CallBackList mListTimer2[2] = {
{ShutDown,NULL},
{NULL,NULL}
};

//{HeartBeatCallBack,&HeartBeat},