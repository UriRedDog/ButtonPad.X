
 /*
 ** file: main.c
 ** target: PIC24FJ256GB110
 ** compiler: C30 version 3.11
 ** IDE: MPLAB 8.30
 **
 ** This works in the real hardware but the
 ** PWM does not work in the simulator.
 */

#if 0
  #define  PWM_PERIOD 62500
  void
  PwmInit(
      void
     )
  {
      /* Unmap RP31(RF13) */
      RPOR15bits.RP31R = 0;

      /* Drive RF13 low and make it an output */
      LATFbits.LATF13 = 0;
      TRISFbits.TRISF13 = 0;
      Nop();

      /* Reset PWM */
      OC1CON1 = 0x0000;
      OC1CON2 = 0x0000;

      /* set PWM duty cycle to 50% */
      OC1R    = PWM_PERIOD >> 1; /* set the duty cycle tp 50% */
      OC1RS   = PWM_PERIOD - 1;  /* set the period */

      /* configure PWM */
      OC1CON2 = 0x001F;   /* Sync with This OC module                               */
      OC1CON1 = 0x1C08;   /* Clock sourc Fcyc, trigger mode 1, Mode 0 (disable OC1) */

      /* enable the PWM */
      OC1CON1 = OC1CON1 | 0x0006;   /* Mode 6, Edge-aligned PWM Mode */

      /* Make pin RP31(RF13) OC1 (PWM output) */
      RPOR15bits.RP31R = 18;

  }

  int
  main(
      void
      )
  {

      CLKDIV =  0; /* set for default clock operations Fcyc = 4MHz */
      AD1PCFGL = 0xffff;
      AD1PCFGH = 0x0003;

      PwmInit();
      for( ; ; );     /* hang here forever */
      return 0;
  }
#endif

