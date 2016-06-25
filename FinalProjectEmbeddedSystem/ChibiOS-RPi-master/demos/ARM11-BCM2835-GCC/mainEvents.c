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

static EVENTSOURCE_DECL(esT1);
static EVENTSOURCE_DECL(esT2);
static EVENTSOURCE_DECL(esT3);
static EVENTSOURCE_DECL(esT4);

static MUTEX_DECL(mutex);

unsigned short int Xvalue =  0;

/*
*This is the main thread, it recieves information 
*of the IO ports and sends a message to the corresponding
*IO port, in order to turn on or off the devices attached to it.
*/
static WORKING_AREA(waMainThread, 128);
static msg_t mainThread(void *p) {
  (void)p;
  chRegSetThreadName("mainThread");

  while (TRUE) {
    if(palReadPad(GPIO0_PORT, GPIO0_PAD) == PAL_HIGH)
    {
      chEvtBroadcastFlags(&esT2,ALL_EVENTS);
    }

    if(palReadPad(GPIO1_PORT, GPIO1_PAD) == PAL_HIGH)
    {
      chEvtBroadcastFlags(&esT2,ALL_EVENTS);
    }

    if(palReadPad(GPIO4_PORT, GPIO4_PAD) == PAL_HIGH)
    {
      chEvtBroadcastFlags(&esT3,ALL_EVENTS);
    }

    if(palReadPad(GPIO17_PORT, GPIO17_PAD) == PAL_HIGH)
    {
      chEvtBroadcastFlags(&esT4,ALL_EVENTS);
    }
     chThdSleepMilliseconds(1000);
  }
  return 0;
}

/*Notify flag counter event*/
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *p) {
  (void)p;
  chRegSetThreadName("T1");
  EventListener elt1;
  chEvtRegister(&esT1,&elt1,1);
  chEvtRegister(&esT1,&elt1,2);

  while (TRUE) {

    chEvtWaitOne(1);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);
    chEvtWaitOne(2);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);

  }
  return 0;
}

static WORKING_AREA(waThread2, 128);
static msg_t Thread2(void *p) {
  (void)p;
  chRegSetThreadName("T2");
  EventListener elt2;
  chEvtRegister(&esT2,&elt2,1);
  chEvtRegister(&esT2,&elt2,2);

  while (TRUE) {

    chEvtWaitOne(1);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);
    chEvtWaitOne(2);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);
  }
  return 0;

}

static WORKING_AREA(waThread3, 128);
static msg_t Thread3(void *p) {
  (void)p;  
  chRegSetThreadName("T3");
  EventListener elt3;
  chEvtRegister(&esT3,&elt3,1);
  chEvtRegister(&esT3,&elt3,2);

  while (TRUE) {

    chEvtWaitOne(1);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);
    chEvtWaitOne(2);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);

  }

  return 0;
}

/*Print on serial port when event1 occurs*/
static WORKING_AREA(waThread4, 128);
static msg_t Thread4(void *p) {
  (void)p;
  chRegSetThreadName("T4");
  EventListener elt4;
  chEvtRegister(&esT4,&elt4,1);
  chEvtRegister(&esT4,&elt4,2);
  while(TRUE)
  {
    chEvtWaitOne(1);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);
    chEvtWaitOne(2);
    palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);
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
  *Init MailBox to Share between Threads
  /

  /*
   * Serial port initialization.
   */
  sdStart(&SD1, NULL); 
  chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");

  /*
  *Event initialization
  */
  chEvtInit(&esT1);
  chEvtInit(&esT2);
  chEvtInit(&esT3);
  chEvtInit(&esT4);
  
  /*
  *Mutex Initialization
  */
  chMtxInit(&mutex);

  /*
   * Set mode of PINES
   */

  palSetPadMode(GPIO0_PORT, GPIO0_PAD, PAL_MODE_INPUT);   //Input T1
  palSetPadMode(GPIO1_PORT, GPIO1_PAD, PAL_MODE_INPUT);   //Input T2
  palSetPadMode(GPIO4_PORT, GPIO4_PAD, PAL_MODE_INPUT);   //Input T3
  palSetPadMode(GPIO17_PORT, GPIO17_PAD, PAL_MODE_INPUT); //Input T4
  
  palSetPadMode(GPIO18_PORT, GPIO18_PAD, PAL_MODE_OUTPUT); //Output T1
  palSetPadMode(GPIO22_PORT, GPIO22_PAD, PAL_MODE_OUTPUT); //Output T2
  palSetPadMode(GPIO23_PORT, GPIO23_PAD, PAL_MODE_OUTPUT); //Output T3
  palSetPadMode(GPIO24_PORT, GPIO24_PAD, PAL_MODE_OUTPUT); //Output T4
  
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waMainThread, sizeof(waMainThread), NORMALPRIO, mainThread, NULL);
  
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
  chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, Thread4, NULL);
  
  /*
   * Events servicing loop.
   */
  chThdWait(chThdSelf());

  return 0;
}