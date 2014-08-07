ButtonPad.X
===========

PIC24F to control Sparkfun 4x4 RGB  LED push button pad

This gets difficult.
The device is wired in such a way that it needs some sort of controller to
provide individual LED control.  One cannot just ground LED-GRD[1-4] because setting
RED4 high would light all the red LED in the row.  Something similar occurs with the columns.
We also need to limit the total current provided by the controller.  All the LED cannot
be on at the same time, even with current limiting resistors, it will exceed the total current.

Each LED must contain it's ON/OFF state.  When column 1 is selected, each LED object
in the column is called to set the LED anode to the correct state.  After a period of time,
the LED is deselected and the next LED is selected.  Once all the LED objects are called
the LED-GRD[] pin is set high and the next LED-GRN[] is selected.  Repeat.
We will use two timers, one to select a column and one to cycle though each LED in that column.

the controller must also have a 2N7002 FET attached to each LED-GRD.  A simple pin cannot sink
the total amount of current of 12 LED.
