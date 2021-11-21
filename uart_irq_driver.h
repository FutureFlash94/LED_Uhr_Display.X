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
 *  \author  M. Arpa
 *
 *  \brief uart irq driver 
 *
 */


#ifndef UART_IRQ_DRIVER_H
#define UART_IRQ_DRIVER_H


/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
#include "ams_types.h"



/*
******************************************************************************
* DEFINES
******************************************************************************
*/

#define UART_TX_BUFFER_SIZE 256 /* must be a 2^n and less than 2^16 */
#define UART_RX_BUFFER_SIZE 256 /* must be a 2^n and less than 2^16 */


/* if you are using a terminal that sends a different end of line character, 
   redefine it here */
#define UART_END_OF_LINE_CHAR '\n'

/* never must the end of line charater be the zero-terminator */
#define UART_ZERO_TERMINATOR  '\0'


/* values returned by uartGetLastError() */
#define UART_NO_ERR 0
#define UART_RX_ERR -1
#define UART_RX_BUF_FULL -3

/*
******************************************************************************
* FUNCTIONS
******************************************************************************
*/
/* configure uart to the system frequency and baudrate specified. Returns the
   actual baudrate.
   Note the pin configuration must be done elsewhere. */
u32 uartInitialise( u32 sysclk, u32 baudrate );

/* disables the uart module
   Note that pin re-configuration must be done elsewhere.  */
void uartDeinitialise();


/* convenience function to transmit a zero terminated string. Returns the
   number of bytes transmitted. */
u16 uartTxString( const char * text );

/* transmits up to <length> bytes. Returns the number of bytes transmitted */
u16 uartTxNBytes( const u8 * buffer, u16 length );

/* returns the number of bytes that can be taken by the next call of 
   uartTxNBytes */
u16 uartTxNBytesFree( );


/* receives up to <length bytes. Returns te number of bytes received */
u16 uartRxNBytes( u8 * buffer, u16 length );

/* receives a complete line (or up to <length> bytes). returns the number of
   bytes received. If line ends not in '\n', the buffer was too small. */
u16 uartReadLine( u8 * buffer, u16 length );

/* returns the number of bytes that have been received (and can be retrieved
   by the next call of uartRxNBytes) */
u16 uartRxNBytesReceived( );


/* returns the last error that occured and clears it */
s8 uartGetLastError( );

#endif /* UART_IRQ_DRIVER_H */
