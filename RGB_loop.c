#include "p24FJ64GB002.h"
#include <i2c.h>
#define USE_AND_OR
#define LIB_BUILD

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL)

int Delay(long Time);
unsigned int I2C_Protocol(unsigned char byte2, unsigned char byte3);
unsigned int MasterputsI2C2_m(unsigned char * wrptr);

int main(void)
{
	AD1PCFG=0xFF;
	int i=0;
	int j=0;
	unsigned int config2, config1;
	unsigned char byte2 = 0,byte3 = 0,	byteCS0 = 0,
										byteCS1 = 0,
										byteCS2 = 0,
										byteCS3 = 0,
										byteCS4 = 0,
										byteCS5 = 0,
										byteCS6 = 0,
										byteCS7 = 0,
										byteCS8 = 0,
										byteCS9 = 0,
										byteCS10 = 0,
										byteCS11 = 0,
										byteCS12 = 0,
										byteCS13 = 0,
										byteCS14 = 0,
										byteCS15 = 0,
										byteCS16 = 0,
										byteCS17 = 0;

	unsigned char daten[]={
              				0x40,			//Frame Address Register, display picture, Frame 0
							0x00,			//Frame Play Register, no loop, one frame
							0x00,			//Frame Time Register, 487.5ms
							0x08,			//Display Option Register, use frame 0 intensity, CS0 to CS8
							0x01,			//Config Register, 2 matrixes
							0xFF,			//Current Source Block A Register, ca. 15 mA
							0xFF,			//Current Source Block B Register, ca. 15 mA
							0xFF,			//Current Source Block C Register, ca. 15 mA
							0x1E,			//Charge Pump Config Register, 1.0s, reduce supply option on, Charge Pump enable
							0x00,			//Open/Short Test Register, start test
							0x01,			//Shutdown Register, normal operation
							0xFF,'\0'};		//I2C Interface Monitoring Register, 32.7ms, I2C monitoring on

	/* Baud rate is set for 1000 kHz */
	config2 = 0x11;

	/* Configure I2C for 7 bit address mode */
	config1 = (I2C_ON & I2C_IDLE_CON & I2C_CLK_HLD &

         	   I2C_7BIT_ADD &

			   I2C_SLW_DIS & I2C_SM_DIS &

			   I2C_GCALL_DIS & I2C_STR_DIS &

			   I2C_NACK & I2C_ACK_DIS & I2C_RCV_DIS &

			   I2C_STOP_DIS & I2C_RESTART_DIS &

			   I2C_START_DIS);

	OpenI2C2(config1,config2);

	IdleI2C2();

	while(i<195)
	{
		//Selects Control Register
		if(i==0)
		{
			byte2=0xFD;
			byte3=0x0B;
			I2C_Protocol(byte2,byte3);
		}
		//Counts Control Register Address until 0x0B
		if(i>=1&&i<13)
		{
			byte2=i-1;
			byte3=daten[(i-1)];
			I2C_Protocol(byte2,byte3);
		}
		//Selects Data Frame 0
		if(i==13)
		{
			byte2=0xFD;
			byte3=0x01;
			I2C_Protocol(byte2,byte3);
		}
		//Set all LEDs on
		if(i>=14&&i<32)
		{
			byte2=i-14;
			byte3=0x00;
			I2C_Protocol(byte2,byte3);
		}
		//Set all LEDs to not blink
		if(i>=32&&i<50)
		{
			byte2=i-14;
			byte3=0x00;
			I2C_Protocol(byte2,byte3);
		}
		//Set all LEDs to medium brightness
		if(i>=50&&i<194)
		{
			byte2=i-14;
			byte3=0xFF;
			I2C_Protocol(byte2,byte3);
		}
		//Selects Control Register
		if(i==194)
		{
			byte2=0xFD;
			byte3=0x0B;
			I2C_Protocol(byte2,byte3);
		}

		if(i<195)
		{
			i++;
		}
	}
	//LED-Motion loop
	unsigned int ii = 0;


	//Register (ON/OFF) für R/G/B links,rechts und oben
	unsigned char rgbr_on_off_reg[] = {0x01, 0x03, 0x05};
	unsigned char rgbl_on_off_reg[] = {0x07, 0x09, 0x0B};
	unsigned char rgbo_on_off_reg[] = {0x0D, 0x0F, 0x11};

	//zulässige ansteuerung der 6 LEDs auf der RGB-Demomatrix von AMS rechts/unten
	//CS9: 10,11,12,13,14,15
	//CS10:26,27,28,29,30,31
	//CS11:42,43,44,45,46,47
	unsigned char LEDr_on_off_data[] = {0x04,0x08,0x10,0x20,0x40,0x80};

	unsigned char LEDr_intensity_r[] = {0x2E,0x2F,0x30,0x31,0x32,0x33};
	unsigned char LEDr_intensity_g[] = {0x3E,0x3F,0x40,0x41,0x42,0x43};
	unsigned char LEDr_intensity_b[] = {0x5E,0x5F,0x50,0x51,0x52,0x53};

	//zulässige ansteuerung der 6 LEDs auf der RGB-Demomatrix von AMS links/unten
	//CS12: 56,57,58,61,62,63
	//CS13: 72,73,74,77,78,79
	//CS14: 88,89,90,93,94,95
	unsigned char LEDl_on_off_data[] = {0x01,0x02,0x04,0x20,0x40,0x80};

	unsigned char LEDl_intensity_r[] = {0x5C,0x5D,0x5E,0x61,0x62,0x63};
	unsigned char LEDl_intensity_g[] = {0x6C,0x6D,0x6E,0x71,0x72,0x73};
	unsigned char LEDl_intensity_b[] = {0x7C,0x7D,0x7E,0x81,0x82,0x83};

	//zulässige ansteuerung der 6 LEDs auf der RGB-Demomatrix von AMS oben
	//CS15: 104,105,106,107,108,109
	//CS16: 120,121,122,123,124,125
	//CS17: 136,137,138,139,140,141
	unsigned char LEDo_on_off_data[] = {0x01,0x02,0x04,0x08,0x10,0x20};

	unsigned char LEDo_intensity_r[] = {0x8C,0x8D,0x8E,0x8F,0x90,0x91};
	unsigned char LEDo_intensity_g[] = {0x9C,0x9D,0x9E,0x9F,0xA0,0xA1};
	unsigned char LEDo_intensity_b[] = {0xAC,0xAD,0xAE,0xAF,0xB0,0xB1};

	int a = 0;
 	unsigned char LEDl_r= 0x00, LEDl_g= 0x00,LEDl_b = 0x00;
	unsigned char LEDr_r= 0x00, LEDr_g= 0x00,LEDr_b = 0x00;
	unsigned char LEDo_r= 0x00, LEDo_g= 0x00,LEDo_b = 0x00;

	while(j<4)
	{
		//Selects Data Frame 0
		if(j==0)
		{
			byte2=0xFD;
			byte3=0x01;
			I2C_Protocol(byte2,byte3);
		}
		if(j==1)
		{
				//*************************************************************
				//rote LEDs der Reihe nach einschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[0];
					LEDr_r = LEDr_r + LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_r);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[0];
					LEDl_r = LEDl_r + LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_r);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2=rgbo_on_off_reg[0];
					LEDo_r = LEDo_r + LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_r);
					Delay(10000);
				}
				//*************************************************************
				//grüne LEDs der Reihe nach einschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[1];
					LEDr_g = LEDr_g + LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_g);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[1];
					LEDl_g = LEDl_g + LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_g);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbo_on_off_reg[1];
					LEDo_g = LEDo_g + LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_g);
					Delay(10000);
				}

				//*************************************************************
				//blaue LEDs der Reihe nach einschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[2];
					LEDr_b = LEDr_b + LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_b);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[2];
					LEDl_b = LEDl_b + LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_b);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbo_on_off_reg[2];
					LEDo_b = LEDo_b + LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_b);
					Delay(10000);
				}
				//*************************************************************
				//rote LEDs der Reihe nach ausschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[0];
					LEDr_r = LEDr_r - LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_r);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[0];
					LEDl_r = LEDl_r - LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_r);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbo_on_off_reg[0];
					LEDo_r = LEDo_r - LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_r);
					Delay(10000);
				}
				//*************************************************************
				//grüne LEDs der Reihe nach ausschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[1];
					LEDr_g = LEDr_g - LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_g);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[1];
					LEDl_g = LEDl_g - LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_g);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbo_on_off_reg[1];
					LEDo_g = LEDo_g - LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_g);
					Delay(10000);
				}
				//*************************************************************
				//blaue LEDs der Reihe nach ausschalten
				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbr_on_off_reg[2];
					LEDr_b = LEDr_b - LEDr_on_off_data[ii];
					I2C_Protocol(byte2,LEDr_b);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbl_on_off_reg[2];
					LEDl_b = LEDl_b - LEDl_on_off_data[ii];
					I2C_Protocol(byte2,LEDl_b);
					Delay(10000);
				}

				for(ii=0;ii<=5;ii++)
				{
					byte2 = rgbo_on_off_reg[2];
					LEDo_b = LEDo_b - LEDo_on_off_data[ii];
					I2C_Protocol(byte2,LEDo_b);
					Delay(10000);
				}
				/*
				I2C_Protocol(0x01,0x00);
				I2C_Protocol(0x03,0x00);
				I2C_Protocol(0x05,0x00);
				I2C_Protocol(0x07,0x00);
				I2C_Protocol(0x09,0x00);
				I2C_Protocol(0x0B,0x00);
				I2C_Protocol(0x0D,0x00);
				I2C_Protocol(0x0F,0x00);
				I2C_Protocol(0x11,0x00);

				LEDl_r = 0x00, LEDl_g = 0x00,LEDl_b = 0x00;
				LEDr_r = 0x00, LEDr_g = 0x00,LEDr_b = 0x00;
				LEDo_r = 0x00, LEDo_g = 0x00,LEDo_b = 0x00;
				*/
		}

		//Selects Control Register
		if(j==2)
		{
			byte2=0xFD;
			byte3=0x0B;
			I2C_Protocol(byte2,byte3);
		}

		if(j<3)
		{
			j++;
		}

		if(j==3)
		{
			j=0;
		}
	}
	CloseI2C2();

	return 0;
}

unsigned int I2C_Protocol(unsigned char byte2, unsigned char byte3)
{

	unsigned char *wrptr;
	unsigned char data[]={0x00,0x00,'\0'};

	data[0]=byte2;
	data[1]=byte3;
	wrptr = data;

	StartI2C2();

	/* Wait till Start sequence is completed */

	while(I2C2CONbits.SEN);

	/* Clear interrupt flag */

	IFS3bits.MI2C2IF = 0;

	/* Write Slave address and set master for transmission */

	MasterWriteI2C2(0x70);

	/* Wait till address is transmitted */

	while(I2C2STATbits.TBF);  // 8 clock cycles

	while(!IFS3bits.MI2C2IF);

	IFS3bits.MI2C2IF = 0;     // Clear interrupt flag

	while(I2C2STATbits.ACKSTAT);

	/* Transmit string of data */

	MasterputsI2C2_m(wrptr);

	StopI2C2();

	/* Wait till stop sequence is completed */

	while(I2C2CONbits.PEN);


	return 0;
}

unsigned int MasterputsI2C2_m(unsigned char * wrptr)
{
	int j=0;
    while(j<2)                           //transmit data 2 times
    {
        if(MasterputcI2C2(*wrptr) == -1)            // write a byte
        return -3;                          //return with write collison error

        while(I2C2STATbits.TBF);             //Wait till data is transmitted.

        IdleI2C2();
        wrptr++;
		j++;
    }
    return 0;
}

int Delay(long Time)
{

	while(Time>0)

		Time--;

	return Time;
}

