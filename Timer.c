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
#include "BitOperations.h"
#include "UnitTest.h"

// forward reference
void ShutDown(void const * instance);

CallBackList mListTimer1[2] = {
{SampleSwitches, NULL},
{NULL,NULL}
};

CallBackList mListTimer3[2] = {
{ShutDown,NULL},
{NULL,NULL}
};

CallBackList mListTimer2[1] = {{NULL,NULL}};

// this is probably not a runtime operation, so we can do a little more processing
static void SetTimerIsrPriority(pTimer_t This, unsigned int priority)
{
    priority = priority & 0x7;

    if(This->TimerBase == &TMR1)
    {
        IPC0bits.T1IP = priority;
    }
    else if(This->TimerBase == &TMR2)
    {
        IPC1bits.T2IP = priority;
    }
    else if(This->TimerBase == &TMR3)
    {
        IPC2bits.T3IP = priority;
    }
    else if(This->TimerBase == &TMR4)
    {
        IPC6bits.T4IP = priority;
    }
    else if(This->TimerBase == &TMR5)
    {
        IPC7bits.INT2IP = priority;
    }
}

static unsigned int GetTimerIsrPriority(pTimer_t This)
{
    unsigned int retValue = 0;

    if(This->TimerBase == &TMR1)
    {
        retValue = IPC0bits.T1IP;
    }
    else if(This->TimerBase == &TMR2)
    {
        retValue = IPC1bits.T2IP;
    }
    else if(This->TimerBase == &TMR3)
    {
        retValue = IPC2bits.T3IP;
    }
    else if(This->TimerBase == &TMR4)
    {
        retValue = IPC6bits.T4IP;
    }
    else if(This->TimerBase == &TMR5)
    {
        retValue = IPC7bits.INT2IP;
    }
    return retValue;
}

static bool Set(pTimer_t This, TimerReg_t timerReg, unsigned int value) {
//  assert (This->mTimer == &T1CON || This->mTimer == &T2CON || This->mTimer == &T3CON)

    switch (timerReg) {
        case TCON:
            *This->TimerBase = value;
            break;
        case TPERIOD:
            *This->Period = value;
            break;
        case TTIME:
            *This->Time = value;
            break;
        case TISR:
            if(value == 0)
                *(This->interruptEnable) &= ~This->mask;
            else
                *(This->interruptEnable) |= This->mask;
            break;
        case TISRPRIORITY:
            SetTimerIsrPriority(This, value);
            break;
    }
    return true;
}

static unsigned int Get(pTimer_t This, TimerReg_t timerReg)
{
    unsigned int retValue = ~0;
    switch(timerReg)
    {
        case TCON :
            retValue = *This->TimerBase;
            break;
        case TPERIOD :
            retValue = *This->Period;
            break;
        case TTIME :
            retValue = *This->Time;
            break;
        case TISR :
            retValue = *(This->interruptEnable) & This->mask;
            retValue = (retValue) ? 1 : 0;
            break;
        case TISRPRIORITY:
            retValue = GetTimerIsrPriority(This);
            break;
    }
    return retValue;
}

static void Execute(pTimer_t This, TimerExecute_t timerexe)
{
  if (timerexe == TSTART)
    *This->TimerBase |= BIT(15);
  if (timerexe == TSTOP)
    *This->TimerBase &= ~BIT(15);
}
  
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
  CallBackList *list = mListTimer1;

  while(list != NULL && list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    if(list)list++;
  }
  _T1IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
  CallBackList *list = mListTimer2;


  LATAbits.LATA0 ^= 1;
  while(list != NULL && list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    list++;
  }  
  _T2IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
  CallBackList *list = mListTimer3;

  while(list != NULL && list->CallBack != NULL)
  {
    list->CallBack(list->instance);
    list++;
  }
  _T3IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
{
  // defensive, if this vector is ever hit then disable it
  _T4IE = 0;
  _T4IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{
  // defensive, if this vector is ever hit then disable it
  _T5IE = 0;
  _T5IF = 0;
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

Timer_t Timer1 = {&T1CON, &PR1, &TMR1, &IEC0, BIT(3), Set, Get, Execute};
Timer_t Timer2 = {&T2CON, &PR2, &TMR2, &IEC0, BIT(7), Set, Get, Execute};
Timer_t Timer3 = {&T3CON, &PR3, &TMR3, &IEC0, BIT(8), Set, Get, Execute};
Timer_t Timer4 = {&T4CON, &PR4, &TMR4, &IEC1, BIT(11), Set, Get, Execute};
Timer_t Timer5 = {&T5CON, &PR5, &TMR5, &IEC1, BIT(12), Set, Get, Execute};



//{HeartBeatCallBack,&HeartBeat},

#if UNIT_TESTS == 1

UnitTestResult_t UnitTestTimerRegisters()
{
        // test setting registers
    unsigned int setValue;
    unsigned int getValue;

    setValue = 0x1000;
    Timer1.Set(&Timer1, TCON, setValue);
    getValue = Timer1.Get(&Timer1, TCON);
    if(setValue != getValue)
        return UnitTestFail;

    Timer1.Set(&Timer1, TPERIOD, setValue);
    getValue = Timer1.Get(&Timer1, TPERIOD);
    if(setValue != getValue)
        return UnitTestFail;

    Timer1.Set(&Timer1, TTIME, setValue);
    getValue = Timer1.Get(&Timer1, TTIME);
    if(setValue != getValue)
        return UnitTestFail;
    
    return UnitTestSuccess;
}

void DoAllTimerTests()
{
    UnitTestResult_t didFail;

    didFail = UnitTestTimerRegisters();
    if(didFail == UnitTestFail)
        while(1)
            Nop(); // some instruction to set break point

    // TODO add more tests
}
#endif