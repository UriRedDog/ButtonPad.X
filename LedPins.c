/*
 * LedPins.c
 *
 * Copyright (c) <2014> <David Thedens, Eric Summers>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 
*/

#include "p24fxxxx.h"
#include "Pin.h"
#include "LedPins.h"

LEDState_t SavedStateArray[48];

// set just sets the saved state
static void SetState(pLED_t This, LEDState_t newState)
{
  *This->state = newState;
}

// this is used to override the the output while maintaining the state
static void Set(pLED_t This, LEDState_t newState)
{
  pPin_t anode = This->anode;

  switch (newState)
  {
    case LED_OFF:
      anode->Set(anode, PIN_LOW);
      break;

    case LED_ON:
      anode->Set(anode, PIN_HIGH);
      break;
  }
}

// this places the LED into the state state
static void Output(pLED_t This)
{
  pPin_t anode = This->anode;

  switch (*This->state)
  {
    case LED_OFF:
      anode->Set(anode, PIN_LOW);
      break;

    case LED_ON:
      anode->Set(anode, PIN_HIGH);
      break;
  }
}


LED_t Red1C1 = {&SavedStateArray[0], &AnodeRed1, Set, SetState, Output};
LED_t Red1C2 = {&SavedStateArray[1], &AnodeRed1, Set, SetState, Output};
LED_t Red1C3 = {&SavedStateArray[2], &AnodeRed1, Set, SetState, Output};
LED_t Red1C4 = {&SavedStateArray[3], &AnodeRed1, Set, SetState, Output};

LED_t Green1C1 = {&SavedStateArray[4], &AnodeGreen1, Set, SetState, Output};
LED_t Green1C2 = {&SavedStateArray[5], &AnodeGreen1, Set, SetState, Output};
LED_t Green1C3 = {&SavedStateArray[6], &AnodeGreen1, Set, SetState, Output};
LED_t Green1C4 = {&SavedStateArray[7], &AnodeGreen1, Set, SetState, Output};

LED_t Blue1C1 = {&SavedStateArray[8], &AnodeBlue1, Set, SetState, Output};
LED_t Blue1C2 = {&SavedStateArray[9], &AnodeBlue1, Set, SetState, Output};
LED_t Blue1C3 = {&SavedStateArray[10], &AnodeBlue1, Set, SetState, Output};
LED_t Blue1C4 = {&SavedStateArray[11], &AnodeBlue1, Set, SetState, Output};

LED_t Red2C1 = {&SavedStateArray[12], &AnodeRed2, Set, SetState, Output};
LED_t Red2C2 = {&SavedStateArray[13], &AnodeRed2, Set, SetState, Output};
LED_t Red2C3 = {&SavedStateArray[14], &AnodeRed2, Set, SetState, Output};
LED_t Red2C4 = {&SavedStateArray[15], &AnodeRed2, Set, SetState, Output};

LED_t Green2C1 = {&SavedStateArray[16], &AnodeGreen2, Set, SetState, Output};
LED_t Green2C2 = {&SavedStateArray[17], &AnodeGreen2, Set, SetState, Output};
LED_t Green2C3 = {&SavedStateArray[18], &AnodeGreen2, Set, SetState, Output};
LED_t Green2C4 = {&SavedStateArray[19], &AnodeGreen2, Set, SetState, Output};

LED_t Blue2C1 = {&SavedStateArray[20], &AnodeBlue2, Set, SetState, Output};
LED_t Blue2C2 = {&SavedStateArray[21], &AnodeBlue2, Set, SetState, Output};
LED_t Blue2C3 = {&SavedStateArray[22], &AnodeBlue2, Set, SetState, Output};
LED_t Blue2C4 = {&SavedStateArray[23], &AnodeBlue2, Set, SetState, Output};

LED_t Red3C1 = {&SavedStateArray[24], &AnodeRed3, Set, SetState, Output};
LED_t Red3C2 = {&SavedStateArray[25], &AnodeRed3, Set, SetState, Output};
LED_t Red3C3 = {&SavedStateArray[26], &AnodeRed3, Set, SetState, Output};
LED_t Red3C4 = {&SavedStateArray[27], &AnodeRed3, Set, SetState, Output};

LED_t Green3C1 = {&SavedStateArray[28], &AnodeGreen3, Set, SetState, Output};
LED_t Green3C2 = {&SavedStateArray[29], &AnodeGreen3, Set, SetState, Output};
LED_t Green3C3 = {&SavedStateArray[30], &AnodeGreen3, Set, SetState, Output};
LED_t Green3C4 = {&SavedStateArray[31], &AnodeGreen3, Set, SetState, Output};

LED_t Blue3C1 = {&SavedStateArray[32], &AnodeBlue3, Set, SetState, Output};
LED_t Blue3C2 = {&SavedStateArray[33], &AnodeBlue3, Set, SetState, Output};
LED_t Blue3C3 = {&SavedStateArray[34], &AnodeBlue3, Set, SetState, Output};
LED_t Blue3C4 = {&SavedStateArray[35], &AnodeBlue3, Set, SetState, Output};

LED_t Red4C1 = {&SavedStateArray[36], &AnodeRed4, Set, SetState, Output};
LED_t Red4C2 = {&SavedStateArray[37], &AnodeRed4, Set, SetState, Output};
LED_t Red4C3 = {&SavedStateArray[38], &AnodeRed4, Set, SetState, Output};
LED_t Red4C4 = {&SavedStateArray[39], &AnodeRed4, Set, SetState, Output};

LED_t Green4C1 = {&SavedStateArray[40], &AnodeGreen4, Set, SetState, Output};
LED_t Green4C2 = {&SavedStateArray[41], &AnodeGreen4, Set, SetState, Output};
LED_t Green4C3 = {&SavedStateArray[42], &AnodeGreen4, Set, SetState, Output};
LED_t Green4C4 = {&SavedStateArray[43], &AnodeGreen4, Set, SetState, Output};

LED_t Blue4C1 = {&SavedStateArray[44], &AnodeBlue4, Set, SetState, Output};
LED_t Blue4C2 = {&SavedStateArray[45], &AnodeBlue4, Set, SetState, Output};
LED_t Blue4C3 = {&SavedStateArray[46], &AnodeBlue4, Set, SetState, Output};
LED_t Blue4C4 = {&SavedStateArray[47], &AnodeBlue4, Set, SetState, Output};

pLED_t LedColumn1[12] =
{
  &Red1C1,
  &Green1C1,
  &Blue1C1,
  &Red2C1,
  &Green2C1,
  &Blue2C1,
  &Red3C1,
  &Green3C1,
  &Blue3C1,
  &Red4C1,
  &Green4C1,
  &Blue4C1,
};

pLED_t LedColumn2[12] =
{
  &Red1C2,
  &Green1C2,
  &Blue1C2,
  &Red2C2,
  &Green2C2,
  &Blue2C2,
  &Red3C2,
  &Green3C2,
  &Blue3C2,
  &Red4C2,
  &Green4C2,
  &Blue4C2,
};

pLED_t LedColumn3[12] =
{
  &Red1C3,
  &Green1C3,
  &Blue1C3,
  &Red2C3,
  &Green2C3,
  &Blue2C3,
  &Red3C3,
  &Green3C3,
  &Blue3C3,
  &Red4C3,
  &Green4C3,
  &Blue4C3,
};

pLED_t LedColumn4[12] =
{
  &Red1C4,
  &Green1C4,
  &Blue1C4,
  &Red2C4,
  &Green2C4,
  &Blue2C4,
  &Red3C4,
  &Green3C4,
  &Blue3C4,
  &Red4C4,
  &Green4C4,
  &Blue4C4,
};

void InitLeds()
{
  Red1C1.anode->SetMode(Red1C1.anode, PIN_OUTPUT);
  Red1C1.Set(&Red1C1, LED_OFF);
  Red2C1.anode->SetMode(Red2C1.anode, PIN_OUTPUT);
  Red2C1.Set(&Red2C1, LED_OFF);
  Red3C1.anode->SetMode(Red3C1.anode, PIN_OUTPUT);
  Red3C1.Set(&Red3C1, LED_OFF);
  Red4C1.anode->SetMode(Red4C1.anode, PIN_OUTPUT);
  Red4C1.Set(&Red4C1, LED_OFF);

  Green1C1.anode->SetMode(Green1C1.anode, PIN_OUTPUT);
  Green1C1.Set(&Green1C1, LED_OFF);
  Green2C1.anode->SetMode(Green2C1.anode, PIN_OUTPUT);
  Green2C1.Set(&Green2C1, LED_OFF);
  Green3C1.anode->SetMode(Green1C1.anode, PIN_OUTPUT);
  Green3C1.Set(&Green3C1, LED_OFF);
  Green4C1.anode->SetMode(Green4C1.anode, PIN_OUTPUT);
  Green4C1.Set(&Green4C1, LED_OFF);

  Blue1C1.anode->SetMode(Blue1C1.anode, PIN_OUTPUT);
  Blue1C1.Set(&Blue1C1, LED_OFF);
  Blue2C1.anode->SetMode(Blue2C1.anode, PIN_OUTPUT);
  Blue2C1.Set(&Blue3C1, LED_OFF);
  Blue3C1.anode->SetMode(Blue3C1.anode, PIN_OUTPUT);
  Blue3C1.Set(&Blue3C1, LED_OFF);
  Blue4C1.anode->SetMode(Blue4C1.anode, PIN_OUTPUT);
  Blue4C1.Set(&Blue4C1, LED_OFF);
}