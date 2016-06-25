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

UARTDriver uartp; //Pointer to uart driver

static VirtualTimer vt1, vt2;

static void restart(void *p) {

  (void)p;

  chSysLockFromIsr();
  uartStartSendI(&uartp, 14, "Hello World!\r\n");
  chSysUnlockFromIsr();
}

static void ledoff(void *p) {

  (void)p;
  palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_HIGH);
}

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {

  (void)uartp;
  palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_LOW);
}

/*
 * This callback is invoked when a transmission has physically completed.
 */
static void txend2(UARTDriver *uartp) {

  (void)uartp;
  palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_HIGH);
  chSysLockFromIsr();
  if (chVTIsArmedI(&vt1))
    chVTResetI(&vt1);
  chVTSetI(&vt1, MS2ST(5000), restart, NULL);
  chSysUnlockFromIsr();
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {

  (void)uartp;
  (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {

  (void)uartp;
  (void)c;
  /* Flashing the LED each time a character is received.*/
  palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_LOW);
  chSysLockFromIsr();
  if (chVTIsArmedI(&vt2))
    chVTResetI(&vt2);
  chVTSetI(&vt2, MS2ST(200), ledoff, NULL);
  chSysUnlockFromIsr();
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {

  (void)uartp;
}

/*Notify flag counter event*/
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *p) {
  (void)p;
  chRegSetThreadName("blinker");

  while (TRUE) {

    if(palReadPad(GPIO22_PORT,GPIO22_PAD) == PAL_HIGH)
      {
        palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_HIGH);
    }else{
        palWritePad(GPIO23_PORT,GPIO23_PAD,PAL_LOW);
    }
  }
  return 0;
}

/*Notify when button is pressed*/
static WORKING_AREA(waThread2, 128);
static msg_t Thread2(void *p) {
  (void)p;
  chRegSetThreadName("blinker2");

  while (TRUE) {
    //Button was pressed!
    if(palReadPad(GPIO24_PORT,GPIO24_PAD) == PAL_HIGH)
      {
        palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_HIGH);
    }else{
        palWritePad(GPIO25_PORT,GPIO25_PAD,PAL_LOW);
    }

  }
  return 0;

}

static UARTConfig uartConfig = {
  txend1,
  txend2,
  rxend,
  rxchar,
  rxerr,
  38400,
  0,
  USART_CR2_LINEN,
  0
};
/*
 * Application entry point.
 */
int main(void) {
  halInit();
  chSysInit();

  /*
  *UART Driver initialization
  */
  uartInit();
  uartObjectInit(&uartp);
  uartStart(&uartp,&uartConfig);

  /*
   * Serial port initialization.
   */
  sdStart(&SD1, NULL); 
  chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");

  
  /*
   * Set mode of onboard LED
   */
  palSetPadMode(ONBOARD_LED_PORT, ONBOARD_LED_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO24_PORT, GPIO24_PAD, PAL_MODE_INPUT); //BUTTON PORT
  palSetPadMode(GPIO22_PORT, GPIO22_PAD, PAL_MODE_INPUT); //BUTTON PORT
  
  palSetPadMode(GPIO25_PORT, GPIO25_PAD, PAL_MODE_OUTPUT); //LED TH1 PORT
  palSetPadMode(GPIO23_PORT, GPIO23_PAD, PAL_MODE_OUTPUT); //LED TH2 PORT
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  
  /*
   * Events servicing loop.
   */
  chThdWait(chThdSelf());

  return 0;
}