#define USE_AND_OR
#include <p24Fxxxx.h>
#include "timer_driver.h"

/*
******************************************************************************
* variables
******************************************************************************
*/
/* clock cycles per microseconds */
static u32 clkCyclesPerUSec[MAX_NR_OF_TIMERS];
/* timer maximum value for microseconds */
static u32 timerMaxValueUSec;

/* flag to indicate whether timer is running or not */
static volatile s8 timerRunning[MAX_NR_OF_TIMERS];

/* timer value - useful for timer values > 1000 */
static volatile u32 timerValue[MAX_NR_OF_TIMERS];

static pCbFunc pCbFuncArray[MAX_NR_OF_TIMERS] = {NULL};

/*
******************************************************************************
* local function prototypes
******************************************************************************
*/
static void timerIsr( u8 timerModule );
static void timerStopSequence( u8 timerModule );

/*
******************************************************************************
* interrupt service routines
******************************************************************************
*/

void __attribute__((interrupt, no_auto_psv)) timer1Isr ( void )
{
    _T1IF = 0;
    timerIsr(TIMER1_MODULE);
}

void __attribute__((interrupt, no_auto_psv)) timer2Isr ( void )
{
    _T2IF = 0;
    timerIsr(TIMER2_MODULE);
}

void __attribute__((interrupt, no_auto_psv)) timer3Isr ( void )
{
    _T3IF = 0;
    timerIsr(TIMER3_MODULE);
}

void __attribute__((interrupt, no_auto_psv)) timer4Isr ( void )
{
    _T4IF = 0;
    timerIsr(TIMER4_MODULE);
}

void __attribute__((interrupt, no_auto_psv)) timer5Isr ( void )
{
    _T5IF = 0;
    timerIsr(TIMER5_MODULE);
}

/*
******************************************************************************
* global functions
******************************************************************************
*/

void timerInitialize(u8 timerModule, u32 systemFrequency )
{
    timerMaxValueUSec = 65536 / (((systemFrequency / 1000000) / 256) + 1);
    clkCyclesPerUSec[timerModule] = systemFrequency / 1000000;
    timerStop( timerModule );
}

void timerStart(u8 timerModule, u32 uSec, void(*cbFunc)() )
{
    //u32 milliSec;
    u32 microSec;
    timerValue[timerModule] = uSec;
    pCbFuncArray[timerModule] = cbFunc;
    if ( uSec > timerMaxValueUSec ) /* cannot handle values bigger than timerMaxValueUSec */
    {
        uSec = timerMaxValueUSec;
    }
    timerValue[timerModule] -= uSec;
    timerRunning[timerModule] = 1;    /* set running flag */
    microSec = ( uSec * clkCyclesPerUSec[timerModule] ) / 256; /* prescaler used */
    switch(timerModule)
    {
        case TIMER1_MODULE:
            PR1 = (u16)microSec;  /* load timer compare register */
            TMR1 = 0;             /* reset timer counter */
            _T1IF = 0;            /* clear interrupt flag */
            _T1IE = 1;            /* enable interrupt */
            T1CONbits.TCKPS = 3;   // prescaler 1:256
            T1CONbits.TON   = 1;   // start timer
            break;
        case TIMER2_MODULE:
            PR2 = (u16)microSec;  /* load timer compare register */
            TMR2 = 0;             /* reset timer counter */
            _T2IF = 0;            /* clear interrupt flag */
            _T2IE = 1;            /* enable interrupt */
            T2CONbits.TCKPS = 3;   // prescaler 1:256
            T2CONbits.TON   = 1;   // start timer
            break;
        case TIMER3_MODULE:
            PR3 = (u16)microSec;  /* load timer compare register */
            TMR3 = 0;             /* reset timer counter */
            _T3IF = 0;            /* clear interrupt flag */
            _T3IE = 1;            /* enable interrupt */
            T3CONbits.TCKPS = 3;   // prescaler 1:256
            T3CONbits.TON   = 1;   // start timer
            break;
        case TIMER4_MODULE:
            PR4 = (u16)microSec;  /* load timer compare register */
            TMR4 = 0;             /* reset timer counter */
            _T4IF = 0;            /* clear interrupt flag */
            _T4IE = 1;            /* enable interrupt */
            T4CONbits.TCKPS = 3;   // prescaler 1:256
            T4CONbits.TON   = 1;   // start timer
            break;
        case TIMER5_MODULE:
            PR5 = (u16)microSec;  /* load timer compare register */
            TMR5 = 0;             /* reset timer counter */
            _T5IF = 0;            /* clear interrupt flag */
            _T5IE = 1;            /* enable interrupt */
            T5CONbits.TCKPS = 3;   // prescaler 1:256
            T5CONbits.TON   = 1;   // start timer
            break;
    }
}

void timerStopWithCb( u8 timerModule )
{
    timerStopSequence(timerModule);
    if (pCbFuncArray[timerModule] != NULL)
        pCbFuncArray[timerModule]();
}

void timerStop( u8 timerModule )
{
    timerStopSequence(timerModule);
}

BOOL timerIsRunning( u8 timerModule )
{
    return ( timerRunning[timerModule] == 1 );
}

/*
******************************************************************************
* local functions
******************************************************************************
*/
static void timerIsr( u8 timerModule )
{
    if ( timerValue[timerModule] > 0 )
    { /* reload */
        if ( timerValue[timerModule] < timerMaxValueUSec )
        {
            u32 microSec = ( timerValue[timerModule] * clkCyclesPerUSec[timerModule] ) / 256; /* prescaler used */
            switch(timerModule)
            {
                case TIMER1_MODULE:
                    PR1 = (u16)microSec;  /* load timer compare register */
                    break;
                case TIMER2_MODULE:
                    PR2 = (u16)microSec;  /* load timer compare register */
                    break;
                case TIMER3_MODULE:
                    PR3 = (u16)microSec;  /* load timer compare register */
                    break;
                case TIMER4_MODULE:
                    PR4 = (u16)microSec;  /* load timer compare register */
                    break;
                case TIMER5_MODULE:
                    PR5 = (u16)microSec;  /* load timer compare register */
                    break;
            }            
            timerValue[timerModule] = 0; /* end of outer loop */
        }
        else /* not the last time we let timer overflow */
        {
            timerValue[timerModule] -= timerMaxValueUSec;
        }
    }
    else /* timer has expired */
    {
        timerStopWithCb( timerModule );
    }
}

static void timerStopSequence( u8 timerModule )
{
    switch(timerModule)
    {
        case TIMER1_MODULE:
            _T1IE = 0; /* disable interrupt */
            T1CON = 0; /* stop timer */
            _T1IF = 0; /* clear interrupt flag */
            break;
        case TIMER2_MODULE:
            _T2IE = 0; /* disable interrupt */
            T2CON = 0; /* stop timer */
            _T2IF = 0; /* clear interrupt flag */
            break;
        case TIMER3_MODULE:
            _T3IE = 0; /* disable interrupt */
            T3CON = 0; /* stop timer */
            _T3IF = 0; /* clear interrupt flag */
            break;
        case TIMER4_MODULE:
            _T4IE = 0; /* disable interrupt */
            T4CON = 0; /* stop timer */
            _T4IF = 0; /* clear interrupt flag */
            break;
        case TIMER5_MODULE:
            _T5IE = 0; /* disable interrupt */
            T5CON = 0; /* stop timer */
            _T5IF = 0; /* clear interrupt flag */
            break;
    }
    timerRunning[timerModule] = 0; /* timer is not running */
}
