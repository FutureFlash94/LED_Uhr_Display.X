/*
 * File:    main.c
 * Author:  Filip Humaj
 */
//**********************************************************************************************************************
//Standartbibliotheken
#include "p24FJ64GB002.h"
#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <i2c.h>
#include <math.h>

//Header für den ADC
#include "ADC.h"

//Steuern jedes einzelnen Pins
#include <PPS.h>

//Header für i2c Funktionen zum Senden und Empfangen
#include "i2c_driver.h"

//Enthällt Funktionen zum Initialisieren, Schreiben und Lesen des AS1119 LED driver
#include "AS1119_driver.h"

//Header für TMD3990 mit Funktionen zum Initialisieren, Schreiben und Lesen
#include "tmd3990_driver.h"

//Header zum Erstellen und Verwalten von Timern
#include "timer_driver.h"

//Header dür den Ladechip AS3610
#include "as3610.h"

//Konfiguration des PIC24FJ64GB002
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)

//**********************************************************************************************************************
//Definition von Konstanten
#define SYSCLK                          4000000UL
#define GlobalTimerOVFvalue             1000000     //Globale OVF Zeit für den Timer in [us]
#define Time_ShowBye                    1           //[min] Zeit nach dem Unterschreiten von 3.2V und Aufforderung zum Aufladen

#define anzeige_aendern_zeit            10          //[s] Interwall, in dem der Anzeige Stunde:Minute in :Sekunde ändert
#define anzeige_aendern_datum           10          //[s] Interwall, in dem die Anzeige Tag.Monat in Jahr ändert

#define AS1119_min                      5           //Minimale Helligkeit
#define AS1119_max                      25          //Maximale Helligkeit

//**********************************************************************************************************************
//Bewegungserkennung
u8 ProxL = 0;
u8 ProxR = 0;

//**********************************************************************************************************************
//                      Funktion wird aufgerufen, wenn das Programm startet.
void CNInit(void){
    _CNIF = 0;		// clear IF
    _CNIP = 5;		// set IP as 5
    _CNIE = 1;		// enable CN

    //Pin 25 - Taster 1
    _TRISB14 = 1;   //Input
    _CN11IE = 1;
    _CN11PUE = 0;

    //Pin 26 - Taster 2
    _TRISB15 = 1;
    _CN12IE = 1;
    _CN12PUE = 0;
}
//**********************************************************************************************************************
//                      Einfache Warteschleife
void _delay(unsigned long dauer){
    while(dauer > 0){
        dauer--;
    }
}
//**********************************************************************************************************************
//                      Funktionen werden aufgerufen, wenn sich der Modus der Uhr ändert
void go_sleep_mode(){
    Sleep();
}

void go_idle_mode(){
    Idle();
}

void go_normal_mode(){
    Nop();
}
//**********************************************************************************************************************
//                      Funktion wird jede Sekunde aufgerufen, und erhöht die Sekundenvariable
void GlobalTimerInterrupt(){
    //Starten den Timer vom Neuen
    timerStart(TIMER1_MODULE, GlobalTimerOVFvalue, &GlobalTimerInterrupt);

}
//**********************************************************************************************************************
//                      Funktion wird aufgerufen, wenn der Zustand det Tasten geändert wird
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    //Entprellen
    _delay(1000);

    //linke Taste gedrückt
    if((_RB15 == 1) && (_RB14 == 0)){
        
    }

    //rechte Taste gedrückt
    else if((_RB14 == 1) && (_RB15 == 0)){
        
    }

    IFS1bits.CNIF = 0;
}
//**********************************************************************************************************************
//                      Funktion wird aufgerufen, wenn die Lichtsensoren kein Objekt vor sich feststellen
volatile bool_t gestic_temp;

void gestic_timerisr(){
    gestic_temp = FALSE;
}

void show_ams(){
    //AMS anzeigen

    //a:
    AS1119_WriteColumn(1,1,0x7E);
    AS1119_WriteColumn(1,2,0xFF);
    AS1119_WriteColumn(1,3,0xE7);
    AS1119_WriteColumn(1,4,0xC3);
    AS1119_WriteColumn(1,5,0xC3);
    AS1119_WriteColumn(1,6,0x66);
    AS1119_WriteColumn(1,7,0xFF);
    AS1119_WriteColumn(1,8,0xFF);

    //m:
    AS1119_WriteColumn(1,10,0xFF);
    AS1119_WriteColumn(1,11,0xFF);
    AS1119_WriteColumn(1,12,0x06);
    AS1119_WriteColumn(1,13,0x03);
    AS1119_WriteColumn(1,14,0x03);
    AS1119_WriteColumn(1,15,0xFE);
    AS1119_WriteColumn(1,16,0xFE);
    AS1119_WriteColumn(2,1,0x03);
    AS1119_WriteColumn(2,2,0x03);
    AS1119_WriteColumn(2,3,0xFE);
    AS1119_WriteColumn(2,4,0xFE);

    //s:
    AS1119_WriteColumn(2,6,0x7F);
    AS1119_WriteColumn(2,7,0xFF);
    AS1119_WriteColumn(2,8,0xC0);
    AS1119_WriteColumn(2,9,0xC0);
    AS1119_WriteColumn(2,10,0xFF);
    AS1119_WriteColumn(2,11,0x7F);
    AS1119_WriteColumn(2,12,0x03);
    AS1119_WriteColumn(2,13,0x03);
    AS1119_WriteColumn(2,14,0xFF);
    AS1119_WriteColumn(2,15,0xFF);
}
//**********************************************************************************************************************
//                      Hauptprogramm
int main() {

    //********************Initialisierung****************************
    AD1PCFG=0xFFFF;//Alle Pins digital
    //i2c #1
    i2cConfig_t i2cConfig_1, i2cConfigReal_1;
    i2cConfig_1.i2cAddressMode  = I2C_ADDRESS_MODE_7_BIT;
    i2cConfig_1.i2cClockMode    = I2C_SCK_1000KHZ;
    i2cConfig_1.i2cModule       = I2C1_MODULE;
    i2cInitialize(SYSCLK, &i2cConfig_1, &i2cConfigReal_1);

    //i2c ##2
    i2cConfig_t i2cConfig_2, i2cConfigReal_2;
    i2cConfig_2.i2cAddressMode = I2C_ADDRESS_MODE_7_BIT;
    i2cConfig_2.i2cClockMode = I2C_SCK_1000KHZ;
    i2cConfig_2.i2cModule = I2C2_MODULE;
    i2cInitialize(SYSCLK, &i2cConfig_2, &i2cConfigReal_2);

    //AS1119 #1 & #2
    AS1119_initialisierung(1);
    AS1119_initialisierung(2);

    //TMD3990 #1 & #2
    tmd3990Initialize(1);
    tmd3990Initialize(2);

    //AS3610 initialisieren
    init_as3610_c1();

    //Interrupt für Taster
    CNInit();

    timerInitialize(TIMER1_MODULE, SYSCLK); _T1IP = 7;

    //ADC initialisieren
    ADCInit();
    //Messpin als Eingang definieren
    _TRISB5 = 0;
    //RB5 Pin auf "1" setzten, dient für die Versorgung des Messboards
    PORTBbits.RB5 = 1;
    //****************************************************************

    //Timer1 ist der wichtigste Timer, hat die höchste Priorität
    //timerStart(TIMER1_MODULE, GlobalTimerOVFvalue, &GlobalTimerInterrupt);

    while(1)
    {
        ProxL = tmd3990GetProx(1);
        ProxR = tmd3990GetProx(2);

        // Linker Lichtsensor
        if(ProxL > 20){
           show_ams();
           _delay(500000);
        }

        //Rechter Lichtsensor
        else if(ProxR > 20){
           show_ams();
           _delay(500000);
        }

        else {
            //Smiley:
            AS1119_WriteColumn(1,1,0x00);
            AS1119_WriteColumn(1,2,0x00);
            AS1119_WriteColumn(1,3,0x00);
            AS1119_WriteColumn(1,4,0x00);
            AS1119_WriteColumn(1,5,0x00);
            AS1119_WriteColumn(1,6,0x00);
            AS1119_WriteColumn(1,7,0x00);
            AS1119_WriteColumn(1,8,0x00);
            AS1119_WriteColumn(1,9,0x00);
            AS1119_WriteColumn(1,10,0x00);
            AS1119_WriteColumn(1,11,0x00);
            AS1119_WriteColumn(1,12,0x00);
            AS1119_WriteColumn(1,13,0x66);
            AS1119_WriteColumn(1,14,0xA9);
            AS1119_WriteColumn(1,15,0xA9);
            AS1119_WriteColumn(1,16,0xA6);

            AS1119_WriteColumn(2,1,0xA0);
            AS1119_WriteColumn(2,2,0xA8);
            AS1119_WriteColumn(2,3,0xA8);
            AS1119_WriteColumn(2,4,0x68);
            AS1119_WriteColumn(2,5,0x00);
            AS1119_WriteColumn(2,6,0x00);
            AS1119_WriteColumn(2,7,0x00);
            AS1119_WriteColumn(2,8,0x00);
            AS1119_WriteColumn(2,9,0x00);
            AS1119_WriteColumn(2,10,0x00);
            AS1119_WriteColumn(2,11,0x00);
            AS1119_WriteColumn(2,12,0x00);
            AS1119_WriteColumn(2,13,0x00);
            AS1119_WriteColumn(2,14,0x00);
            AS1119_WriteColumn(2,15,0x00);
            AS1119_WriteColumn(2,16,0x00);
        }
    }

    return (EXIT_SUCCESS);
}
//**********************************************************************************************************************
