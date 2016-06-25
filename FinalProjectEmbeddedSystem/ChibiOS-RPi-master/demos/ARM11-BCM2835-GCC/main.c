/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    CORREOS:
    jesshack10@gmail.com
    evamargarita.villarreal@gmail.com
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "shell.h"
#include "chprintf.h"
#include "chsem.h"

#define TEST_WA_SIZE        THD_WA_SIZE(4096)

static SEMAPHORE_DECL(mySemaphore,0); 

/*
*This is the main thread, it recieves information 
*of the IO ports and sends a message to the corresponding
*IO port, in order to turn on or off the devices attached to it.
*/

static WORKING_AREA(waTh1, 128);
static msg_t Th1(void *p) {
  (void)p;
  chRegSetThreadName("Th1");

  while (TRUE) {

  	/////DEVICE 1///////////
    if(palReadPad(GPIO4_PORT, GPIO4_PAD) == PAL_HIGH)
    {
      palWritePad(GPIO22_PORT,GPIO22_PAD,PAL_HIGH);

      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "1ON\r\n");
      chSemSignal(&mySemaphore);

    }else{
      palWritePad(GPIO22_PORT,GPIO22_PAD,PAL_LOW);
      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "1OFF\r\n");
      chSemSignal(&mySemaphore);
    }

     chThdSleepMilliseconds(1000);
  }

  return 0;

}

static WORKING_AREA(waTh2, 128);
static msg_t Th2(void *p) {
  (void)p;
  chRegSetThreadName("Th2");

  while (TRUE) {

  	/////DEVICE 1///////////
    if(palReadPad(GPIO17_PORT, GPIO17_PAD) == PAL_HIGH)
    {
      palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);

      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "2ON\r\n");
      chSemSignal(&mySemaphore);

    }else{
      palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);
      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "2OFF\r\n");
      chSemSignal(&mySemaphore);
    }

     chThdSleepMilliseconds(1000);
  }

  return 0;

}

static WORKING_AREA(waTh3, 128);
static msg_t Th3(void *p) {
  (void)p;
  chRegSetThreadName("Th3");

  while (TRUE) {

  	/////DEVICE 1///////////
    if(palReadPad(GPIO18_PORT, GPIO18_PAD) == PAL_HIGH)
    {
      palWritePad(GPIO24_PORT,GPIO24_PAD,PAL_HIGH);

      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "3ON\r\n");
      chSemSignal(&mySemaphore);

    }else{
      palWritePad(GPIO24_PORT,GPIO24_PAD,PAL_LOW);
      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "3OFF\r\n");
      chSemSignal(&mySemaphore);
    }

     chThdSleepMilliseconds(1000);
  }

  return 0;

}

static WORKING_AREA(waTh4, 128);
static msg_t Th4(void *p) {
  (void)p;
  chRegSetThreadName("Th4");

  while (TRUE) {

  	/////DEVICE 1///////////
    if(palReadPad(GPIO21_PORT, GPIO21_PAD) == PAL_HIGH)
    {
      palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_HIGH);

      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "4ON\r\n");
      chSemSignal(&mySemaphore);

    }else{
      palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_LOW);
      chSemWait(&mySemaphore);
      	chprintf((BaseSequentialStream *)&SD1, "4OFF\r\n");
      chSemSignal(&mySemaphore);
    }

     chThdSleepMilliseconds(1000);
  }

  return 0;

}

/*
 * Application entry point.
 */
int main(void) {
  halInit();
  chSysInit();

  /*
   * Serial port initialization.
   */
  sdStart(&SD1, NULL); 
  chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");

   /*
  *Semaphore Initialization
  */
  chSemInit(&mySemaphore, 1);

  /*
   * Set mode of PINES
   */


  palSetPadMode(GPIO4_PORT, GPIO4_PAD, PAL_MODE_INPUT);   //Input T1
  palSetPadMode(GPIO17_PORT, GPIO17_PAD, PAL_MODE_INPUT); //Input T2
  palSetPadMode(GPIO18_PORT, GPIO0_PAD, PAL_MODE_INPUT);   //Input T3
  palSetPadMode(GPIO21_PORT, GPIO21_PAD, PAL_MODE_INPUT);   //Input T4
  
  palSetPadMode(GPIO22_PORT, GPIO22_PAD, PAL_MODE_OUTPUT); //Output T1
  palSetPadMode(GPIO23_PORT, GPIO23_PAD, PAL_MODE_OUTPUT); //Output T2
  palSetPadMode(GPIO24_PORT, GPIO24_PAD, PAL_MODE_OUTPUT); //Output T3
  palSetPadMode(GPIO25_PORT, GPIO25_PAD, PAL_MODE_OUTPUT); //Output T4
  
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waTh1, sizeof(waTh1), NORMALPRIO, Th1, NULL);
  chThdCreateStatic(waTh2, sizeof(waTh2), NORMALPRIO, Th2, NULL);
  chThdCreateStatic(waTh3, sizeof(waTh3), NORMALPRIO, Th3, NULL);
  chThdCreateStatic(waTh4, sizeof(waTh4), NORMALPRIO, Th4, NULL);
  
  /*
   * Events servicing loop.
   */
  chThdWait(chThdSelf());

  return 0;
}