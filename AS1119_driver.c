/*
 * Name:    Filip Humaj
 * Datum:   9.9.2013
 *
 * AS1119_driver zur einfachen Initialisierung und Kommunikation mit dem PIC24
 */

#include <p24Fxxxx.h>
#include <i2c.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ams_types.h"
#include "GenericTypeDefs.h"
#include "errno.h"
#include "i2c_driver.h"
#include "AS1119_driver.h"

void _delay(unsigned long dauer);

unsigned char currenti2caddr;

/*******************************************************************************************
 *
 * Funktion: AS1119WriteRegister
 *
 * Beschreibung:    Schreibt ein Byte 'val' in das Register 'reg' des AS1119
 *                  Beim Auftreten eines Fehlers: Rückgabewert = -3
 *                  Ansonsten: Rückgabewert = 0
 ******************************************************************************************/
unsigned char AS1119WriteRegister(int i2caddr, unsigned char reg, unsigned char val) {
    i2cSwitchModule(I2C2_MODULE);

    u8 buf[2];
    buf[0] = reg;
    buf[1] = val;

    if(i2caddr == 1)
    {
        currenti2caddr = AS1119_I2C_ADDR_1;
    }
    else if(i2caddr == 2)
    {
        currenti2caddr = AS1119_I2C_ADDR_2;
    }
    else
    {
        return ERR_PARAM;
    }

    if (i2cTx(currenti2caddr, buf, 2) != 2)
    {
        RestartI2C2();
        return ERR_IO;
    }
    else
        return ERR_NONE;
}

/*******************************************************************************************
 * Funktion: AS1119WriteRegister
 *
 * Beschreibung:    Liest ein Byte '*val' in das Register 'reg' des AS1119
 *                  Beim Auftreten eines Fehlers: Rückgabewert -3
 *                  Ansonsten: Rückgabewert = 0
 ******************************************************************************************/
unsigned char AS1119ReadRegister(int i2caddr, unsigned char reg, unsigned char *val) {

    i2cSwitchModule(I2C2_MODULE);
    if(i2caddr == 1)
    {
        currenti2caddr = AS1119_I2C_ADDR_1;
    }
    else if(i2caddr == 2)
    {
        currenti2caddr = AS1119_I2C_ADDR_2;
    }
    else
    {
        return ERR_PARAM;
    }
    if (i2cRx(currenti2caddr, &reg, 1, val, 1) != 1)
        return ERR_IO;
    else
        return ERR_NONE;
}

void AS1119_initialisierung(int i2caddr){
    AS1119WriteRegister(i2caddr, 0xFD, 0x0B);    //Selects Control Register

    //Control Register Address
    AS1119WriteRegister(i2caddr, 0x00, 0x40);    //Frame Address Register
    AS1119WriteRegister(i2caddr, 0x01, 0x00);    //Frame Play Register
    AS1119WriteRegister(i2caddr, 0x02, 0x00);    //Frame Time Register
    AS1119WriteRegister(i2caddr, 0x03, 0x08);    //Display Option Register
    AS1119WriteRegister(i2caddr, 0x04, 0x01);    //Config Register, 2 matrixes
    AS1119WriteRegister(i2caddr, 0x05, 0x10);    //Current Source Block A Register
    AS1119WriteRegister(i2caddr, 0x06, 0x10);    //Current Source Block B Register
    AS1119WriteRegister(i2caddr, 0x07, 0x10);    //Current Source Block C Register
    AS1119WriteRegister(i2caddr, 0x08, 0x1E);    //Charge Pump Config Register
    AS1119WriteRegister(i2caddr, 0x09, 0x00);    //Open/Short Test Register
    AS1119WriteRegister(i2caddr, 0x0A, 0x01);    //Shutdown Register
    AS1119WriteRegister(i2caddr, 0x0B, 0x00);    //I2C Interface Monitoring Register
    AS1119WriteRegister(i2caddr, 0xFD, 0x01);    //Selects Data Frame 0

    int i = 0;
    //Ausschalten aller LEDs
    //Adresse von 0x00 (CS0) bis 0x11 (CS17)
    for(i = 0; i<=17; i++)
    {
        AS1119WriteRegister(i2caddr, i, 0x00);
    }

    //Alle LEDs auf kein Blinken setzten
    //Adresse von 0x12 (CS0) bis 0x23 (CS17)
    for(i = 18; i<=35; i++)
    {
        AS1119WriteRegister(i2caddr, i, 0x00);
    }

    //Helligkeit der LEDs setzten
    //Adresse von 0x24 (LED0) bis 0xB3 (LED143)
    for(i = 36; i<=179; i++)
    {
        AS1119WriteRegister(i2caddr, i, 0xFF);
    }
}

void AS1119_LED(int i2caddr,unsigned char reg, unsigned char val){
    AS1119WriteRegister(i2caddr,reg, val);
}

int AS1119_WriteColumn(int i2caddr,unsigned char column, unsigned char val){
    unsigned char buffer;   /*(val&(1<<0)): 0, wenn Bit 1 '0' ist, else 1*/
    switch(column)
    {
        case 1: case 2:  case 3: case 4: case 5: case 6: case 7: case 8:
                AS1119ReadRegister(i2caddr, 0x00, &buffer); AS1119WriteRegister(i2caddr, 0x00, abs(0xFF*(1-((val&(1<<0))>>0)) - (abs((0xFF*(1-((val&(1<<0))>>0)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x02, &buffer); AS1119WriteRegister(i2caddr, 0x02, abs(0xFF*(1-((val&(1<<1))>>1)) - (abs((0xFF*(1-((val&(1<<1))>>1)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x04, &buffer); AS1119WriteRegister(i2caddr, 0x04, abs(0xFF*(1-((val&(1<<2))>>2)) - (abs((0xFF*(1-((val&(1<<2))>>2)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x06, &buffer); AS1119WriteRegister(i2caddr, 0x06, abs(0xFF*(1-((val&(1<<3))>>3)) - (abs((0xFF*(1-((val&(1<<3))>>3)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x08, &buffer); AS1119WriteRegister(i2caddr, 0x08, abs(0xFF*(1-((val&(1<<4))>>4)) - (abs((0xFF*(1-((val&(1<<4))>>4)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x0A, &buffer); AS1119WriteRegister(i2caddr, 0x0A, abs(0xFF*(1-((val&(1<<5))>>5)) - (abs((0xFF*(1-((val&(1<<5))>>5)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x0C, &buffer); AS1119WriteRegister(i2caddr, 0x0C, abs(0xFF*(1-((val&(1<<6))>>6)) - (abs((0xFF*(1-((val&(1<<6))>>6)))-buffer)|(1<<(column-1)))));
                AS1119ReadRegister(i2caddr, 0x0E, &buffer); AS1119WriteRegister(i2caddr, 0x0E, abs(0xFF*(1-((val&(1<<7))>>7)) - (abs((0xFF*(1-((val&(1<<7))>>7)))-buffer)|(1<<(column-1)))));
        break;

        case 9: case 10:  case 11: case 12: case 13: case 14: case 15: case 16:
                AS1119ReadRegister(i2caddr, 0x01, &buffer); AS1119WriteRegister(i2caddr, 0x01, abs(0xFF*(1-((val&(1<<0))>>0)) - (abs((0xFF*(1-((val&(1<<0))>>0)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x03, &buffer); AS1119WriteRegister(i2caddr, 0x03, abs(0xFF*(1-((val&(1<<1))>>1)) - (abs((0xFF*(1-((val&(1<<1))>>1)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x05, &buffer); AS1119WriteRegister(i2caddr, 0x05, abs(0xFF*(1-((val&(1<<2))>>2)) - (abs((0xFF*(1-((val&(1<<2))>>2)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x07, &buffer); AS1119WriteRegister(i2caddr, 0x07, abs(0xFF*(1-((val&(1<<3))>>3)) - (abs((0xFF*(1-((val&(1<<3))>>3)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x09, &buffer); AS1119WriteRegister(i2caddr, 0x09, abs(0xFF*(1-((val&(1<<4))>>4)) - (abs((0xFF*(1-((val&(1<<4))>>4)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x0B, &buffer); AS1119WriteRegister(i2caddr, 0x0B, abs(0xFF*(1-((val&(1<<5))>>5)) - (abs((0xFF*(1-((val&(1<<5))>>5)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x0D, &buffer); AS1119WriteRegister(i2caddr, 0x0D, abs(0xFF*(1-((val&(1<<6))>>6)) - (abs((0xFF*(1-((val&(1<<6))>>6)))-buffer)|(1<<(column-9)))));
                AS1119ReadRegister(i2caddr, 0x0F, &buffer); AS1119WriteRegister(i2caddr, 0x0F, abs(0xFF*(1-((val&(1<<7))>>7)) - (abs((0xFF*(1-((val&(1<<7))>>7)))-buffer)|(1<<(column-9)))));

        break;

        default:
            return ERR_PARAM;
        break;
    }
    return 0;
}

void Helligkeit(int i2caddr,int h)
{
    AS1119_LED(i2caddr, 0xFD, 0x0B);
    AS1119_LED(i2caddr, 0x05, h);
    AS1119_LED(i2caddr, 0x06, h);
    AS1119_LED(i2caddr, 0xFD, 0x01);
}

void clear_display(){
    int i = 0;
    for(i = 0; i<=17; i++)
    {
        AS1119WriteRegister(1, i, 0x00);
        AS1119WriteRegister(2, i, 0x00);
    }
}

void fill_display(){
    int i = 0;
    for(i = 0; i<=17; i++)
    {
        AS1119WriteRegister(1, i, 0xFF);
        AS1119WriteRegister(2, i, 0xFF);
    }
}

//Uhrzeit anzeigen: Größe der Zahlen: 3 Spalten, 7 Zeilen
void show_time(u8 minutes, u8 seconds){
    u8 s1 = seconds%10;                   //Erste Stelle der Sekundenanzeige
    u8 s2 = (seconds-(seconds%10))/10;    //zweite Stelle der Sekundenanzeige
    u8 m1 = minutes%10;                   //Erste Stelle der Minutenanzeige
    u8 m2 = (minutes-(minutes%10))/10;    //zweite Stelle der Minutenanzeige

    switch(s1)
    {
        case 0:
            AS1119_WriteColumn(2, 5,0x7F);
            AS1119_WriteColumn(2, 6,0x41);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 1:
            AS1119_WriteColumn(2, 5,0x04);
            AS1119_WriteColumn(2, 6,0x02);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 2:
            AS1119_WriteColumn(2, 5,0x79);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x4F); break;

        case 3:
            AS1119_WriteColumn(2, 5,0x49);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 4:
            AS1119_WriteColumn(2, 5,0x0F);
            AS1119_WriteColumn(2, 6,0x08);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 5:
            AS1119_WriteColumn(2, 5,0x4F);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x79); break;

        case 6:
            AS1119_WriteColumn(2, 5,0x7F);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x79); break;

        case 7:
            AS1119_WriteColumn(2, 5,0x01);
            AS1119_WriteColumn(2, 6,0x01);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 8:
            AS1119_WriteColumn(2, 5,0x7F);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x7F); break;

        case 9:
            AS1119_WriteColumn(2, 5,0x4F);
            AS1119_WriteColumn(2, 6,0x49);
            AS1119_WriteColumn(2, 7,0x7F); break;
    }

    switch(s2)
    {
        case 0:
            AS1119_WriteColumn(2, 1,0x7F);
            AS1119_WriteColumn(2, 2,0x41);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 1:
            AS1119_WriteColumn(2, 1,0x04);
            AS1119_WriteColumn(2, 2,0x02);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 2:
            AS1119_WriteColumn(2, 1,0x79);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x4F); break;

        case 3:
            AS1119_WriteColumn(2, 1,0x49);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 4:
            AS1119_WriteColumn(2, 1,0x0F);
            AS1119_WriteColumn(2, 2,0x08);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 5:
            AS1119_WriteColumn(2, 1,0x4F);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x79); break;

       case 6:
            AS1119_WriteColumn(2, 1,0x7F);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x79); break;

        case 7:
            AS1119_WriteColumn(2, 1,0x01);
            AS1119_WriteColumn(2, 2,0x01);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 8:
            AS1119_WriteColumn(2, 1,0x7F);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x7F); break;

        case 9:
            AS1119_WriteColumn(2, 1,0x4F);
            AS1119_WriteColumn(2, 2,0x49);
            AS1119_WriteColumn(2, 3,0x7F); break;
    }

    switch(m1)
    {
        case 0:
            AS1119_WriteColumn(1, 5,0x7F);
            AS1119_WriteColumn(1, 6,0x41);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 1:
            AS1119_WriteColumn(1, 5,0x04);
            AS1119_WriteColumn(1, 6,0x02);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 2:
            AS1119_WriteColumn(1, 5,0x79);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x4F); break;

        case 3:
            AS1119_WriteColumn(1, 5,0x49);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 4:
            AS1119_WriteColumn(1, 5,0x0F);
            AS1119_WriteColumn(1, 6,0x08);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 5:
            AS1119_WriteColumn(1, 5,0x4F);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x79); break;

        case 6:
            AS1119_WriteColumn(1, 5,0x7F);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x79); break;

        case 7:
            AS1119_WriteColumn(1, 5,0x01);
            AS1119_WriteColumn(1, 6,0x01);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 8:
            AS1119_WriteColumn(1, 5,0x7F);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x7F); break;

        case 9:
            AS1119_WriteColumn(1, 5,0x4F);
            AS1119_WriteColumn(1, 6,0x49);
            AS1119_WriteColumn(1, 7,0x7F); break;
    }

    switch(m2)
    {
        case 0:
            AS1119_WriteColumn(1, 1,0x7F);
            AS1119_WriteColumn(1, 2,0x41);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 1:
            AS1119_WriteColumn(1, 1,0x04);
            AS1119_WriteColumn(1, 2,0x02);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 2:
            AS1119_WriteColumn(1, 1,0x79);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x4F); break;

        case 3:
            AS1119_WriteColumn(1, 1,0x49);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 4:
            AS1119_WriteColumn(1, 1,0x0F);
            AS1119_WriteColumn(1, 2,0x08);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 5:
            AS1119_WriteColumn(1, 1,0x4F);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x79); break;

       case 6:
            AS1119_WriteColumn(1, 1,0x7F);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x79); break;

        case 7:
            AS1119_WriteColumn(1, 1,0x01);
            AS1119_WriteColumn(1, 2,0x01);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 8:
            AS1119_WriteColumn(1, 1,0x7F);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x7F); break;

        case 9:
            AS1119_WriteColumn(1, 1,0x4F);
            AS1119_WriteColumn(1, 2,0x49);
            AS1119_WriteColumn(1, 3,0x7F); break;
    }
}

//Uhrzeit anzeigen: Größe der Zahl: 8 Zeilen - 6 Spalten
void show_num_8_6(u8 left_num, u8 right_num){
    u8 m1 = right_num%10;                   //erste Stelle der Minutenanzeige
    u8 m2 = (right_num-(right_num%10))/10;  //zweite Stelle der Minutenanzeige
    u8 h1 = left_num%10;                    //erste Stelle der Stundenanzeige
    u8 h2 = (left_num-(left_num%10))/10;    //zweite Stelle der Stundenanzeige

    AS1119_WriteColumn(1, 7, 0x00);
    AS1119_WriteColumn(1, 8, 0x00);
    AS1119_WriteColumn(1, 15, 0x00);
    AS1119_WriteColumn(2, 2, 0x00);
    AS1119_WriteColumn(2, 9, 0x00);
    AS1119_WriteColumn(2, 10, 0x00);

    switch(m1)
    {
        case 0:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xC3);
            AS1119_WriteColumn(2, 14, 0xC3);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 1:
            AS1119_WriteColumn(2, 11, 0x00);
            AS1119_WriteColumn(2, 12, 0x00);
            AS1119_WriteColumn(2, 13, 0x00);
            AS1119_WriteColumn(2, 14, 0x00);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 2:
            AS1119_WriteColumn(2, 11, 0xFB);
            AS1119_WriteColumn(2, 12, 0xFB);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xDF);
            AS1119_WriteColumn(2, 16, 0xDF);
            break;

        case 3:
            AS1119_WriteColumn(2, 11, 0xDB);
            AS1119_WriteColumn(2, 12, 0xDB);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 4:
            AS1119_WriteColumn(2, 11, 0x1F);
            AS1119_WriteColumn(2, 12, 0x1F);
            AS1119_WriteColumn(2, 13, 0x18);
            AS1119_WriteColumn(2, 14, 0x18);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 5:
            AS1119_WriteColumn(2, 11, 0xDF);
            AS1119_WriteColumn(2, 12, 0xDF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFB);
            AS1119_WriteColumn(2, 16, 0xFB);
            break;

        case 6:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFB);
            AS1119_WriteColumn(2, 16, 0xFB);
            break;

        case 7:
            AS1119_WriteColumn(2, 11, 0x03);
            AS1119_WriteColumn(2, 12, 0x03);
            AS1119_WriteColumn(2, 13, 0x03);
            AS1119_WriteColumn(2, 14, 0x03);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 8:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 9:
            AS1119_WriteColumn(2, 11, 0xDF);
            AS1119_WriteColumn(2, 12, 0xDF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;
    }

    switch(m2)
    {
        case 0:
            AS1119_WriteColumn(2, 3, 0xFF);
            AS1119_WriteColumn(2, 4, 0xFF);
            AS1119_WriteColumn(2, 5, 0xC3);
            AS1119_WriteColumn(2, 6, 0xC3);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 1:
            AS1119_WriteColumn(2, 3, 0x00);
            AS1119_WriteColumn(2, 4, 0x00);
            AS1119_WriteColumn(2, 5, 0x00);
            AS1119_WriteColumn(2, 6, 0x00);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 2:
            AS1119_WriteColumn(2, 3, 0xFB);
            AS1119_WriteColumn(2, 4, 0xFB);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xDF);
            AS1119_WriteColumn(2, 8, 0xDF);
            break;

        case 3:
            AS1119_WriteColumn(2, 3, 0xDB);
            AS1119_WriteColumn(2, 4, 0xDB);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 4:
            AS1119_WriteColumn(2, 3, 0x1F);
            AS1119_WriteColumn(2, 4, 0x1F);
            AS1119_WriteColumn(2, 5, 0x18);
            AS1119_WriteColumn(2, 6, 0x18);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 5:
            AS1119_WriteColumn(2, 3, 0xDF);
            AS1119_WriteColumn(2, 4, 0xDF);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xFB);
            AS1119_WriteColumn(2, 8, 0xFB);
            break;
    }

    switch(h1)
    {
        case 0:
            AS1119_WriteColumn(1, 9, 0xFF);
            AS1119_WriteColumn(1, 10, 0xFF);
            AS1119_WriteColumn(1, 11, 0xC3);
            AS1119_WriteColumn(1, 12, 0xC3);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 1:
            AS1119_WriteColumn(1, 9, 0x00);
            AS1119_WriteColumn(1, 10, 0x00);
            AS1119_WriteColumn(1, 11, 0x00);
            AS1119_WriteColumn(1, 12, 0x00);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 2:
            AS1119_WriteColumn(1, 9, 0xFB);
            AS1119_WriteColumn(1, 10, 0xFB);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xDF);
            AS1119_WriteColumn(1, 14, 0xDF);
            break;
        case 3:
            AS1119_WriteColumn(1, 9, 0xDB);
            AS1119_WriteColumn(1, 10, 0xDB);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 4:
            AS1119_WriteColumn(1, 9, 0x1F);
            AS1119_WriteColumn(1, 10, 0x1F);
            AS1119_WriteColumn(1, 11, 0x18);
            AS1119_WriteColumn(1, 12, 0x18);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 5:
            AS1119_WriteColumn(1, 9, 0xDF);
            AS1119_WriteColumn(1, 10, 0xDF);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xFB);
            AS1119_WriteColumn(1, 14, 0xFB);
            break;
        case 6:
            AS1119_WriteColumn(1, 9, 0xFF);
            AS1119_WriteColumn(1, 10, 0xFF);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xFB);
            AS1119_WriteColumn(1, 14, 0xFB);
            break;
        case 7:
            AS1119_WriteColumn(1, 9, 0x03);
            AS1119_WriteColumn(1, 10, 0x03);
            AS1119_WriteColumn(1, 11, 0x03);
            AS1119_WriteColumn(1, 12, 0x03);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 8:
            AS1119_WriteColumn(1, 9, 0xFF);
            AS1119_WriteColumn(1, 10, 0xFF);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
        case 9:
            AS1119_WriteColumn(1, 9, 0xDF);
            AS1119_WriteColumn(1, 10, 0xDF);
            AS1119_WriteColumn(1, 11, 0xDB);
            AS1119_WriteColumn(1, 12, 0xDB);
            AS1119_WriteColumn(1, 13, 0xFF);
            AS1119_WriteColumn(1, 14, 0xFF);
            break;
    }

    switch(h2)
    {
        case 0:
            AS1119_WriteColumn(1, 1, 0xFF);
            AS1119_WriteColumn(1, 2, 0xFF);
            AS1119_WriteColumn(1, 3, 0xC3);
            AS1119_WriteColumn(1, 4, 0xC3);
            AS1119_WriteColumn(1, 5, 0xFF);
            AS1119_WriteColumn(1, 6, 0xFF);
            break;
        case 1:
            AS1119_WriteColumn(1, 1, 0x00);
            AS1119_WriteColumn(1, 2, 0x00);
            AS1119_WriteColumn(1, 3, 0x00);
            AS1119_WriteColumn(1, 4, 0x00);
            AS1119_WriteColumn(1, 5, 0xFF);
            AS1119_WriteColumn(1, 6, 0xFF);
            break;
        case 2:
            AS1119_WriteColumn(1, 1, 0xFB);
            AS1119_WriteColumn(1, 2, 0xFB);
            AS1119_WriteColumn(1, 3, 0xDB);
            AS1119_WriteColumn(1, 4, 0xDB);
            AS1119_WriteColumn(1, 5, 0xDF);
            AS1119_WriteColumn(1, 6, 0xDF);
            break;
        case 3:
            AS1119_WriteColumn(1, 1, 0xDB);
            AS1119_WriteColumn(1, 2, 0xDB);
            AS1119_WriteColumn(1, 3, 0xDB);
            AS1119_WriteColumn(1, 4, 0xDB);
            AS1119_WriteColumn(1, 5, 0xFF);
            AS1119_WriteColumn(1, 6, 0xFF);
            break;
        default:
            AS1119_WriteColumn(1, 1, 0x00);
            AS1119_WriteColumn(1, 2, 0x00);
            AS1119_WriteColumn(1, 3, 0x00);
            AS1119_WriteColumn(1, 4, 0x00);
            AS1119_WriteColumn(1, 5, 0x00);
            AS1119_WriteColumn(1, 6, 0x00);
            break;

    }
}

//Anzeige der Sekunden mit Doppelpunkt
void show_time_8_6_sec(u8 seconds){
    u8 s1 = seconds%10;                 //Erste Stelle der Sekundenanzeige
    u8 s2 = (seconds-(seconds%10))/10;  //zweite Stelle der Sekundenanzeige
    int x;

    for(x=1; x<=15; x++)
    {
        AS1119_WriteColumn(1,x,0x00);
    }
    AS1119_WriteColumn(2,2,0x00);
    AS1119_WriteColumn(2,9,0x00);
    AS1119_WriteColumn(2,10,0x00);

    switch(s1)
    {
        case 0:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xC3);
            AS1119_WriteColumn(2, 14, 0xC3);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 1:
            AS1119_WriteColumn(2, 11, 0x00);
            AS1119_WriteColumn(2, 12, 0x00);
            AS1119_WriteColumn(2, 13, 0x00);
            AS1119_WriteColumn(2, 14, 0x00);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 2:
            AS1119_WriteColumn(2, 11, 0xFB);
            AS1119_WriteColumn(2, 12, 0xFB);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xDF);
            AS1119_WriteColumn(2, 16, 0xDF);
            break;

        case 3:
            AS1119_WriteColumn(2, 11, 0xDB);
            AS1119_WriteColumn(2, 12, 0xDB);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 4:
            AS1119_WriteColumn(2, 11, 0x1F);
            AS1119_WriteColumn(2, 12, 0x1F);
            AS1119_WriteColumn(2, 13, 0x18);
            AS1119_WriteColumn(2, 14, 0x18);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 5:
            AS1119_WriteColumn(2, 11, 0xDF);
            AS1119_WriteColumn(2, 12, 0xDF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFB);
            AS1119_WriteColumn(2, 16, 0xFB);
            break;

        case 6:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFB);
            AS1119_WriteColumn(2, 16, 0xFB);
            break;

        case 7:
            AS1119_WriteColumn(2, 11, 0x03);
            AS1119_WriteColumn(2, 12, 0x03);
            AS1119_WriteColumn(2, 13, 0x03);
            AS1119_WriteColumn(2, 14, 0x03);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 8:
            AS1119_WriteColumn(2, 11, 0xFF);
            AS1119_WriteColumn(2, 12, 0xFF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;

        case 9:
            AS1119_WriteColumn(2, 11, 0xDF);
            AS1119_WriteColumn(2, 12, 0xDF);
            AS1119_WriteColumn(2, 13, 0xDB);
            AS1119_WriteColumn(2, 14, 0xDB);
            AS1119_WriteColumn(2, 15, 0xFF);
            AS1119_WriteColumn(2, 16, 0xFF);
            break;
    }

    switch(s2)
    {
        case 0:
            AS1119_WriteColumn(2, 3, 0xFF);
            AS1119_WriteColumn(2, 4, 0xFF);
            AS1119_WriteColumn(2, 5, 0xC3);
            AS1119_WriteColumn(2, 6, 0xC3);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 1:
            AS1119_WriteColumn(2, 3, 0x00);
            AS1119_WriteColumn(2, 4, 0x00);
            AS1119_WriteColumn(2, 5, 0x00);
            AS1119_WriteColumn(2, 6, 0x00);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 2:
            AS1119_WriteColumn(2, 3, 0xFB);
            AS1119_WriteColumn(2, 4, 0xFB);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xDF);
            AS1119_WriteColumn(2, 8, 0xDF);
            break;

        case 3:
            AS1119_WriteColumn(2, 3, 0xDB);
            AS1119_WriteColumn(2, 4, 0xDB);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 4:
            AS1119_WriteColumn(2, 3, 0x1F);
            AS1119_WriteColumn(2, 4, 0x1F);
            AS1119_WriteColumn(2, 5, 0x18);
            AS1119_WriteColumn(2, 6, 0x18);
            AS1119_WriteColumn(2, 7, 0xFF);
            AS1119_WriteColumn(2, 8, 0xFF);
            break;

        case 5:
            AS1119_WriteColumn(2, 3, 0xDF);
            AS1119_WriteColumn(2, 4, 0xDF);
            AS1119_WriteColumn(2, 5, 0xDB);
            AS1119_WriteColumn(2, 6, 0xDB);
            AS1119_WriteColumn(2, 7, 0xFB);
            AS1119_WriteColumn(2, 8, 0xFB);
            break;
    }


}

void show_year(u16 J){
    u8 J12 = floor(J/100);  //Ersten 2 Stellen
    u8 J34 = J-(J12*100);   //Letzten 2 Stellen

    u8 J4 = J34%10;         //4. Stelle
    u8 J3 = (J34-J4)/10;      //3. Stelle
    u8 J2 = J12%10;         //2. Stelle
    u8 J1 = (J12-J2)/10;    //1. Stelle

    AS1119_WriteColumn(1,1,0x00);
    AS1119_WriteColumn(1,8,0x00);
    AS1119_WriteColumn(1,9,0x00);
    AS1119_WriteColumn(1,16,0x00);
    AS1119_WriteColumn(2,1,0x00);
    AS1119_WriteColumn(2,8,0x00);
    AS1119_WriteColumn(2,9,0x00);
    AS1119_WriteColumn(2,16,0x00);
    /*-------------------------------------------------------------------------------------------------------------------*/
    switch(J1)
    {
        case 0:
            AS1119_WriteColumn(1,2,0xFF);
            AS1119_WriteColumn(1,3,0xFF);
            AS1119_WriteColumn(1,4,0xC3);
            AS1119_WriteColumn(1,5,0xC3);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF);  break;
        case 1:
            AS1119_WriteColumn(1,2,0x00);
            AS1119_WriteColumn(1,3,0x00);
            AS1119_WriteColumn(1,4,0x00);
            AS1119_WriteColumn(1,5,0x00);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF); break;
        case 2:
            AS1119_WriteColumn(1,2,0xFB);
            AS1119_WriteColumn(1,3,0xFB);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xDF);
            AS1119_WriteColumn(1,7,0xDF); break;
        case 3:
            AS1119_WriteColumn(1,2,0xDB);
            AS1119_WriteColumn(1,3,0xDB);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF); break;
        case 4:
            AS1119_WriteColumn(1,2,0x1F);
            AS1119_WriteColumn(1,3,0x1F);
            AS1119_WriteColumn(1,4,0x18);
            AS1119_WriteColumn(1,5,0x18);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF); break;
        case 5:
            AS1119_WriteColumn(1,2,0xDF);
            AS1119_WriteColumn(1,3,0xDF);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xFB);
            AS1119_WriteColumn(1,7,0xFB);  break;
        case 6:
            AS1119_WriteColumn(1,2,0xFF);
            AS1119_WriteColumn(1,3,0xFF);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xFB);
            AS1119_WriteColumn(1,7,0xFB);  break;
        case 7:
            AS1119_WriteColumn(1,3,0x03);
            AS1119_WriteColumn(1,4,0x03);
            AS1119_WriteColumn(1,5,0x03);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF); break;
        case 8:
            AS1119_WriteColumn(1,2,0xFF);
            AS1119_WriteColumn(1,3,0xFF);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF); break;
        case 9:
            AS1119_WriteColumn(1,2,0xDF);
            AS1119_WriteColumn(1,3,0xDF);
            AS1119_WriteColumn(1,4,0xDB);
            AS1119_WriteColumn(1,5,0xDB);
            AS1119_WriteColumn(1,6,0xFF);
            AS1119_WriteColumn(1,7,0xFF);  break;
    }

    /*---------------------------------------------------------------------------------------------------------------*/
    switch(J2)
    {
        case 0:
            AS1119_WriteColumn(1,10,0xFF);
            AS1119_WriteColumn(1,11,0xFF);
            AS1119_WriteColumn(1,12,0xC3);
            AS1119_WriteColumn(1,13,0xC3);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 1:
            AS1119_WriteColumn(1,10,0x00);
            AS1119_WriteColumn(1,11,0x00);
            AS1119_WriteColumn(1,12,0x00);
            AS1119_WriteColumn(1,13,0x00);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 2:
            AS1119_WriteColumn(1,10,0xFB);
            AS1119_WriteColumn(1,11,0xFB);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xDF);
            AS1119_WriteColumn(1,15,0xDF);
        break;
        case 3:
            AS1119_WriteColumn(1,10,0xDB);
            AS1119_WriteColumn(1,11,0xDB);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 4:
            AS1119_WriteColumn(1,10,0x1F);
            AS1119_WriteColumn(1,11,0x1F);
            AS1119_WriteColumn(1,12,0x18);
            AS1119_WriteColumn(1,13,0x18);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 5:
            AS1119_WriteColumn(1,10,0xDF);
            AS1119_WriteColumn(1,11,0xDF);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xFB);
            AS1119_WriteColumn(1,15,0xFB);
        break;
        case 6:
            AS1119_WriteColumn(1,10,0xFF);
            AS1119_WriteColumn(1,11,0xFF);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xFB);
            AS1119_WriteColumn(1,15,0xFB);


        break;
        case 7:
            AS1119_WriteColumn(1,11,0x03);
            AS1119_WriteColumn(1,12,0x03);
            AS1119_WriteColumn(1,13,0x03);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 8:
            AS1119_WriteColumn(1,10,0xFF);
            AS1119_WriteColumn(1,11,0xFF);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
        case 9:
            AS1119_WriteColumn(1,10,0xDF);
            AS1119_WriteColumn(1,11,0xDF);
            AS1119_WriteColumn(1,12,0xDB);
            AS1119_WriteColumn(1,13,0xDB);
            AS1119_WriteColumn(1,14,0xFF);
            AS1119_WriteColumn(1,15,0xFF);
        break;
    }
    /*-------------------------------------------------------------------------------------------------------------------*/
    switch(J3)
    {
        case 0:
            AS1119_WriteColumn(2,2,0xFF);
            AS1119_WriteColumn(2,3,0xFF);
            AS1119_WriteColumn(2,4,0xC3);
            AS1119_WriteColumn(2,5,0xC3);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 1:
            AS1119_WriteColumn(2,2,0x00);
            AS1119_WriteColumn(2,3,0x00);
            AS1119_WriteColumn(2,4,0x00);
            AS1119_WriteColumn(2,5,0x00);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 2:
            AS1119_WriteColumn(2,2,0xFB);
            AS1119_WriteColumn(2,3,0xFB);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xDF);
            AS1119_WriteColumn(2,7,0xDF);
        break;
        case 3:
            AS1119_WriteColumn(2,2,0xDB);
            AS1119_WriteColumn(2,3,0xDB);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 4:
            AS1119_WriteColumn(2,2,0x1F);
            AS1119_WriteColumn(2,3,0x1F);
            AS1119_WriteColumn(2,4,0x18);
            AS1119_WriteColumn(2,5,0x18);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 5:
            AS1119_WriteColumn(2,2,0xDF);
            AS1119_WriteColumn(2,3,0xDF);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xFB);
            AS1119_WriteColumn(2,7,0xFB);
        break;
        case 6:
            AS1119_WriteColumn(2,2,0xFF);
            AS1119_WriteColumn(2,3,0xFF);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 7:
            AS1119_WriteColumn(2,3,0x03);
            AS1119_WriteColumn(2,4,0x03);
            AS1119_WriteColumn(2,5,0x03);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 8:
            AS1119_WriteColumn(2,2,0xFF);
            AS1119_WriteColumn(2,3,0xFF);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
        case 9:
            AS1119_WriteColumn(2,2,0xDF);
            AS1119_WriteColumn(2,3,0xDF);
            AS1119_WriteColumn(2,4,0xDB);
            AS1119_WriteColumn(2,5,0xDB);
            AS1119_WriteColumn(2,6,0xFF);
            AS1119_WriteColumn(2,7,0xFF);
        break;
    }

    switch(J4)
    {
        case 0:
            AS1119_WriteColumn(2,10,0xFF);
            AS1119_WriteColumn(2,11,0xFF);
            AS1119_WriteColumn(2,12,0xC3);
            AS1119_WriteColumn(2,13,0xC3);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF); break;
        case 1:
            AS1119_WriteColumn(2,10,0x00);
            AS1119_WriteColumn(2,11,0x00);
            AS1119_WriteColumn(2,12,0x00);
            AS1119_WriteColumn(2,13,0x00);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF); break;
    case 2:
            AS1119_WriteColumn(2,10,0xFB);
            AS1119_WriteColumn(2,11,0xFB);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xDF);
            AS1119_WriteColumn(2,15,0xDF); break;
    case 3:
            AS1119_WriteColumn(2,10,0xDB);
            AS1119_WriteColumn(2,11,0xDB);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF); break;
    case 4:
            AS1119_WriteColumn(2,10,0x1F);
            AS1119_WriteColumn(2,11,0x1F);
            AS1119_WriteColumn(2,12,0x18);
            AS1119_WriteColumn(2,13,0x18);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF); break;
    case 5:
            AS1119_WriteColumn(2,10,0xDF);
            AS1119_WriteColumn(2,11,0xDF);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xFB);
            AS1119_WriteColumn(2,15,0xFB);  break;
    case 6:
            AS1119_WriteColumn(2,10,0xFF);
            AS1119_WriteColumn(2,11,0xFF);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xFB);
            AS1119_WriteColumn(2,15,0xFB);  break;
    case 7:
            AS1119_WriteColumn(2,10,0x00);
            AS1119_WriteColumn(2,11,0x03);
            AS1119_WriteColumn(2,12,0x03);
            AS1119_WriteColumn(2,13,0x03);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF); break;
    case 8:
            AS1119_WriteColumn(2,10,0xFF);
            AS1119_WriteColumn(2,11,0xFF);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF);  break;
    case 9:
            AS1119_WriteColumn(2,10,0xDF);
            AS1119_WriteColumn(2,11,0xDF);
            AS1119_WriteColumn(2,12,0xDB);
            AS1119_WriteColumn(2,13,0xDB);
            AS1119_WriteColumn(2,14,0xFF);
            AS1119_WriteColumn(2,15,0xFF);  break;
    }
}

void bootscreen(){
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
    AS1119_WriteColumn(1,13,0x00);
    AS1119_WriteColumn(1,14,0xC3);
    AS1119_WriteColumn(1,15,0xA5);
    AS1119_WriteColumn(1,16,0x99);

    AS1119_WriteColumn(2,1,0x99);
    AS1119_WriteColumn(2,2,0xA5);
    AS1119_WriteColumn(2,3,0xC3);
    AS1119_WriteColumn(2,4,0x00);
    AS1119_WriteColumn(2,5,0x00);
    AS1119_WriteColumn(2,6,0x00);
    AS1119_WriteColumn(2,7,0x00);
    AS1119_WriteColumn(2,8,0x00);

    AS1119_WriteColumn(2,9,0x00);
    AS1119_WriteColumn(2,10,0x00);
    AS1119_WriteColumn(2,11,0x00);
    AS1119_WriteColumn(2,12,0x00);
    AS1119_WriteColumn(2,13,0x0);
    AS1119_WriteColumn(2,14,0x00);
    AS1119_WriteColumn(2,15,0x00);
    AS1119_WriteColumn(2,16,0x00);
    _delay(100000);

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
    AS1119_WriteColumn(1,13,0x7E);
    AS1119_WriteColumn(1,14,0x42);
    AS1119_WriteColumn(1,15,0x24);
    AS1119_WriteColumn(1,16,0x18);

    AS1119_WriteColumn(2,1,0x18);
    AS1119_WriteColumn(2,2,0x24);
    AS1119_WriteColumn(2,3,0x42);
    AS1119_WriteColumn(2,4,0x7E);
    AS1119_WriteColumn(2,5,0x00);
    AS1119_WriteColumn(2,6,0x00);
    AS1119_WriteColumn(2,7,0x00);
    AS1119_WriteColumn(2,8,0x00);

    AS1119_WriteColumn(2,9,0x00);
    AS1119_WriteColumn(2,10,0x00);
    AS1119_WriteColumn(2,11,0x00);
    AS1119_WriteColumn(2,12,0x00);
    AS1119_WriteColumn(2,13,0x0);
    AS1119_WriteColumn(2,14,0x00);
    AS1119_WriteColumn(2,15,0x00);
    AS1119_WriteColumn(2,16,0x00);
    _delay(100000);

}

void Batterie(long double Akkustand){
    if((Akkustand <= 100) && (Akkustand > 90))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xFF);
	AS1119_WriteColumn(2,3,0xFF);
	AS1119_WriteColumn(2,4,0xFF);
	AS1119_WriteColumn(2,5,0xFF);
	AS1119_WriteColumn(2,6,0xFF);
	AS1119_WriteColumn(2,7,0xFF);
	AS1119_WriteColumn(2,8,0xFF);
	AS1119_WriteColumn(2,9,0xFF);
	AS1119_WriteColumn(2,10,0xFF);
	AS1119_WriteColumn(2,11,0xFF);
	AS1119_WriteColumn(2,12,0xFF);
	AS1119_WriteColumn(2,13,0xFF);
	AS1119_WriteColumn(2,14,0xFF);
	AS1119_WriteColumn(2,15,0x3C);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 90) && (Akkustand > 80))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xFF);
	AS1119_WriteColumn(2,3,0xFF);
	AS1119_WriteColumn(2,4,0xFF);
	AS1119_WriteColumn(2,5,0xFF);
	AS1119_WriteColumn(2,6,0xFF);
	AS1119_WriteColumn(2,7,0xFF);
	AS1119_WriteColumn(2,8,0xFF);
	AS1119_WriteColumn(2,9,0xFF);
	AS1119_WriteColumn(2,10,0xFF);
	AS1119_WriteColumn(2,11,0xFF);
	AS1119_WriteColumn(2,12,0xFF);
	AS1119_WriteColumn(2,13,0xFF);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 80) && (Akkustand > 70))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xFF);
	AS1119_WriteColumn(2,3,0xFF);
	AS1119_WriteColumn(2,4,0xFF);
	AS1119_WriteColumn(2,5,0xFF);
	AS1119_WriteColumn(2,6,0xFF);
	AS1119_WriteColumn(2,7,0xFF);
	AS1119_WriteColumn(2,8,0xFF);
	AS1119_WriteColumn(2,9,0xFF);
	AS1119_WriteColumn(2,10,0xFF);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 70) && (Akkustand > 60))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xFF);
	AS1119_WriteColumn(2,3,0xFF);
	AS1119_WriteColumn(2,4,0xFF);
	AS1119_WriteColumn(2,5,0xFF);
	AS1119_WriteColumn(2,6,0xFF);
	AS1119_WriteColumn(2,7,0xFF);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 60) && (Akkustand > 50))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xFF);
	AS1119_WriteColumn(2,3,0xFF);
	AS1119_WriteColumn(2,4,0xFF);
	AS1119_WriteColumn(2,5,0xC3);
	AS1119_WriteColumn(2,6,0xC3);
	AS1119_WriteColumn(2,7,0xC3);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 50) && (Akkustand > 40))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xFF);
	AS1119_WriteColumn(1,16,0xFF);
	AS1119_WriteColumn(2,1,0xFF);
	AS1119_WriteColumn(2,2,0xC3);
	AS1119_WriteColumn(2,3,0xC3);
	AS1119_WriteColumn(2,4,0xC3);
	AS1119_WriteColumn(2,5,0xC3);
	AS1119_WriteColumn(2,6,0xC3);
	AS1119_WriteColumn(2,7,0xC3);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 40) && (Akkustand > 30))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xFF);
	AS1119_WriteColumn(1,13,0xFF);
	AS1119_WriteColumn(1,14,0xFF);
	AS1119_WriteColumn(1,15,0xC3);
	AS1119_WriteColumn(1,16,0xC3);
	AS1119_WriteColumn(2,1,0xC3);
	AS1119_WriteColumn(2,2,0xC3);
	AS1119_WriteColumn(2,3,0xC3);
	AS1119_WriteColumn(2,4,0xC3);
	AS1119_WriteColumn(2,5,0xC3);
	AS1119_WriteColumn(2,6,0xC3);
	AS1119_WriteColumn(2,7,0xC3);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 30) && (Akkustand > 20))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xFF);
	AS1119_WriteColumn(1,10,0xFF);
	AS1119_WriteColumn(1,11,0xFF);
	AS1119_WriteColumn(1,12,0xC3);
	AS1119_WriteColumn(1,13,0xC3);
	AS1119_WriteColumn(1,14,0xC3);
	AS1119_WriteColumn(1,15,0xC3);
	AS1119_WriteColumn(1,16,0xC3);
	AS1119_WriteColumn(2,1,0xC3);
	AS1119_WriteColumn(2,2,0xC3);
	AS1119_WriteColumn(2,3,0xC3);
	AS1119_WriteColumn(2,4,0xC3);
	AS1119_WriteColumn(2,5,0xC3);
	AS1119_WriteColumn(2,6,0xC3);
	AS1119_WriteColumn(2,7,0xC3);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 20) && (Akkustand > 10))
    {
	AS1119_WriteColumn(1,1,0xFF);
	AS1119_WriteColumn(1,2,0xFF);
	AS1119_WriteColumn(1,3,0xFF);
	AS1119_WriteColumn(1,4,0xFF);
	AS1119_WriteColumn(1,5,0xFF);
	AS1119_WriteColumn(1,6,0xFF);
	AS1119_WriteColumn(1,7,0xFF);
	AS1119_WriteColumn(1,8,0xFF);
	AS1119_WriteColumn(1,9,0xC3);
	AS1119_WriteColumn(1,10,0xC3);
	AS1119_WriteColumn(1,11,0xC3);
	AS1119_WriteColumn(1,12,0xC3);
	AS1119_WriteColumn(1,13,0xC3);
	AS1119_WriteColumn(1,14,0xC3);
	AS1119_WriteColumn(1,15,0xC3);
	AS1119_WriteColumn(1,16,0xC3);
	AS1119_WriteColumn(2,1,0xC3);
	AS1119_WriteColumn(2,2,0xC3);
	AS1119_WriteColumn(2,3,0xC3);
	AS1119_WriteColumn(2,4,0xC3);
	AS1119_WriteColumn(2,5,0xC3);
	AS1119_WriteColumn(2,6,0xC3);
	AS1119_WriteColumn(2,7,0xC3);
	AS1119_WriteColumn(2,8,0xC3);
	AS1119_WriteColumn(2,9,0xC3);
	AS1119_WriteColumn(2,10,0xC3);
	AS1119_WriteColumn(2,11,0xC3);
	AS1119_WriteColumn(2,12,0xC3);
	AS1119_WriteColumn(2,13,0xC3);
	AS1119_WriteColumn(2,14,0xE7);
	AS1119_WriteColumn(2,15,0x24);
	AS1119_WriteColumn(2,16,0x3C);
    }
    else if((Akkustand <= 10) && (Akkustand > 5))
    {
        AS1119_WriteColumn(1,1,0xFF);
        AS1119_WriteColumn(1,2,0xFF);
        AS1119_WriteColumn(1,3,0xFF);
        AS1119_WriteColumn(1,4,0xFF);
        AS1119_WriteColumn(1,5,0xFF);
        AS1119_WriteColumn(1,6,0xC3);
        AS1119_WriteColumn(1,7,0xC3);
        AS1119_WriteColumn(1,8,0xC3);
        AS1119_WriteColumn(1,9,0xC3);
        AS1119_WriteColumn(1,10,0xC3);
        AS1119_WriteColumn(1,11,0xC3);
        AS1119_WriteColumn(1,12,0xC3);
        AS1119_WriteColumn(1,13,0xC3);
        AS1119_WriteColumn(1,14,0xC3);
        AS1119_WriteColumn(1,15,0xC3);
        AS1119_WriteColumn(1,16,0xC3);
        AS1119_WriteColumn(2,1,0xC3);
        AS1119_WriteColumn(2,2,0xC3);
        AS1119_WriteColumn(2,3,0xC3);
        AS1119_WriteColumn(2,4,0xC3);
        AS1119_WriteColumn(2,5,0xC3);
        AS1119_WriteColumn(2,6,0xC3);
        AS1119_WriteColumn(2,7,0xC3);
        AS1119_WriteColumn(2,8,0xC3);
        AS1119_WriteColumn(2,9,0xC3);
        AS1119_WriteColumn(2,10,0xC3);
        AS1119_WriteColumn(2,11,0xC3);
        AS1119_WriteColumn(2,12,0xC3);
        AS1119_WriteColumn(2,13,0xC3);
        AS1119_WriteColumn(2,14,0xE7);
        AS1119_WriteColumn(2,15,0x24);
        AS1119_WriteColumn(2,16,0x3C);
    }
}

void WTag_anzeige(int wochentag){
    switch(wochentag)
    {
        case 1:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0xFF);
                    AS1119_WriteColumn(1,4,0xFF);
                    AS1119_WriteColumn(1,5,0x06);
                    AS1119_WriteColumn(1,6,0x0C);
                    AS1119_WriteColumn(1,7,0x18);
                    AS1119_WriteColumn(1,8,0x0C);

                    AS1119_WriteColumn(1,9,0x06);
                    AS1119_WriteColumn(1,10,0xFF);
                    AS1119_WriteColumn(1,11,0xFF);
                    AS1119_WriteColumn(1,12,0x00);
                    AS1119_WriteColumn(1,13,0x00);
                    AS1119_WriteColumn(1,14,0xFF);
                    AS1119_WriteColumn(1,15,0xFF);
                    AS1119_WriteColumn(1,16,0xC3);

                    AS1119_WriteColumn(2,1,0xC3);
                    AS1119_WriteColumn(2,2,0xC3);
                    AS1119_WriteColumn(2,3,0xFF);
                    AS1119_WriteColumn(2,4,0xFF);
                    AS1119_WriteColumn(2,5,0x00);
                    AS1119_WriteColumn(2,6,0x00);
                    AS1119_WriteColumn(2,7,0xFF);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0x0C);
                    AS1119_WriteColumn(2,10,0x18);
                    AS1119_WriteColumn(2,11,0x30);
                    AS1119_WriteColumn(2,12,0xFF);
                    AS1119_WriteColumn(2,13,0xFF);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
        break;
        case 2:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0x03);
                    AS1119_WriteColumn(1,5,0x03);
                    AS1119_WriteColumn(1,6,0x03);
                    AS1119_WriteColumn(1,7,0xFF);
                    AS1119_WriteColumn(1,8,0xFF);

                    AS1119_WriteColumn(1,9,0x03);
                    AS1119_WriteColumn(1,10,0x03);
                    AS1119_WriteColumn(1,11,0x03);
                    AS1119_WriteColumn(1,12,0x00);
                    AS1119_WriteColumn(1,13,0x00);
                    AS1119_WriteColumn(1,14,0xFF);
                    AS1119_WriteColumn(1,15,0xFF);
                    AS1119_WriteColumn(1,16,0xC0);

                    AS1119_WriteColumn(2,1,0xC0);
                    AS1119_WriteColumn(2,2,0xC0);
                    AS1119_WriteColumn(2,3,0xFF);
                    AS1119_WriteColumn(2,4,0xFF);
                    AS1119_WriteColumn(2,5,0x00);
                    AS1119_WriteColumn(2,6,0x00);
                    AS1119_WriteColumn(2,7,0xFF);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0xDB);
                    AS1119_WriteColumn(2,10,0xDB);
                    AS1119_WriteColumn(2,11,0xDB);
                    AS1119_WriteColumn(2,12,0xDB);
                    AS1119_WriteColumn(2,13,0x00);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
        case 3:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0xFF);
                    AS1119_WriteColumn(1,5,0xFF);
                    AS1119_WriteColumn(1,6,0x60);
                    AS1119_WriteColumn(1,7,0x30);
                    AS1119_WriteColumn(1,8,0x18);

                    AS1119_WriteColumn(1,9,0x30);
                    AS1119_WriteColumn(1,10,0x60);
                    AS1119_WriteColumn(1,11,0xFF);
                    AS1119_WriteColumn(1,12,0xFF);
                    AS1119_WriteColumn(1,13,0x00);
                    AS1119_WriteColumn(1,14,0x00);
                    AS1119_WriteColumn(1,15,0xFF);
                    AS1119_WriteColumn(1,16,0xFF);

                    AS1119_WriteColumn(2,1,0xDB);
                    AS1119_WriteColumn(2,2,0xDB);
                    AS1119_WriteColumn(2,3,0xDB);
                    AS1119_WriteColumn(2,4,0xDB);
                    AS1119_WriteColumn(2,5,0x00);
                    AS1119_WriteColumn(2,6,0x00);
                    AS1119_WriteColumn(2,7,0x00);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0xFF);
                    AS1119_WriteColumn(2,10,0xCF);
                    AS1119_WriteColumn(2,11,0xC3);
                    AS1119_WriteColumn(2,12,0x7E);
                    AS1119_WriteColumn(2,13,0x3C);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
        case 4:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0x03);
                    AS1119_WriteColumn(1,5,0x03);
                    AS1119_WriteColumn(1,6,0x03);
                    AS1119_WriteColumn(1,7,0xFF);
                    AS1119_WriteColumn(1,8,0xFF);

                    AS1119_WriteColumn(1,9,0x03);
                    AS1119_WriteColumn(1,10,0x03);
                    AS1119_WriteColumn(1,11,0x03);
                    AS1119_WriteColumn(1,12,0x00);
                    AS1119_WriteColumn(1,13,0x00);
                    AS1119_WriteColumn(1,14,0xFF);
                    AS1119_WriteColumn(1,15,0xFF);
                    AS1119_WriteColumn(1,16,0x18);

                    AS1119_WriteColumn(2,1,0x18);
                    AS1119_WriteColumn(2,2,0x18);
                    AS1119_WriteColumn(2,3,0xFF);
                    AS1119_WriteColumn(2,4,0xFF);
                    AS1119_WriteColumn(2,5,0x00);
                    AS1119_WriteColumn(2,6,0x00);
                    AS1119_WriteColumn(2,7,0xFF);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0xC0);
                    AS1119_WriteColumn(2,10,0xC0);
                    AS1119_WriteColumn(2,11,0xC0);
                    AS1119_WriteColumn(2,12,0xFF);
                    AS1119_WriteColumn(2,13,0xFF);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
        case 5:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0x00);
                    AS1119_WriteColumn(1,5,0x00);
                    AS1119_WriteColumn(1,6,0x00);
                    AS1119_WriteColumn(1,7,0x00);
                    AS1119_WriteColumn(1,8,0xFF);

                    AS1119_WriteColumn(1,9,0xFF);
                    AS1119_WriteColumn(1,10,0x1B);
                    AS1119_WriteColumn(1,11,0x1B);
                    AS1119_WriteColumn(1,12,0x03);
                    AS1119_WriteColumn(1,13,0x03);
                    AS1119_WriteColumn(1,14,0x00);
                    AS1119_WriteColumn(1,15,0x00);
                    AS1119_WriteColumn(1,16,0xFF);

                    AS1119_WriteColumn(2,1,0xFF);
                    AS1119_WriteColumn(2,2,0x13);
                    AS1119_WriteColumn(2,3,0x13);
                    AS1119_WriteColumn(2,4,0xFF);
                    AS1119_WriteColumn(2,5,0xEE);
                    AS1119_WriteColumn(2,6,0x00);
                    AS1119_WriteColumn(2,7,0x00);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0xFF);
                    AS1119_WriteColumn(2,10,0x00);
                    AS1119_WriteColumn(2,11,0x00);
                    AS1119_WriteColumn(2,12,0x00);
                    AS1119_WriteColumn(2,13,0x00);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
        case 6:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0xDF);
                    AS1119_WriteColumn(1,5,0xDF);
                    AS1119_WriteColumn(1,6,0xDB);
                    AS1119_WriteColumn(1,7,0xDB);
                    AS1119_WriteColumn(1,8,0xFB);

                    AS1119_WriteColumn(1,9,0xFB);
                    AS1119_WriteColumn(1,10,0x00);
                    AS1119_WriteColumn(1,11,0x00);
                    AS1119_WriteColumn(1,12,0xFF);
                    AS1119_WriteColumn(1,13,0xFF);
                    AS1119_WriteColumn(1,14,0x1B);
                    AS1119_WriteColumn(1,15,0x1B);
                    AS1119_WriteColumn(1,16,0x1B);

                    AS1119_WriteColumn(2,1,0xFF);
                    AS1119_WriteColumn(2,2,0xFF);
                    AS1119_WriteColumn(2,3,0x00);
                    AS1119_WriteColumn(2,4,0x00);
                    AS1119_WriteColumn(2,5,0x03);
                    AS1119_WriteColumn(2,6,0x03);
                    AS1119_WriteColumn(2,7,0x03);
                    AS1119_WriteColumn(2,8,0xFF);

                    AS1119_WriteColumn(2,9,0xFF);
                    AS1119_WriteColumn(2,10,0x03);
                    AS1119_WriteColumn(2,11,0x03);
                    AS1119_WriteColumn(2,12,0x03);
                    AS1119_WriteColumn(2,13,0x00);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
        case 0:
                    AS1119_WriteColumn(1,1,0x00);
                    AS1119_WriteColumn(1,2,0x00);
                    AS1119_WriteColumn(1,3,0x00);
                    AS1119_WriteColumn(1,4,0xDF);
                    AS1119_WriteColumn(1,5,0xDF);
                    AS1119_WriteColumn(1,6,0xDB);
                    AS1119_WriteColumn(1,7,0xDB);
                    AS1119_WriteColumn(1,8,0xFB);

                    AS1119_WriteColumn(1,9,0xFB);
                    AS1119_WriteColumn(1,10,0x00);
                    AS1119_WriteColumn(1,11,0x00);
                    AS1119_WriteColumn(1,12,0xFF);
                    AS1119_WriteColumn(1,13,0xFF);
                    AS1119_WriteColumn(1,14,0xC0);
                    AS1119_WriteColumn(1,15,0xC0);
                    AS1119_WriteColumn(1,16,0xC0);

                    AS1119_WriteColumn(2,1,0xFF);
                    AS1119_WriteColumn(2,2,0xFF);
                    AS1119_WriteColumn(2,3,0x00);
                    AS1119_WriteColumn(2,4,0x00);
                    AS1119_WriteColumn(2,5,0xFF);
                    AS1119_WriteColumn(2,6,0xFF);
                    AS1119_WriteColumn(2,7,0x0C);
                    AS1119_WriteColumn(2,8,0x18);

                    AS1119_WriteColumn(2,9,0x30);
                    AS1119_WriteColumn(2,10,0xFF);
                    AS1119_WriteColumn(2,11,0xFF);
                    AS1119_WriteColumn(2,12,0x00);
                    AS1119_WriteColumn(2,13,0x00);
                    AS1119_WriteColumn(2,14,0x00);
                    AS1119_WriteColumn(2,15,0x00);
                    AS1119_WriteColumn(2,16,0x00);
            break;
    }
}

void akku_aufladen(){
    AS1119_WriteColumn(1,1,0x00);
    AS1119_WriteColumn(1,2,0x00);
    AS1119_WriteColumn(1,3,0xDF);
    AS1119_WriteColumn(1,4,0xDF);
    AS1119_WriteColumn(1,5,0x00);
    AS1119_WriteColumn(1,6,0x00);
    AS1119_WriteColumn(1,7,0x00);
    AS1119_WriteColumn(1,8,0x00);

    AS1119_WriteColumn(1,9,0x00);
    AS1119_WriteColumn(1,10,0x00);
    AS1119_WriteColumn(1,11,0x00);
    AS1119_WriteColumn(1,12,0x18);
    AS1119_WriteColumn(1,13,0x18);
    AS1119_WriteColumn(1,14,0x18);
    AS1119_WriteColumn(1,15,0x18);
    AS1119_WriteColumn(1,16,0x18);

    AS1119_WriteColumn(2,1,0x7E);
    AS1119_WriteColumn(2,2,0x3C);
    AS1119_WriteColumn(2,3,0x18);
    AS1119_WriteColumn(2,4,0x00);
    AS1119_WriteColumn(2,5,0x00);
    AS1119_WriteColumn(2,6,0x00);
    AS1119_WriteColumn(2,7,0x00);
    AS1119_WriteColumn(2,8,0x00);

    AS1119_WriteColumn(2,9,0x00);
    AS1119_WriteColumn(2,10,0x00);
    AS1119_WriteColumn(2,11,0xFE);
    AS1119_WriteColumn(2,12,0xC1);
    AS1119_WriteColumn(2,13,0xC1);
    AS1119_WriteColumn(2,14,0xC1);
    AS1119_WriteColumn(2,15,0xFE);
    AS1119_WriteColumn(2,16,0x00);
    _delay(100000);

    AS1119_WriteColumn(1,1,0x00);
    AS1119_WriteColumn(1,2,0x00);
    AS1119_WriteColumn(1,3,0xDF);
    AS1119_WriteColumn(1,4,0xDF);
    AS1119_WriteColumn(1,5,0x00);
    AS1119_WriteColumn(1,6,0x00);
    AS1119_WriteColumn(1,7,0x00);
    AS1119_WriteColumn(1,8,0x00);

    AS1119_WriteColumn(1,9,0x00);
    AS1119_WriteColumn(1,10,0x00);
    AS1119_WriteColumn(1,11,0x00);
    AS1119_WriteColumn(1,12,0x18);
    AS1119_WriteColumn(1,13,0x18);
    AS1119_WriteColumn(1,14,0x18);
    AS1119_WriteColumn(1,15,0x18);
    AS1119_WriteColumn(1,16,0x18);

    AS1119_WriteColumn(2,1,0x7E);
    AS1119_WriteColumn(2,2,0x3C);
    AS1119_WriteColumn(2,3,0x18);
    AS1119_WriteColumn(2,4,0x00);
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
    _delay(100000);
}

void bye(){
    AS1119_WriteColumn(1,1,0x00);
    AS1119_WriteColumn(1,2,0x00);
    AS1119_WriteColumn(1,3,0x00);
    AS1119_WriteColumn(1,4,0x00);
    AS1119_WriteColumn(1,5,0x00);
    AS1119_WriteColumn(1,6,0xFF);
    AS1119_WriteColumn(1,7,0xFF);
    AS1119_WriteColumn(1,8,0xDB);

    AS1119_WriteColumn(1,9,0xDB);
    AS1119_WriteColumn(1,10,0xFF);
    AS1119_WriteColumn(1,11,0x66);
    AS1119_WriteColumn(1,12,0x00);
    AS1119_WriteColumn(1,13,0x00);
    AS1119_WriteColumn(1,14,0x03);
    AS1119_WriteColumn(1,15,0x06);
    AS1119_WriteColumn(1,16,0x0C);

    AS1119_WriteColumn(2,1,0xF8);
    AS1119_WriteColumn(2,2,0xF8);
    AS1119_WriteColumn(2,3,0x0C);
    AS1119_WriteColumn(2,4,0x06);
    AS1119_WriteColumn(2,5,0x03);
    AS1119_WriteColumn(2,6,0x00);
    AS1119_WriteColumn(2,7,0x00);
    AS1119_WriteColumn(2,8,0xFF);

    AS1119_WriteColumn(2,9,0xFF);
    AS1119_WriteColumn(2,10,0xDB);
    AS1119_WriteColumn(2,11,0xDB);
    AS1119_WriteColumn(2,12,0xDB);
    AS1119_WriteColumn(2,13,0xDB);
    AS1119_WriteColumn(2,14,0x00);
    AS1119_WriteColumn(2,15,0x00);
    AS1119_WriteColumn(2,16,0x00);
}

void clear_num12(){
    int i;
    for(i = 1; i <= 15; i++){
    AS1119_WriteColumn(1,i,0x00);
    }
}

void clear_num34(){
    int i;
    for(i = 2; i <= 16; i++){
    AS1119_WriteColumn(2,i,0x00);
    }
}

void clear_num3(){
    int i;
    for(i = 2; i <= 7; i++){
    AS1119_WriteColumn(2,i,0x00);
    }
}

void clear_num4(){
    int i;
    for(i = 10; i <= 16; i++){
    AS1119_WriteColumn(2,i,0x00);
    }
}

