/*
 * File:   ADC.c
 * Author: Simon Mlineritsch
 *
 * Created on 30. September 2013, 09:50
 */


#include "p24FJ64GB002.h"
#include <stdint.h>
#include "ADC.h"

////////////////////////////////////////////////////////////////////////////////
//  ADC Funktionen                                                            //
////////////////////////////////////////////////////////////////////////////////

int scale(uint16_t adcValue ){
    /*if(adcValue > 500){
        adcValue = adcValue - 500;
    }
    return (adcValue/49);
    */
    
    if(adcValue > 500){
        adcValue = adcValue - 500;
    }
    return (adcValue/44);
    
   
}

void ADCInit(void){

    
    // integer format, auto conversion,sample after conversion ends
    AD1CON1 = 0x00E4;
    
    // AVDD & AVSS as references,Disable Scan mode,
    //interrupt after 1 sample/convert sequence, use MuxA
    AD1CON2 = 0;
    
    // AD Clock as derivative of system clock
    AD1CON3 = 0x0109;
    //AD1CON3 = 0x010D;

    // Positive sample input channel for MUX A to use VR+,
    //Negative input channel for MUX A to use VR-
    AD1CHS = 0x090B;
    
    //Disable digital input on AN10
    AD1PCFGbits.PCFG11 = 0;

    // Channel Scanning Disabled
    AD1CSSL = 0; 
    
    // Clear A/D conversion interrupt.
    IFS0bits.AD1IF = 0; 
    
    // Turn on the A/D converter
    AD1CON1bits.ADON = 1;     
    
    ////////////////////////////////////////////////////////////////////////////
    //                          ADC interrupt                                 //
    ////////////////////////////////////////////////////////////////////////////
    //INTCON1 = 0x8000;
    //IEC0bits.AD1IE = 1;

}

