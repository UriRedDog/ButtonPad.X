/* 
 * File:   SPI.h
 * Author: dthedens
 *
 * The PIC24 is a secondary processor that controls all the LEDs and reads the switches.
 * The host cpu will communicate with the secondary processor.
 * that means we have to have to have communication protocol.
 *
 * The first byte of each SPI message is the command byte.
 *
 *
 * Created on June 13, 2014, 3:53 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum _COMMAND
{

}commands_t;



#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

