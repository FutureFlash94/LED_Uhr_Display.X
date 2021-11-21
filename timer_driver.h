#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include "ams_types.h"

/*
******************************************************************************
* GLOBAL MACROS
******************************************************************************
*/
/*! map timer1Isr to _T1Interrupt */
#define timer1Isr _T1Interrupt
/*! map timer2Isr to _T2Interrupt */
#define timer2Isr _T2Interrupt
/*! map timer3Isr to _T3Interrupt */
#define timer3Isr _T3Interrupt
/*! map timer4Isr to _T4Interrupt */
#define timer4Isr _T4Interrupt
/*! map timer5Isr to _T5Interrupt */
#define timer5Isr _T5Interrupt

/*
******************************************************************************
* DEFINES
******************************************************************************
*/
#define MAX_NR_OF_TIMERS    5   /*!< maximum number of supported timers */
#define TIMER1_MODULE 0 /*!< define for timer 1 module */
#define TIMER2_MODULE 1 /*!< define for timer 2 module */
#define TIMER3_MODULE 2 /*!< define for timer 3 module */
#define TIMER4_MODULE 3 /*!< define for timer 4 module */
#define TIMER5_MODULE 4 /*!< define for timer 5 module */

/*! typedef for timer callback function */
typedef void (*pCbFunc)();

/*
******************************************************************************
* GLOBAL FUNCTION PROTOTYPES
******************************************************************************
*/
/*! 
 *****************************************************************************
 *  \brief  Initializes the timer module
 *
 * Initializes the timer of the given timer module
 *
 * \param timerModule : timer module number (use defines for timer 1-5)
 * \param clockCyclesPerSecond : system clock cycles per second. A typical
 *                                  value for clockCyclesPerSecond is
 *                                  e.g. 16000000 for 16 MHz.
 *****************************************************************************
 */
void timerInitialize(u8 timerModule, u32 clockCyclesPerSecond );

/*! 
 *****************************************************************************
 *  \brief  Wind up timer for the given period in micro-seconds.
 *
 * Wind up given timer module for the given period in micro-seconds and execute
 * the given callback function if not NULL.
 *
 * \param timerModule : timer module number (use defines for timer 1-5)
 * \param uSec : period in microseconds
 * \param *cbFunc : pointer to timer callback function which is called after
 *                  timer expired (use NULL if no callback function is required)
 *****************************************************************************
 */
void timerStart(u8 timerModule, u32 uSec, void(*cbFunc)() );

/*! 
 *****************************************************************************
 *  \brief Stops the timer if it was running.
 *
 * Stops the timer if it was running without calling any callback function.
 *
 * \param timerModule : timer module number (use defines for timer 1-5)
 *****************************************************************************
 */
void timerStop(u8 timerModule);

/*! 
 *****************************************************************************
 *  \brief Stops the timer if it was running and calls timer callback function.
 *
 * Stops the timer if it was running and executes the timer callback function.
 *
 * \param timerModule : timer module number (use defines for timer 1-5)
 *****************************************************************************
 */
void timerStopWithCb( u8 timerModule );

/*! 
 *****************************************************************************
 *  \brief Checks if the given timer is running.
 *
 * Checks if the given timer is running.
 *
 * \param timerModule : timer module number (use defines for timer 1-5)
 *
 * \return TRUE : given timer is running
 * \return FALSE : given timer is not running
 *****************************************************************************
 */
BOOL timerIsRunning( u8 timerModule );

#endif /* TIMER_DRIVER_H */
