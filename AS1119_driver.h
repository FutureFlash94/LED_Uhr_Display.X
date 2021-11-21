/*
 * File:    AS1119_driver.h
 * Author:  Filip Humaj
 * Datum:   9.9.2013
 *
 */

#ifndef AS1119_DRIVER_H
#define	AS1119_DRIVER_H

#define AS1119_I2C_ADDR_1 0x70
#define AS1119_I2C_ADDR_2 0x76

unsigned char AS1119WriteRegister(int i2caddr, unsigned char reg, unsigned char val);
unsigned char AS1119ReadRegister(int i2caddr, unsigned char reg, unsigned char *val);
void AS1119_initialisierung(int i2caddr);
void AS1119_LED(int i2caddr,unsigned char reg, unsigned char val);
int AS1119_WriteColumn(int i2caddr,unsigned char column, unsigned char val);
void Helligkeit(int i2caddr, int h);
void clear_display();
void fill_display();
void show_time(u8 minutes, u8 seconds);
void show_num_8_6(u8 left_num, u8 right_num);
void show_time_8_6_sec(u8 seconds);
void show_year(u16 J);
void bootscreen();
void Batterie(long double Akkustand);
void WTag_anzeige(int wochentag);
void akku_aufladen();
void bye();
void clear_num12();
void clear_num34();
void clear_num3();
void clear_num4();

#endif	/* AS1119_DRIVER_H */

