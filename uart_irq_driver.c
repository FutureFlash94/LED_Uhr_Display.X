/*
 *****************************************************************************
 * Copyright by ams AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */
/*
 *      PROJECT: Pic  Uart Terminal
 *      $Revision: $
 *      LANGUAGE:  ANSI C
 */

/*! \file
 *
 *  \author M. Arpa
 *
 *  \brief uart driver implementation for PIC24FJ64
 *
 */
/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include <p24Fxxxx.h>
#include "uart_irq_driver.h"
#include "uart.h"

/*
******************************************************************************
* LOCAL DEFINES
******************************************************************************
*/

#define UART_TX_BUFFER_SIZE 256 /* must be a 2^n and less than 2^16 */
#define UART_RX_BUFFER_SIZE 256 /* must be a 2^n and less than 2^16 */




#define UART_TX_MASK ( (UART_TX_BUFFER_SIZE) - 1 )
#define UART_RX_MASK ( (UART_RX_BUFFER_SIZE) - 1 )

/* put a byte into the tx-buffer - done by normal fn */
#define TX_IN( value ) \
  uartTxBuffer[ UART_TX_MASK & uartTxIn++ ]  = (value)

/* get a byte from the tx-buffer - done by irq */
#define TX_OUT( ) \
  uartTxBuffer[ UART_TX_MASK & uartTxOut++ ]

/* put a byte in rx-buffer - done by irq */
#define RX_IN( value ) \
  uartRxBuffer[ UART_RX_MASK & uartRxIn++  ] = (value)

/* get a byte from rx-buffer - done by normal fn */
#define RX_OUT( ) \
  uartRxBuffer[ UART_RX_MASK & uartRxOut++ ]


/* if there is no place in the tx-buffer */
#define TX_FULL() \
  ( uartTxOut + UART_TX_BUFFER_SIZE == uartTxIn )

/* tx buffer is empty */
#define TX_EMPTY() \
  ( uartTxOut == uartTxIn )


/* if there is nothing in the rx buffer */
#define RX_EMPTY() \
  ( uartRxOut == uartRxIn )

/* rx buffer is full */
#define RX_FULL() \
  ( uartRxOut + UART_RX_BUFFER_SIZE == uartRxIn )


/* number of bytes in rx buffer */
#define RX_FILL() \
  ( uartRxOut <= uartRxIn ? uartRxIn - uartRxOut : uartRxIn + UART_RX_BUFFER_SIZE - ( uartRxOut & UART_RX_MASK ) )

/* number of bytes in tx buffer */
#define TX_FILL() \
  ( uartTxOut <= uartTxIn ? uartTxIn - uartTxOut : uartTxIn + UART_TX_BUFFER_SIZE - ( uartTxOut & UART_TX_MASK ) )


/*
******************************************************************************
* LOCAL VARIABLES
******************************************************************************
*/

/* ring buffers to hold the data received or to transmit */
static u8 uartTxBuffer [ UART_TX_BUFFER_SIZE ];
static u8 uartRxBuffer [ UART_RX_BUFFER_SIZE ];

/* irq does read & write, normal fn does read only (of variable) */
static volatile u16 uartRxIn; 

/* irq does read only, normal fn does read & write (of variable) */
static volatile u16 uartRxOut;

/* irq does read & write, normal fn does read only (of variable) */
static volatile u16 uartTxOut;

/* irq does read only, normal fn does read & write (of variable) */
static volatile u16 uartTxIn;

/* store a uart error in this variable */
static volatile s8 uartError;

/*
******************************************************************************
* GLOBAL FUNCTIONS
******************************************************************************
*/

u32 uartInitialise ( u32 sysclk, u32 baudrate )
{
    u32 br1, br2;
    u16 breg;

    /* Disable UART for configuration */
    U1MODE = 0x0;
    U1STA = 0x0;

    /* Setup UART registers */
    /* equation according to the datasheet:
       (sysclk / (16 * baudrate)) - 1
     */
    breg = (sysclk / (16 * baudrate)) - 1;

    /* round up/down w/o using floating point maths */
    br1 = sysclk / (16 * (breg + 1));
    br2 = sysclk / (16 * (breg + 2));

    /* check which of the two values produce fewer error rate */
    if ((br1 - baudrate) > (baudrate - br2))
    {
        U1BRG = breg + 1;
        baudrate = br2;
    }
    else
    {
        U1BRG = breg;
        baudrate = br1;
    }

    uartTxIn = 0;
    uartTxOut = 0;
    uartRxIn = 0;
    uartRxOut = 0;

 
    /* Enable UART */
    U1MODE |=  0x8000;
    U1STA |= 0x0400;

   /* clear receive buffer */
    while ( DataRdyUART1() )
    {
        ReadUART1();
    }

    U1RX_Clear_Intr_Status_Bit;
    U1TX_Clear_Intr_Status_Bit;

    /* enable interrupts */
    ConfigIntUART1( UART_RX_INT_EN | UART_TX_INT_EN | UART_RX_INT_PR4 | UART_TX_INT_PR4 ); 

    return baudrate;
}

void uartDeinitialise ()
{
    /* disable UART */
    U1MODE = 0x0;
    U1STA = 0x0;
}

u16 uartTxString ( const char * text )
{
    u16 length = 0;
    const char * p = text;
    while ( *p != '\0' && length <= UART_TX_BUFFER_SIZE )
    {
	length++;
	++p;
    }
    return uartTxNBytes( (const u8 *)text, length );
}

u16 uartTxNBytes ( const u8 * buffer, u16 length )
{
    u16 toSend = length;
    DisableIntU1TX;

    if ( length && U1STAbits.TRMT ) /* last transmission has completed */ 
    {
	IFS0bits.U1TXIF = 1; /* trigger tx-interrupt */
    }
 
    while ( length && !TX_FULL() )
    {
        TX_IN( *buffer ); /* put them in the tx-ring-buffer */
	buffer++;
	length--;
    }

    EnableIntU1TX;
    return toSend - length; /* number of bytes ready for transmit */
}

u16 uartTxNBytesFree ( )
{
    return UART_TX_BUFFER_SIZE - TX_FILL();
}

u16 uartRxNBytes ( u8 * buffer, u16 length )
{
    u16 rxed = length;
    DisableIntU1RX;

    while ( length && !RX_EMPTY() )
    {
	*buffer = RX_OUT();
	buffer++;
	length--;
    }
	
    EnableIntU1RX;
    return rxed - length;
}

u16 uartReadLine ( u8 * buffer, u16 length )
{
    u16 rxed = length;
    u8 c = ~UART_END_OF_LINE_CHAR;
    DisableIntU1RX;

    while ( c != UART_END_OF_LINE_CHAR && length && !RX_EMPTY() )
    {
        c = RX_OUT();
	*buffer = c;
	buffer++;
	length--;
    }
	
    EnableIntU1RX;
    return rxed - length;
}
   
u16 uartRxNBytesReceived ( )
{
    return RX_FILL();
}

s8 uartGetLastError ( )
{
  s8 res = uartError;
  uartError = 0;
  return res;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void)
{
    U1RX_Clear_Intr_Status_Bit;

    while( DataRdyUART1() )
    {
        u8 temp = (u8)ReadUART1();
	
	if ( ! RX_FULL() )
	{
	    RX_IN( temp );
	}
	else
	{
	    uartError = UART_RX_BUF_FULL;
	}
        if ( U1STAbits.OERR )
        {
            uartError = UART_RX_ERR;
            U1STAbits.OERR = 0;
	}
    }
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt (void)
{
    U1TX_Clear_Intr_Status_Bit;

    while ( ! U1STAbits.UTXBF && ! TX_EMPTY() )
    {
        u16 temp = TX_OUT();
        WriteUART1( temp );
    } 
}

