/* 
 * File:    main.c
 * Author:  Filip Humaj
 * Datum:   10.1.2014
 *
 */

/* Beschreibung:
 * 
 * Das Programm dient als Hauptprogramm für das Maturaprojekt LED UHR Display.
 * Umfasst zurzeit folgende Funktionen:
 *      - Helligkeit der LEDs an die Umgebung angepasst
 *      - Uhrzeit 
 */

/********************************************************************************************
 *                                 Einfügen aller benötigten Header                         *
 *                                                                                          *
 ********************************************************************************************/

//Standartbibliotheken
#include "p24FJ64GB002.h"
#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <i2c.h>
#include <math.h>

#include "ADC.h"

//Steuern jedes einzelnen Pins
#include <PPS.h>

//Header für i2c Funktionen zum Senden und Empfangen
#include "i2c_driver.h"

//Enthällt Funktionen zum Initialisieren, Schreiben und Lesen des AS1119 LED driver
#include "AS1119_driver.h"

//Header für TMD3990 mit Funktionen zum Initialisieren, Schreiben und Lesen
#include "tmd3990_driver.h"

//Header zur Erstellung von Timern
#include "timer_driver.h"

#include "uart_irq_driver.h"

#include "as3610.h"

/********************************************************************************************
 *                                  Konfiguration des PIC24FJ64GB002                        *
 *                                                                                          *
 ********************************************************************************************/

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_PRIPLL)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_IO & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)

/********************************************************************************************
 *                 Definition der zu verwendenden Funktion und Variablen                    *
 *                                                                                          *
 ********************************************************************************************/
#define SYSCLK                          4000000UL
#define GlobalTimerOVFvalue             1000000     //Globale OVF Zeit für den Timer in [us]
#define UART_BAUDRATE                   9600
#define Time_ShowAufladen               5           //Zeit nach dem Unterschreiten von 3.2V und Aufforderung zum Aufladen
        
#define anzeige_aendern_zeit            3           //[s] Interwall, in dem der Doppelpunkt der Uhr blinken soll
#define anzeige_aendern_datum           3           //[s] Interwall, in dem die Anzeige Tag.Monat in Jahr ändert
#define anzeige_aendern_akku_aufladen   30          //[s] Interwall, in dem die Anzeige anzeigt, die Uhr aufzuladen

#define AS1119_min              5           //Minimale Helligkeit
#define AS1119_max              80          //Maximale Helligkeit

void _delay(unsigned long dauer);
void update_time();

//Variablen für die Funktion 'Gestic'
u16 clear_left_old, clear_left_new, clear_var;
u16 clear_right_old, clear_right_new;       //Helligkeitswert vom Sensor
u8 clear_val_u8;                            //Helligkeit für AS1119

//Variablendefinition für die Zeitdarstellung
u8 i=0, sekunde = 35, minute = 29, stunde = 16, tag = 27, monat = 2;
u16 jahr = 2014, schaltjahr;
u8 wochentag;

u16 AS1119_diff;
u8 temp1 = 0,temp2 = 0, temp3 = 0, anzeige_aendern_z = 0, anzeige_aendern_d = 0 ;

u8 ProxL = 0;
u8 ProxR = 0;

u8 show_time_state = 1;
u8 show_datum_state = 0;
u8 show_akku_state = 0;
u8 show_menu = 0;
u8 charger_status = 0;
u8 show_nothing = 0;
u8 show_akku_aufladen = 0;
u8 clear_display_after_shut_down = 0;

//Stelle die im Menü gerade blinkt und geändert werden kann
u8 aktuelle_stelle_aendern = 1;

long double Akkustand;
int wert=0;
float volt=0;
char string[50];
u8 timer_start = 1;
u8 timer_sek = 0;

u8 is_low_power_mode = 0;

void init_uart()
{
    OUT_PIN_PPS_RP4 = OUT_FN_PPS_U1TX;     // RP5 is U1TX pin --> AUF PIN2
    //OUT_PIN_PPS_RP10 = OUT_FN_PPS_U1TX;     // RP5 is U1TX pin --> AUF PIN2
    //IN_FN_PPS_U1RX = IN_PIN_PPS_RP4;     // RP4 is U1RX pin
    uartInitialise( SYSCLK, UART_BAUDRATE );
}

void _delay(unsigned long dauer){
    while(dauer > 0){
        dauer--;
    }
}

void akku_aufladen_timer()
{
   timer_sek = timer_sek + 1;
   if(timer_sek >= Time_ShowAufladen*60)
   {
       
   }
   else
   {
        timerStart(TIMER3_MODULE, GlobalTimerOVFvalue, &akku_aufladen_timer);
   }
}

void GlobalTimerInterrupt(){
    //Starten den Timer vom Neuen
    timerStart(TIMER1_MODULE, GlobalTimerOVFvalue, &GlobalTimerInterrupt);
    if(show_menu == 0){
        sekunde = sekunde + 1;
        temp1 = temp1 + 1;
        temp2 = temp2 + 1;
        temp3 = temp3 + 1;
    }
    else{
        sekunde = 0;
    }
    update_time();
}

void update_date()
{
    schaltjahr = jahr%4;

    if(monat == 2){
        if(schaltjahr > 0){
            if(tag >= 29){
                tag=1;
                monat=monat+1;
            }
        }
        else if(schaltjahr == 0){
            if(tag >= 30){
                tag=1;
                monat=monat+1;
            }
        }
    }
    if((monat == 4) || (monat == 6) || (monat == 9) || (monat == 11)){
        if(tag > 30){
            tag=1;
            monat=monat+1;
        }
    }

    if((monat == 1) || (monat == 3) || (monat == 5) || (monat == 7) || (monat == 8) || (monat == 10)){
        if(tag > 31){
            tag=1;
            monat=monat+1;
        }
    }

    if(monat == 12){
        if(tag > 31){
            tag=1;
            monat=1;
            jahr=jahr+1;
        }
    }

    u8 nm;
    u8 nsj;

    switch(monat){
        case 1: nm=0; break;
        case 2: nm=3; break;
        case 3: nm=3; break;
        case 4: nm=6; break;
        case 5: nm=1; break;
        case 6: nm=4; break;
        case 7: nm=6; break;
        case 8: nm=2; break;
        case 9: nm=5; break;
        case 10: nm=0; break;
        case 11: nm=3; break;
        case 12: nm=5; break;
    }

    u8 nt = (tag%7);
    u8 j12 = floor(jahr/100);
    u8 njh = ((3-(j12%4))*2);
    u8 j34 = jahr-(floor(jahr/100)*100);
    u8 njz = floor((j34+(j34/4))%7);

    if((schaltjahr == 0) && (monat == 1||2)){
        nsj = -1;
    }
    else{
        nsj = 0;
    }
    wochentag = floor((nt+nm+njh+njz+nsj)%7);
}

void update_time()
{

    //Sekunden 0-59:
    if(sekunde > 59){
        sekunde = 0;
        //Minuten: 0 - 59
        if(minute < 59){
            minute = minute + 1;
        }
        //Jede 59 Minuten
        else{
            minute = 0;
            //Stunden: 0 - 23
            if(stunde < 23){
                stunde = stunde + 1;
            }
            else{
                stunde = 0;
                tag = tag + 1;
                update_date();
            }
        }
    }

    //Batteriespannung messen
    wert=Batterie_berechnen();
    //sprintf(string, "wert:%i    ",wert);
    //uartTxString(string);

    volt=((2*wert)/3.302075365387)/100;
    Akkustand = ceil((volt-3.1)*100/(4-3.1));

    //sprintf(string, "Akkustand:%f\n\n",volt);
    //uartTxString(string);
   
    if(wert <= 518)
    {
        if(timer_start == 1)
        {
            timerStart(TIMER3_MODULE, GlobalTimerOVFvalue, &akku_aufladen_timer);
            timer_start = 0;
        }
        show_akku_aufladen = 1;
    }
    else
    {
        timerStop(TIMER3_MODULE);
        timer_start = 1;
        timer_sek = 1;
        if(is_low_power_mode == 0)
        {
            show_akku_aufladen = 0;
            show_nothing = 0;
        }
    }
}

void update_date_menu()
{
    schaltjahr = jahr%4;
    if(monat == 2){
        if(schaltjahr > 0){
            if(tag >= 29){
                tag = 1;
            }
        }
    }
    else if(schaltjahr == 0){
        if(tag >= 30){
            tag = 1;
        }
    }
    if((monat == 4) || (monat == 6) || (monat == 9) || (monat == 11)){
        if(tag > 30){
            if(tag > 30){
                tag = 1;
            }
        }
    }
    if((monat == 1) || (monat == 3) || (monat == 5) || (monat == 7) || (monat == 8) || (monat == 10)){
        if(tag > 31){
            tag = 1;
        }
    }
    if(monat == 12){
        if(tag > 31){
            if(tag > 31){
                tag = 1;
            }
        }
    }
    u8 nm;
    u8 nsj;

    switch(monat){
        case 1: nm=0; break;
        case 2: nm=3; break;
        case 3: nm=3; break;
        case 4: nm=6; break;
        case 5: nm=1; break;
        case 6: nm=4; break;
        case 7: nm=6; break;
        case 8: nm=2; break;
        case 9: nm=5; break;
        case 10: nm=0; break;
        case 11: nm=3; break;
        case 12: nm=5; break;
    }

    u8 nt = (tag%7);
    u8 j12 = floor(jahr/100);
    u8 njh = ((3-(j12%4))*2);
    u8 j34 = jahr-(floor(jahr/100)*100);
    u8 njz = floor((j34+(j34/4))%7);

    if((schaltjahr == 0) && (monat == 1||2)){
        nsj = -1;
    }
    else{
        nsj = 0;
    }
    wochentag = floor((nt+nm+njh+njz+nsj)%7);
}

void go_sleep_mode(){
    Sleep();
}

void go_idle_mode(){
    Idle();
}

void go_normal_mode(){
    Nop();
}

void low_power_modus()
{
    is_low_power_mode = 1;
    tmd_shut_down(1);
    tmd_shut_down(2);
    go_sleep_mode();
}

void normal_mode()
{
    is_low_power_mode = 0;
    go_normal_mode();
    tmd3990Initialize(1);
    tmd3990Initialize(2);
}

void CNInit(void){
    _CNIF = 0;		// clear IF
    _CNIP = 7;		// set IP as 7
    _CNIE = 1;		// enable CN
    
    //Pin 25 - Taster 1
    _TRISB14 = 1;   //Input
    _CN11IE = 1;
    _CN11PUE = 0;
    
    //Pin 26 - Taster 2
    _TRISB15 = 1;
    _CN12IE = 1;
    _CN12PUE = 0;

    //Lichtsensor 1
    _TRISA2 = 1;
    _CN30IE = 1;
    _CN30PUE = 0;

    //Lichtsensor 2
    _TRISA3 = 1;
    _CN29IE = 1;
    _CN29PUE = 0;
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    //Entprellen
    _delay(10000);
    
    if((_RB14 == 1) && (_RB15 == 0)){
        //Im Menü: Bestätigen und nächste Variable ändern
        if(show_menu == 1){
            aktuelle_stelle_aendern = aktuelle_stelle_aendern + 1;
            show_nothing = 1;
            if(show_time_state){
                if(aktuelle_stelle_aendern >= 3){
                    show_menu = 0;
                    aktuelle_stelle_aendern = 1;
                    show_nothing = 0;
                }
            }
            if(show_datum_state){
                if(aktuelle_stelle_aendern >= 5){
                    show_menu = 0;
                    aktuelle_stelle_aendern = 1;
                    show_nothing = 0;
                }
            }
        }

        //Von aktueller Anzeige auf Akkustandanzeige
        else{
            if(charger_status == 0){
                show_time_state = 0;
                show_datum_state = 0;
                show_akku_state = 1;
            }
            else{
                show_akku_state = 0;
                show_datum_state = 0;
                show_time_state = 1;
            }
            charger_status = 1-charger_status;
        }
    }

    else if((_RB15 == 1) && (_RB14 == 0)){
        //Im Menü: erhöhen der aktuellen Variable
        if(show_menu == 1){
            if(show_time_state){
                switch(aktuelle_stelle_aendern){
                    case 1: stunde = stunde + 1;
                        if(stunde > 23){
                            stunde = 0;
                        }
                        break;
                    case 2: minute = minute + 1;
                        if(minute > 59){
                            minute = 0;
                        }
                    break;
                }
            }
            
            if(show_datum_state){
                switch(aktuelle_stelle_aendern){
                    case 1: tag = tag + 1;
                        break;
                    case 2: monat = monat + 1;
                            if(monat > 12){
                                monat = 1;
                            }
                        break;
                    case 3: jahr = jahr + 10;
                        if(jahr >= 2099){
                            jahr = 2014;
                        }
                    break;
                    case 4: jahr = jahr + 1;
                        if(jahr%10 == 0){
                            jahr = jahr - 10;
                        }
                    break;
                }
                update_date_menu();
            }
        }
        
        //Energiesparmodus: Display aus, Lichtsensoren aus, PIC im idle mode
        else{
            ProxL= tmd3990GetProx(1);
            ProxR = tmd3990GetProx(2);
            if(ProxL > 20){
                show_menu = 1;
                show_time_state = 0;
                show_datum_state = 1;
            }
            else if(ProxR > 20){
                show_menu = 1;
                show_datum_state = 0;
                show_time_state = 1;
            }
            else{
                if(show_nothing == 0){
                    low_power_modus();
                    show_nothing = 1-show_nothing;
                }
                else if(show_akku_aufladen == 1)
                {
                    low_power_modus();
                    show_akku_aufladen = 1-show_akku_aufladen;
                }
                else{
                     normal_mode();
                     if(show_nothing == 1)
                     {
                         show_nothing = 1-show_nothing;
                     }
                }
            }
            clear_display_after_shut_down = 1;
            
        }
    }
    IFS1bits.CNIF = 0;
}

volatile bool_t gestic_temp;

void gestic_timerisr(){
    gestic_temp = FALSE;
}

void MeasureGestic(){
    ProxL = tmd3990GetProx(1);
    ProxR = tmd3990GetProx(2);

    //Bewegung von link nach rechts
    if(ProxL > 20){
        gestic_temp = TRUE;
        timerInitialize(TIMER2_MODULE, SYSCLK);
        timerStart(TIMER2_MODULE, 500000 , &gestic_timerisr );
        while(gestic_temp == TRUE){
            ProxR = tmd3990GetProx(2);
            if(ProxR > 20){
                gestic_temp = TRUE;
                timerInitialize(TIMER2_MODULE, SYSCLK);
                timerStart(TIMER2_MODULE, 500000 , &gestic_timerisr );
                while(gestic_temp == TRUE){
                    ProxL = tmd3990GetProx(1);
                    ProxR = tmd3990GetProx(2);
                    if((ProxL < 20) && (ProxR < 20)){
                        show_datum_state = 0;
                        show_akku_state = 0;
                        show_time_state = 1;
                        timerStop(TIMER2_MODULE);
                        gestic_temp = FALSE;
                    }
                }
            }
        }
    }

    //Bewegung von rechts nach links
    else if(ProxR > 20){
        gestic_temp = TRUE;
        timerInitialize(TIMER2_MODULE, SYSCLK);
        timerStart(TIMER2_MODULE, 500000 , &gestic_timerisr );
        while(gestic_temp == TRUE){
            ProxL = tmd3990GetProx(1);
            if(ProxL > 20){
                gestic_temp = TRUE;
                timerInitialize(TIMER2_MODULE, SYSCLK);
                timerStart(TIMER2_MODULE, 500000 , &gestic_timerisr );
                while(gestic_temp == TRUE){
                    ProxL = tmd3990GetProx(1);
                    ProxR = tmd3990GetProx(2);
                    if((ProxL < 20) && (ProxR < 20)){
                        show_datum_state = 1;
                        show_time_state = 0;
                        show_akku_state = 0;
                        gestic_temp = FALSE;
                    }
                }
            }
        }
    }
}

//Messen der aktuellen Helligkeit und überschreiben des AS1119 Helligkeitswertes
void Umgebung_anpassen(u16 diff){
    clear_left_old = tmd3990GetClear(1);                    //Aktueller Helligkeitswert der Umgebung
    clear_right_old = tmd3990GetClear(2);                   //Aktueller Helligkeitswert der Umgebung
    if((clear_left_old >= 0 )&& (clear_right_old >= 0))     //Falls kein Fehler aufgetreten ist
    {
        clear_var = (clear_left_old + clear_right_old)/2;   //Mittelwert
        clear_val_u8 = clear_var/diff + AS1119_min;    //skalieren des Helligkeit von 16bit auf 8bit

        //Helligkeit des ersten AS1119 ändern
        AS1119_LED(1, 0xFD, 0x0B);
        AS1119_LED(1, 0x05, clear_val_u8);
        AS1119_LED(1, 0x06, clear_val_u8);
        AS1119_LED(1, 0xFD, 0x01);

        //Helligkeit des zweiten AS1119 ändern
        AS1119_LED(2, 0xFD, 0x0B);
        AS1119_LED(2, 0x05, clear_val_u8);
        AS1119_LED(2, 0x06, clear_val_u8);
        AS1119_LED(2, 0xFD, 0x01);
    }
}

int Batterie_berechnen()
{
    int adc_wert[10];

    for( i = 0 ; i < 10 ; i++ )
    {
         wert=ADC1BUF0;
         adc_wert[i] = wert;
    }

    int m = 0;
    for( i = 0; i < 10; i++ )
    {
        m = m + adc_wert[i];
    }
    return m/10;
}

int main() {

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

    timerInitialize(TIMER1_MODULE, SYSCLK);
    timerInitialize(TIMER2_MODULE, SYSCLK);
    timerInitialize(TIMER3_MODULE, SYSCLK);

    //Timer1 ist der wichtigste Timer! Zeit
    timerStart(TIMER1_MODULE, GlobalTimerOVFvalue, &GlobalTimerInterrupt);

    AS1119_diff = 65535/(AS1119_max - AS1119_min);  //Differenz der AS1119 Helligkeitseinstellung

    //ADC initialisieren
    ADCInit();
    _TRISB5 = 0;
    PORTBbits.RB5 = 1;

    //Datum aktualisieren
    update_date();

    //Seriel
    init_uart();

    /*
    u8 x;
    for (x = 1; x <= 3; x++)
    {
        bootscreen();
    }*/

    #define ShowTimeDate
    
    while(1)
    {
        //Wenn Pic nicht im Ruhemodus ist
        if(show_nothing == 0)
        {
            //Bewegungserkennung
            MeasureGestic();

            //Anzeige Zeit / Datum / Akku
            //Zeit anzeigen
            if(show_time_state){
                //Doppelpunkt
                AS1119_WriteColumn(1, 16, 0x66);
                AS1119_WriteColumn(2, 1, 0x66);
                if(anzeige_aendern_z == 0){
                    show_num_8_6(stunde, minute);            //Zeitdarstellung
                }
                else{
                    show_time_8_6_sec(sekunde);            //Zeitdarstellung
                }
            }

            //Datum anzeigen
            else if(show_datum_state){
                if(anzeige_aendern_d == 0){
                    AS1119_WriteColumn(1, 16, 0xC0);
                    AS1119_WriteColumn(2, 1, 0xC0);
                    show_num_8_6(tag, monat);
                }
                else{
                    WTag_anzeige(wochentag);
                }
            }

            //Akkustand anzeigen
            else if(show_akku_state){
                Batterie(Akkustand);
            }
            
            //Automatisches Ändern von [Stunde:Minute] auf [:Skunde]
            if(temp1 >= anzeige_aendern_zeit){
                temp1 = 1;
                anzeige_aendern_z = 1-anzeige_aendern_z;
            }

            //Automatisches Ändern von [Tag.Monat] auf [Jahr]
            if(temp2 >= anzeige_aendern_datum){
                temp2 = 1;
                anzeige_aendern_d = 1-anzeige_aendern_d;
            }

            //Display an Umgebung anpassen
            //Umgebung_anpassen(AS1119_diff);
        }

        if(show_akku_aufladen)
        {
            show_nothing = 1;
            akku_aufladen();
        }

        if(show_menu == 1){
            if(show_time_state){
                //Doppelpunkt
                AS1119_WriteColumn(1, 16, 0x66);
                AS1119_WriteColumn(2, 1, 0x66);

                show_num_8_6(stunde, minute);
                _delay(40000);

                switch(aktuelle_stelle_aendern)
                {
                    case 1:  clear_num12(); break;
                    case 2:  clear_num34(); break;
                }
                _delay(40000);
            }

            //Datum anzeigen
            else if(show_datum_state){
                switch(aktuelle_stelle_aendern)
                {
                    case 1: AS1119_WriteColumn(1, 16, 0xC0);
                            AS1119_WriteColumn(2, 1, 0xC0);
                            show_num_8_6(tag, monat);
                            _delay(40000);
                            clear_num12(); break;

                    case 2: AS1119_WriteColumn(1, 16, 0xC0);
                            AS1119_WriteColumn(2, 1, 0xC0);
                            show_num_8_6(tag, monat);
                            _delay(40000);
                            clear_num34(); break;
                            
                    case 3: show_year(jahr);
                            _delay(40000);
                            clear_num3();
                            break;

                    case 4: show_year(jahr);
                            _delay(40000);
                            clear_num4();
                            break;
                }
                _delay(40000);
            }
        }
        
        if(clear_display_after_shut_down){
            clear_display();
            clear_display_after_shut_down = 1 - clear_display_after_shut_down;
        }

        //Batteriespannung messen
        wert=Batterie_berechnen();
        volt=((2*wert)/3.302075365387)/100;
        Akkustand = ceil((volt-3.1)*100/(4-3.1));
    }

    return (EXIT_SUCCESS);
}
