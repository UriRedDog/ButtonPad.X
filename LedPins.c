
#include "p24fxxxx.h"
#include "Pin.h"
#include "LedPins.h"

#define BIT(a) (1 <<(a))

static void Set(pLED_t This, LEDState_t newState)
{
    pPin_t anode = This->anode;

    switch(newState)
    {
    case LED_OFF :
        anode->Set(anode, PIN_LOW);
        break;

    case LED_ON :
        anode->Set(anode, PIN_HIGH);
        break;
    }
}


LED_t Red1 =     {&AnodeRed1, Set};
LED_t Green1 =   {&AnodeGreen1, Set};
LED_t Blue1 =    {&AnodeBlue1, Set};

LED_t Red2 =     {&AnodeRed2, Set};
LED_t Green2 =   {&AnodeGreen2, Set};
LED_t Blue2 =    {&AnodeBlue2, Set};

LED_t Red3 =     {&AnodeRed3, Set};
LED_t Green3 =   {&AnodeGreen3, Set};
LED_t Blue3 =    {&AnodeBlue3, Set};

LED_t Red4 =     {&AnodeRed4, Set};
LED_t Green4 =   {&AnodeGreen4, Set};
LED_t Blue4 =    {&AnodeBlue4, Set};

void InitLeds()
{
    Red1.anode->SetMode(Red1.anode, PIN_OUTPUT);
    Red1.Set(&Red1, LED_OFF);
    Red2.anode->SetMode(Red2.anode, PIN_OUTPUT);
    Red2.Set(&Red2, LED_OFF);
    Red3.anode->SetMode(Red3.anode, PIN_OUTPUT);
    Red3.Set(&Red3, LED_OFF);
    Red4.anode->SetMode(Red4.anode, PIN_OUTPUT);
    Red4.Set(&Red4, LED_OFF);

    Green1.anode->SetMode(Green1.anode, PIN_OUTPUT);
    Green1.Set(&Green1, LED_OFF);
    Green2.anode->SetMode(Green2.anode, PIN_OUTPUT);
    Green2.Set(&Green2, LED_OFF);
    Green3.anode->SetMode(Green1.anode, PIN_OUTPUT);
    Green3.Set(&Green3, LED_OFF);
    Green4.anode->SetMode(Green4.anode, PIN_OUTPUT);
    Green4.Set(&Green4, LED_OFF);

    Blue1.anode->SetMode(Blue1.anode, PIN_OUTPUT);
    Blue1.Set(&Blue1, LED_OFF);
    Blue2.anode->SetMode(Blue2.anode, PIN_OUTPUT);
    Blue2.Set(&Blue3, LED_OFF);
    Blue3.anode->SetMode(Blue3.anode, PIN_OUTPUT);
    Blue3.Set(&Blue3, LED_OFF);
    Blue4.anode->SetMode(Blue4.anode, PIN_OUTPUT);
    Blue4.Set(&Blue4, LED_OFF);
}