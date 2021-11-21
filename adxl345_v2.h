/* 
 * File:   adxl345_v2.h
 * Author: emu
 *
 * Created on 28. März 2014, 21:40
 */

#ifndef ADXL345_V2_H
#define	ADXL345_V2_H

#include <stdio.h>
#include <stdlib.h>
#include "errno.h"
#include "i2c_driver.h"
#include <p24Fxxxx.h>

#define XL345_SLAVE_ADDR 0x1d
#define XL345_ALT_ADDR 0x53

/* additional I2C defines for communications functions that need the
address shifted with the read/write bit appended*/
#define XL345_SLAVE_WRITE       0x53//0x3A//XL345_SLAVE_ADDR << 1 | 0x01
#define XL345_SLAVE_READ        0x54//0x3B//XL345_SLAVE_ADDR << 1 | 0x00
#define XL345_ALT_WRITE         0x53//0xA6//XL345_ALT_ADDR << 1 | 0x01
#define XL345_ALT_READ          0x54//0xA7//XL345_ALT_ADDR << 1 | 0x00

/* ------- REGISTER MAP ------- */
#define XL345_DEVID             0x00    //(Read Only)
#define XL345_RESERVED1         0x01    //(Not Readable)
#define XL345_THRESH_TAP        0x1d    //(Read/Write)
#define XL345_OFSX              0x1e    //(Read/Write)
#define XL345_OFSY              0x1f    //(Read/Write)
#define XL345_OFSZ              0x20    //(Read/Write)
#define XL345_DUR               0x21    //(Read/Write)
#define XL345_LATENT            0x22    //(Read/Write)
#define XL345_WINDOW            0x23    //(Read/Write)
#define XL345_THRESH_ACT        0x24    //(Read/Write)
#define XL345_THRESH_INACT      0x25    //(Read/Write)
#define XL345_TIME_INACT        0x26    //(Read/Write)
#define XL345_ACT_INACT_CTL     0x27    //(Read/Write)
#define XL345_THRESH_FF         0x28    //(Read/Write)
#define XL345_TIME_FF           0x29    //(Read/Write)
#define XL345_TAP_AXES          0x2a    //(Read/Write)
#define XL345_ACT_TAP_STATUS    0x2b    //(Read Only)
#define XL345_BW_RATE           0x2c    //(Read/Write)
#define XL345_POWER_CTL         0x2d    //(Read/Write)
#define XL345_INT_ENABLE        0x2e    //(Read/Write)
#define XL345_INT_MAP           0x2f    //(Read/Write)
#define XL345_INT_SOURCE        0x30    //(Read Only)
#define XL345_DATA_FORMAT       0x31    //(Read/Write)
#define XL345_DATAX0            0x32    //(Read Only)
#define XL345_DATAX1            0x33    //(Read Only)
#define XL345_DATAY0            0x34    //(Read Only)
#define XL345_DATAY1            0x35    //(Read Only)
#define XL345_DATAZ0            0x36    //(Read Only)
#define XL345_DATAZ1            0x37    //(Read Only)
#define XL345_FIFO_CTL          0x38    //(Read/Write)
#define XL345_FIFO_STATUS       0x39    //(Read Only)
/*----------------------------------------------------------------------
Bit field definitions and register values
----------------------------------------------------------------------*/
//#define XL345_
/* register values for DEVID
*/
/* The device ID should always read this value, The customer does not
need to use this value but it can be read to check that the
device can communicate*/
#define XL345_ID                0xe5 //dieser wert sollte im Register XL345_DEVID stehen --> Zur kontrolle ob devise angeschlossen!!

/* Reserved soft reset value*/
#define XL345_SOFT_RESET        0x52

/* Registers THRESH_TAP through TIME_INACT take only 8-bit values
There are no specific bit fields in these registers*/

/* Register 0x27 ACT_INACT_CTL (Read/Write) */
#define XL345_INACT_Z_ENABLE    0x01
#define XL345_INACT_Z_DISABLE   0x00
#define XL345_INACT_Y_ENABLE    0x02
#define XL345_INACT_Y_DISABLE   0x00
#define XL345_INACT_X_ENABLE    0x04
#define XL345_INACT_X_DISABLE   0x00
#define XL345_INACT_AC          0x08
#define XL345_INACT_DC          0x00
#define XL345_ACT_Z_ENABLE      0x10
#define XL345_ACT_Z_DISABLE     0x00
#define XL345_ACT_Y_ENABLE      0x20
#define XL345_ACT_Y_DISABLE     0x00
#define XL345_ACT_X_ENABLE      0x40
#define XL345_ACT_X_DISABLE     0x00
#define XL345_ACT_AC            0x80
#define XL345_ACT_DC            0x00


/* Register 0x2A TAP_AXES (Read/Write) */
#define XL345_TAP_Z_ENABLE      0x01
#define XL345_TAP_Z_DISABLE     0x00
#define XL345_TAP_Y_ENABLE      0x02
#define XL345_TAP_Y_DISABLE     0x00
#define XL345_TAP_X_ENABLE      0x04
#define XL345_TAP_X_DISABLE     0x00
#define XL345_TAP_SUPPRESS      0x08

/* Register 0x2B ACT_TAP_STATUS (Read Only) */
#define XL345_TAP_Z_SOURCE      0x01
#define XL345_TAP_Y_SOURCE      0x02
#define XL345_TAP_X_SOURCE      0x04
#define XL345_STAT_ASLEEP       0x08
#define XL345_ACT_Z_SOURCE      0x10
#define XL345_ACT_Y_SOURCE      0x20
#define XL345_ACT_X_SOURCE      0x40


/* Register 0x2C BW_RATE (Read/Write) */

#define XL345_LOW_POWER             0x08
#define XL345_NORMAL_POWER          0x00

/* Expresed as Output Data Rate (Hz) */
// ++++ NORMAL POWER MODE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define XL345_RATE_3200_HZ       0x0f    //140uA
#define XL345_RATE_1600_HZ       0x0e    //90uA
#define XL345_RATE_800_HZ        0x0d    //140uA
#define XL345_RATE_400_HZ        0x0c    //140uA
#define XL345_RATE_200_HZ        0x0b    //140uA
#define XL345_RATE_100_HZ        0x0a    //140uA
#define XL345_RATE_50_HZ         0x09    //90uA
#define XL345_RATE_25_HZ         0x08    //60uA
#define XL345_RATE_12_5_HZ       0x07    //50uA
#define XL345_RATE_6_25_HZ       0x06    //45uA
#define XL345_RATE_3_13_HZ       0x05    //40uA
#define XL345_RATE_1_56_HZ       0x04    //34uA
#define XL345_RATE_0_78_HZ       0x03    //23uA
#define XL345_RATE_0_39_HZ       0x02    //23uA
#define XL345_RATE_0_20_HZ       0x01    //23uA
#define XL345_RATE_0_01_HZ       0x00    //23uA

/* Expressed as output bandwidth */
/* Use either the bandwidth or rate code, whichever is more appropriate for your application */
/* Bandwidth (Hz) */
#define XL345_BW_1600_HZ         0x0f    //140uA
#define XL345_BW_800_HZ          0x0e    //90uA
#define XL345_BW_400_HZ          0x0d    //140uA
#define XL345_BW_200_HZ          0x0c    //140uA
#define XL345_BW_100_HZ          0x0b    //140uA
#define XL345_BW_50_HZ           0x0a    //140uA
#define XL345_BW_25_HZ           0x09    //90uA
#define XL345_BW_12_5_HZ         0x08    //60uA
#define XL345_BW_6_25_HZ         0x07    //50uA
#define XL345_BW_3_13_HZ         0x06    //45uA
#define XL345_BW_1_56_HZ         0x05    //40uA
#define XL345_BW_0_78_HZ         0x04    //34uA
#define XL345_BW_0_39_HZ         0x03    //23uA
#define XL345_BW_0_20_HZ         0x02    //23uA
#define XL345_BW_0_10_HZ         0x01    //23uA
#define XL345_BW_0_05_HZ         0x00    //23uA

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++ LOW POWER MODE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* Expresed as Output Data Rate (Hz) */
#define XL345_LOW_POWER_RATE_400_HZ     0x0C
#define XL345_LOW_POWER_RATE_200_HZ     0x0B
#define XL345_LOW_POWER_RATE_100_HZ     0x0A
#define XL345_LOW_POWER_RATE_50_HZ      0x09
#define XL345_LOW_POWER_RATE_25_HZ      0x08
#define XL345_LOW_POWER_RATE_12_5_HZ    0x07


/* Expressed as output bandwidth */
#define XL345_LOW_POWER_BW_200_HZ      0x0C
#define XL345_LOW_POWER_BW_100_HZ      0x0B
#define XL345_LOW_POWER_BW_50_HZ       0x0A
#define XL345_LOW_POWER_BW_25_HZ       0x09
#define XL345_LOW_POWER_BW_12_5_HZ     0x08
#define XL345_LOW_POWER_BW_6_25_HZ     0x07



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/* Register 0x2D - POWER_CTL (Read/Write)
*/
#define XL345_WAKEUP_8_HZ           0x00
#define XL345_WAKEUP_4_HZ           0x01
#define XL345_WAKEUP_2_HZ           0x02
#define XL345_WAKEUP_1_HZ           0x03
#define XL345_SLEEP                 0x04
#define XL345_MEASURE               0x08
#define XL345_STANDBY               0x00
#define XL345_AUTO_SLEEP            0x10
#define XL345_ACT_INACT_SERIAL      0x20
#define XL345_ACT_INACT_CONCURRENT  0x00

/* Bit values in INT_ENABLE, INT_MAP, and INT_SOURCE are identical.
Use these bit values to read or write any of these registers.*/

/* Register 0x2E INT_ENABLE (Read/Write) bzw. */

/*
 Setting bits in this register to a value of 1 enables their respective
functions to generate interrupts, whereas a value of 0 prevents
the functions from generating interrupts. The DATA_READY,
watermark, and overrun bits enable only the interrupt output;
the functions are always enabled. It is recommended that interrupts
be configured before enabling their outputs.
 */
#define XL345_INT_ENABLE_OVERRUN            0x01
#define XL345_INT_DISABLE_OVERRUN           0x00
#define XL345_INT_ENABLE_WATERMARK          0x02
#define XL345_INT_DISABLE_WATERMARK         0x00
#define XL345_INT_ENABLE_FREEFALL           0x04
#define XL345_INT_DISABLE_FREEFALL          0x00
#define XL345_INT_ENABLE_INACTIVITY         0x08
#define XL345_INT_DISABLE_INACTIVITY        0x00
#define XL345_INT_ENABLE_ACTIVITY           0x10
#define XL345_INT_DISABLE_ACTIVITY          0x00
#define XL345_INT_ENABLE_DOUBLETAP          0x20
#define XL345_INT_DISABLE_DOUBLETAP         0x00
#define XL345_INT_ENABLE_SINGLETAP          0x40
#define XL345_INT_DISABLE_SINGLETAP         0x00
#define XL345_INT_ENABLE_DATAREADY          0x80
#define XL345_INT_DISABLE_DATAREADY         0x00

/* Register 0x2F INT_MAP (R/W) bzw. */

/*
Any bits set to 0 in this register send their respective interrupts to
the INT1 pin, whereas bits set to 1 send their respective interrupts
to the INT2 pin. All selected interrupts for a given pin are OR?ed.
 */

#define XL345_INT_MAP_OVERRUN_ON_INT1        0x01
#define XL345_INT_MAP_OVERRUN_ON_INT0        0x00
#define XL345_INT_MAP_WATERMARK_ON_INT1      0x02
#define XL345_INT_MAP_WATERMARK_ON_INT0      0x00
#define XL345_INT_MAP_FREEFALL_ON_INT1       0x04
#define XL345_INT_MAP_FREEFALL_ON_INT0       0x00
#define XL345_INT_MAP_INACTIVITY_ON_INT1     0x08
#define XL345_INT_MAP_INACTIVITY_ON_INT0     0x00
#define XL345_INT_MAP_ACTIVITY_ON_INT1       0x10
#define XL345_INT_MAP_ACTIVITY_ON_INT0       0x00
#define XL345_INT_MAP_DOUBLETAP_ON_INT1      0x20
#define XL345_INT_MAP_DOUBLETAP_ON_INT0      0x00
#define XL345_INT_MAP_SINGLETAP_ON_INT1      0x40
#define XL345_INT_MAP_SINGLETAP_ON_INT0      0x00
#define XL345_INT_MAP_DATAREADY_ON_INT1      0x80
#define XL345_INT_MAP_DATAREADY_ON_INT0      0x00


/* Register 0x30 INT_SOURCE (Read Only) */

/*
Bits set to 1 in this register indicate that their respective functions
have triggered an event, whereas a value of 0 indicates that the
corresponding event has not occurred. The DATA_READY,
watermark, and overrun bits are always set if the corresponding
events occur, regardless of the INT_ENABLE register settings,
and are cleared by reading data from the DATAX, DATAY, and
DATAZ registers. The DATA_READY and watermark bits may
require multiple reads, as indicated in the FIFO mode descriptions
in the FIFO section. Other bits, and the corresponding interrupts,
are cleared by reading the INT_SOURCE register.
 */

#define XL345_INT_SOURCE_OVERRUN           0x01
#define XL345_INT_SOURCE_WATERMARK         0x02
#define XL345_INT_SOURCE_FREEFALL          0x04
#define XL345_INT_SOURCE_INACTIVITY        0x08
#define XL345_INT_SOURCE_ACTIVITY          0x10
#define XL345_INT_SOURCE_DOUBLETAP         0x20
#define XL345_INT_SOURCE_SINGLETAP         0x40
#define XL345_INT_SOURCE_DATAREADY         0x80
/* Bit values in DATA_FORMAT
*/
/* Register values read in DATAX0 through DATAZ1 are dependent on the
value specified in data format.
Customer code will need to interpret
the data as desired.
*/
/* Register 0x31 DATA_FORMAT (Read/Write) */
#define XL345_RANGE_2G          0x00
#define XL345_RANGE_4G          0x01
#define XL345_RANGE_8G          0x02
#define XL345_RANGE_16G         0x03
#define XL345_DATA_JUST_RIGHT   0x00
#define XL345_DATA_JUST_LEFT    0x04
#define XL345_10BIT             0x00
#define XL345_FULL_RESOLUTION   0x08
#define XL345_INT_LOW           0x20
#define XL345_INT_HIGH          0x00
#define XL345_SPI3WIRE          0x40
#define XL345_SPI4WIRE          0x00
#define XL345_SELFTEST          0x80

/* Register 0x38 FIFO_CTL (Read/Write) */
/* The low bits are a value 0 to 31 used for the watermark or the number
of pre-trigger samples when in triggered mode*/

#define XL345_TRIGGER_INT1 0x00
#define XL345_TRIGGER_INT2 0x20
#define XL345_FIFO_MODE_BYPASS 0x00
#define XL345_FIFO_RESET 0x00
#define XL345_FIFO_MODE_FIFO 0x40
#define XL345_FIFO_MODE_STREAM 0x80
#define XL345_FIFO_MODE_TRIGGER 0xc0

/* 0x39 FIFO_STATUS (Read Only)
*/
/* The low bits are a value 0 to 32 showing the number of entries
currently available in the FIFO buffer */
#define XL345_FIFO_TRIGGERED 0x80

/*
 The THRESH_TAP register is eight bits and holds the threshold
value for tap interrupts. The data format is unsigned, therefore,
the magnitude of the tap event is compared with the value
in THRESH_TAP for normal tap detection. The scale factor is
62.5 mg/LSB (that is, 0xFF = 16 g). A value of 0 may result in
undesirable behavior if single tap/double tap interrupts are
enabled.
 */

#define	XL345_THRESH_TAP_VALUE_0_G      0x00	//result in undesirable behavior if single tap/double tap interrupts are Enabled
#define	XL345_THRESH_TAP_VALUE_0_06_G 	0x01	//threshold value for tap interrupts = 0,0625_G
#define	XL345_THRESH_TAP_VALUE_0_13_G 	0x02	//threshold value for tap interrupts = 0,125_G
#define	XL345_THRESH_TAP_VALUE_0_19_G 	0x03	//threshold value for tap interrupts = 0,1875_G
#define	XL345_THRESH_TAP_VALUE_0_25_G 	0x04	//threshold value for tap interrupts = 0,25_G
#define	XL345_THRESH_TAP_VALUE_0_31_G 	0x05	//threshold value for tap interrupts = 0,3125_G
#define	XL345_THRESH_TAP_VALUE_0_38_G 	0x06	//threshold value for tap interrupts = 0,375_G
#define	XL345_THRESH_TAP_VALUE_0_44_G 	0x07	//threshold value for tap interrupts = 0,4375_G
#define	XL345_THRESH_TAP_VALUE_0_50_G 	0x08	//threshold value for tap interrupts = 0,5_G
#define	XL345_THRESH_TAP_VALUE_0_56_G 	0x09	//threshold value for tap interrupts = 0,5625_G
#define	XL345_THRESH_TAP_VALUE_0_63_G 	0x0A	//threshold value for tap interrupts = 0,625_G
#define	XL345_THRESH_TAP_VALUE_0_69_G 	0x0B	//threshold value for tap interrupts = 0,6875_G
#define	XL345_THRESH_TAP_VALUE_0_75_G 	0x0C	//threshold value for tap interrupts = 0,75_G
#define	XL345_THRESH_TAP_VALUE_0_81_G 	0x0D	//threshold value for tap interrupts = 0,8125_G
#define	XL345_THRESH_TAP_VALUE_0_88_G 	0x0E	//threshold value for tap interrupts = 0,875_G
#define	XL345_THRESH_TAP_VALUE_0_94_G 	0x0F	//threshold value for tap interrupts = 0,9375_G
#define	XL345_THRESH_TAP_VALUE_1_00_G 	0x10	//threshold value for tap interrupts = 1_G
#define	XL345_THRESH_TAP_VALUE_1_06_G 	0x11	//threshold value for tap interrupts = 1,0625_G
#define	XL345_THRESH_TAP_VALUE_1_13_G 	0x12	//threshold value for tap interrupts = 1,125_G
#define	XL345_THRESH_TAP_VALUE_1_19_G 	0x13	//threshold value for tap interrupts = 1,1875_G
#define	XL345_THRESH_TAP_VALUE_1_25_G 	0x14	//threshold value for tap interrupts = 1,25_G
#define	XL345_THRESH_TAP_VALUE_1_31_G 	0x15	//threshold value for tap interrupts = 1,3125_G
#define	XL345_THRESH_TAP_VALUE_1_38_G 	0x16	//threshold value for tap interrupts = 1,375_G
#define	XL345_THRESH_TAP_VALUE_1_44_G 	0x17	//threshold value for tap interrupts = 1,4375_G
#define	XL345_THRESH_TAP_VALUE_1_50_G 	0x18	//threshold value for tap interrupts = 1,5_G
#define	XL345_THRESH_TAP_VALUE_1_56_G 	0x19	//threshold value for tap interrupts = 1,5625_G
#define	XL345_THRESH_TAP_VALUE_1_63_G 	0x1A	//threshold value for tap interrupts = 1,625_G
#define	XL345_THRESH_TAP_VALUE_1_69_G 	0x1B	//threshold value for tap interrupts = 1,6875_G
#define	XL345_THRESH_TAP_VALUE_1_75_G 	0x1C	//threshold value for tap interrupts = 1,75_G
#define	XL345_THRESH_TAP_VALUE_1_81_G 	0x1D	//threshold value for tap interrupts = 1,8125_G
#define	XL345_THRESH_TAP_VALUE_1_88_G 	0x1E	//threshold value for tap interrupts = 1,875_G
#define	XL345_THRESH_TAP_VALUE_1_94_G 	0x1F	//threshold value for tap interrupts = 1,9375_G
#define	XL345_THRESH_TAP_VALUE_2_00_G 	0x20	//threshold value for tap interrupts = 2_G
#define	XL345_THRESH_TAP_VALUE_2_06_G 	0x21	//threshold value for tap interrupts = 2,0625_G
#define	XL345_THRESH_TAP_VALUE_2_13_G 	0x22	//threshold value for tap interrupts = 2,125_G
#define	XL345_THRESH_TAP_VALUE_2_19_G 	0x23	//threshold value for tap interrupts = 2,1875_G
#define	XL345_THRESH_TAP_VALUE_2_25_G 	0x24	//threshold value for tap interrupts = 2,25_G
#define	XL345_THRESH_TAP_VALUE_2_31_G 	0x25	//threshold value for tap interrupts = 2,3125_G
#define	XL345_THRESH_TAP_VALUE_2_38_G 	0x26	//threshold value for tap interrupts = 2,375_G
#define	XL345_THRESH_TAP_VALUE_2_44_G 	0x27	//threshold value for tap interrupts = 2,4375_G
#define	XL345_THRESH_TAP_VALUE_2_50_G 	0x28	//threshold value for tap interrupts = 2,5_G
#define	XL345_THRESH_TAP_VALUE_2_56_G 	0x29	//threshold value for tap interrupts = 2,5625_G
#define	XL345_THRESH_TAP_VALUE_2_63_G 	0x2A	//threshold value for tap interrupts = 2,625_G
#define	XL345_THRESH_TAP_VALUE_2_69_G 	0x2B	//threshold value for tap interrupts = 2,6875_G
#define	XL345_THRESH_TAP_VALUE_2_75_G 	0x2C	//threshold value for tap interrupts = 2,75_G
#define	XL345_THRESH_TAP_VALUE_2_81_G 	0x2D	//threshold value for tap interrupts = 2,8125_G
#define	XL345_THRESH_TAP_VALUE_2_88_G 	0x2E	//threshold value for tap interrupts = 2,875_G
#define	XL345_THRESH_TAP_VALUE_2_94_G 	0x2F	//threshold value for tap interrupts = 2,9375_G
#define	XL345_THRESH_TAP_VALUE_3_00_G 	0x30	//threshold value for tap interrupts = 3_G
#define	XL345_THRESH_TAP_VALUE_3_06_G 	0x31	//threshold value for tap interrupts = 3,0625_G
#define	XL345_THRESH_TAP_VALUE_3_13_G 	0x32	//threshold value for tap interrupts = 3,125_G
#define	XL345_THRESH_TAP_VALUE_3_19_G 	0x33	//threshold value for tap interrupts = 3,1875_G
#define	XL345_THRESH_TAP_VALUE_3_25_G 	0x34	//threshold value for tap interrupts = 3,25_G
#define	XL345_THRESH_TAP_VALUE_3_31_G 	0x35	//threshold value for tap interrupts = 3,3125_G
#define	XL345_THRESH_TAP_VALUE_3_38_G 	0x36	//threshold value for tap interrupts = 3,375_G
#define	XL345_THRESH_TAP_VALUE_3_44_G 	0x37	//threshold value for tap interrupts = 3,4375_G
#define	XL345_THRESH_TAP_VALUE_3_50_G 	0x38	//threshold value for tap interrupts = 3,5_G
#define	XL345_THRESH_TAP_VALUE_3_56_G 	0x39	//threshold value for tap interrupts = 3,5625_G
#define	XL345_THRESH_TAP_VALUE_3_63_G 	0x3A	//threshold value for tap interrupts = 3,625_G
#define	XL345_THRESH_TAP_VALUE_3_69_G 	0x3B	//threshold value for tap interrupts = 3,6875_G
#define	XL345_THRESH_TAP_VALUE_3_75_G 	0x3C	//threshold value for tap interrupts = 3,75_G
#define	XL345_THRESH_TAP_VALUE_3_81_G 	0x3D	//threshold value for tap interrupts = 3,8125_G
#define	XL345_THRESH_TAP_VALUE_3_88_G 	0x3E	//threshold value for tap interrupts = 3,875_G
#define	XL345_THRESH_TAP_VALUE_3_94_G 	0x3F	//threshold value for tap interrupts = 3,9375_G
#define	XL345_THRESH_TAP_VALUE_4_00_G 	0x40	//threshold value for tap interrupts = 4_G
#define	XL345_THRESH_TAP_VALUE_4_06_G 	0x41	//threshold value for tap interrupts = 4,0625_G
#define	XL345_THRESH_TAP_VALUE_4_13_G 	0x42	//threshold value for tap interrupts = 4,125_G
#define	XL345_THRESH_TAP_VALUE_4_19_G 	0x43	//threshold value for tap interrupts = 4,1875_G
#define	XL345_THRESH_TAP_VALUE_4_25_G 	0x44	//threshold value for tap interrupts = 4,25_G
#define	XL345_THRESH_TAP_VALUE_4_31_G 	0x45	//threshold value for tap interrupts = 4,3125_G
#define	XL345_THRESH_TAP_VALUE_4_38_G 	0x46	//threshold value for tap interrupts = 4,375_G
#define	XL345_THRESH_TAP_VALUE_4_44_G 	0x47	//threshold value for tap interrupts = 4,4375_G
#define	XL345_THRESH_TAP_VALUE_4_50_G 	0x48	//threshold value for tap interrupts = 4,5_G
#define	XL345_THRESH_TAP_VALUE_4_56_G 	0x49	//threshold value for tap interrupts = 4,5625_G
#define	XL345_THRESH_TAP_VALUE_4_63_G 	0x4A	//threshold value for tap interrupts = 4,625_G
#define	XL345_THRESH_TAP_VALUE_4_69_G 	0x4B	//threshold value for tap interrupts = 4,6875_G
#define	XL345_THRESH_TAP_VALUE_4_75_G 	0x4C	//threshold value for tap interrupts = 4,75_G
#define	XL345_THRESH_TAP_VALUE_4_81_G 	0x4D	//threshold value for tap interrupts = 4,8125_G
#define	XL345_THRESH_TAP_VALUE_4_88_G 	0x4E	//threshold value for tap interrupts = 4,875_G
#define	XL345_THRESH_TAP_VALUE_4_94_G 	0x4F	//threshold value for tap interrupts = 4,9375_G
#define	XL345_THRESH_TAP_VALUE_5_00_G 	0x50	//threshold value for tap interrupts = 5_G
#define	XL345_THRESH_TAP_VALUE_5_06_G 	0x51	//threshold value for tap interrupts = 5,0625_G
#define	XL345_THRESH_TAP_VALUE_5_13_G 	0x52	//threshold value for tap interrupts = 5,125_G
#define	XL345_THRESH_TAP_VALUE_5_19_G 	0x53	//threshold value for tap interrupts = 5,1875_G
#define	XL345_THRESH_TAP_VALUE_5_25_G 	0x54	//threshold value for tap interrupts = 5,25_G
#define	XL345_THRESH_TAP_VALUE_5_31_G 	0x55	//threshold value for tap interrupts = 5,3125_G
#define	XL345_THRESH_TAP_VALUE_5_38_G 	0x56	//threshold value for tap interrupts = 5,375_G
#define	XL345_THRESH_TAP_VALUE_5_44_G 	0x57	//threshold value for tap interrupts = 5,4375_G
#define	XL345_THRESH_TAP_VALUE_5_50_G 	0x58	//threshold value for tap interrupts = 5,5_G
#define	XL345_THRESH_TAP_VALUE_5_56_G 	0x59	//threshold value for tap interrupts = 5,5625_G
#define	XL345_THRESH_TAP_VALUE_5_63_G 	0x5A	//threshold value for tap interrupts = 5,625_G
#define	XL345_THRESH_TAP_VALUE_5_69_G 	0x5B	//threshold value for tap interrupts = 5,6875_G
#define	XL345_THRESH_TAP_VALUE_5_75_G 	0x5C	//threshold value for tap interrupts = 5,75_G
#define	XL345_THRESH_TAP_VALUE_5_81_G 	0x5D	//threshold value for tap interrupts = 5,8125_G
#define	XL345_THRESH_TAP_VALUE_5_88_G 	0x5E	//threshold value for tap interrupts = 5,875_G
#define	XL345_THRESH_TAP_VALUE_5_94_G 	0x5F	//threshold value for tap interrupts = 5,9375_G
#define	XL345_THRESH_TAP_VALUE_6_00_G 	0x60	//threshold value for tap interrupts = 6_G
#define	XL345_THRESH_TAP_VALUE_6_06_G 	0x61	//threshold value for tap interrupts = 6,0625_G
#define	XL345_THRESH_TAP_VALUE_6_13_G 	0x62	//threshold value for tap interrupts = 6,125_G
#define	XL345_THRESH_TAP_VALUE_6_19_G 	0x63	//threshold value for tap interrupts = 6,1875_G
#define	XL345_THRESH_TAP_VALUE_6_25_G 	0x64	//threshold value for tap interrupts = 6,25_G
#define	XL345_THRESH_TAP_VALUE_6_31_G 	0x65	//threshold value for tap interrupts = 6,3125_G
#define	XL345_THRESH_TAP_VALUE_6_38_G 	0x66	//threshold value for tap interrupts = 6,375_G
#define	XL345_THRESH_TAP_VALUE_6_44_G 	0x67	//threshold value for tap interrupts = 6,4375_G
#define	XL345_THRESH_TAP_VALUE_6_50_G 	0x68	//threshold value for tap interrupts = 6,5_G
#define	XL345_THRESH_TAP_VALUE_6_56_G 	0x69	//threshold value for tap interrupts = 6,5625_G
#define	XL345_THRESH_TAP_VALUE_6_63_G 	0x6A	//threshold value for tap interrupts = 6,625_G
#define	XL345_THRESH_TAP_VALUE_6_69_G 	0x6B	//threshold value for tap interrupts = 6,6875_G
#define	XL345_THRESH_TAP_VALUE_6_75_G 	0x6C	//threshold value for tap interrupts = 6,75_G
#define	XL345_THRESH_TAP_VALUE_6_81_G 	0x6D	//threshold value for tap interrupts = 6,8125_G
#define	XL345_THRESH_TAP_VALUE_6_88_G 	0x6E	//threshold value for tap interrupts = 6,875_G
#define	XL345_THRESH_TAP_VALUE_6_94_G 	0x6F	//threshold value for tap interrupts = 6,9375_G
#define	XL345_THRESH_TAP_VALUE_7_00_G 	0x70	//threshold value for tap interrupts = 7_G
#define	XL345_THRESH_TAP_VALUE_7_06_G 	0x71	//threshold value for tap interrupts = 7,0625_G
#define	XL345_THRESH_TAP_VALUE_7_13_G 	0x72	//threshold value for tap interrupts = 7,125_G
#define	XL345_THRESH_TAP_VALUE_7_19_G 	0x73	//threshold value for tap interrupts = 7,1875_G
#define	XL345_THRESH_TAP_VALUE_7_25_G 	0x74	//threshold value for tap interrupts = 7,25_G
#define	XL345_THRESH_TAP_VALUE_7_31_G 	0x75	//threshold value for tap interrupts = 7,3125_G
#define	XL345_THRESH_TAP_VALUE_7_38_G 	0x76	//threshold value for tap interrupts = 7,375_G
#define	XL345_THRESH_TAP_VALUE_7_44_G 	0x77	//threshold value for tap interrupts = 7,4375_G
#define	XL345_THRESH_TAP_VALUE_7_50_G 	0x78	//threshold value for tap interrupts = 7,5_G
#define	XL345_THRESH_TAP_VALUE_7_56_G 	0x79	//threshold value for tap interrupts = 7,5625_G
#define	XL345_THRESH_TAP_VALUE_7_63_G 	0x7A	//threshold value for tap interrupts = 7,625_G
#define	XL345_THRESH_TAP_VALUE_7_69_G 	0x7B	//threshold value for tap interrupts = 7,6875_G
#define	XL345_THRESH_TAP_VALUE_7_75_G 	0x7C	//threshold value for tap interrupts = 7,75_G
#define	XL345_THRESH_TAP_VALUE_7_81_G 	0x7D	//threshold value for tap interrupts = 7,8125_G
#define	XL345_THRESH_TAP_VALUE_7_88_G 	0x7E	//threshold value for tap interrupts = 7,875_G
#define	XL345_THRESH_TAP_VALUE_7_94_G 	0x7F	//threshold value for tap interrupts = 7,9375_G
#define	XL345_THRESH_TAP_VALUE_8_00_G 	0x80	//threshold value for tap interrupts = 8_G
#define	XL345_THRESH_TAP_VALUE_8_06_G 	0x81	//threshold value for tap interrupts = 8,0625_G
#define	XL345_THRESH_TAP_VALUE_8_13_G 	0x82	//threshold value for tap interrupts = 8,125_G
#define	XL345_THRESH_TAP_VALUE_8_19_G 	0x83	//threshold value for tap interrupts = 8,1875_G
#define	XL345_THRESH_TAP_VALUE_8_25_G 	0x84	//threshold value for tap interrupts = 8,25_G
#define	XL345_THRESH_TAP_VALUE_8_31_G 	0x85	//threshold value for tap interrupts = 8,3125_G
#define	XL345_THRESH_TAP_VALUE_8_38_G 	0x86	//threshold value for tap interrupts = 8,375_G
#define	XL345_THRESH_TAP_VALUE_8_44_G 	0x87	//threshold value for tap interrupts = 8,4375_G
#define	XL345_THRESH_TAP_VALUE_8_50_G 	0x88	//threshold value for tap interrupts = 8,5_G
#define	XL345_THRESH_TAP_VALUE_8_56_G 	0x89	//threshold value for tap interrupts = 8,5625_G
#define	XL345_THRESH_TAP_VALUE_8_63_G 	0x8A	//threshold value for tap interrupts = 8,625_G
#define	XL345_THRESH_TAP_VALUE_8_69_G 	0x8B	//threshold value for tap interrupts = 8,6875_G
#define	XL345_THRESH_TAP_VALUE_8_75_G 	0x8C	//threshold value for tap interrupts = 8,75_G
#define	XL345_THRESH_TAP_VALUE_8_81_G 	0x8D	//threshold value for tap interrupts = 8,8125_G
#define	XL345_THRESH_TAP_VALUE_8_88_G 	0x8E	//threshold value for tap interrupts = 8,875_G
#define	XL345_THRESH_TAP_VALUE_8_94_G 	0x8F	//threshold value for tap interrupts = 8,9375_G
#define	XL345_THRESH_TAP_VALUE_9_00_G 	0x90	//threshold value for tap interrupts = 9_G
#define	XL345_THRESH_TAP_VALUE_9_06_G 	0x91	//threshold value for tap interrupts = 9,0625_G
#define	XL345_THRESH_TAP_VALUE_9_13_G 	0x92	//threshold value for tap interrupts = 9,125_G
#define	XL345_THRESH_TAP_VALUE_9_19_G 	0x93	//threshold value for tap interrupts = 9,1875_G
#define	XL345_THRESH_TAP_VALUE_9_25_G 	0x94	//threshold value for tap interrupts = 9,25_G
#define	XL345_THRESH_TAP_VALUE_9_31_G 	0x95	//threshold value for tap interrupts = 9,3125_G
#define	XL345_THRESH_TAP_VALUE_9_38_G 	0x96	//threshold value for tap interrupts = 9,375_G
#define	XL345_THRESH_TAP_VALUE_9_44_G 	0x97	//threshold value for tap interrupts = 9,4375_G
#define	XL345_THRESH_TAP_VALUE_9_50_G 	0x98	//threshold value for tap interrupts = 9,5_G
#define	XL345_THRESH_TAP_VALUE_9_56_G 	0x99	//threshold value for tap interrupts = 9,5625_G
#define	XL345_THRESH_TAP_VALUE_9_63_G 	0x9A	//threshold value for tap interrupts = 9,625_G
#define	XL345_THRESH_TAP_VALUE_9_69_G 	0x9B	//threshold value for tap interrupts = 9,6875_G
#define	XL345_THRESH_TAP_VALUE_9_75_G 	0x9C	//threshold value for tap interrupts = 9,75_G
#define	XL345_THRESH_TAP_VALUE_9_81_G 	0x9D	//threshold value for tap interrupts = 9,8125_G
#define	XL345_THRESH_TAP_VALUE_9_88_G 	0x9E	//threshold value for tap interrupts = 9,875_G
#define	XL345_THRESH_TAP_VALUE_9_94_G 	0x9F	//threshold value for tap interrupts = 9,9375_G
#define	XL345_THRESH_TAP_VALUE_10_00_G	0xA0	//threshold value for tap interrupts = 10_G
#define	XL345_THRESH_TAP_VALUE_10_06_G	0xA1	//threshold value for tap interrupts = 10,0625_G
#define	XL345_THRESH_TAP_VALUE_10_13_G	0xA2	//threshold value for tap interrupts = 10,125_G
#define	XL345_THRESH_TAP_VALUE_10_19_G	0xA3	//threshold value for tap interrupts = 10,1875_G
#define	XL345_THRESH_TAP_VALUE_10_25_G	0xA4	//threshold value for tap interrupts = 10,25_G
#define	XL345_THRESH_TAP_VALUE_10_31_G	0xA5	//threshold value for tap interrupts = 10,3125_G
#define	XL345_THRESH_TAP_VALUE_10_38_G	0xA6	//threshold value for tap interrupts = 10,375_G
#define	XL345_THRESH_TAP_VALUE_10_44_G	0xA7	//threshold value for tap interrupts = 10,4375_G
#define	XL345_THRESH_TAP_VALUE_10_50_G	0xA8	//threshold value for tap interrupts = 10,5_G
#define	XL345_THRESH_TAP_VALUE_10_56_G	0xA9	//threshold value for tap interrupts = 10,5625_G
#define	XL345_THRESH_TAP_VALUE_10_63_G	0xAA	//threshold value for tap interrupts = 10,625_G
#define	XL345_THRESH_TAP_VALUE_10_69_G	0xAB	//threshold value for tap interrupts = 10,6875_G
#define	XL345_THRESH_TAP_VALUE_10_75_G	0xAC	//threshold value for tap interrupts = 10,75_G
#define	XL345_THRESH_TAP_VALUE_10_81_G	0xAD	//threshold value for tap interrupts = 10,8125_G
#define	XL345_THRESH_TAP_VALUE_10_88_G	0xAE	//threshold value for tap interrupts = 10,875_G
#define	XL345_THRESH_TAP_VALUE_10_94_G	0xAF	//threshold value for tap interrupts = 10,9375_G
#define	XL345_THRESH_TAP_VALUE_11_00_G	0xB0	//threshold value for tap interrupts = 11_G
#define	XL345_THRESH_TAP_VALUE_11_06_G	0xB1	//threshold value for tap interrupts = 11,0625_G
#define	XL345_THRESH_TAP_VALUE_11_13_G	0xB2	//threshold value for tap interrupts = 11,125_G
#define	XL345_THRESH_TAP_VALUE_11_19_G	0xB3	//threshold value for tap interrupts = 11,1875_G
#define	XL345_THRESH_TAP_VALUE_11_25_G	0xB4	//threshold value for tap interrupts = 11,25_G
#define	XL345_THRESH_TAP_VALUE_11_31_G	0xB5	//threshold value for tap interrupts = 11,3125_G
#define	XL345_THRESH_TAP_VALUE_11_38_G	0xB6	//threshold value for tap interrupts = 11,375_G
#define	XL345_THRESH_TAP_VALUE_11_44_G	0xB7	//threshold value for tap interrupts = 11,4375_G
#define	XL345_THRESH_TAP_VALUE_11_50_G	0xB8	//threshold value for tap interrupts = 11,5_G
#define	XL345_THRESH_TAP_VALUE_11_56_G	0xB9	//threshold value for tap interrupts = 11,5625_G
#define	XL345_THRESH_TAP_VALUE_11_63_G	0xBA	//threshold value for tap interrupts = 11,625_G
#define	XL345_THRESH_TAP_VALUE_11_69_G	0xBB	//threshold value for tap interrupts = 11,6875_G
#define	XL345_THRESH_TAP_VALUE_11_75_G	0xBC	//threshold value for tap interrupts = 11,75_G
#define	XL345_THRESH_TAP_VALUE_11_81_G	0xBD	//threshold value for tap interrupts = 11,8125_G
#define	XL345_THRESH_TAP_VALUE_11_88_G	0xBE	//threshold value for tap interrupts = 11,875_G
#define	XL345_THRESH_TAP_VALUE_11_94_G	0xBF	//threshold value for tap interrupts = 11,9375_G
#define	XL345_THRESH_TAP_VALUE_12_00_G	0xC0	//threshold value for tap interrupts = 12_G
#define	XL345_THRESH_TAP_VALUE_12_06_G	0xC1	//threshold value for tap interrupts = 12,0625_G
#define	XL345_THRESH_TAP_VALUE_12_13_G	0xC2	//threshold value for tap interrupts = 12,125_G
#define	XL345_THRESH_TAP_VALUE_12_19_G	0xC3	//threshold value for tap interrupts = 12,1875_G
#define	XL345_THRESH_TAP_VALUE_12_25_G	0xC4	//threshold value for tap interrupts = 12,25_G
#define	XL345_THRESH_TAP_VALUE_12_31_G	0xC5	//threshold value for tap interrupts = 12,3125_G
#define	XL345_THRESH_TAP_VALUE_12_38_G	0xC6	//threshold value for tap interrupts = 12,375_G
#define	XL345_THRESH_TAP_VALUE_12_44_G	0xC7	//threshold value for tap interrupts = 12,4375_G
#define	XL345_THRESH_TAP_VALUE_12_50_G	0xC8	//threshold value for tap interrupts = 12,5_G
#define	XL345_THRESH_TAP_VALUE_12_56_G	0xC9	//threshold value for tap interrupts = 12,5625_G
#define	XL345_THRESH_TAP_VALUE_12_63_G	0xCA	//threshold value for tap interrupts = 12,625_G
#define	XL345_THRESH_TAP_VALUE_12_69_G	0xCB	//threshold value for tap interrupts = 12,6875_G
#define	XL345_THRESH_TAP_VALUE_12_75_G	0xCC	//threshold value for tap interrupts = 12,75_G
#define	XL345_THRESH_TAP_VALUE_12_81_G	0xCD	//threshold value for tap interrupts = 12,8125_G
#define	XL345_THRESH_TAP_VALUE_12_88_G	0xCE	//threshold value for tap interrupts = 12,875_G
#define	XL345_THRESH_TAP_VALUE_12_94_G	0xCF	//threshold value for tap interrupts = 12,9375_G
#define	XL345_THRESH_TAP_VALUE_13_00_G	0xD0	//threshold value for tap interrupts = 13_G
#define	XL345_THRESH_TAP_VALUE_13_06_G	0xD1	//threshold value for tap interrupts = 13,0625_G
#define	XL345_THRESH_TAP_VALUE_13_13_G	0xD2	//threshold value for tap interrupts = 13,125_G
#define	XL345_THRESH_TAP_VALUE_13_19_G	0xD3	//threshold value for tap interrupts = 13,1875_G
#define	XL345_THRESH_TAP_VALUE_13_25_G	0xD4	//threshold value for tap interrupts = 13,25_G
#define	XL345_THRESH_TAP_VALUE_13_31_G	0xD5	//threshold value for tap interrupts = 13,3125_G
#define	XL345_THRESH_TAP_VALUE_13_38_G	0xD6	//threshold value for tap interrupts = 13,375_G
#define	XL345_THRESH_TAP_VALUE_13_44_G	0xD7	//threshold value for tap interrupts = 13,4375_G
#define	XL345_THRESH_TAP_VALUE_13_50_G	0xD8	//threshold value for tap interrupts = 13,5_G
#define	XL345_THRESH_TAP_VALUE_13_56_G	0xD9	//threshold value for tap interrupts = 13,5625_G
#define	XL345_THRESH_TAP_VALUE_13_63_G	0xDA	//threshold value for tap interrupts = 13,625_G
#define	XL345_THRESH_TAP_VALUE_13_69_G	0xDB	//threshold value for tap interrupts = 13,6875_G
#define	XL345_THRESH_TAP_VALUE_13_75_G	0xDC	//threshold value for tap interrupts = 13,75_G
#define	XL345_THRESH_TAP_VALUE_13_81_G	0xDD	//threshold value for tap interrupts = 13,8125_G
#define	XL345_THRESH_TAP_VALUE_13_88_G	0xDE	//threshold value for tap interrupts = 13,875_G
#define	XL345_THRESH_TAP_VALUE_13_94_G	0xDF	//threshold value for tap interrupts = 13,9375_G
#define	XL345_THRESH_TAP_VALUE_14_00_G	0xE0	//threshold value for tap interrupts = 14_G
#define	XL345_THRESH_TAP_VALUE_14_06_G	0xE1	//threshold value for tap interrupts = 14,0625_G
#define	XL345_THRESH_TAP_VALUE_14_13_G	0xE2	//threshold value for tap interrupts = 14,125_G
#define	XL345_THRESH_TAP_VALUE_14_19_G	0xE3	//threshold value for tap interrupts = 14,1875_G
#define	XL345_THRESH_TAP_VALUE_14_25_G	0xE4	//threshold value for tap interrupts = 14,25_G
#define	XL345_THRESH_TAP_VALUE_14_31_G	0xE5	//threshold value for tap interrupts = 14,3125_G
#define	XL345_THRESH_TAP_VALUE_14_38_G	0xE6	//threshold value for tap interrupts = 14,375_G
#define	XL345_THRESH_TAP_VALUE_14_44_G	0xE7	//threshold value for tap interrupts = 14,4375_G
#define	XL345_THRESH_TAP_VALUE_14_50_G	0xE8	//threshold value for tap interrupts = 14,5_G
#define	XL345_THRESH_TAP_VALUE_14_56_G	0xE9	//threshold value for tap interrupts = 14,5625_G
#define	XL345_THRESH_TAP_VALUE_14_63_G	0xEA	//threshold value for tap interrupts = 14,625_G
#define	XL345_THRESH_TAP_VALUE_14_69_G	0xEB	//threshold value for tap interrupts = 14,6875_G
#define	XL345_THRESH_TAP_VALUE_14_75_G	0xEC	//threshold value for tap interrupts = 14,75_G
#define	XL345_THRESH_TAP_VALUE_14_81_G	0xED	//threshold value for tap interrupts = 14,8125_G
#define	XL345_THRESH_TAP_VALUE_14_88_G	0xEE	//threshold value for tap interrupts = 14,875_G
#define	XL345_THRESH_TAP_VALUE_14_94_G	0xEF	//threshold value for tap interrupts = 14,9375_G
#define	XL345_THRESH_TAP_VALUE_15_00_G	0xF0	//threshold value for tap interrupts = 15_G
#define	XL345_THRESH_TAP_VALUE_15_06_G	0xF1	//threshold value for tap interrupts = 15,0625_G
#define	XL345_THRESH_TAP_VALUE_15_13_G	0xF2	//threshold value for tap interrupts = 15,125_G
#define	XL345_THRESH_TAP_VALUE_15_19_G	0xF3	//threshold value for tap interrupts = 15,1875_G
#define	XL345_THRESH_TAP_VALUE_15_25_G	0xF4	//threshold value for tap interrupts = 15,25_G
#define	XL345_THRESH_TAP_VALUE_15_31_G	0xF5	//threshold value for tap interrupts = 15,3125_G
#define	XL345_THRESH_TAP_VALUE_15_38_G	0xF6	//threshold value for tap interrupts = 15,375_G
#define	XL345_THRESH_TAP_VALUE_15_44_G	0xF7	//threshold value for tap interrupts = 15,4375_G
#define	XL345_THRESH_TAP_VALUE_15_50_G	0xF8	//threshold value for tap interrupts = 15,5_G
#define	XL345_THRESH_TAP_VALUE_15_56_G	0xF9	//threshold value for tap interrupts = 15,5625_G
#define	XL345_THRESH_TAP_VALUE_15_63_G	0xFA	//threshold value for tap interrupts = 15,625_G
#define	XL345_THRESH_TAP_VALUE_15_69_G	0xFB	//threshold value for tap interrupts = 15,6875_G
#define	XL345_THRESH_TAP_VALUE_15_75_G	0xFC	//threshold value for tap interrupts = 15,75_G
#define	XL345_THRESH_TAP_VALUE_15_81_G	0xFD	//threshold value for tap interrupts = 15,8125_G
#define	XL345_THRESH_TAP_VALUE_15_88_G	0xFE	//threshold value for tap interrupts = 15,875_G
#define	XL345_THRESH_TAP_VALUE_15_94_G	0xFF	//threshold value for tap interrupts = 15,9375_G




/*
 The OFSX, OFSY, and OFSZ registers are each eight bits and
offer user-set offset adjustments in twos complement format
with a scale factor of 15.6 mg/LSB (that is, 0x7F = 2 g). The
value stored in the offset registers is automatically added to the
acceleration data, and the resulting value is stored in the output
data registers. For additional information regarding offset
calibration and the use of the offset registers, refer to the Offset
Calibration section.
 */

#define	XL345_OFSX_VALUE_NO_OFFSET	0x00	//user-set offset adjustments = 0_G
#define	XL345_OFSX_VALUE_0_02_G	0x01	//user-set offset adjustments = 0,0156_G
#define	XL345_OFSX_VALUE_0_03_G	0x02	//user-set offset adjustments = 0,0312_G
#define	XL345_OFSX_VALUE_0_05_G	0x03	//user-set offset adjustments = 0,0468_G
#define	XL345_OFSX_VALUE_0_06_G	0x04	//user-set offset adjustments = 0,0624_G
#define	XL345_OFSX_VALUE_0_08_G	0x05	//user-set offset adjustments = 0,078_G
#define	XL345_OFSX_VALUE_0_09_G	0x06	//user-set offset adjustments = 0,0936_G
#define	XL345_OFSX_VALUE_0_11_G	0x07	//user-set offset adjustments = 0,1092_G
#define	XL345_OFSX_VALUE_0_12_G	0x08	//user-set offset adjustments = 0,1248_G
#define	XL345_OFSX_VALUE_0_14_G	0x09	//user-set offset adjustments = 0,1404_G
#define	XL345_OFSX_VALUE_0_16_G	0x0A	//user-set offset adjustments = 0,156_G
#define	XL345_OFSX_VALUE_0_17_G	0x0B	//user-set offset adjustments = 0,1716_G
#define	XL345_OFSX_VALUE_0_19_G	0x0C	//user-set offset adjustments = 0,1872_G
#define	XL345_OFSX_VALUE_0_20_G	0x0D	//user-set offset adjustments = 0,2028_G
#define	XL345_OFSX_VALUE_0_22_G	0x0E	//user-set offset adjustments = 0,2184_G
#define	XL345_OFSX_VALUE_0_23_G	0x0F	//user-set offset adjustments = 0,234_G
#define	XL345_OFSX_VALUE_0_25_G	0x10	//user-set offset adjustments = 0,2496_G
#define	XL345_OFSX_VALUE_0_27_G	0x11	//user-set offset adjustments = 0,2652_G
#define	XL345_OFSX_VALUE_0_28_G	0x12	//user-set offset adjustments = 0,2808_G
#define	XL345_OFSX_VALUE_0_30_G	0x13	//user-set offset adjustments = 0,2964_G
#define	XL345_OFSX_VALUE_0_31_G	0x14	//user-set offset adjustments = 0,312_G
#define	XL345_OFSX_VALUE_0_33_G	0x15	//user-set offset adjustments = 0,3276_G
#define	XL345_OFSX_VALUE_0_34_G	0x16	//user-set offset adjustments = 0,3432_G
#define	XL345_OFSX_VALUE_0_36_G	0x17	//user-set offset adjustments = 0,3588_G
#define	XL345_OFSX_VALUE_0_37_G	0x18	//user-set offset adjustments = 0,3744_G
#define	XL345_OFSX_VALUE_0_39_G	0x19	//user-set offset adjustments = 0,39_G
#define	XL345_OFSX_VALUE_0_41_G	0x1A	//user-set offset adjustments = 0,4056_G
#define	XL345_OFSX_VALUE_0_42_G	0x1B	//user-set offset adjustments = 0,4212_G
#define	XL345_OFSX_VALUE_0_44_G	0x1C	//user-set offset adjustments = 0,4368_G
#define	XL345_OFSX_VALUE_0_45_G	0x1D	//user-set offset adjustments = 0,4524_G
#define	XL345_OFSX_VALUE_0_47_G	0x1E	//user-set offset adjustments = 0,468_G
#define	XL345_OFSX_VALUE_0_48_G	0x1F	//user-set offset adjustments = 0,4836_G
#define	XL345_OFSX_VALUE_0_50_G	0x20	//user-set offset adjustments = 0,4992_G
#define	XL345_OFSX_VALUE_0_51_G	0x21	//user-set offset adjustments = 0,5148_G
#define	XL345_OFSX_VALUE_0_53_G	0x22	//user-set offset adjustments = 0,5304_G
#define	XL345_OFSX_VALUE_0_55_G	0x23	//user-set offset adjustments = 0,546_G
#define	XL345_OFSX_VALUE_0_56_G	0x24	//user-set offset adjustments = 0,5616_G
#define	XL345_OFSX_VALUE_0_58_G	0x25	//user-set offset adjustments = 0,5772_G
#define	XL345_OFSX_VALUE_0_59_G	0x26	//user-set offset adjustments = 0,5928_G
#define	XL345_OFSX_VALUE_0_61_G	0x27	//user-set offset adjustments = 0,6084_G
#define	XL345_OFSX_VALUE_0_62_G	0x28	//user-set offset adjustments = 0,624_G
#define	XL345_OFSX_VALUE_0_64_G	0x29	//user-set offset adjustments = 0,6396_G
#define	XL345_OFSX_VALUE_0_66_G	0x2A	//user-set offset adjustments = 0,6552_G
#define	XL345_OFSX_VALUE_0_67_G	0x2B	//user-set offset adjustments = 0,6708_G
#define	XL345_OFSX_VALUE_0_69_G	0x2C	//user-set offset adjustments = 0,6864_G
#define	XL345_OFSX_VALUE_0_70_G	0x2D	//user-set offset adjustments = 0,702_G
#define	XL345_OFSX_VALUE_0_72_G	0x2E	//user-set offset adjustments = 0,7176_G
#define	XL345_OFSX_VALUE_0_73_G	0x2F	//user-set offset adjustments = 0,7332_G
#define	XL345_OFSX_VALUE_0_75_G	0x30	//user-set offset adjustments = 0,7488_G
#define	XL345_OFSX_VALUE_0_76_G	0x31	//user-set offset adjustments = 0,7644_G
#define	XL345_OFSX_VALUE_0_78_G	0x32	//user-set offset adjustments = 0,78_G
#define	XL345_OFSX_VALUE_0_80_G	0x33	//user-set offset adjustments = 0,7956_G
#define	XL345_OFSX_VALUE_0_81_G	0x34	//user-set offset adjustments = 0,8112_G
#define	XL345_OFSX_VALUE_0_83_G	0x35	//user-set offset adjustments = 0,8268_G
#define	XL345_OFSX_VALUE_0_84_G	0x36	//user-set offset adjustments = 0,8424_G
#define	XL345_OFSX_VALUE_0_86_G	0x37	//user-set offset adjustments = 0,858_G
#define	XL345_OFSX_VALUE_0_87_G	0x38	//user-set offset adjustments = 0,8736_G
#define	XL345_OFSX_VALUE_0_89_G	0x39	//user-set offset adjustments = 0,8892_G
#define	XL345_OFSX_VALUE_0_90_G	0x3A	//user-set offset adjustments = 0,9048_G
#define	XL345_OFSX_VALUE_0_92_G	0x3B	//user-set offset adjustments = 0,9204_G
#define	XL345_OFSX_VALUE_0_94_G	0x3C	//user-set offset adjustments = 0,936_G
#define	XL345_OFSX_VALUE_0_95_G	0x3D	//user-set offset adjustments = 0,9516_G
#define	XL345_OFSX_VALUE_0_97_G	0x3E	//user-set offset adjustments = 0,9672_G
#define	XL345_OFSX_VALUE_0_98_G	0x3F	//user-set offset adjustments = 0,9828_G
#define	XL345_OFSX_VALUE_1_00_G	0x40	//user-set offset adjustments = 0,9984_G
#define	XL345_OFSX_VALUE_1_01_G	0x41	//user-set offset adjustments = 1,014_G
#define	XL345_OFSX_VALUE_1_03_G	0x42	//user-set offset adjustments = 1,0296_G
#define	XL345_OFSX_VALUE_1_05_G	0x43	//user-set offset adjustments = 1,0452_G
#define	XL345_OFSX_VALUE_1_06_G	0x44	//user-set offset adjustments = 1,0608_G
#define	XL345_OFSX_VALUE_1_08_G	0x45	//user-set offset adjustments = 1,0764_G
#define	XL345_OFSX_VALUE_1_09_G	0x46	//user-set offset adjustments = 1,092_G
#define	XL345_OFSX_VALUE_1_11_G	0x47	//user-set offset adjustments = 1,1076_G
#define	XL345_OFSX_VALUE_1_12_G	0x48	//user-set offset adjustments = 1,1232_G
#define	XL345_OFSX_VALUE_1_14_G	0x49	//user-set offset adjustments = 1,1388_G
#define	XL345_OFSX_VALUE_1_15_G	0x4A	//user-set offset adjustments = 1,1544_G
#define	XL345_OFSX_VALUE_1_17_G	0x4B	//user-set offset adjustments = 1,17_G
#define	XL345_OFSX_VALUE_1_19_G	0x4C	//user-set offset adjustments = 1,1856_G
#define	XL345_OFSX_VALUE_1_20_G	0x4D	//user-set offset adjustments = 1,2012_G
#define	XL345_OFSX_VALUE_1_22_G	0x4E	//user-set offset adjustments = 1,2168_G
#define	XL345_OFSX_VALUE_1_23_G	0x4F	//user-set offset adjustments = 1,2324_G
#define	XL345_OFSX_VALUE_1_25_G	0x50	//user-set offset adjustments = 1,248_G
#define	XL345_OFSX_VALUE_1_26_G	0x51	//user-set offset adjustments = 1,2636_G
#define	XL345_OFSX_VALUE_1_28_G	0x52	//user-set offset adjustments = 1,2792_G
#define	XL345_OFSX_VALUE_1_29_G	0x53	//user-set offset adjustments = 1,2948_G
#define	XL345_OFSX_VALUE_1_31_G	0x54	//user-set offset adjustments = 1,3104_G
#define	XL345_OFSX_VALUE_1_33_G	0x55	//user-set offset adjustments = 1,326_G
#define	XL345_OFSX_VALUE_1_34_G	0x56	//user-set offset adjustments = 1,3416_G
#define	XL345_OFSX_VALUE_1_36_G	0x57	//user-set offset adjustments = 1,3572_G
#define	XL345_OFSX_VALUE_1_37_G	0x58	//user-set offset adjustments = 1,3728_G
#define	XL345_OFSX_VALUE_1_39_G	0x59	//user-set offset adjustments = 1,3884_G
#define	XL345_OFSX_VALUE_1_40_G	0x5A	//user-set offset adjustments = 1,404_G
#define	XL345_OFSX_VALUE_1_42_G	0x5B	//user-set offset adjustments = 1,4196_G
#define	XL345_OFSX_VALUE_1_44_G	0x5C	//user-set offset adjustments = 1,4352_G
#define	XL345_OFSX_VALUE_1_45_G	0x5D	//user-set offset adjustments = 1,4508_G
#define	XL345_OFSX_VALUE_1_47_G	0x5E	//user-set offset adjustments = 1,4664_G
#define	XL345_OFSX_VALUE_1_48_G	0x5F	//user-set offset adjustments = 1,482_G
#define	XL345_OFSX_VALUE_1_50_G	0x60	//user-set offset adjustments = 1,4976_G
#define	XL345_OFSX_VALUE_1_51_G	0x61	//user-set offset adjustments = 1,5132_G
#define	XL345_OFSX_VALUE_1_53_G	0x62	//user-set offset adjustments = 1,5288_G
#define	XL345_OFSX_VALUE_1_54_G	0x63	//user-set offset adjustments = 1,5444_G
#define	XL345_OFSX_VALUE_1_56_G	0x64	//user-set offset adjustments = 1,56_G
#define	XL345_OFSX_VALUE_1_58_G	0x65	//user-set offset adjustments = 1,5756_G
#define	XL345_OFSX_VALUE_1_59_G	0x66	//user-set offset adjustments = 1,5912_G
#define	XL345_OFSX_VALUE_1_61_G	0x67	//user-set offset adjustments = 1,6068_G
#define	XL345_OFSX_VALUE_1_62_G	0x68	//user-set offset adjustments = 1,6224_G
#define	XL345_OFSX_VALUE_1_64_G	0x69	//user-set offset adjustments = 1,638_G
#define	XL345_OFSX_VALUE_1_65_G	0x6A	//user-set offset adjustments = 1,6536_G
#define	XL345_OFSX_VALUE_1_67_G	0x6B	//user-set offset adjustments = 1,6692_G
#define	XL345_OFSX_VALUE_1_68_G	0x6C	//user-set offset adjustments = 1,6848_G
#define	XL345_OFSX_VALUE_1_70_G	0x6D	//user-set offset adjustments = 1,7004_G
#define	XL345_OFSX_VALUE_1_72_G	0x6E	//user-set offset adjustments = 1,716_G
#define	XL345_OFSX_VALUE_1_73_G	0x6F	//user-set offset adjustments = 1,7316_G
#define	XL345_OFSX_VALUE_1_75_G	0x70	//user-set offset adjustments = 1,7472_G
#define	XL345_OFSX_VALUE_1_76_G	0x71	//user-set offset adjustments = 1,7628_G
#define	XL345_OFSX_VALUE_1_78_G	0x72	//user-set offset adjustments = 1,7784_G
#define	XL345_OFSX_VALUE_1_79_G	0x73	//user-set offset adjustments = 1,794_G
#define	XL345_OFSX_VALUE_1_81_G	0x74	//user-set offset adjustments = 1,8096_G
#define	XL345_OFSX_VALUE_1_83_G	0x75	//user-set offset adjustments = 1,8252_G
#define	XL345_OFSX_VALUE_1_84_G	0x76	//user-set offset adjustments = 1,8408_G
#define	XL345_OFSX_VALUE_1_86_G	0x77	//user-set offset adjustments = 1,8564_G
#define	XL345_OFSX_VALUE_1_87_G	0x78	//user-set offset adjustments = 1,872_G
#define	XL345_OFSX_VALUE_1_89_G	0x79	//user-set offset adjustments = 1,8876_G
#define	XL345_OFSX_VALUE_1_90_G	0x7A	//user-set offset adjustments = 1,9032_G
#define	XL345_OFSX_VALUE_1_92_G	0x7B	//user-set offset adjustments = 1,9188_G
#define	XL345_OFSX_VALUE_1_93_G	0x7C	//user-set offset adjustments = 1,9344_G
#define	XL345_OFSX_VALUE_1_95_G	0x7D	//user-set offset adjustments = 1,95_G
#define	XL345_OFSX_VALUE_1_97_G	0x7E	//user-set offset adjustments = 1,9656_G
#define	XL345_OFSX_VALUE_1_98_G	0x7F	//user-set offset adjustments = 1,9812_G
#define	XL345_OFSX_VALUE_2_00_G	0x80	//user-set offset adjustments = 1,9968_G
#define	XL345_OFSX_VALUE_2_01_G	0x81	//user-set offset adjustments = 2,0124_G
#define	XL345_OFSX_VALUE_2_03_G	0x82	//user-set offset adjustments = 2,028_G
#define	XL345_OFSX_VALUE_2_04_G	0x83	//user-set offset adjustments = 2,0436_G
#define	XL345_OFSX_VALUE_2_06_G	0x84	//user-set offset adjustments = 2,0592_G
#define	XL345_OFSX_VALUE_2_07_G	0x85	//user-set offset adjustments = 2,0748_G
#define	XL345_OFSX_VALUE_2_09_G	0x86	//user-set offset adjustments = 2,0904_G
#define	XL345_OFSX_VALUE_2_11_G	0x87	//user-set offset adjustments = 2,106_G
#define	XL345_OFSX_VALUE_2_12_G	0x88	//user-set offset adjustments = 2,1216_G
#define	XL345_OFSX_VALUE_2_14_G	0x89	//user-set offset adjustments = 2,1372_G
#define	XL345_OFSX_VALUE_2_15_G	0x8A	//user-set offset adjustments = 2,1528_G
#define	XL345_OFSX_VALUE_2_17_G	0x8B	//user-set offset adjustments = 2,1684_G
#define	XL345_OFSX_VALUE_2_18_G	0x8C	//user-set offset adjustments = 2,184_G
#define	XL345_OFSX_VALUE_2_20_G	0x8D	//user-set offset adjustments = 2,1996_G
#define	XL345_OFSX_VALUE_2_22_G	0x8E	//user-set offset adjustments = 2,2152_G
#define	XL345_OFSX_VALUE_2_23_G	0x8F	//user-set offset adjustments = 2,2308_G
#define	XL345_OFSX_VALUE_2_25_G	0x90	//user-set offset adjustments = 2,2464_G
#define	XL345_OFSX_VALUE_2_26_G	0x91	//user-set offset adjustments = 2,262_G
#define	XL345_OFSX_VALUE_2_28_G	0x92	//user-set offset adjustments = 2,2776_G
#define	XL345_OFSX_VALUE_2_29_G	0x93	//user-set offset adjustments = 2,2932_G
#define	XL345_OFSX_VALUE_2_31_G	0x94	//user-set offset adjustments = 2,3088_G
#define	XL345_OFSX_VALUE_2_32_G	0x95	//user-set offset adjustments = 2,3244_G
#define	XL345_OFSX_VALUE_2_34_G	0x96	//user-set offset adjustments = 2,34_G
#define	XL345_OFSX_VALUE_2_36_G	0x97	//user-set offset adjustments = 2,3556_G
#define	XL345_OFSX_VALUE_2_37_G	0x98	//user-set offset adjustments = 2,3712_G
#define	XL345_OFSX_VALUE_2_39_G	0x99	//user-set offset adjustments = 2,3868_G
#define	XL345_OFSX_VALUE_2_40_G	0x9A	//user-set offset adjustments = 2,4024_G
#define	XL345_OFSX_VALUE_2_42_G	0x9B	//user-set offset adjustments = 2,418_G
#define	XL345_OFSX_VALUE_2_43_G	0x9C	//user-set offset adjustments = 2,4336_G
#define	XL345_OFSX_VALUE_2_45_G	0x9D	//user-set offset adjustments = 2,4492_G
#define	XL345_OFSX_VALUE_2_46_G	0x9E	//user-set offset adjustments = 2,4648_G
#define	XL345_OFSX_VALUE_2_48_G	0x9F	//user-set offset adjustments = 2,4804_G
#define	XL345_OFSX_VALUE_2_50_G	0xA0	//user-set offset adjustments = 2,496_G
#define	XL345_OFSX_VALUE_2_51_G	0xA1	//user-set offset adjustments = 2,5116_G
#define	XL345_OFSX_VALUE_2_53_G	0xA2	//user-set offset adjustments = 2,5272_G
#define	XL345_OFSX_VALUE_2_54_G	0xA3	//user-set offset adjustments = 2,5428_G
#define	XL345_OFSX_VALUE_2_56_G	0xA4	//user-set offset adjustments = 2,5584_G
#define	XL345_OFSX_VALUE_2_57_G	0xA5	//user-set offset adjustments = 2,574_G
#define	XL345_OFSX_VALUE_2_59_G	0xA6	//user-set offset adjustments = 2,5896_G
#define	XL345_OFSX_VALUE_2_61_G	0xA7	//user-set offset adjustments = 2,6052_G
#define	XL345_OFSX_VALUE_2_62_G	0xA8	//user-set offset adjustments = 2,6208_G
#define	XL345_OFSX_VALUE_2_64_G	0xA9	//user-set offset adjustments = 2,6364_G
#define	XL345_OFSX_VALUE_2_65_G	0xAA	//user-set offset adjustments = 2,652_G
#define	XL345_OFSX_VALUE_2_67_G	0xAB	//user-set offset adjustments = 2,6676_G
#define	XL345_OFSX_VALUE_2_68_G	0xAC	//user-set offset adjustments = 2,6832_G
#define	XL345_OFSX_VALUE_2_70_G	0xAD	//user-set offset adjustments = 2,6988_G
#define	XL345_OFSX_VALUE_2_71_G	0xAE	//user-set offset adjustments = 2,7144_G
#define	XL345_OFSX_VALUE_2_73_G	0xAF	//user-set offset adjustments = 2,73_G
#define	XL345_OFSX_VALUE_2_75_G	0xB0	//user-set offset adjustments = 2,7456_G
#define	XL345_OFSX_VALUE_2_76_G	0xB1	//user-set offset adjustments = 2,7612_G
#define	XL345_OFSX_VALUE_2_78_G	0xB2	//user-set offset adjustments = 2,7768_G
#define	XL345_OFSX_VALUE_2_79_G	0xB3	//user-set offset adjustments = 2,7924_G
#define	XL345_OFSX_VALUE_2_81_G	0xB4	//user-set offset adjustments = 2,808_G
#define	XL345_OFSX_VALUE_2_82_G	0xB5	//user-set offset adjustments = 2,8236_G
#define	XL345_OFSX_VALUE_2_84_G	0xB6	//user-set offset adjustments = 2,8392_G
#define	XL345_OFSX_VALUE_2_85_G	0xB7	//user-set offset adjustments = 2,8548_G
#define	XL345_OFSX_VALUE_2_87_G	0xB8	//user-set offset adjustments = 2,8704_G
#define	XL345_OFSX_VALUE_2_89_G	0xB9	//user-set offset adjustments = 2,886_G
#define	XL345_OFSX_VALUE_2_90_G	0xBA	//user-set offset adjustments = 2,9016_G
#define	XL345_OFSX_VALUE_2_92_G	0xBB	//user-set offset adjustments = 2,9172_G
#define	XL345_OFSX_VALUE_2_93_G	0xBC	//user-set offset adjustments = 2,9328_G
#define	XL345_OFSX_VALUE_2_95_G	0xBD	//user-set offset adjustments = 2,9484_G
#define	XL345_OFSX_VALUE_2_96_G	0xBE	//user-set offset adjustments = 2,964_G
#define	XL345_OFSX_VALUE_2_98_G	0xBF	//user-set offset adjustments = 2,9796_G
#define	XL345_OFSX_VALUE_3_00_G	0xC0	//user-set offset adjustments = 2,9952_G
#define	XL345_OFSX_VALUE_3_01_G	0xC1	//user-set offset adjustments = 3,0108_G
#define	XL345_OFSX_VALUE_3_03_G	0xC2	//user-set offset adjustments = 3,0264_G
#define	XL345_OFSX_VALUE_3_04_G	0xC3	//user-set offset adjustments = 3,042_G
#define	XL345_OFSX_VALUE_3_06_G	0xC4	//user-set offset adjustments = 3,0576_G
#define	XL345_OFSX_VALUE_3_07_G	0xC5	//user-set offset adjustments = 3,0732_G
#define	XL345_OFSX_VALUE_3_09_G	0xC6	//user-set offset adjustments = 3,0888_G
#define	XL345_OFSX_VALUE_3_10_G	0xC7	//user-set offset adjustments = 3,1044_G
#define	XL345_OFSX_VALUE_3_12_G	0xC8	//user-set offset adjustments = 3,12_G
#define	XL345_OFSX_VALUE_3_14_G	0xC9	//user-set offset adjustments = 3,1356_G
#define	XL345_OFSX_VALUE_3_15_G	0xCA	//user-set offset adjustments = 3,1512_G
#define	XL345_OFSX_VALUE_3_17_G	0xCB	//user-set offset adjustments = 3,1668_G
#define	XL345_OFSX_VALUE_3_18_G	0xCC	//user-set offset adjustments = 3,1824_G
#define	XL345_OFSX_VALUE_3_20_G	0xCD	//user-set offset adjustments = 3,198_G
#define	XL345_OFSX_VALUE_3_21_G	0xCE	//user-set offset adjustments = 3,2136_G
#define	XL345_OFSX_VALUE_3_23_G	0xCF	//user-set offset adjustments = 3,2292_G
#define	XL345_OFSX_VALUE_3_24_G	0xD0	//user-set offset adjustments = 3,2448_G
#define	XL345_OFSX_VALUE_3_26_G	0xD1	//user-set offset adjustments = 3,2604_G
#define	XL345_OFSX_VALUE_3_28_G	0xD2	//user-set offset adjustments = 3,276_G
#define	XL345_OFSX_VALUE_3_29_G	0xD3	//user-set offset adjustments = 3,2916_G
#define	XL345_OFSX_VALUE_3_31_G	0xD4	//user-set offset adjustments = 3,3072_G
#define	XL345_OFSX_VALUE_3_32_G	0xD5	//user-set offset adjustments = 3,3228_G
#define	XL345_OFSX_VALUE_3_34_G	0xD6	//user-set offset adjustments = 3,3384_G
#define	XL345_OFSX_VALUE_3_35_G	0xD7	//user-set offset adjustments = 3,354_G
#define	XL345_OFSX_VALUE_3_37_G	0xD8	//user-set offset adjustments = 3,3696_G
#define	XL345_OFSX_VALUE_3_39_G	0xD9	//user-set offset adjustments = 3,3852_G
#define	XL345_OFSX_VALUE_3_40_G	0xDA	//user-set offset adjustments = 3,4008_G
#define	XL345_OFSX_VALUE_3_42_G	0xDB	//user-set offset adjustments = 3,4164_G
#define	XL345_OFSX_VALUE_3_43_G	0xDC	//user-set offset adjustments = 3,432_G
#define	XL345_OFSX_VALUE_3_45_G	0xDD	//user-set offset adjustments = 3,4476_G
#define	XL345_OFSX_VALUE_3_46_G	0xDE	//user-set offset adjustments = 3,4632_G
#define	XL345_OFSX_VALUE_3_48_G	0xDF	//user-set offset adjustments = 3,4788_G
#define	XL345_OFSX_VALUE_3_49_G	0xE0	//user-set offset adjustments = 3,4944_G
#define	XL345_OFSX_VALUE_3_51_G	0xE1	//user-set offset adjustments = 3,51_G
#define	XL345_OFSX_VALUE_3_53_G	0xE2	//user-set offset adjustments = 3,5256_G
#define	XL345_OFSX_VALUE_3_54_G	0xE3	//user-set offset adjustments = 3,5412_G
#define	XL345_OFSX_VALUE_3_56_G	0xE4	//user-set offset adjustments = 3,5568_G
#define	XL345_OFSX_VALUE_3_57_G	0xE5	//user-set offset adjustments = 3,5724_G
#define	XL345_OFSX_VALUE_3_59_G	0xE6	//user-set offset adjustments = 3,588_G
#define	XL345_OFSX_VALUE_3_60_G	0xE7	//user-set offset adjustments = 3,6036_G
#define	XL345_OFSX_VALUE_3_62_G	0xE8	//user-set offset adjustments = 3,6192_G
#define	XL345_OFSX_VALUE_3_63_G	0xE9	//user-set offset adjustments = 3,6348_G
#define	XL345_OFSX_VALUE_3_65_G	0xEA	//user-set offset adjustments = 3,6504_G
#define	XL345_OFSX_VALUE_3_67_G	0xEB	//user-set offset adjustments = 3,666_G
#define	XL345_OFSX_VALUE_3_68_G	0xEC	//user-set offset adjustments = 3,6816_G
#define	XL345_OFSX_VALUE_3_70_G	0xED	//user-set offset adjustments = 3,6972_G
#define	XL345_OFSX_VALUE_3_71_G	0xEE	//user-set offset adjustments = 3,7128_G
#define	XL345_OFSX_VALUE_3_73_G	0xEF	//user-set offset adjustments = 3,7284_G
#define	XL345_OFSX_VALUE_3_74_G	0xF0	//user-set offset adjustments = 3,744_G
#define	XL345_OFSX_VALUE_3_76_G	0xF1	//user-set offset adjustments = 3,7596_G
#define	XL345_OFSX_VALUE_3_78_G	0xF2	//user-set offset adjustments = 3,7752_G
#define	XL345_OFSX_VALUE_3_79_G	0xF3	//user-set offset adjustments = 3,7908_G
#define	XL345_OFSX_VALUE_3_81_G	0xF4	//user-set offset adjustments = 3,8064_G
#define	XL345_OFSX_VALUE_3_82_G	0xF5	//user-set offset adjustments = 3,822_G
#define	XL345_OFSX_VALUE_3_84_G	0xF6	//user-set offset adjustments = 3,8376_G
#define	XL345_OFSX_VALUE_3_85_G	0xF7	//user-set offset adjustments = 3,8532_G
#define	XL345_OFSX_VALUE_3_87_G	0xF8	//user-set offset adjustments = 3,8688_G
#define	XL345_OFSX_VALUE_3_88_G	0xF9	//user-set offset adjustments = 3,8844_G
#define	XL345_OFSX_VALUE_3_90_G	0xFA	//user-set offset adjustments = 3,9_G
#define	XL345_OFSX_VALUE_3_92_G	0xFB	//user-set offset adjustments = 3,9156_G
#define	XL345_OFSX_VALUE_3_93_G	0xFC	//user-set offset adjustments = 3,9312_G
#define	XL345_OFSX_VALUE_3_95_G	0xFD	//user-set offset adjustments = 3,9468_G
#define	XL345_OFSX_VALUE_3_96_G	0xFE	//user-set offset adjustments = 3,9624_G
#define	XL345_OFSX_VALUE_3_98_G	0xFF	//user-set offset adjustments = 3,978_G

//OFSY_VALUE

#define	XL345_OFSY_VALUE_NO_OFFSET	0x00	//user-set offset adjustments = 0_G
#define	XL345_OFSY_VALUE_0_02_G	0x01	//user-set offset adjustments = 0,0156_G
#define	XL345_OFSY_VALUE_0_03_G	0x02	//user-set offset adjustments = 0,0312_G
#define	XL345_OFSY_VALUE_0_05_G	0x03	//user-set offset adjustments = 0,0468_G
#define	XL345_OFSY_VALUE_0_06_G	0x04	//user-set offset adjustments = 0,0624_G
#define	XL345_OFSY_VALUE_0_08_G	0x05	//user-set offset adjustments = 0,078_G
#define	XL345_OFSY_VALUE_0_09_G	0x06	//user-set offset adjustments = 0,0936_G
#define	XL345_OFSY_VALUE_0_11_G	0x07	//user-set offset adjustments = 0,1092_G
#define	XL345_OFSY_VALUE_0_12_G	0x08	//user-set offset adjustments = 0,1248_G
#define	XL345_OFSY_VALUE_0_14_G	0x09	//user-set offset adjustments = 0,1404_G
#define	XL345_OFSY_VALUE_0_16_G	0x0A	//user-set offset adjustments = 0,156_G
#define	XL345_OFSY_VALUE_0_17_G	0x0B	//user-set offset adjustments = 0,1716_G
#define	XL345_OFSY_VALUE_0_19_G	0x0C	//user-set offset adjustments = 0,1872_G
#define	XL345_OFSY_VALUE_0_20_G	0x0D	//user-set offset adjustments = 0,2028_G
#define	XL345_OFSY_VALUE_0_22_G	0x0E	//user-set offset adjustments = 0,2184_G
#define	XL345_OFSY_VALUE_0_23_G	0x0F	//user-set offset adjustments = 0,234_G
#define	XL345_OFSY_VALUE_0_25_G	0x10	//user-set offset adjustments = 0,2496_G
#define	XL345_OFSY_VALUE_0_27_G	0x11	//user-set offset adjustments = 0,2652_G
#define	XL345_OFSY_VALUE_0_28_G	0x12	//user-set offset adjustments = 0,2808_G
#define	XL345_OFSY_VALUE_0_30_G	0x13	//user-set offset adjustments = 0,2964_G
#define	XL345_OFSY_VALUE_0_31_G	0x14	//user-set offset adjustments = 0,312_G
#define	XL345_OFSY_VALUE_0_33_G	0x15	//user-set offset adjustments = 0,3276_G
#define	XL345_OFSY_VALUE_0_34_G	0x16	//user-set offset adjustments = 0,3432_G
#define	XL345_OFSY_VALUE_0_36_G	0x17	//user-set offset adjustments = 0,3588_G
#define	XL345_OFSY_VALUE_0_37_G	0x18	//user-set offset adjustments = 0,3744_G
#define	XL345_OFSY_VALUE_0_39_G	0x19	//user-set offset adjustments = 0,39_G
#define	XL345_OFSY_VALUE_0_41_G	0x1A	//user-set offset adjustments = 0,4056_G
#define	XL345_OFSY_VALUE_0_42_G	0x1B	//user-set offset adjustments = 0,4212_G
#define	XL345_OFSY_VALUE_0_44_G	0x1C	//user-set offset adjustments = 0,4368_G
#define	XL345_OFSY_VALUE_0_45_G	0x1D	//user-set offset adjustments = 0,4524_G
#define	XL345_OFSY_VALUE_0_47_G	0x1E	//user-set offset adjustments = 0,468_G
#define	XL345_OFSY_VALUE_0_48_G	0x1F	//user-set offset adjustments = 0,4836_G
#define	XL345_OFSY_VALUE_0_50_G	0x20	//user-set offset adjustments = 0,4992_G
#define	XL345_OFSY_VALUE_0_51_G	0x21	//user-set offset adjustments = 0,5148_G
#define	XL345_OFSY_VALUE_0_53_G	0x22	//user-set offset adjustments = 0,5304_G
#define	XL345_OFSY_VALUE_0_55_G	0x23	//user-set offset adjustments = 0,546_G
#define	XL345_OFSY_VALUE_0_56_G	0x24	//user-set offset adjustments = 0,5616_G
#define	XL345_OFSY_VALUE_0_58_G	0x25	//user-set offset adjustments = 0,5772_G
#define	XL345_OFSY_VALUE_0_59_G	0x26	//user-set offset adjustments = 0,5928_G
#define	XL345_OFSY_VALUE_0_61_G	0x27	//user-set offset adjustments = 0,6084_G
#define	XL345_OFSY_VALUE_0_62_G	0x28	//user-set offset adjustments = 0,624_G
#define	XL345_OFSY_VALUE_0_64_G	0x29	//user-set offset adjustments = 0,6396_G
#define	XL345_OFSY_VALUE_0_66_G	0x2A	//user-set offset adjustments = 0,6552_G
#define	XL345_OFSY_VALUE_0_67_G	0x2B	//user-set offset adjustments = 0,6708_G
#define	XL345_OFSY_VALUE_0_69_G	0x2C	//user-set offset adjustments = 0,6864_G
#define	XL345_OFSY_VALUE_0_70_G	0x2D	//user-set offset adjustments = 0,702_G
#define	XL345_OFSY_VALUE_0_72_G	0x2E	//user-set offset adjustments = 0,7176_G
#define	XL345_OFSY_VALUE_0_73_G	0x2F	//user-set offset adjustments = 0,7332_G
#define	XL345_OFSY_VALUE_0_75_G	0x30	//user-set offset adjustments = 0,7488_G
#define	XL345_OFSY_VALUE_0_76_G	0x31	//user-set offset adjustments = 0,7644_G
#define	XL345_OFSY_VALUE_0_78_G	0x32	//user-set offset adjustments = 0,78_G
#define	XL345_OFSY_VALUE_0_80_G	0x33	//user-set offset adjustments = 0,7956_G
#define	XL345_OFSY_VALUE_0_81_G	0x34	//user-set offset adjustments = 0,8112_G
#define	XL345_OFSY_VALUE_0_83_G	0x35	//user-set offset adjustments = 0,8268_G
#define	XL345_OFSY_VALUE_0_84_G	0x36	//user-set offset adjustments = 0,8424_G
#define	XL345_OFSY_VALUE_0_86_G	0x37	//user-set offset adjustments = 0,858_G
#define	XL345_OFSY_VALUE_0_87_G	0x38	//user-set offset adjustments = 0,8736_G
#define	XL345_OFSY_VALUE_0_89_G	0x39	//user-set offset adjustments = 0,8892_G
#define	XL345_OFSY_VALUE_0_90_G	0x3A	//user-set offset adjustments = 0,9048_G
#define	XL345_OFSY_VALUE_0_92_G	0x3B	//user-set offset adjustments = 0,9204_G
#define	XL345_OFSY_VALUE_0_94_G	0x3C	//user-set offset adjustments = 0,936_G
#define	XL345_OFSY_VALUE_0_95_G	0x3D	//user-set offset adjustments = 0,9516_G
#define	XL345_OFSY_VALUE_0_97_G	0x3E	//user-set offset adjustments = 0,9672_G
#define	XL345_OFSY_VALUE_0_98_G	0x3F	//user-set offset adjustments = 0,9828_G
#define	XL345_OFSY_VALUE_1_00_G	0x40	//user-set offset adjustments = 0,9984_G
#define	XL345_OFSY_VALUE_1_01_G	0x41	//user-set offset adjustments = 1,014_G
#define	XL345_OFSY_VALUE_1_03_G	0x42	//user-set offset adjustments = 1,0296_G
#define	XL345_OFSY_VALUE_1_05_G	0x43	//user-set offset adjustments = 1,0452_G
#define	XL345_OFSY_VALUE_1_06_G	0x44	//user-set offset adjustments = 1,0608_G
#define	XL345_OFSY_VALUE_1_08_G	0x45	//user-set offset adjustments = 1,0764_G
#define	XL345_OFSY_VALUE_1_09_G	0x46	//user-set offset adjustments = 1,092_G
#define	XL345_OFSY_VALUE_1_11_G	0x47	//user-set offset adjustments = 1,1076_G
#define	XL345_OFSY_VALUE_1_12_G	0x48	//user-set offset adjustments = 1,1232_G
#define	XL345_OFSY_VALUE_1_14_G	0x49	//user-set offset adjustments = 1,1388_G
#define	XL345_OFSY_VALUE_1_15_G	0x4A	//user-set offset adjustments = 1,1544_G
#define	XL345_OFSY_VALUE_1_17_G	0x4B	//user-set offset adjustments = 1,17_G
#define	XL345_OFSY_VALUE_1_19_G	0x4C	//user-set offset adjustments = 1,1856_G
#define	XL345_OFSY_VALUE_1_20_G	0x4D	//user-set offset adjustments = 1,2012_G
#define	XL345_OFSY_VALUE_1_22_G	0x4E	//user-set offset adjustments = 1,2168_G
#define	XL345_OFSY_VALUE_1_23_G	0x4F	//user-set offset adjustments = 1,2324_G
#define	XL345_OFSY_VALUE_1_25_G	0x50	//user-set offset adjustments = 1,248_G
#define	XL345_OFSY_VALUE_1_26_G	0x51	//user-set offset adjustments = 1,2636_G
#define	XL345_OFSY_VALUE_1_28_G	0x52	//user-set offset adjustments = 1,2792_G
#define	XL345_OFSY_VALUE_1_29_G	0x53	//user-set offset adjustments = 1,2948_G
#define	XL345_OFSY_VALUE_1_31_G	0x54	//user-set offset adjustments = 1,3104_G
#define	XL345_OFSY_VALUE_1_33_G	0x55	//user-set offset adjustments = 1,326_G
#define	XL345_OFSY_VALUE_1_34_G	0x56	//user-set offset adjustments = 1,3416_G
#define	XL345_OFSY_VALUE_1_36_G	0x57	//user-set offset adjustments = 1,3572_G
#define	XL345_OFSY_VALUE_1_37_G	0x58	//user-set offset adjustments = 1,3728_G
#define	XL345_OFSY_VALUE_1_39_G	0x59	//user-set offset adjustments = 1,3884_G
#define	XL345_OFSY_VALUE_1_40_G	0x5A	//user-set offset adjustments = 1,404_G
#define	XL345_OFSY_VALUE_1_42_G	0x5B	//user-set offset adjustments = 1,4196_G
#define	XL345_OFSY_VALUE_1_44_G	0x5C	//user-set offset adjustments = 1,4352_G
#define	XL345_OFSY_VALUE_1_45_G	0x5D	//user-set offset adjustments = 1,4508_G
#define	XL345_OFSY_VALUE_1_47_G	0x5E	//user-set offset adjustments = 1,4664_G
#define	XL345_OFSY_VALUE_1_48_G	0x5F	//user-set offset adjustments = 1,482_G
#define	XL345_OFSY_VALUE_1_50_G	0x60	//user-set offset adjustments = 1,4976_G
#define	XL345_OFSY_VALUE_1_51_G	0x61	//user-set offset adjustments = 1,5132_G
#define	XL345_OFSY_VALUE_1_53_G	0x62	//user-set offset adjustments = 1,5288_G
#define	XL345_OFSY_VALUE_1_54_G	0x63	//user-set offset adjustments = 1,5444_G
#define	XL345_OFSY_VALUE_1_56_G	0x64	//user-set offset adjustments = 1,56_G
#define	XL345_OFSY_VALUE_1_58_G	0x65	//user-set offset adjustments = 1,5756_G
#define	XL345_OFSY_VALUE_1_59_G	0x66	//user-set offset adjustments = 1,5912_G
#define	XL345_OFSY_VALUE_1_61_G	0x67	//user-set offset adjustments = 1,6068_G
#define	XL345_OFSY_VALUE_1_62_G	0x68	//user-set offset adjustments = 1,6224_G
#define	XL345_OFSY_VALUE_1_64_G	0x69	//user-set offset adjustments = 1,638_G
#define	XL345_OFSY_VALUE_1_65_G	0x6A	//user-set offset adjustments = 1,6536_G
#define	XL345_OFSY_VALUE_1_67_G	0x6B	//user-set offset adjustments = 1,6692_G
#define	XL345_OFSY_VALUE_1_68_G	0x6C	//user-set offset adjustments = 1,6848_G
#define	XL345_OFSY_VALUE_1_70_G	0x6D	//user-set offset adjustments = 1,7004_G
#define	XL345_OFSY_VALUE_1_72_G	0x6E	//user-set offset adjustments = 1,716_G
#define	XL345_OFSY_VALUE_1_73_G	0x6F	//user-set offset adjustments = 1,7316_G
#define	XL345_OFSY_VALUE_1_75_G	0x70	//user-set offset adjustments = 1,7472_G
#define	XL345_OFSY_VALUE_1_76_G	0x71	//user-set offset adjustments = 1,7628_G
#define	XL345_OFSY_VALUE_1_78_G	0x72	//user-set offset adjustments = 1,7784_G
#define	XL345_OFSY_VALUE_1_79_G	0x73	//user-set offset adjustments = 1,794_G
#define	XL345_OFSY_VALUE_1_81_G	0x74	//user-set offset adjustments = 1,8096_G
#define	XL345_OFSY_VALUE_1_83_G	0x75	//user-set offset adjustments = 1,8252_G
#define	XL345_OFSY_VALUE_1_84_G	0x76	//user-set offset adjustments = 1,8408_G
#define	XL345_OFSY_VALUE_1_86_G	0x77	//user-set offset adjustments = 1,8564_G
#define	XL345_OFSY_VALUE_1_87_G	0x78	//user-set offset adjustments = 1,872_G
#define	XL345_OFSY_VALUE_1_89_G	0x79	//user-set offset adjustments = 1,8876_G
#define	XL345_OFSY_VALUE_1_90_G	0x7A	//user-set offset adjustments = 1,9032_G
#define	XL345_OFSY_VALUE_1_92_G	0x7B	//user-set offset adjustments = 1,9188_G
#define	XL345_OFSY_VALUE_1_93_G	0x7C	//user-set offset adjustments = 1,9344_G
#define	XL345_OFSY_VALUE_1_95_G	0x7D	//user-set offset adjustments = 1,95_G
#define	XL345_OFSY_VALUE_1_97_G	0x7E	//user-set offset adjustments = 1,9656_G
#define	XL345_OFSY_VALUE_1_98_G	0x7F	//user-set offset adjustments = 1,9812_G
#define	XL345_OFSY_VALUE_2_00_G	0x80	//user-set offset adjustments = 1,9968_G
#define	XL345_OFSY_VALUE_2_01_G	0x81	//user-set offset adjustments = 2,0124_G
#define	XL345_OFSY_VALUE_2_03_G	0x82	//user-set offset adjustments = 2,028_G
#define	XL345_OFSY_VALUE_2_04_G	0x83	//user-set offset adjustments = 2,0436_G
#define	XL345_OFSY_VALUE_2_06_G	0x84	//user-set offset adjustments = 2,0592_G
#define	XL345_OFSY_VALUE_2_07_G	0x85	//user-set offset adjustments = 2,0748_G
#define	XL345_OFSY_VALUE_2_09_G	0x86	//user-set offset adjustments = 2,0904_G
#define	XL345_OFSY_VALUE_2_11_G	0x87	//user-set offset adjustments = 2,106_G
#define	XL345_OFSY_VALUE_2_12_G	0x88	//user-set offset adjustments = 2,1216_G
#define	XL345_OFSY_VALUE_2_14_G	0x89	//user-set offset adjustments = 2,1372_G
#define	XL345_OFSY_VALUE_2_15_G	0x8A	//user-set offset adjustments = 2,1528_G
#define	XL345_OFSY_VALUE_2_17_G	0x8B	//user-set offset adjustments = 2,1684_G
#define	XL345_OFSY_VALUE_2_18_G	0x8C	//user-set offset adjustments = 2,184_G
#define	XL345_OFSY_VALUE_2_20_G	0x8D	//user-set offset adjustments = 2,1996_G
#define	XL345_OFSY_VALUE_2_22_G	0x8E	//user-set offset adjustments = 2,2152_G
#define	XL345_OFSY_VALUE_2_23_G	0x8F	//user-set offset adjustments = 2,2308_G
#define	XL345_OFSY_VALUE_2_25_G	0x90	//user-set offset adjustments = 2,2464_G
#define	XL345_OFSY_VALUE_2_26_G	0x91	//user-set offset adjustments = 2,262_G
#define	XL345_OFSY_VALUE_2_28_G	0x92	//user-set offset adjustments = 2,2776_G
#define	XL345_OFSY_VALUE_2_29_G	0x93	//user-set offset adjustments = 2,2932_G
#define	XL345_OFSY_VALUE_2_31_G	0x94	//user-set offset adjustments = 2,3088_G
#define	XL345_OFSY_VALUE_2_32_G	0x95	//user-set offset adjustments = 2,3244_G
#define	XL345_OFSY_VALUE_2_34_G	0x96	//user-set offset adjustments = 2,34_G
#define	XL345_OFSY_VALUE_2_36_G	0x97	//user-set offset adjustments = 2,3556_G
#define	XL345_OFSY_VALUE_2_37_G	0x98	//user-set offset adjustments = 2,3712_G
#define	XL345_OFSY_VALUE_2_39_G	0x99	//user-set offset adjustments = 2,3868_G
#define	XL345_OFSY_VALUE_2_40_G	0x9A	//user-set offset adjustments = 2,4024_G
#define	XL345_OFSY_VALUE_2_42_G	0x9B	//user-set offset adjustments = 2,418_G
#define	XL345_OFSY_VALUE_2_43_G	0x9C	//user-set offset adjustments = 2,4336_G
#define	XL345_OFSY_VALUE_2_45_G	0x9D	//user-set offset adjustments = 2,4492_G
#define	XL345_OFSY_VALUE_2_46_G	0x9E	//user-set offset adjustments = 2,4648_G
#define	XL345_OFSY_VALUE_2_48_G	0x9F	//user-set offset adjustments = 2,4804_G
#define	XL345_OFSY_VALUE_2_50_G	0xA0	//user-set offset adjustments = 2,496_G
#define	XL345_OFSY_VALUE_2_51_G	0xA1	//user-set offset adjustments = 2,5116_G
#define	XL345_OFSY_VALUE_2_53_G	0xA2	//user-set offset adjustments = 2,5272_G
#define	XL345_OFSY_VALUE_2_54_G	0xA3	//user-set offset adjustments = 2,5428_G
#define	XL345_OFSY_VALUE_2_56_G	0xA4	//user-set offset adjustments = 2,5584_G
#define	XL345_OFSY_VALUE_2_57_G	0xA5	//user-set offset adjustments = 2,574_G
#define	XL345_OFSY_VALUE_2_59_G	0xA6	//user-set offset adjustments = 2,5896_G
#define	XL345_OFSY_VALUE_2_61_G	0xA7	//user-set offset adjustments = 2,6052_G
#define	XL345_OFSY_VALUE_2_62_G	0xA8	//user-set offset adjustments = 2,6208_G
#define	XL345_OFSY_VALUE_2_64_G	0xA9	//user-set offset adjustments = 2,6364_G
#define	XL345_OFSY_VALUE_2_65_G	0xAA	//user-set offset adjustments = 2,652_G
#define	XL345_OFSY_VALUE_2_67_G	0xAB	//user-set offset adjustments = 2,6676_G
#define	XL345_OFSY_VALUE_2_68_G	0xAC	//user-set offset adjustments = 2,6832_G
#define	XL345_OFSY_VALUE_2_70_G	0xAD	//user-set offset adjustments = 2,6988_G
#define	XL345_OFSY_VALUE_2_71_G	0xAE	//user-set offset adjustments = 2,7144_G
#define	XL345_OFSY_VALUE_2_73_G	0xAF	//user-set offset adjustments = 2,73_G
#define	XL345_OFSY_VALUE_2_75_G	0xB0	//user-set offset adjustments = 2,7456_G
#define	XL345_OFSY_VALUE_2_76_G	0xB1	//user-set offset adjustments = 2,7612_G
#define	XL345_OFSY_VALUE_2_78_G	0xB2	//user-set offset adjustments = 2,7768_G
#define	XL345_OFSY_VALUE_2_79_G	0xB3	//user-set offset adjustments = 2,7924_G
#define	XL345_OFSY_VALUE_2_81_G	0xB4	//user-set offset adjustments = 2,808_G
#define	XL345_OFSY_VALUE_2_82_G	0xB5	//user-set offset adjustments = 2,8236_G
#define	XL345_OFSY_VALUE_2_84_G	0xB6	//user-set offset adjustments = 2,8392_G
#define	XL345_OFSY_VALUE_2_85_G	0xB7	//user-set offset adjustments = 2,8548_G
#define	XL345_OFSY_VALUE_2_87_G	0xB8	//user-set offset adjustments = 2,8704_G
#define	XL345_OFSY_VALUE_2_89_G	0xB9	//user-set offset adjustments = 2,886_G
#define	XL345_OFSY_VALUE_2_90_G	0xBA	//user-set offset adjustments = 2,9016_G
#define	XL345_OFSY_VALUE_2_92_G	0xBB	//user-set offset adjustments = 2,9172_G
#define	XL345_OFSY_VALUE_2_93_G	0xBC	//user-set offset adjustments = 2,9328_G
#define	XL345_OFSY_VALUE_2_95_G	0xBD	//user-set offset adjustments = 2,9484_G
#define	XL345_OFSY_VALUE_2_96_G	0xBE	//user-set offset adjustments = 2,964_G
#define	XL345_OFSY_VALUE_2_98_G	0xBF	//user-set offset adjustments = 2,9796_G
#define	XL345_OFSY_VALUE_3_00_G	0xC0	//user-set offset adjustments = 2,9952_G
#define	XL345_OFSY_VALUE_3_01_G	0xC1	//user-set offset adjustments = 3,0108_G
#define	XL345_OFSY_VALUE_3_03_G	0xC2	//user-set offset adjustments = 3,0264_G
#define	XL345_OFSY_VALUE_3_04_G	0xC3	//user-set offset adjustments = 3,042_G
#define	XL345_OFSY_VALUE_3_06_G	0xC4	//user-set offset adjustments = 3,0576_G
#define	XL345_OFSY_VALUE_3_07_G	0xC5	//user-set offset adjustments = 3,0732_G
#define	XL345_OFSY_VALUE_3_09_G	0xC6	//user-set offset adjustments = 3,0888_G
#define	XL345_OFSY_VALUE_3_10_G	0xC7	//user-set offset adjustments = 3,1044_G
#define	XL345_OFSY_VALUE_3_12_G	0xC8	//user-set offset adjustments = 3,12_G
#define	XL345_OFSY_VALUE_3_14_G	0xC9	//user-set offset adjustments = 3,1356_G
#define	XL345_OFSY_VALUE_3_15_G	0xCA	//user-set offset adjustments = 3,1512_G
#define	XL345_OFSY_VALUE_3_17_G	0xCB	//user-set offset adjustments = 3,1668_G
#define	XL345_OFSY_VALUE_3_18_G	0xCC	//user-set offset adjustments = 3,1824_G
#define	XL345_OFSY_VALUE_3_20_G	0xCD	//user-set offset adjustments = 3,198_G
#define	XL345_OFSY_VALUE_3_21_G	0xCE	//user-set offset adjustments = 3,2136_G
#define	XL345_OFSY_VALUE_3_23_G	0xCF	//user-set offset adjustments = 3,2292_G
#define	XL345_OFSY_VALUE_3_24_G	0xD0	//user-set offset adjustments = 3,2448_G
#define	XL345_OFSY_VALUE_3_26_G	0xD1	//user-set offset adjustments = 3,2604_G
#define	XL345_OFSY_VALUE_3_28_G	0xD2	//user-set offset adjustments = 3,276_G
#define	XL345_OFSY_VALUE_3_29_G	0xD3	//user-set offset adjustments = 3,2916_G
#define	XL345_OFSY_VALUE_3_31_G	0xD4	//user-set offset adjustments = 3,3072_G
#define	XL345_OFSY_VALUE_3_32_G	0xD5	//user-set offset adjustments = 3,3228_G
#define	XL345_OFSY_VALUE_3_34_G	0xD6	//user-set offset adjustments = 3,3384_G
#define	XL345_OFSY_VALUE_3_35_G	0xD7	//user-set offset adjustments = 3,354_G
#define	XL345_OFSY_VALUE_3_37_G	0xD8	//user-set offset adjustments = 3,3696_G
#define	XL345_OFSY_VALUE_3_39_G	0xD9	//user-set offset adjustments = 3,3852_G
#define	XL345_OFSY_VALUE_3_40_G	0xDA	//user-set offset adjustments = 3,4008_G
#define	XL345_OFSY_VALUE_3_42_G	0xDB	//user-set offset adjustments = 3,4164_G
#define	XL345_OFSY_VALUE_3_43_G	0xDC	//user-set offset adjustments = 3,432_G
#define	XL345_OFSY_VALUE_3_45_G	0xDD	//user-set offset adjustments = 3,4476_G
#define	XL345_OFSY_VALUE_3_46_G	0xDE	//user-set offset adjustments = 3,4632_G
#define	XL345_OFSY_VALUE_3_48_G	0xDF	//user-set offset adjustments = 3,4788_G
#define	XL345_OFSY_VALUE_3_49_G	0xE0	//user-set offset adjustments = 3,4944_G
#define	XL345_OFSY_VALUE_3_51_G	0xE1	//user-set offset adjustments = 3,51_G
#define	XL345_OFSY_VALUE_3_53_G	0xE2	//user-set offset adjustments = 3,5256_G
#define	XL345_OFSY_VALUE_3_54_G	0xE3	//user-set offset adjustments = 3,5412_G
#define	XL345_OFSY_VALUE_3_56_G	0xE4	//user-set offset adjustments = 3,5568_G
#define	XL345_OFSY_VALUE_3_57_G	0xE5	//user-set offset adjustments = 3,5724_G
#define	XL345_OFSY_VALUE_3_59_G	0xE6	//user-set offset adjustments = 3,588_G
#define	XL345_OFSY_VALUE_3_60_G	0xE7	//user-set offset adjustments = 3,6036_G
#define	XL345_OFSY_VALUE_3_62_G	0xE8	//user-set offset adjustments = 3,6192_G
#define	XL345_OFSY_VALUE_3_63_G	0xE9	//user-set offset adjustments = 3,6348_G
#define	XL345_OFSY_VALUE_3_65_G	0xEA	//user-set offset adjustments = 3,6504_G
#define	XL345_OFSY_VALUE_3_67_G	0xEB	//user-set offset adjustments = 3,666_G
#define	XL345_OFSY_VALUE_3_68_G	0xEC	//user-set offset adjustments = 3,6816_G
#define	XL345_OFSY_VALUE_3_70_G	0xED	//user-set offset adjustments = 3,6972_G
#define	XL345_OFSY_VALUE_3_71_G	0xEE	//user-set offset adjustments = 3,7128_G
#define	XL345_OFSY_VALUE_3_73_G	0xEF	//user-set offset adjustments = 3,7284_G
#define	XL345_OFSY_VALUE_3_74_G	0xF0	//user-set offset adjustments = 3,744_G
#define	XL345_OFSY_VALUE_3_76_G	0xF1	//user-set offset adjustments = 3,7596_G
#define	XL345_OFSY_VALUE_3_78_G	0xF2	//user-set offset adjustments = 3,7752_G
#define	XL345_OFSY_VALUE_3_79_G	0xF3	//user-set offset adjustments = 3,7908_G
#define	XL345_OFSY_VALUE_3_81_G	0xF4	//user-set offset adjustments = 3,8064_G
#define	XL345_OFSY_VALUE_3_82_G	0xF5	//user-set offset adjustments = 3,822_G
#define	XL345_OFSY_VALUE_3_84_G	0xF6	//user-set offset adjustments = 3,8376_G
#define	XL345_OFSY_VALUE_3_85_G	0xF7	//user-set offset adjustments = 3,8532_G
#define	XL345_OFSY_VALUE_3_87_G	0xF8	//user-set offset adjustments = 3,8688_G
#define	XL345_OFSY_VALUE_3_88_G	0xF9	//user-set offset adjustments = 3,8844_G
#define	XL345_OFSY_VALUE_3_90_G	0xFA	//user-set offset adjustments = 3,9_G
#define	XL345_OFSY_VALUE_3_92_G	0xFB	//user-set offset adjustments = 3,9156_G
#define	XL345_OFSY_VALUE_3_93_G	0xFC	//user-set offset adjustments = 3,9312_G
#define	XL345_OFSY_VALUE_3_95_G	0xFD	//user-set offset adjustments = 3,9468_G
#define	XL345_OFSY_VALUE_3_96_G	0xFE	//user-set offset adjustments = 3,9624_G
#define	XL345_OFSY_VALUE_3_98_G	0xFF	//user-set offset adjustments = 3,978_G

//OFSZ Value:

#define	XL345_OFSZ_VALUE_NO_OFFSET	0x00	//user-set offset adjustments = 0_G
#define	XL345_OFSZ_VALUE_0_02_G	0x01	//user-set offset adjustments = 0,0156_G
#define	XL345_OFSZ_VALUE_0_03_G	0x02	//user-set offset adjustments = 0,0312_G
#define	XL345_OFSZ_VALUE_0_05_G	0x03	//user-set offset adjustments = 0,0468_G
#define	XL345_OFSZ_VALUE_0_06_G	0x04	//user-set offset adjustments = 0,0624_G
#define	XL345_OFSZ_VALUE_0_08_G	0x05	//user-set offset adjustments = 0,078_G
#define	XL345_OFSZ_VALUE_0_09_G	0x06	//user-set offset adjustments = 0,0936_G
#define	XL345_OFSZ_VALUE_0_11_G	0x07	//user-set offset adjustments = 0,1092_G
#define	XL345_OFSZ_VALUE_0_12_G	0x08	//user-set offset adjustments = 0,1248_G
#define	XL345_OFSZ_VALUE_0_14_G	0x09	//user-set offset adjustments = 0,1404_G
#define	XL345_OFSZ_VALUE_0_16_G	0x0A	//user-set offset adjustments = 0,156_G
#define	XL345_OFSZ_VALUE_0_17_G	0x0B	//user-set offset adjustments = 0,1716_G
#define	XL345_OFSZ_VALUE_0_19_G	0x0C	//user-set offset adjustments = 0,1872_G
#define	XL345_OFSZ_VALUE_0_20_G	0x0D	//user-set offset adjustments = 0,2028_G
#define	XL345_OFSZ_VALUE_0_22_G	0x0E	//user-set offset adjustments = 0,2184_G
#define	XL345_OFSZ_VALUE_0_23_G	0x0F	//user-set offset adjustments = 0,234_G
#define	XL345_OFSZ_VALUE_0_25_G	0x10	//user-set offset adjustments = 0,2496_G
#define	XL345_OFSZ_VALUE_0_27_G	0x11	//user-set offset adjustments = 0,2652_G
#define	XL345_OFSZ_VALUE_0_28_G	0x12	//user-set offset adjustments = 0,2808_G
#define	XL345_OFSZ_VALUE_0_30_G	0x13	//user-set offset adjustments = 0,2964_G
#define	XL345_OFSZ_VALUE_0_31_G	0x14	//user-set offset adjustments = 0,312_G
#define	XL345_OFSZ_VALUE_0_33_G	0x15	//user-set offset adjustments = 0,3276_G
#define	XL345_OFSZ_VALUE_0_34_G	0x16	//user-set offset adjustments = 0,3432_G
#define	XL345_OFSZ_VALUE_0_36_G	0x17	//user-set offset adjustments = 0,3588_G
#define	XL345_OFSZ_VALUE_0_37_G	0x18	//user-set offset adjustments = 0,3744_G
#define	XL345_OFSZ_VALUE_0_39_G	0x19	//user-set offset adjustments = 0,39_G
#define	XL345_OFSZ_VALUE_0_41_G	0x1A	//user-set offset adjustments = 0,4056_G
#define	XL345_OFSZ_VALUE_0_42_G	0x1B	//user-set offset adjustments = 0,4212_G
#define	XL345_OFSZ_VALUE_0_44_G	0x1C	//user-set offset adjustments = 0,4368_G
#define	XL345_OFSZ_VALUE_0_45_G	0x1D	//user-set offset adjustments = 0,4524_G
#define	XL345_OFSZ_VALUE_0_47_G	0x1E	//user-set offset adjustments = 0,468_G
#define	XL345_OFSZ_VALUE_0_48_G	0x1F	//user-set offset adjustments = 0,4836_G
#define	XL345_OFSZ_VALUE_0_50_G	0x20	//user-set offset adjustments = 0,4992_G
#define	XL345_OFSZ_VALUE_0_51_G	0x21	//user-set offset adjustments = 0,5148_G
#define	XL345_OFSZ_VALUE_0_53_G	0x22	//user-set offset adjustments = 0,5304_G
#define	XL345_OFSZ_VALUE_0_55_G	0x23	//user-set offset adjustments = 0,546_G
#define	XL345_OFSZ_VALUE_0_56_G	0x24	//user-set offset adjustments = 0,5616_G
#define	XL345_OFSZ_VALUE_0_58_G	0x25	//user-set offset adjustments = 0,5772_G
#define	XL345_OFSZ_VALUE_0_59_G	0x26	//user-set offset adjustments = 0,5928_G
#define	XL345_OFSZ_VALUE_0_61_G	0x27	//user-set offset adjustments = 0,6084_G
#define	XL345_OFSZ_VALUE_0_62_G	0x28	//user-set offset adjustments = 0,624_G
#define	XL345_OFSZ_VALUE_0_64_G	0x29	//user-set offset adjustments = 0,6396_G
#define	XL345_OFSZ_VALUE_0_66_G	0x2A	//user-set offset adjustments = 0,6552_G
#define	XL345_OFSZ_VALUE_0_67_G	0x2B	//user-set offset adjustments = 0,6708_G
#define	XL345_OFSZ_VALUE_0_69_G	0x2C	//user-set offset adjustments = 0,6864_G
#define	XL345_OFSZ_VALUE_0_70_G	0x2D	//user-set offset adjustments = 0,702_G
#define	XL345_OFSZ_VALUE_0_72_G	0x2E	//user-set offset adjustments = 0,7176_G
#define	XL345_OFSZ_VALUE_0_73_G	0x2F	//user-set offset adjustments = 0,7332_G
#define	XL345_OFSZ_VALUE_0_75_G	0x30	//user-set offset adjustments = 0,7488_G
#define	XL345_OFSZ_VALUE_0_76_G	0x31	//user-set offset adjustments = 0,7644_G
#define	XL345_OFSZ_VALUE_0_78_G	0x32	//user-set offset adjustments = 0,78_G
#define	XL345_OFSZ_VALUE_0_80_G	0x33	//user-set offset adjustments = 0,7956_G
#define	XL345_OFSZ_VALUE_0_81_G	0x34	//user-set offset adjustments = 0,8112_G
#define	XL345_OFSZ_VALUE_0_83_G	0x35	//user-set offset adjustments = 0,8268_G
#define	XL345_OFSZ_VALUE_0_84_G	0x36	//user-set offset adjustments = 0,8424_G
#define	XL345_OFSZ_VALUE_0_86_G	0x37	//user-set offset adjustments = 0,858_G
#define	XL345_OFSZ_VALUE_0_87_G	0x38	//user-set offset adjustments = 0,8736_G
#define	XL345_OFSZ_VALUE_0_89_G	0x39	//user-set offset adjustments = 0,8892_G
#define	XL345_OFSZ_VALUE_0_90_G	0x3A	//user-set offset adjustments = 0,9048_G
#define	XL345_OFSZ_VALUE_0_92_G	0x3B	//user-set offset adjustments = 0,9204_G
#define	XL345_OFSZ_VALUE_0_94_G	0x3C	//user-set offset adjustments = 0,936_G
#define	XL345_OFSZ_VALUE_0_95_G	0x3D	//user-set offset adjustments = 0,9516_G
#define	XL345_OFSZ_VALUE_0_97_G	0x3E	//user-set offset adjustments = 0,9672_G
#define	XL345_OFSZ_VALUE_0_98_G	0x3F	//user-set offset adjustments = 0,9828_G
#define	XL345_OFSZ_VALUE_1_00_G	0x40	//user-set offset adjustments = 0,9984_G
#define	XL345_OFSZ_VALUE_1_01_G	0x41	//user-set offset adjustments = 1,014_G
#define	XL345_OFSZ_VALUE_1_03_G	0x42	//user-set offset adjustments = 1,0296_G
#define	XL345_OFSZ_VALUE_1_05_G	0x43	//user-set offset adjustments = 1,0452_G
#define	XL345_OFSZ_VALUE_1_06_G	0x44	//user-set offset adjustments = 1,0608_G
#define	XL345_OFSZ_VALUE_1_08_G	0x45	//user-set offset adjustments = 1,0764_G
#define	XL345_OFSZ_VALUE_1_09_G	0x46	//user-set offset adjustments = 1,092_G
#define	XL345_OFSZ_VALUE_1_11_G	0x47	//user-set offset adjustments = 1,1076_G
#define	XL345_OFSZ_VALUE_1_12_G	0x48	//user-set offset adjustments = 1,1232_G
#define	XL345_OFSZ_VALUE_1_14_G	0x49	//user-set offset adjustments = 1,1388_G
#define	XL345_OFSZ_VALUE_1_15_G	0x4A	//user-set offset adjustments = 1,1544_G
#define	XL345_OFSZ_VALUE_1_17_G	0x4B	//user-set offset adjustments = 1,17_G
#define	XL345_OFSZ_VALUE_1_19_G	0x4C	//user-set offset adjustments = 1,1856_G
#define	XL345_OFSZ_VALUE_1_20_G	0x4D	//user-set offset adjustments = 1,2012_G
#define	XL345_OFSZ_VALUE_1_22_G	0x4E	//user-set offset adjustments = 1,2168_G
#define	XL345_OFSZ_VALUE_1_23_G	0x4F	//user-set offset adjustments = 1,2324_G
#define	XL345_OFSZ_VALUE_1_25_G	0x50	//user-set offset adjustments = 1,248_G
#define	XL345_OFSZ_VALUE_1_26_G	0x51	//user-set offset adjustments = 1,2636_G
#define	XL345_OFSZ_VALUE_1_28_G	0x52	//user-set offset adjustments = 1,2792_G
#define	XL345_OFSZ_VALUE_1_29_G	0x53	//user-set offset adjustments = 1,2948_G
#define	XL345_OFSZ_VALUE_1_31_G	0x54	//user-set offset adjustments = 1,3104_G
#define	XL345_OFSZ_VALUE_1_33_G	0x55	//user-set offset adjustments = 1,326_G
#define	XL345_OFSZ_VALUE_1_34_G	0x56	//user-set offset adjustments = 1,3416_G
#define	XL345_OFSZ_VALUE_1_36_G	0x57	//user-set offset adjustments = 1,3572_G
#define	XL345_OFSZ_VALUE_1_37_G	0x58	//user-set offset adjustments = 1,3728_G
#define	XL345_OFSZ_VALUE_1_39_G	0x59	//user-set offset adjustments = 1,3884_G
#define	XL345_OFSZ_VALUE_1_40_G	0x5A	//user-set offset adjustments = 1,404_G
#define	XL345_OFSZ_VALUE_1_42_G	0x5B	//user-set offset adjustments = 1,4196_G
#define	XL345_OFSZ_VALUE_1_44_G	0x5C	//user-set offset adjustments = 1,4352_G
#define	XL345_OFSZ_VALUE_1_45_G	0x5D	//user-set offset adjustments = 1,4508_G
#define	XL345_OFSZ_VALUE_1_47_G	0x5E	//user-set offset adjustments = 1,4664_G
#define	XL345_OFSZ_VALUE_1_48_G	0x5F	//user-set offset adjustments = 1,482_G
#define	XL345_OFSZ_VALUE_1_50_G	0x60	//user-set offset adjustments = 1,4976_G
#define	XL345_OFSZ_VALUE_1_51_G	0x61	//user-set offset adjustments = 1,5132_G
#define	XL345_OFSZ_VALUE_1_53_G	0x62	//user-set offset adjustments = 1,5288_G
#define	XL345_OFSZ_VALUE_1_54_G	0x63	//user-set offset adjustments = 1,5444_G
#define	XL345_OFSZ_VALUE_1_56_G	0x64	//user-set offset adjustments = 1,56_G
#define	XL345_OFSZ_VALUE_1_58_G	0x65	//user-set offset adjustments = 1,5756_G
#define	XL345_OFSZ_VALUE_1_59_G	0x66	//user-set offset adjustments = 1,5912_G
#define	XL345_OFSZ_VALUE_1_61_G	0x67	//user-set offset adjustments = 1,6068_G
#define	XL345_OFSZ_VALUE_1_62_G	0x68	//user-set offset adjustments = 1,6224_G
#define	XL345_OFSZ_VALUE_1_64_G	0x69	//user-set offset adjustments = 1,638_G
#define	XL345_OFSZ_VALUE_1_65_G	0x6A	//user-set offset adjustments = 1,6536_G
#define	XL345_OFSZ_VALUE_1_67_G	0x6B	//user-set offset adjustments = 1,6692_G
#define	XL345_OFSZ_VALUE_1_68_G	0x6C	//user-set offset adjustments = 1,6848_G
#define	XL345_OFSZ_VALUE_1_70_G	0x6D	//user-set offset adjustments = 1,7004_G
#define	XL345_OFSZ_VALUE_1_72_G	0x6E	//user-set offset adjustments = 1,716_G
#define	XL345_OFSZ_VALUE_1_73_G	0x6F	//user-set offset adjustments = 1,7316_G
#define	XL345_OFSZ_VALUE_1_75_G	0x70	//user-set offset adjustments = 1,7472_G
#define	XL345_OFSZ_VALUE_1_76_G	0x71	//user-set offset adjustments = 1,7628_G
#define	XL345_OFSZ_VALUE_1_78_G	0x72	//user-set offset adjustments = 1,7784_G
#define	XL345_OFSZ_VALUE_1_79_G	0x73	//user-set offset adjustments = 1,794_G
#define	XL345_OFSZ_VALUE_1_81_G	0x74	//user-set offset adjustments = 1,8096_G
#define	XL345_OFSZ_VALUE_1_83_G	0x75	//user-set offset adjustments = 1,8252_G
#define	XL345_OFSZ_VALUE_1_84_G	0x76	//user-set offset adjustments = 1,8408_G
#define	XL345_OFSZ_VALUE_1_86_G	0x77	//user-set offset adjustments = 1,8564_G
#define	XL345_OFSZ_VALUE_1_87_G	0x78	//user-set offset adjustments = 1,872_G
#define	XL345_OFSZ_VALUE_1_89_G	0x79	//user-set offset adjustments = 1,8876_G
#define	XL345_OFSZ_VALUE_1_90_G	0x7A	//user-set offset adjustments = 1,9032_G
#define	XL345_OFSZ_VALUE_1_92_G	0x7B	//user-set offset adjustments = 1,9188_G
#define	XL345_OFSZ_VALUE_1_93_G	0x7C	//user-set offset adjustments = 1,9344_G
#define	XL345_OFSZ_VALUE_1_95_G	0x7D	//user-set offset adjustments = 1,95_G
#define	XL345_OFSZ_VALUE_1_97_G	0x7E	//user-set offset adjustments = 1,9656_G
#define	XL345_OFSZ_VALUE_1_98_G	0x7F	//user-set offset adjustments = 1,9812_G
#define	XL345_OFSZ_VALUE_2_00_G	0x80	//user-set offset adjustments = 1,9968_G
#define	XL345_OFSZ_VALUE_2_01_G	0x81	//user-set offset adjustments = 2,0124_G
#define	XL345_OFSZ_VALUE_2_03_G	0x82	//user-set offset adjustments = 2,028_G
#define	XL345_OFSZ_VALUE_2_04_G	0x83	//user-set offset adjustments = 2,0436_G
#define	XL345_OFSZ_VALUE_2_06_G	0x84	//user-set offset adjustments = 2,0592_G
#define	XL345_OFSZ_VALUE_2_07_G	0x85	//user-set offset adjustments = 2,0748_G
#define	XL345_OFSZ_VALUE_2_09_G	0x86	//user-set offset adjustments = 2,0904_G
#define	XL345_OFSZ_VALUE_2_11_G	0x87	//user-set offset adjustments = 2,106_G
#define	XL345_OFSZ_VALUE_2_12_G	0x88	//user-set offset adjustments = 2,1216_G
#define	XL345_OFSZ_VALUE_2_14_G	0x89	//user-set offset adjustments = 2,1372_G
#define	XL345_OFSZ_VALUE_2_15_G	0x8A	//user-set offset adjustments = 2,1528_G
#define	XL345_OFSZ_VALUE_2_17_G	0x8B	//user-set offset adjustments = 2,1684_G
#define	XL345_OFSZ_VALUE_2_18_G	0x8C	//user-set offset adjustments = 2,184_G
#define	XL345_OFSZ_VALUE_2_20_G	0x8D	//user-set offset adjustments = 2,1996_G
#define	XL345_OFSZ_VALUE_2_22_G	0x8E	//user-set offset adjustments = 2,2152_G
#define	XL345_OFSZ_VALUE_2_23_G	0x8F	//user-set offset adjustments = 2,2308_G
#define	XL345_OFSZ_VALUE_2_25_G	0x90	//user-set offset adjustments = 2,2464_G
#define	XL345_OFSZ_VALUE_2_26_G	0x91	//user-set offset adjustments = 2,262_G
#define	XL345_OFSZ_VALUE_2_28_G	0x92	//user-set offset adjustments = 2,2776_G
#define	XL345_OFSZ_VALUE_2_29_G	0x93	//user-set offset adjustments = 2,2932_G
#define	XL345_OFSZ_VALUE_2_31_G	0x94	//user-set offset adjustments = 2,3088_G
#define	XL345_OFSZ_VALUE_2_32_G	0x95	//user-set offset adjustments = 2,3244_G
#define	XL345_OFSZ_VALUE_2_34_G	0x96	//user-set offset adjustments = 2,34_G
#define	XL345_OFSZ_VALUE_2_36_G	0x97	//user-set offset adjustments = 2,3556_G
#define	XL345_OFSZ_VALUE_2_37_G	0x98	//user-set offset adjustments = 2,3712_G
#define	XL345_OFSZ_VALUE_2_39_G	0x99	//user-set offset adjustments = 2,3868_G
#define	XL345_OFSZ_VALUE_2_40_G	0x9A	//user-set offset adjustments = 2,4024_G
#define	XL345_OFSZ_VALUE_2_42_G	0x9B	//user-set offset adjustments = 2,418_G
#define	XL345_OFSZ_VALUE_2_43_G	0x9C	//user-set offset adjustments = 2,4336_G
#define	XL345_OFSZ_VALUE_2_45_G	0x9D	//user-set offset adjustments = 2,4492_G
#define	XL345_OFSZ_VALUE_2_46_G	0x9E	//user-set offset adjustments = 2,4648_G
#define	XL345_OFSZ_VALUE_2_48_G	0x9F	//user-set offset adjustments = 2,4804_G
#define	XL345_OFSZ_VALUE_2_50_G	0xA0	//user-set offset adjustments = 2,496_G
#define	XL345_OFSZ_VALUE_2_51_G	0xA1	//user-set offset adjustments = 2,5116_G
#define	XL345_OFSZ_VALUE_2_53_G	0xA2	//user-set offset adjustments = 2,5272_G
#define	XL345_OFSZ_VALUE_2_54_G	0xA3	//user-set offset adjustments = 2,5428_G
#define	XL345_OFSZ_VALUE_2_56_G	0xA4	//user-set offset adjustments = 2,5584_G
#define	XL345_OFSZ_VALUE_2_57_G	0xA5	//user-set offset adjustments = 2,574_G
#define	XL345_OFSZ_VALUE_2_59_G	0xA6	//user-set offset adjustments = 2,5896_G
#define	XL345_OFSZ_VALUE_2_61_G	0xA7	//user-set offset adjustments = 2,6052_G
#define	XL345_OFSZ_VALUE_2_62_G	0xA8	//user-set offset adjustments = 2,6208_G
#define	XL345_OFSZ_VALUE_2_64_G	0xA9	//user-set offset adjustments = 2,6364_G
#define	XL345_OFSZ_VALUE_2_65_G	0xAA	//user-set offset adjustments = 2,652_G
#define	XL345_OFSZ_VALUE_2_67_G	0xAB	//user-set offset adjustments = 2,6676_G
#define	XL345_OFSZ_VALUE_2_68_G	0xAC	//user-set offset adjustments = 2,6832_G
#define	XL345_OFSZ_VALUE_2_70_G	0xAD	//user-set offset adjustments = 2,6988_G
#define	XL345_OFSZ_VALUE_2_71_G	0xAE	//user-set offset adjustments = 2,7144_G
#define	XL345_OFSZ_VALUE_2_73_G	0xAF	//user-set offset adjustments = 2,73_G
#define	XL345_OFSZ_VALUE_2_75_G	0xB0	//user-set offset adjustments = 2,7456_G
#define	XL345_OFSZ_VALUE_2_76_G	0xB1	//user-set offset adjustments = 2,7612_G
#define	XL345_OFSZ_VALUE_2_78_G	0xB2	//user-set offset adjustments = 2,7768_G
#define	XL345_OFSZ_VALUE_2_79_G	0xB3	//user-set offset adjustments = 2,7924_G
#define	XL345_OFSZ_VALUE_2_81_G	0xB4	//user-set offset adjustments = 2,808_G
#define	XL345_OFSZ_VALUE_2_82_G	0xB5	//user-set offset adjustments = 2,8236_G
#define	XL345_OFSZ_VALUE_2_84_G	0xB6	//user-set offset adjustments = 2,8392_G
#define	XL345_OFSZ_VALUE_2_85_G	0xB7	//user-set offset adjustments = 2,8548_G
#define	XL345_OFSZ_VALUE_2_87_G	0xB8	//user-set offset adjustments = 2,8704_G
#define	XL345_OFSZ_VALUE_2_89_G	0xB9	//user-set offset adjustments = 2,886_G
#define	XL345_OFSZ_VALUE_2_90_G	0xBA	//user-set offset adjustments = 2,9016_G
#define	XL345_OFSZ_VALUE_2_92_G	0xBB	//user-set offset adjustments = 2,9172_G
#define	XL345_OFSZ_VALUE_2_93_G	0xBC	//user-set offset adjustments = 2,9328_G
#define	XL345_OFSZ_VALUE_2_95_G	0xBD	//user-set offset adjustments = 2,9484_G
#define	XL345_OFSZ_VALUE_2_96_G	0xBE	//user-set offset adjustments = 2,964_G
#define	XL345_OFSZ_VALUE_2_98_G	0xBF	//user-set offset adjustments = 2,9796_G
#define	XL345_OFSZ_VALUE_3_00_G	0xC0	//user-set offset adjustments = 2,9952_G
#define	XL345_OFSZ_VALUE_3_01_G	0xC1	//user-set offset adjustments = 3,0108_G
#define	XL345_OFSZ_VALUE_3_03_G	0xC2	//user-set offset adjustments = 3,0264_G
#define	XL345_OFSZ_VALUE_3_04_G	0xC3	//user-set offset adjustments = 3,042_G
#define	XL345_OFSZ_VALUE_3_06_G	0xC4	//user-set offset adjustments = 3,0576_G
#define	XL345_OFSZ_VALUE_3_07_G	0xC5	//user-set offset adjustments = 3,0732_G
#define	XL345_OFSZ_VALUE_3_09_G	0xC6	//user-set offset adjustments = 3,0888_G
#define	XL345_OFSZ_VALUE_3_10_G	0xC7	//user-set offset adjustments = 3,1044_G
#define	XL345_OFSZ_VALUE_3_12_G	0xC8	//user-set offset adjustments = 3,12_G
#define	XL345_OFSZ_VALUE_3_14_G	0xC9	//user-set offset adjustments = 3,1356_G
#define	XL345_OFSZ_VALUE_3_15_G	0xCA	//user-set offset adjustments = 3,1512_G
#define	XL345_OFSZ_VALUE_3_17_G	0xCB	//user-set offset adjustments = 3,1668_G
#define	XL345_OFSZ_VALUE_3_18_G	0xCC	//user-set offset adjustments = 3,1824_G
#define	XL345_OFSZ_VALUE_3_20_G	0xCD	//user-set offset adjustments = 3,198_G
#define	XL345_OFSZ_VALUE_3_21_G	0xCE	//user-set offset adjustments = 3,2136_G
#define	XL345_OFSZ_VALUE_3_23_G	0xCF	//user-set offset adjustments = 3,2292_G
#define	XL345_OFSZ_VALUE_3_24_G	0xD0	//user-set offset adjustments = 3,2448_G
#define	XL345_OFSZ_VALUE_3_26_G	0xD1	//user-set offset adjustments = 3,2604_G
#define	XL345_OFSZ_VALUE_3_28_G	0xD2	//user-set offset adjustments = 3,276_G
#define	XL345_OFSZ_VALUE_3_29_G	0xD3	//user-set offset adjustments = 3,2916_G
#define	XL345_OFSZ_VALUE_3_31_G	0xD4	//user-set offset adjustments = 3,3072_G
#define	XL345_OFSZ_VALUE_3_32_G	0xD5	//user-set offset adjustments = 3,3228_G
#define	XL345_OFSZ_VALUE_3_34_G	0xD6	//user-set offset adjustments = 3,3384_G
#define	XL345_OFSZ_VALUE_3_35_G	0xD7	//user-set offset adjustments = 3,354_G
#define	XL345_OFSZ_VALUE_3_37_G	0xD8	//user-set offset adjustments = 3,3696_G
#define	XL345_OFSZ_VALUE_3_39_G	0xD9	//user-set offset adjustments = 3,3852_G
#define	XL345_OFSZ_VALUE_3_40_G	0xDA	//user-set offset adjustments = 3,4008_G
#define	XL345_OFSZ_VALUE_3_42_G	0xDB	//user-set offset adjustments = 3,4164_G
#define	XL345_OFSZ_VALUE_3_43_G	0xDC	//user-set offset adjustments = 3,432_G
#define	XL345_OFSZ_VALUE_3_45_G	0xDD	//user-set offset adjustments = 3,4476_G
#define	XL345_OFSZ_VALUE_3_46_G	0xDE	//user-set offset adjustments = 3,4632_G
#define	XL345_OFSZ_VALUE_3_48_G	0xDF	//user-set offset adjustments = 3,4788_G
#define	XL345_OFSZ_VALUE_3_49_G	0xE0	//user-set offset adjustments = 3,4944_G
#define	XL345_OFSZ_VALUE_3_51_G	0xE1	//user-set offset adjustments = 3,51_G
#define	XL345_OFSZ_VALUE_3_53_G	0xE2	//user-set offset adjustments = 3,5256_G
#define	XL345_OFSZ_VALUE_3_54_G	0xE3	//user-set offset adjustments = 3,5412_G
#define	XL345_OFSZ_VALUE_3_56_G	0xE4	//user-set offset adjustments = 3,5568_G
#define	XL345_OFSZ_VALUE_3_57_G	0xE5	//user-set offset adjustments = 3,5724_G
#define	XL345_OFSZ_VALUE_3_59_G	0xE6	//user-set offset adjustments = 3,588_G
#define	XL345_OFSZ_VALUE_3_60_G	0xE7	//user-set offset adjustments = 3,6036_G
#define	XL345_OFSZ_VALUE_3_62_G	0xE8	//user-set offset adjustments = 3,6192_G
#define	XL345_OFSZ_VALUE_3_63_G	0xE9	//user-set offset adjustments = 3,6348_G
#define	XL345_OFSZ_VALUE_3_65_G	0xEA	//user-set offset adjustments = 3,6504_G
#define	XL345_OFSZ_VALUE_3_67_G	0xEB	//user-set offset adjustments = 3,666_G
#define	XL345_OFSZ_VALUE_3_68_G	0xEC	//user-set offset adjustments = 3,6816_G
#define	XL345_OFSZ_VALUE_3_70_G	0xED	//user-set offset adjustments = 3,6972_G
#define	XL345_OFSZ_VALUE_3_71_G	0xEE	//user-set offset adjustments = 3,7128_G
#define	XL345_OFSZ_VALUE_3_73_G	0xEF	//user-set offset adjustments = 3,7284_G
#define	XL345_OFSZ_VALUE_3_74_G	0xF0	//user-set offset adjustments = 3,744_G
#define	XL345_OFSZ_VALUE_3_76_G	0xF1	//user-set offset adjustments = 3,7596_G
#define	XL345_OFSZ_VALUE_3_78_G	0xF2	//user-set offset adjustments = 3,7752_G
#define	XL345_OFSZ_VALUE_3_79_G	0xF3	//user-set offset adjustments = 3,7908_G
#define	XL345_OFSZ_VALUE_3_81_G	0xF4	//user-set offset adjustments = 3,8064_G
#define	XL345_OFSZ_VALUE_3_82_G	0xF5	//user-set offset adjustments = 3,822_G
#define	XL345_OFSZ_VALUE_3_84_G	0xF6	//user-set offset adjustments = 3,8376_G
#define	XL345_OFSZ_VALUE_3_85_G	0xF7	//user-set offset adjustments = 3,8532_G
#define	XL345_OFSZ_VALUE_3_87_G	0xF8	//user-set offset adjustments = 3,8688_G
#define	XL345_OFSZ_VALUE_3_88_G	0xF9	//user-set offset adjustments = 3,8844_G
#define	XL345_OFSZ_VALUE_3_90_G	0xFA	//user-set offset adjustments = 3,9_G
#define	XL345_OFSZ_VALUE_3_92_G	0xFB	//user-set offset adjustments = 3,9156_G
#define	XL345_OFSZ_VALUE_3_93_G	0xFC	//user-set offset adjustments = 3,9312_G
#define	XL345_OFSZ_VALUE_3_95_G	0xFD	//user-set offset adjustments = 3,9468_G
#define	XL345_OFSZ_VALUE_3_96_G	0xFE	//user-set offset adjustments = 3,9624_G
#define	XL345_OFSZ_VALUE_3_98_G	0xFF	//user-set offset adjustments = 3,978_G


/*
The DUR register is eight bits and contains an unsigned time
value representing the maximum time that an event must be
above the THRESH_TAP threshold to qualify as a tap event. The
scale factor is 625 Î¼s/LSB. A value of 0 disables the single tap/
double tap functions.
 */

#define	XL345_DUR_TAP_EVENT_DISABLE	0x00	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 0_MS
#define	XL345_DUR_TAP_EVENT_0_63_MS	0x01	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 0,625_MS
#define	XL345_DUR_TAP_EVENT_1_25_MS	0x02	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 1,25_MS
#define	XL345_DUR_TAP_EVENT_1_88_MS	0x03	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 1,875_MS
#define	XL345_DUR_TAP_EVENT_2_50_MS	0x04	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 2,5_MS
#define	XL345_DUR_TAP_EVENT_3_13_MS	0x05	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 3,125_MS
#define	XL345_DUR_TAP_EVENT_3_75_MS	0x06	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 3,75_MS
#define	XL345_DUR_TAP_EVENT_4_38_MS	0x07	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 4,375_MS
#define	XL345_DUR_TAP_EVENT_5_00_MS	0x08	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 5_MS
#define	XL345_DUR_TAP_EVENT_5_63_MS	0x09	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 5,625_MS
#define	XL345_DUR_TAP_EVENT_6_25_MS	0x0A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 6,25_MS
#define	XL345_DUR_TAP_EVENT_6_88_MS	0x0B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 6,875_MS
#define	XL345_DUR_TAP_EVENT_7_50_MS	0x0C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 7,5_MS
#define	XL345_DUR_TAP_EVENT_8_13_MS	0x0D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 8,125_MS
#define	XL345_DUR_TAP_EVENT_8_75_MS	0x0E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 8,75_MS
#define	XL345_DUR_TAP_EVENT_9_38_MS	0x0F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 9,375_MS
#define	XL345_DUR_TAP_EVENT_10_00_MS	0x10	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 10_MS
#define	XL345_DUR_TAP_EVENT_10_63_MS	0x11	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 10,625_MS
#define	XL345_DUR_TAP_EVENT_11_25_MS	0x12	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 11,25_MS
#define	XL345_DUR_TAP_EVENT_11_88_MS	0x13	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 11,875_MS
#define	XL345_DUR_TAP_EVENT_12_50_MS	0x14	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 12,5_MS
#define	XL345_DUR_TAP_EVENT_13_13_MS	0x15	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 13,125_MS
#define	XL345_DUR_TAP_EVENT_13_75_MS	0x16	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 13,75_MS
#define	XL345_DUR_TAP_EVENT_14_38_MS	0x17	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 14,375_MS
#define	XL345_DUR_TAP_EVENT_15_00_MS	0x18	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 15_MS
#define	XL345_DUR_TAP_EVENT_15_63_MS	0x19	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 15,625_MS
#define	XL345_DUR_TAP_EVENT_16_25_MS	0x1A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 16,25_MS
#define	XL345_DUR_TAP_EVENT_16_88_MS	0x1B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 16,875_MS
#define	XL345_DUR_TAP_EVENT_17_50_MS	0x1C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 17,5_MS
#define	XL345_DUR_TAP_EVENT_18_13_MS	0x1D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 18,125_MS
#define	XL345_DUR_TAP_EVENT_18_75_MS	0x1E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 18,75_MS
#define	XL345_DUR_TAP_EVENT_19_38_MS	0x1F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 19,375_MS
#define	XL345_DUR_TAP_EVENT_20_00_MS	0x20	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 20_MS
#define	XL345_DUR_TAP_EVENT_20_63_MS	0x21	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 20,625_MS
#define	XL345_DUR_TAP_EVENT_21_25_MS	0x22	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 21,25_MS
#define	XL345_DUR_TAP_EVENT_21_88_MS	0x23	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 21,875_MS
#define	XL345_DUR_TAP_EVENT_22_50_MS	0x24	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 22,5_MS
#define	XL345_DUR_TAP_EVENT_23_13_MS	0x25	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 23,125_MS
#define	XL345_DUR_TAP_EVENT_23_75_MS	0x26	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 23,75_MS
#define	XL345_DUR_TAP_EVENT_24_38_MS	0x27	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 24,375_MS
#define	XL345_DUR_TAP_EVENT_25_00_MS	0x28	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 25_MS
#define	XL345_DUR_TAP_EVENT_25_63_MS	0x29	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 25,625_MS
#define	XL345_DUR_TAP_EVENT_26_25_MS	0x2A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 26,25_MS
#define	XL345_DUR_TAP_EVENT_26_88_MS	0x2B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 26,875_MS
#define	XL345_DUR_TAP_EVENT_27_50_MS	0x2C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 27,5_MS
#define	XL345_DUR_TAP_EVENT_28_13_MS	0x2D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 28,125_MS
#define	XL345_DUR_TAP_EVENT_28_75_MS	0x2E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 28,75_MS
#define	XL345_DUR_TAP_EVENT_29_38_MS	0x2F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 29,375_MS
#define	XL345_DUR_TAP_EVENT_30_00_MS	0x30	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 30_MS
#define	XL345_DUR_TAP_EVENT_30_63_MS	0x31	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 30,625_MS
#define	XL345_DUR_TAP_EVENT_31_25_MS	0x32	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 31,25_MS
#define	XL345_DUR_TAP_EVENT_31_88_MS	0x33	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 31,875_MS
#define	XL345_DUR_TAP_EVENT_32_50_MS	0x34	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 32,5_MS
#define	XL345_DUR_TAP_EVENT_33_13_MS	0x35	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 33,125_MS
#define	XL345_DUR_TAP_EVENT_33_75_MS	0x36	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 33,75_MS
#define	XL345_DUR_TAP_EVENT_34_38_MS	0x37	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 34,375_MS
#define	XL345_DUR_TAP_EVENT_35_00_MS	0x38	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 35_MS
#define	XL345_DUR_TAP_EVENT_35_63_MS	0x39	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 35,625_MS
#define	XL345_DUR_TAP_EVENT_36_25_MS	0x3A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 36,25_MS
#define	XL345_DUR_TAP_EVENT_36_88_MS	0x3B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 36,875_MS
#define	XL345_DUR_TAP_EVENT_37_50_MS	0x3C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 37,5_MS
#define	XL345_DUR_TAP_EVENT_38_13_MS	0x3D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 38,125_MS
#define	XL345_DUR_TAP_EVENT_38_75_MS	0x3E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 38,75_MS
#define	XL345_DUR_TAP_EVENT_39_38_MS	0x3F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 39,375_MS
#define	XL345_DUR_TAP_EVENT_40_00_MS	0x40	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 40_MS
#define	XL345_DUR_TAP_EVENT_40_63_MS	0x41	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 40,625_MS
#define	XL345_DUR_TAP_EVENT_41_25_MS	0x42	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 41,25_MS
#define	XL345_DUR_TAP_EVENT_41_88_MS	0x43	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 41,875_MS
#define	XL345_DUR_TAP_EVENT_42_50_MS	0x44	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 42,5_MS
#define	XL345_DUR_TAP_EVENT_43_13_MS	0x45	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 43,125_MS
#define	XL345_DUR_TAP_EVENT_43_75_MS	0x46	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 43,75_MS
#define	XL345_DUR_TAP_EVENT_44_38_MS	0x47	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 44,375_MS
#define	XL345_DUR_TAP_EVENT_45_00_MS	0x48	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 45_MS
#define	XL345_DUR_TAP_EVENT_45_63_MS	0x49	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 45,625_MS
#define	XL345_DUR_TAP_EVENT_46_25_MS	0x4A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 46,25_MS
#define	XL345_DUR_TAP_EVENT_46_88_MS	0x4B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 46,875_MS
#define	XL345_DUR_TAP_EVENT_47_50_MS	0x4C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 47,5_MS
#define	XL345_DUR_TAP_EVENT_48_13_MS	0x4D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 48,125_MS
#define	XL345_DUR_TAP_EVENT_48_75_MS	0x4E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 48,75_MS
#define	XL345_DUR_TAP_EVENT_49_38_MS	0x4F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 49,375_MS
#define	XL345_DUR_TAP_EVENT_50_00_MS	0x50	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 50_MS
#define	XL345_DUR_TAP_EVENT_50_63_MS	0x51	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 50,625_MS
#define	XL345_DUR_TAP_EVENT_51_25_MS	0x52	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 51,25_MS
#define	XL345_DUR_TAP_EVENT_51_88_MS	0x53	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 51,875_MS
#define	XL345_DUR_TAP_EVENT_52_50_MS	0x54	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 52,5_MS
#define	XL345_DUR_TAP_EVENT_53_13_MS	0x55	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 53,125_MS
#define	XL345_DUR_TAP_EVENT_53_75_MS	0x56	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 53,75_MS
#define	XL345_DUR_TAP_EVENT_54_38_MS	0x57	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 54,375_MS
#define	XL345_DUR_TAP_EVENT_55_00_MS	0x58	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 55_MS
#define	XL345_DUR_TAP_EVENT_55_63_MS	0x59	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 55,625_MS
#define	XL345_DUR_TAP_EVENT_56_25_MS	0x5A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 56,25_MS
#define	XL345_DUR_TAP_EVENT_56_88_MS	0x5B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 56,875_MS
#define	XL345_DUR_TAP_EVENT_57_50_MS	0x5C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 57,5_MS
#define	XL345_DUR_TAP_EVENT_58_13_MS	0x5D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 58,125_MS
#define	XL345_DUR_TAP_EVENT_58_75_MS	0x5E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 58,75_MS
#define	XL345_DUR_TAP_EVENT_59_38_MS	0x5F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 59,375_MS
#define	XL345_DUR_TAP_EVENT_60_00_MS	0x60	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 60_MS
#define	XL345_DUR_TAP_EVENT_60_63_MS	0x61	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 60,625_MS
#define	XL345_DUR_TAP_EVENT_61_25_MS	0x62	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 61,25_MS
#define	XL345_DUR_TAP_EVENT_61_88_MS	0x63	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 61,875_MS
#define	XL345_DUR_TAP_EVENT_62_50_MS	0x64	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 62,5_MS
#define	XL345_DUR_TAP_EVENT_63_13_MS	0x65	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 63,125_MS
#define	XL345_DUR_TAP_EVENT_63_75_MS	0x66	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 63,75_MS
#define	XL345_DUR_TAP_EVENT_64_38_MS	0x67	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 64,375_MS
#define	XL345_DUR_TAP_EVENT_65_00_MS	0x68	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 65_MS
#define	XL345_DUR_TAP_EVENT_65_63_MS	0x69	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 65,625_MS
#define	XL345_DUR_TAP_EVENT_66_25_MS	0x6A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 66,25_MS
#define	XL345_DUR_TAP_EVENT_66_88_MS	0x6B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 66,875_MS
#define	XL345_DUR_TAP_EVENT_67_50_MS	0x6C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 67,5_MS
#define	XL345_DUR_TAP_EVENT_68_13_MS	0x6D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 68,125_MS
#define	XL345_DUR_TAP_EVENT_68_75_MS	0x6E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 68,75_MS
#define	XL345_DUR_TAP_EVENT_69_38_MS	0x6F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 69,375_MS
#define	XL345_DUR_TAP_EVENT_70_00_MS	0x70	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 70_MS
#define	XL345_DUR_TAP_EVENT_70_63_MS	0x71	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 70,625_MS
#define	XL345_DUR_TAP_EVENT_71_25_MS	0x72	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 71,25_MS
#define	XL345_DUR_TAP_EVENT_71_88_MS	0x73	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 71,875_MS
#define	XL345_DUR_TAP_EVENT_72_50_MS	0x74	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 72,5_MS
#define	XL345_DUR_TAP_EVENT_73_13_MS	0x75	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 73,125_MS
#define	XL345_DUR_TAP_EVENT_73_75_MS	0x76	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 73,75_MS
#define	XL345_DUR_TAP_EVENT_74_38_MS	0x77	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 74,375_MS
#define	XL345_DUR_TAP_EVENT_75_00_MS	0x78	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 75_MS
#define	XL345_DUR_TAP_EVENT_75_63_MS	0x79	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 75,625_MS
#define	XL345_DUR_TAP_EVENT_76_25_MS	0x7A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 76,25_MS
#define	XL345_DUR_TAP_EVENT_76_88_MS	0x7B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 76,875_MS
#define	XL345_DUR_TAP_EVENT_77_50_MS	0x7C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 77,5_MS
#define	XL345_DUR_TAP_EVENT_78_13_MS	0x7D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 78,125_MS
#define	XL345_DUR_TAP_EVENT_78_75_MS	0x7E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 78,75_MS
#define	XL345_DUR_TAP_EVENT_79_38_MS	0x7F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 79,375_MS
#define	XL345_DUR_TAP_EVENT_80_00_MS	0x80	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 80_MS
#define	XL345_DUR_TAP_EVENT_80_63_MS	0x81	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 80,625_MS
#define	XL345_DUR_TAP_EVENT_81_25_MS	0x82	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 81,25_MS
#define	XL345_DUR_TAP_EVENT_81_88_MS	0x83	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 81,875_MS
#define	XL345_DUR_TAP_EVENT_82_50_MS	0x84	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 82,5_MS
#define	XL345_DUR_TAP_EVENT_83_13_MS	0x85	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 83,125_MS
#define	XL345_DUR_TAP_EVENT_83_75_MS	0x86	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 83,75_MS
#define	XL345_DUR_TAP_EVENT_84_38_MS	0x87	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 84,375_MS
#define	XL345_DUR_TAP_EVENT_85_00_MS	0x88	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 85_MS
#define	XL345_DUR_TAP_EVENT_85_63_MS	0x89	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 85,625_MS
#define	XL345_DUR_TAP_EVENT_86_25_MS	0x8A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 86,25_MS
#define	XL345_DUR_TAP_EVENT_86_88_MS	0x8B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 86,875_MS
#define	XL345_DUR_TAP_EVENT_87_50_MS	0x8C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 87,5_MS
#define	XL345_DUR_TAP_EVENT_88_13_MS	0x8D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 88,125_MS
#define	XL345_DUR_TAP_EVENT_88_75_MS	0x8E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 88,75_MS
#define	XL345_DUR_TAP_EVENT_89_38_MS	0x8F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 89,375_MS
#define	XL345_DUR_TAP_EVENT_90_00_MS	0x90	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 90_MS
#define	XL345_DUR_TAP_EVENT_90_63_MS	0x91	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 90,625_MS
#define	XL345_DUR_TAP_EVENT_91_25_MS	0x92	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 91,25_MS
#define	XL345_DUR_TAP_EVENT_91_88_MS	0x93	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 91,875_MS
#define	XL345_DUR_TAP_EVENT_92_50_MS	0x94	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 92,5_MS
#define	XL345_DUR_TAP_EVENT_93_13_MS	0x95	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 93,125_MS
#define	XL345_DUR_TAP_EVENT_93_75_MS	0x96	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 93,75_MS
#define	XL345_DUR_TAP_EVENT_94_38_MS	0x97	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 94,375_MS
#define	XL345_DUR_TAP_EVENT_95_00_MS	0x98	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 95_MS
#define	XL345_DUR_TAP_EVENT_95_63_MS	0x99	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 95,625_MS
#define	XL345_DUR_TAP_EVENT_96_25_MS	0x9A	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 96,25_MS
#define	XL345_DUR_TAP_EVENT_96_88_MS	0x9B	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 96,875_MS
#define	XL345_DUR_TAP_EVENT_97_50_MS	0x9C	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 97,5_MS
#define	XL345_DUR_TAP_EVENT_98_13_MS	0x9D	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 98,125_MS
#define	XL345_DUR_TAP_EVENT_98_75_MS	0x9E	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 98,75_MS
#define	XL345_DUR_TAP_EVENT_99_38_MS	0x9F	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 99,375_MS
#define	XL345_DUR_TAP_EVENT_100_00_MS	0xA0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 100_MS
#define	XL345_DUR_TAP_EVENT_100_63_MS	0xA1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 100,625_MS
#define	XL345_DUR_TAP_EVENT_101_25_MS	0xA2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 101,25_MS
#define	XL345_DUR_TAP_EVENT_101_88_MS	0xA3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 101,875_MS
#define	XL345_DUR_TAP_EVENT_102_50_MS	0xA4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 102,5_MS
#define	XL345_DUR_TAP_EVENT_103_13_MS	0xA5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 103,125_MS
#define	XL345_DUR_TAP_EVENT_103_75_MS	0xA6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 103,75_MS
#define	XL345_DUR_TAP_EVENT_104_38_MS	0xA7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 104,375_MS
#define	XL345_DUR_TAP_EVENT_105_00_MS	0xA8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 105_MS
#define	XL345_DUR_TAP_EVENT_105_63_MS	0xA9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 105,625_MS
#define	XL345_DUR_TAP_EVENT_106_25_MS	0xAA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 106,25_MS
#define	XL345_DUR_TAP_EVENT_106_88_MS	0xAB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 106,875_MS
#define	XL345_DUR_TAP_EVENT_107_50_MS	0xAC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 107,5_MS
#define	XL345_DUR_TAP_EVENT_108_13_MS	0xAD	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 108,125_MS
#define	XL345_DUR_TAP_EVENT_108_75_MS	0xAE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 108,75_MS
#define	XL345_DUR_TAP_EVENT_109_38_MS	0xAF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 109,375_MS
#define	XL345_DUR_TAP_EVENT_110_00_MS	0xB0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 110_MS
#define	XL345_DUR_TAP_EVENT_110_63_MS	0xB1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 110,625_MS
#define	XL345_DUR_TAP_EVENT_111_25_MS	0xB2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 111,25_MS
#define	XL345_DUR_TAP_EVENT_111_88_MS	0xB3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 111,875_MS
#define	XL345_DUR_TAP_EVENT_112_50_MS	0xB4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 112,5_MS
#define	XL345_DUR_TAP_EVENT_113_13_MS	0xB5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 113,125_MS
#define	XL345_DUR_TAP_EVENT_113_75_MS	0xB6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 113,75_MS
#define	XL345_DUR_TAP_EVENT_114_38_MS	0xB7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 114,375_MS
#define	XL345_DUR_TAP_EVENT_115_00_MS	0xB8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 115_MS
#define	XL345_DUR_TAP_EVENT_115_63_MS	0xB9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 115,625_MS
#define	XL345_DUR_TAP_EVENT_116_25_MS	0xBA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 116,25_MS
#define	XL345_DUR_TAP_EVENT_116_88_MS	0xBB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 116,875_MS
#define	XL345_DUR_TAP_EVENT_117_50_MS	0xBC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 117,5_MS
#define	XL345_DUR_TAP_EVENT_118_13_MS	0xBD	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 118,125_MS
#define	XL345_DUR_TAP_EVENT_118_75_MS	0xBE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 118,75_MS
#define	XL345_DUR_TAP_EVENT_119_38_MS	0xBF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 119,375_MS
#define	XL345_DUR_TAP_EVENT_120_00_MS	0xC0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 120_MS
#define	XL345_DUR_TAP_EVENT_120_63_MS	0xC1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 120,625_MS
#define	XL345_DUR_TAP_EVENT_121_25_MS	0xC2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 121,25_MS
#define	XL345_DUR_TAP_EVENT_121_88_MS	0xC3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 121,875_MS
#define	XL345_DUR_TAP_EVENT_122_50_MS	0xC4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 122,5_MS
#define	XL345_DUR_TAP_EVENT_123_13_MS	0xC5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 123,125_MS
#define	XL345_DUR_TAP_EVENT_123_75_MS	0xC6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 123,75_MS
#define	XL345_DUR_TAP_EVENT_124_38_MS	0xC7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 124,375_MS
#define	XL345_DUR_TAP_EVENT_125_00_MS	0xC8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 125_MS
#define	XL345_DUR_TAP_EVENT_125_63_MS	0xC9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 125,625_MS
#define	XL345_DUR_TAP_EVENT_126_25_MS	0xCA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 126,25_MS
#define	XL345_DUR_TAP_EVENT_126_88_MS	0xCB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 126,875_MS
#define	XL345_DUR_TAP_EVENT_127_50_MS	0xCC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 127,5_MS
#define	XL345_DUR_TAP_EVENT_128_13_MS	0xCD	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 128,125_MS
#define	XL345_DUR_TAP_EVENT_128_75_MS	0xCE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 128,75_MS
#define	XL345_DUR_TAP_EVENT_129_38_MS	0xCF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 129,375_MS
#define	XL345_DUR_TAP_EVENT_130_00_MS	0xD0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 130_MS
#define	XL345_DUR_TAP_EVENT_130_63_MS	0xD1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 130,625_MS
#define	XL345_DUR_TAP_EVENT_131_25_MS	0xD2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 131,25_MS
#define	XL345_DUR_TAP_EVENT_131_88_MS	0xD3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 131,875_MS
#define	XL345_DUR_TAP_EVENT_132_50_MS	0xD4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 132,5_MS
#define	XL345_DUR_TAP_EVENT_133_13_MS	0xD5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 133,125_MS
#define	XL345_DUR_TAP_EVENT_133_75_MS	0xD6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 133,75_MS
#define	XL345_DUR_TAP_EVENT_134_38_MS	0xD7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 134,375_MS
#define	XL345_DUR_TAP_EVENT_135_00_MS	0xD8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 135_MS
#define	XL345_DUR_TAP_EVENT_135_63_MS	0xD9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 135,625_MS
#define	XL345_DUR_TAP_EVENT_136_25_MS	0xDA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 136,25_MS
#define	XL345_DUR_TAP_EVENT_136_88_MS	0xDB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 136,875_MS
#define	XL345_DUR_TAP_EVENT_137_50_MS	0xDC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 137,5_MS
#define	XL345_DUR_TAP_EVENT_138_13_MS	0xDD	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 138,125_MS
#define	XL345_DUR_TAP_EVENT_138_75_MS	0xDE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 138,75_MS
#define	XL345_DUR_TAP_EVENT_139_38_MS	0xDF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 139,375_MS
#define	XL345_DUR_TAP_EVENT_140_00_MS	0xE0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 140_MS
#define	XL345_DUR_TAP_EVENT_140_63_MS	0xE1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 140,625_MS
#define	XL345_DUR_TAP_EVENT_141_25_MS	0xE2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 141,25_MS
#define	XL345_DUR_TAP_EVENT_141_88_MS	0xE3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 141,875_MS
#define	XL345_DUR_TAP_EVENT_142_50_MS	0xE4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 142,5_MS
#define	XL345_DUR_TAP_EVENT_143_13_MS	0xE5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 143,125_MS
#define	XL345_DUR_TAP_EVENT_143_75_MS	0xE6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 143,75_MS
#define	XL345_DUR_TAP_EVENT_144_38_MS	0xE7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 144,375_MS
#define	XL345_DUR_TAP_EVENT_145_00_MS	0xE8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 145_MS
#define	XL345_DUR_TAP_EVENT_145_63_MS	0xE9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 145,625_MS
#define	XL345_DUR_TAP_EVENT_146_25_MS	0xEA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 146,25_MS
#define	XL345_DUR_TAP_EVENT_146_88_MS	0xEB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 146,875_MS
#define	XL345_DUR_TAP_EVENT_147_50_MS	0xEC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 147,5_MS
#define	XL345_DUR_TAP_EVENT_148_13_MS	0xED	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 148,125_MS
#define	XL345_DUR_TAP_EVENT_148_75_MS	0xEE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 148,75_MS
#define	XL345_DUR_TAP_EVENT_149_38_MS	0xEF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 149,375_MS
#define	XL345_DUR_TAP_EVENT_150_00_MS	0xF0	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 150_MS
#define	XL345_DUR_TAP_EVENT_150_63_MS	0xF1	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 150,625_MS
#define	XL345_DUR_TAP_EVENT_151_25_MS	0xF2	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 151,25_MS
#define	XL345_DUR_TAP_EVENT_151_88_MS	0xF3	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 151,875_MS
#define	XL345_DUR_TAP_EVENT_152_50_MS	0xF4	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 152,5_MS
#define	XL345_DUR_TAP_EVENT_153_13_MS	0xF5	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 153,125_MS
#define	XL345_DUR_TAP_EVENT_153_75_MS	0xF6	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 153,75_MS
#define	XL345_DUR_TAP_EVENT_154_38_MS	0xF7	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 154,375_MS
#define	XL345_DUR_TAP_EVENT_155_00_MS	0xF8	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 155_MS
#define	XL345_DUR_TAP_EVENT_155_63_MS	0xF9	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 155,625_MS
#define	XL345_DUR_TAP_EVENT_156_25_MS	0xFA	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 156,25_MS
#define	XL345_DUR_TAP_EVENT_156_88_MS	0xFB	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 156,875_MS
#define	XL345_DUR_TAP_EVENT_157_50_MS	0xFC	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 157,5_MS
#define	XL345_DUR_TAP_EVENT_158_13_MS	0xFD	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 158,125_MS
#define	XL345_DUR_TAP_EVENT_158_75_MS	0xFE	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 158,75_MS
#define	XL345_DUR_TAP_EVENT_159_38_MS	0xFF	//max time that an event must be above the THRESH_TAP threshold to qualify as a tap event = 159,375_MS

/*
The latent register is eight bits and contains an unsigned time
value representing the wait time from the detection of a tap
event to the start of the time window (defined by the window
register) during which a possible second tap event can be detected.
The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap
function.
*/

#define	XL345_LATENT_DISABLE_DOUBLE_TAP 	0x00	//wait time from the detection of a tap event to the start of the time window = 0_MS
#define	XL345_LATENT_TIME_WAIT_1_25_MS  	0x01	//wait time from the detection of a tap event to the start of the time window = 1,25_MS
#define	XL345_LATENT_TIME_WAIT_2_50_MS  	0x02	//wait time from the detection of a tap event to the start of the time window = 2,5_MS
#define	XL345_LATENT_TIME_WAIT_3_75_MS  	0x03	//wait time from the detection of a tap event to the start of the time window = 3,75_MS
#define	XL345_LATENT_TIME_WAIT_5_00_MS  	0x04	//wait time from the detection of a tap event to the start of the time window = 5_MS
#define	XL345_LATENT_TIME_WAIT_6_25_MS  	0x05	//wait time from the detection of a tap event to the start of the time window = 6,25_MS
#define	XL345_LATENT_TIME_WAIT_7_50_MS  	0x06	//wait time from the detection of a tap event to the start of the time window = 7,5_MS
#define	XL345_LATENT_TIME_WAIT_8_75_MS  	0x07	//wait time from the detection of a tap event to the start of the time window = 8,75_MS
#define	XL345_LATENT_TIME_WAIT_10_00_MS 	0x08	//wait time from the detection of a tap event to the start of the time window = 10_MS
#define	XL345_LATENT_TIME_WAIT_11_25_MS 	0x09	//wait time from the detection of a tap event to the start of the time window = 11,25_MS
#define	XL345_LATENT_TIME_WAIT_12_50_MS 	0x0A	//wait time from the detection of a tap event to the start of the time window = 12,5_MS
#define	XL345_LATENT_TIME_WAIT_13_75_MS 	0x0B	//wait time from the detection of a tap event to the start of the time window = 13,75_MS
#define	XL345_LATENT_TIME_WAIT_15_00_MS 	0x0C	//wait time from the detection of a tap event to the start of the time window = 15_MS
#define	XL345_LATENT_TIME_WAIT_16_25_MS 	0x0D	//wait time from the detection of a tap event to the start of the time window = 16,25_MS
#define	XL345_LATENT_TIME_WAIT_17_50_MS 	0x0E	//wait time from the detection of a tap event to the start of the time window = 17,5_MS
#define	XL345_LATENT_TIME_WAIT_18_75_MS 	0x0F	//wait time from the detection of a tap event to the start of the time window = 18,75_MS
#define	XL345_LATENT_TIME_WAIT_20_00_MS 	0x10	//wait time from the detection of a tap event to the start of the time window = 20_MS
#define	XL345_LATENT_TIME_WAIT_21_25_MS 	0x11	//wait time from the detection of a tap event to the start of the time window = 21,25_MS
#define	XL345_LATENT_TIME_WAIT_22_50_MS 	0x12	//wait time from the detection of a tap event to the start of the time window = 22,5_MS
#define	XL345_LATENT_TIME_WAIT_23_75_MS 	0x13	//wait time from the detection of a tap event to the start of the time window = 23,75_MS
#define	XL345_LATENT_TIME_WAIT_25_00_MS 	0x14	//wait time from the detection of a tap event to the start of the time window = 25_MS
#define	XL345_LATENT_TIME_WAIT_26_25_MS 	0x15	//wait time from the detection of a tap event to the start of the time window = 26,25_MS
#define	XL345_LATENT_TIME_WAIT_27_50_MS 	0x16	//wait time from the detection of a tap event to the start of the time window = 27,5_MS
#define	XL345_LATENT_TIME_WAIT_28_75_MS 	0x17	//wait time from the detection of a tap event to the start of the time window = 28,75_MS
#define	XL345_LATENT_TIME_WAIT_30_00_MS 	0x18	//wait time from the detection of a tap event to the start of the time window = 30_MS
#define	XL345_LATENT_TIME_WAIT_31_25_MS 	0x19	//wait time from the detection of a tap event to the start of the time window = 31,25_MS
#define	XL345_LATENT_TIME_WAIT_32_50_MS 	0x1A	//wait time from the detection of a tap event to the start of the time window = 32,5_MS
#define	XL345_LATENT_TIME_WAIT_33_75_MS 	0x1B	//wait time from the detection of a tap event to the start of the time window = 33,75_MS
#define	XL345_LATENT_TIME_WAIT_35_00_MS 	0x1C	//wait time from the detection of a tap event to the start of the time window = 35_MS
#define	XL345_LATENT_TIME_WAIT_36_25_MS 	0x1D	//wait time from the detection of a tap event to the start of the time window = 36,25_MS
#define	XL345_LATENT_TIME_WAIT_37_50_MS 	0x1E	//wait time from the detection of a tap event to the start of the time window = 37,5_MS
#define	XL345_LATENT_TIME_WAIT_38_75_MS 	0x1F	//wait time from the detection of a tap event to the start of the time window = 38,75_MS
#define	XL345_LATENT_TIME_WAIT_40_00_MS 	0x20	//wait time from the detection of a tap event to the start of the time window = 40_MS
#define	XL345_LATENT_TIME_WAIT_41_25_MS 	0x21	//wait time from the detection of a tap event to the start of the time window = 41,25_MS
#define	XL345_LATENT_TIME_WAIT_42_50_MS 	0x22	//wait time from the detection of a tap event to the start of the time window = 42,5_MS
#define	XL345_LATENT_TIME_WAIT_43_75_MS 	0x23	//wait time from the detection of a tap event to the start of the time window = 43,75_MS
#define	XL345_LATENT_TIME_WAIT_45_00_MS 	0x24	//wait time from the detection of a tap event to the start of the time window = 45_MS
#define	XL345_LATENT_TIME_WAIT_46_25_MS 	0x25	//wait time from the detection of a tap event to the start of the time window = 46,25_MS
#define	XL345_LATENT_TIME_WAIT_47_50_MS 	0x26	//wait time from the detection of a tap event to the start of the time window = 47,5_MS
#define	XL345_LATENT_TIME_WAIT_48_75_MS 	0x27	//wait time from the detection of a tap event to the start of the time window = 48,75_MS
#define	XL345_LATENT_TIME_WAIT_50_00_MS 	0x28	//wait time from the detection of a tap event to the start of the time window = 50_MS
#define	XL345_LATENT_TIME_WAIT_51_25_MS 	0x29	//wait time from the detection of a tap event to the start of the time window = 51,25_MS
#define	XL345_LATENT_TIME_WAIT_52_50_MS 	0x2A	//wait time from the detection of a tap event to the start of the time window = 52,5_MS
#define	XL345_LATENT_TIME_WAIT_53_75_MS 	0x2B	//wait time from the detection of a tap event to the start of the time window = 53,75_MS
#define	XL345_LATENT_TIME_WAIT_55_00_MS 	0x2C	//wait time from the detection of a tap event to the start of the time window = 55_MS
#define	XL345_LATENT_TIME_WAIT_56_25_MS 	0x2D	//wait time from the detection of a tap event to the start of the time window = 56,25_MS
#define	XL345_LATENT_TIME_WAIT_57_50_MS 	0x2E	//wait time from the detection of a tap event to the start of the time window = 57,5_MS
#define	XL345_LATENT_TIME_WAIT_58_75_MS 	0x2F	//wait time from the detection of a tap event to the start of the time window = 58,75_MS
#define	XL345_LATENT_TIME_WAIT_60_00_MS 	0x30	//wait time from the detection of a tap event to the start of the time window = 60_MS
#define	XL345_LATENT_TIME_WAIT_61_25_MS 	0x31	//wait time from the detection of a tap event to the start of the time window = 61,25_MS
#define	XL345_LATENT_TIME_WAIT_62_50_MS 	0x32	//wait time from the detection of a tap event to the start of the time window = 62,5_MS
#define	XL345_LATENT_TIME_WAIT_63_75_MS 	0x33	//wait time from the detection of a tap event to the start of the time window = 63,75_MS
#define	XL345_LATENT_TIME_WAIT_65_00_MS 	0x34	//wait time from the detection of a tap event to the start of the time window = 65_MS
#define	XL345_LATENT_TIME_WAIT_66_25_MS 	0x35	//wait time from the detection of a tap event to the start of the time window = 66,25_MS
#define	XL345_LATENT_TIME_WAIT_67_50_MS 	0x36	//wait time from the detection of a tap event to the start of the time window = 67,5_MS
#define	XL345_LATENT_TIME_WAIT_68_75_MS 	0x37	//wait time from the detection of a tap event to the start of the time window = 68,75_MS
#define	XL345_LATENT_TIME_WAIT_70_00_MS 	0x38	//wait time from the detection of a tap event to the start of the time window = 70_MS
#define	XL345_LATENT_TIME_WAIT_71_25_MS 	0x39	//wait time from the detection of a tap event to the start of the time window = 71,25_MS
#define	XL345_LATENT_TIME_WAIT_72_50_MS 	0x3A	//wait time from the detection of a tap event to the start of the time window = 72,5_MS
#define	XL345_LATENT_TIME_WAIT_73_75_MS 	0x3B	//wait time from the detection of a tap event to the start of the time window = 73,75_MS
#define	XL345_LATENT_TIME_WAIT_75_00_MS 	0x3C	//wait time from the detection of a tap event to the start of the time window = 75_MS
#define	XL345_LATENT_TIME_WAIT_76_25_MS 	0x3D	//wait time from the detection of a tap event to the start of the time window = 76,25_MS
#define	XL345_LATENT_TIME_WAIT_77_50_MS 	0x3E	//wait time from the detection of a tap event to the start of the time window = 77,5_MS
#define	XL345_LATENT_TIME_WAIT_78_75_MS 	0x3F	//wait time from the detection of a tap event to the start of the time window = 78,75_MS
#define	XL345_LATENT_TIME_WAIT_80_00_MS 	0x40	//wait time from the detection of a tap event to the start of the time window = 80_MS
#define	XL345_LATENT_TIME_WAIT_81_25_MS 	0x41	//wait time from the detection of a tap event to the start of the time window = 81,25_MS
#define	XL345_LATENT_TIME_WAIT_82_50_MS 	0x42	//wait time from the detection of a tap event to the start of the time window = 82,5_MS
#define	XL345_LATENT_TIME_WAIT_83_75_MS 	0x43	//wait time from the detection of a tap event to the start of the time window = 83,75_MS
#define	XL345_LATENT_TIME_WAIT_85_00_MS 	0x44	//wait time from the detection of a tap event to the start of the time window = 85_MS
#define	XL345_LATENT_TIME_WAIT_86_25_MS 	0x45	//wait time from the detection of a tap event to the start of the time window = 86,25_MS
#define	XL345_LATENT_TIME_WAIT_87_50_MS 	0x46	//wait time from the detection of a tap event to the start of the time window = 87,5_MS
#define	XL345_LATENT_TIME_WAIT_88_75_MS 	0x47	//wait time from the detection of a tap event to the start of the time window = 88,75_MS
#define	XL345_LATENT_TIME_WAIT_90_00_MS 	0x48	//wait time from the detection of a tap event to the start of the time window = 90_MS
#define	XL345_LATENT_TIME_WAIT_91_25_MS 	0x49	//wait time from the detection of a tap event to the start of the time window = 91,25_MS
#define	XL345_LATENT_TIME_WAIT_92_50_MS 	0x4A	//wait time from the detection of a tap event to the start of the time window = 92,5_MS
#define	XL345_LATENT_TIME_WAIT_93_75_MS         0x4B	//wait time from the detection of a tap event to the start of the time window = 93,75_MS
#define	XL345_LATENT_TIME_WAIT_95_00_MS     	0x4C	//wait time from the detection of a tap event to the start of the time window = 95_MS
#define	XL345_LATENT_TIME_WAIT_96_25_MS         0x4D	//wait time from the detection of a tap event to the start of the time window = 96,25_MS
#define	XL345_LATENT_TIME_WAIT_97_50_MS         0x4E	//wait time from the detection of a tap event to the start of the time window = 97,5_MS
#define	XL345_LATENT_TIME_WAIT_98_75_MS         0x4F	//wait time from the detection of a tap event to the start of the time window = 98,75_MS
#define	XL345_LATENT_TIME_WAIT_100_00_MS	0x50	//wait time from the detection of a tap event to the start of the time window = 100_MS
#define	XL345_LATENT_TIME_WAIT_101_25_MS	0x51	//wait time from the detection of a tap event to the start of the time window = 101,25_MS
#define	XL345_LATENT_TIME_WAIT_102_50_MS	0x52	//wait time from the detection of a tap event to the start of the time window = 102,5_MS
#define	XL345_LATENT_TIME_WAIT_103_75_MS	0x53	//wait time from the detection of a tap event to the start of the time window = 103,75_MS
#define	XL345_LATENT_TIME_WAIT_105_00_MS	0x54	//wait time from the detection of a tap event to the start of the time window = 105_MS
#define	XL345_LATENT_TIME_WAIT_106_25_MS	0x55	//wait time from the detection of a tap event to the start of the time window = 106,25_MS
#define	XL345_LATENT_TIME_WAIT_107_50_MS	0x56	//wait time from the detection of a tap event to the start of the time window = 107,5_MS
#define	XL345_LATENT_TIME_WAIT_108_75_MS	0x57	//wait time from the detection of a tap event to the start of the time window = 108,75_MS
#define	XL345_LATENT_TIME_WAIT_110_00_MS	0x58	//wait time from the detection of a tap event to the start of the time window = 110_MS
#define	XL345_LATENT_TIME_WAIT_111_25_MS	0x59	//wait time from the detection of a tap event to the start of the time window = 111,25_MS
#define	XL345_LATENT_TIME_WAIT_112_50_MS	0x5A	//wait time from the detection of a tap event to the start of the time window = 112,5_MS
#define	XL345_LATENT_TIME_WAIT_113_75_MS	0x5B	//wait time from the detection of a tap event to the start of the time window = 113,75_MS
#define	XL345_LATENT_TIME_WAIT_115_00_MS	0x5C	//wait time from the detection of a tap event to the start of the time window = 115_MS
#define	XL345_LATENT_TIME_WAIT_116_25_MS	0x5D	//wait time from the detection of a tap event to the start of the time window = 116,25_MS
#define	XL345_LATENT_TIME_WAIT_117_50_MS	0x5E	//wait time from the detection of a tap event to the start of the time window = 117,5_MS
#define	XL345_LATENT_TIME_WAIT_118_75_MS	0x5F	//wait time from the detection of a tap event to the start of the time window = 118,75_MS
#define	XL345_LATENT_TIME_WAIT_120_00_MS	0x60	//wait time from the detection of a tap event to the start of the time window = 120_MS
#define	XL345_LATENT_TIME_WAIT_121_25_MS	0x61	//wait time from the detection of a tap event to the start of the time window = 121,25_MS
#define	XL345_LATENT_TIME_WAIT_122_50_MS	0x62	//wait time from the detection of a tap event to the start of the time window = 122,5_MS
#define	XL345_LATENT_TIME_WAIT_123_75_MS	0x63	//wait time from the detection of a tap event to the start of the time window = 123,75_MS
#define	XL345_LATENT_TIME_WAIT_125_00_MS	0x64	//wait time from the detection of a tap event to the start of the time window = 125_MS
#define	XL345_LATENT_TIME_WAIT_126_25_MS	0x65	//wait time from the detection of a tap event to the start of the time window = 126,25_MS
#define	XL345_LATENT_TIME_WAIT_127_50_MS	0x66	//wait time from the detection of a tap event to the start of the time window = 127,5_MS
#define	XL345_LATENT_TIME_WAIT_128_75_MS	0x67	//wait time from the detection of a tap event to the start of the time window = 128,75_MS
#define	XL345_LATENT_TIME_WAIT_130_00_MS	0x68	//wait time from the detection of a tap event to the start of the time window = 130_MS
#define	XL345_LATENT_TIME_WAIT_131_25_MS	0x69	//wait time from the detection of a tap event to the start of the time window = 131,25_MS
#define	XL345_LATENT_TIME_WAIT_132_50_MS	0x6A	//wait time from the detection of a tap event to the start of the time window = 132,5_MS
#define	XL345_LATENT_TIME_WAIT_133_75_MS	0x6B	//wait time from the detection of a tap event to the start of the time window = 133,75_MS
#define	XL345_LATENT_TIME_WAIT_135_00_MS	0x6C	//wait time from the detection of a tap event to the start of the time window = 135_MS
#define	XL345_LATENT_TIME_WAIT_136_25_MS	0x6D	//wait time from the detection of a tap event to the start of the time window = 136,25_MS
#define	XL345_LATENT_TIME_WAIT_137_50_MS	0x6E	//wait time from the detection of a tap event to the start of the time window = 137,5_MS
#define	XL345_LATENT_TIME_WAIT_138_75_MS	0x6F	//wait time from the detection of a tap event to the start of the time window = 138,75_MS
#define	XL345_LATENT_TIME_WAIT_140_00_MS	0x70	//wait time from the detection of a tap event to the start of the time window = 140_MS
#define	XL345_LATENT_TIME_WAIT_141_25_MS	0x71	//wait time from the detection of a tap event to the start of the time window = 141,25_MS
#define	XL345_LATENT_TIME_WAIT_142_50_MS	0x72	//wait time from the detection of a tap event to the start of the time window = 142,5_MS
#define	XL345_LATENT_TIME_WAIT_143_75_MS	0x73	//wait time from the detection of a tap event to the start of the time window = 143,75_MS
#define	XL345_LATENT_TIME_WAIT_145_00_MS	0x74	//wait time from the detection of a tap event to the start of the time window = 145_MS
#define	XL345_LATENT_TIME_WAIT_146_25_MS	0x75	//wait time from the detection of a tap event to the start of the time window = 146,25_MS
#define	XL345_LATENT_TIME_WAIT_147_50_MS	0x76	//wait time from the detection of a tap event to the start of the time window = 147,5_MS
#define	XL345_LATENT_TIME_WAIT_148_75_MS	0x77	//wait time from the detection of a tap event to the start of the time window = 148,75_MS
#define	XL345_LATENT_TIME_WAIT_150_00_MS	0x78	//wait time from the detection of a tap event to the start of the time window = 150_MS
#define	XL345_LATENT_TIME_WAIT_151_25_MS	0x79	//wait time from the detection of a tap event to the start of the time window = 151,25_MS
#define	XL345_LATENT_TIME_WAIT_152_50_MS	0x7A	//wait time from the detection of a tap event to the start of the time window = 152,5_MS
#define	XL345_LATENT_TIME_WAIT_153_75_MS	0x7B	//wait time from the detection of a tap event to the start of the time window = 153,75_MS
#define	XL345_LATENT_TIME_WAIT_155_00_MS	0x7C	//wait time from the detection of a tap event to the start of the time window = 155_MS
#define	XL345_LATENT_TIME_WAIT_156_25_MS	0x7D	//wait time from the detection of a tap event to the start of the time window = 156,25_MS
#define	XL345_LATENT_TIME_WAIT_157_50_MS	0x7E	//wait time from the detection of a tap event to the start of the time window = 157,5_MS
#define	XL345_LATENT_TIME_WAIT_158_75_MS	0x7F	//wait time from the detection of a tap event to the start of the time window = 158,75_MS
#define	XL345_LATENT_TIME_WAIT_160_00_MS	0x80	//wait time from the detection of a tap event to the start of the time window = 160_MS
#define	XL345_LATENT_TIME_WAIT_161_25_MS	0x81	//wait time from the detection of a tap event to the start of the time window = 161,25_MS
#define	XL345_LATENT_TIME_WAIT_162_50_MS	0x82	//wait time from the detection of a tap event to the start of the time window = 162,5_MS
#define	XL345_LATENT_TIME_WAIT_163_75_MS	0x83	//wait time from the detection of a tap event to the start of the time window = 163,75_MS
#define	XL345_LATENT_TIME_WAIT_165_00_MS	0x84	//wait time from the detection of a tap event to the start of the time window = 165_MS
#define	XL345_LATENT_TIME_WAIT_166_25_MS	0x85	//wait time from the detection of a tap event to the start of the time window = 166,25_MS
#define	XL345_LATENT_TIME_WAIT_167_50_MS	0x86	//wait time from the detection of a tap event to the start of the time window = 167,5_MS
#define	XL345_LATENT_TIME_WAIT_168_75_MS	0x87	//wait time from the detection of a tap event to the start of the time window = 168,75_MS
#define	XL345_LATENT_TIME_WAIT_170_00_MS	0x88	//wait time from the detection of a tap event to the start of the time window = 170_MS
#define	XL345_LATENT_TIME_WAIT_171_25_MS	0x89	//wait time from the detection of a tap event to the start of the time window = 171,25_MS
#define	XL345_LATENT_TIME_WAIT_172_50_MS	0x8A	//wait time from the detection of a tap event to the start of the time window = 172,5_MS
#define	XL345_LATENT_TIME_WAIT_173_75_MS	0x8B	//wait time from the detection of a tap event to the start of the time window = 173,75_MS
#define	XL345_LATENT_TIME_WAIT_175_00_MS	0x8C	//wait time from the detection of a tap event to the start of the time window = 175_MS
#define	XL345_LATENT_TIME_WAIT_176_25_MS	0x8D	//wait time from the detection of a tap event to the start of the time window = 176,25_MS
#define	XL345_LATENT_TIME_WAIT_177_50_MS	0x8E	//wait time from the detection of a tap event to the start of the time window = 177,5_MS
#define	XL345_LATENT_TIME_WAIT_178_75_MS	0x8F	//wait time from the detection of a tap event to the start of the time window = 178,75_MS
#define	XL345_LATENT_TIME_WAIT_180_00_MS	0x90	//wait time from the detection of a tap event to the start of the time window = 180_MS
#define	XL345_LATENT_TIME_WAIT_181_25_MS	0x91	//wait time from the detection of a tap event to the start of the time window = 181,25_MS
#define	XL345_LATENT_TIME_WAIT_182_50_MS	0x92	//wait time from the detection of a tap event to the start of the time window = 182,5_MS
#define	XL345_LATENT_TIME_WAIT_183_75_MS	0x93	//wait time from the detection of a tap event to the start of the time window = 183,75_MS
#define	XL345_LATENT_TIME_WAIT_185_00_MS	0x94	//wait time from the detection of a tap event to the start of the time window = 185_MS
#define	XL345_LATENT_TIME_WAIT_186_25_MS	0x95	//wait time from the detection of a tap event to the start of the time window = 186,25_MS
#define	XL345_LATENT_TIME_WAIT_187_50_MS	0x96	//wait time from the detection of a tap event to the start of the time window = 187,5_MS
#define	XL345_LATENT_TIME_WAIT_188_75_MS	0x97	//wait time from the detection of a tap event to the start of the time window = 188,75_MS
#define	XL345_LATENT_TIME_WAIT_190_00_MS	0x98	//wait time from the detection of a tap event to the start of the time window = 190_MS
#define	XL345_LATENT_TIME_WAIT_191_25_MS	0x99	//wait time from the detection of a tap event to the start of the time window = 191,25_MS
#define	XL345_LATENT_TIME_WAIT_192_50_MS	0x9A	//wait time from the detection of a tap event to the start of the time window = 192,5_MS
#define	XL345_LATENT_TIME_WAIT_193_75_MS	0x9B	//wait time from the detection of a tap event to the start of the time window = 193,75_MS
#define	XL345_LATENT_TIME_WAIT_195_00_MS	0x9C	//wait time from the detection of a tap event to the start of the time window = 195_MS
#define	XL345_LATENT_TIME_WAIT_196_25_MS	0x9D	//wait time from the detection of a tap event to the start of the time window = 196,25_MS
#define	XL345_LATENT_TIME_WAIT_197_50_MS	0x9E	//wait time from the detection of a tap event to the start of the time window = 197,5_MS
#define	XL345_LATENT_TIME_WAIT_198_75_MS	0x9F	//wait time from the detection of a tap event to the start of the time window = 198,75_MS
#define	XL345_LATENT_TIME_WAIT_200_00_MS	0xA0	//wait time from the detection of a tap event to the start of the time window = 200_MS
#define	XL345_LATENT_TIME_WAIT_201_25_MS	0xA1	//wait time from the detection of a tap event to the start of the time window = 201,25_MS
#define	XL345_LATENT_TIME_WAIT_202_50_MS	0xA2	//wait time from the detection of a tap event to the start of the time window = 202,5_MS
#define	XL345_LATENT_TIME_WAIT_203_75_MS	0xA3	//wait time from the detection of a tap event to the start of the time window = 203,75_MS
#define	XL345_LATENT_TIME_WAIT_205_00_MS	0xA4	//wait time from the detection of a tap event to the start of the time window = 205_MS
#define	XL345_LATENT_TIME_WAIT_206_25_MS	0xA5	//wait time from the detection of a tap event to the start of the time window = 206,25_MS
#define	XL345_LATENT_TIME_WAIT_207_50_MS	0xA6	//wait time from the detection of a tap event to the start of the time window = 207,5_MS
#define	XL345_LATENT_TIME_WAIT_208_75_MS	0xA7	//wait time from the detection of a tap event to the start of the time window = 208,75_MS
#define	XL345_LATENT_TIME_WAIT_210_00_MS	0xA8	//wait time from the detection of a tap event to the start of the time window = 210_MS
#define	XL345_LATENT_TIME_WAIT_211_25_MS	0xA9	//wait time from the detection of a tap event to the start of the time window = 211,25_MS
#define	XL345_LATENT_TIME_WAIT_212_50_MS	0xAA	//wait time from the detection of a tap event to the start of the time window = 212,5_MS
#define	XL345_LATENT_TIME_WAIT_213_75_MS	0xAB	//wait time from the detection of a tap event to the start of the time window = 213,75_MS
#define	XL345_LATENT_TIME_WAIT_215_00_MS	0xAC	//wait time from the detection of a tap event to the start of the time window = 215_MS
#define	XL345_LATENT_TIME_WAIT_216_25_MS	0xAD	//wait time from the detection of a tap event to the start of the time window = 216,25_MS
#define	XL345_LATENT_TIME_WAIT_217_50_MS	0xAE	//wait time from the detection of a tap event to the start of the time window = 217,5_MS
#define	XL345_LATENT_TIME_WAIT_218_75_MS	0xAF	//wait time from the detection of a tap event to the start of the time window = 218,75_MS
#define	XL345_LATENT_TIME_WAIT_220_00_MS	0xB0	//wait time from the detection of a tap event to the start of the time window = 220_MS
#define	XL345_LATENT_TIME_WAIT_221_25_MS	0xB1	//wait time from the detection of a tap event to the start of the time window = 221,25_MS
#define	XL345_LATENT_TIME_WAIT_222_50_MS	0xB2	//wait time from the detection of a tap event to the start of the time window = 222,5_MS
#define	XL345_LATENT_TIME_WAIT_223_75_MS	0xB3	//wait time from the detection of a tap event to the start of the time window = 223,75_MS
#define	XL345_LATENT_TIME_WAIT_225_00_MS	0xB4	//wait time from the detection of a tap event to the start of the time window = 225_MS
#define	XL345_LATENT_TIME_WAIT_226_25_MS	0xB5	//wait time from the detection of a tap event to the start of the time window = 226,25_MS
#define	XL345_LATENT_TIME_WAIT_227_50_MS	0xB6	//wait time from the detection of a tap event to the start of the time window = 227,5_MS
#define	XL345_LATENT_TIME_WAIT_228_75_MS	0xB7	//wait time from the detection of a tap event to the start of the time window = 228,75_MS
#define	XL345_LATENT_TIME_WAIT_230_00_MS	0xB8	//wait time from the detection of a tap event to the start of the time window = 230_MS
#define	XL345_LATENT_TIME_WAIT_231_25_MS	0xB9	//wait time from the detection of a tap event to the start of the time window = 231,25_MS
#define	XL345_LATENT_TIME_WAIT_232_50_MS	0xBA	//wait time from the detection of a tap event to the start of the time window = 232,5_MS
#define	XL345_LATENT_TIME_WAIT_233_75_MS	0xBB	//wait time from the detection of a tap event to the start of the time window = 233,75_MS
#define	XL345_LATENT_TIME_WAIT_235_00_MS	0xBC	//wait time from the detection of a tap event to the start of the time window = 235_MS
#define	XL345_LATENT_TIME_WAIT_236_25_MS	0xBD	//wait time from the detection of a tap event to the start of the time window = 236,25_MS
#define	XL345_LATENT_TIME_WAIT_237_50_MS	0xBE	//wait time from the detection of a tap event to the start of the time window = 237,5_MS
#define	XL345_LATENT_TIME_WAIT_238_75_MS	0xBF	//wait time from the detection of a tap event to the start of the time window = 238,75_MS
#define	XL345_LATENT_TIME_WAIT_240_00_MS	0xC0	//wait time from the detection of a tap event to the start of the time window = 240_MS
#define	XL345_LATENT_TIME_WAIT_241_25_MS	0xC1	//wait time from the detection of a tap event to the start of the time window = 241,25_MS
#define	XL345_LATENT_TIME_WAIT_242_50_MS	0xC2	//wait time from the detection of a tap event to the start of the time window = 242,5_MS
#define	XL345_LATENT_TIME_WAIT_243_75_MS	0xC3	//wait time from the detection of a tap event to the start of the time window = 243,75_MS
#define	XL345_LATENT_TIME_WAIT_245_00_MS	0xC4	//wait time from the detection of a tap event to the start of the time window = 245_MS
#define	XL345_LATENT_TIME_WAIT_246_25_MS	0xC5	//wait time from the detection of a tap event to the start of the time window = 246,25_MS
#define	XL345_LATENT_TIME_WAIT_247_50_MS	0xC6	//wait time from the detection of a tap event to the start of the time window = 247,5_MS
#define	XL345_LATENT_TIME_WAIT_248_75_MS	0xC7	//wait time from the detection of a tap event to the start of the time window = 248,75_MS
#define	XL345_LATENT_TIME_WAIT_250_00_MS	0xC8	//wait time from the detection of a tap event to the start of the time window = 250_MS
#define	XL345_LATENT_TIME_WAIT_251_25_MS	0xC9	//wait time from the detection of a tap event to the start of the time window = 251,25_MS
#define	XL345_LATENT_TIME_WAIT_252_50_MS	0xCA	//wait time from the detection of a tap event to the start of the time window = 252,5_MS
#define	XL345_LATENT_TIME_WAIT_253_75_MS	0xCB	//wait time from the detection of a tap event to the start of the time window = 253,75_MS
#define	XL345_LATENT_TIME_WAIT_255_00_MS	0xCC	//wait time from the detection of a tap event to the start of the time window = 255_MS
#define	XL345_LATENT_TIME_WAIT_256_25_MS	0xCD	//wait time from the detection of a tap event to the start of the time window = 256,25_MS
#define	XL345_LATENT_TIME_WAIT_257_50_MS	0xCE	//wait time from the detection of a tap event to the start of the time window = 257,5_MS
#define	XL345_LATENT_TIME_WAIT_258_75_MS	0xCF	//wait time from the detection of a tap event to the start of the time window = 258,75_MS
#define	XL345_LATENT_TIME_WAIT_260_00_MS	0xD0	//wait time from the detection of a tap event to the start of the time window = 260_MS
#define	XL345_LATENT_TIME_WAIT_261_25_MS	0xD1	//wait time from the detection of a tap event to the start of the time window = 261,25_MS
#define	XL345_LATENT_TIME_WAIT_262_50_MS	0xD2	//wait time from the detection of a tap event to the start of the time window = 262,5_MS
#define	XL345_LATENT_TIME_WAIT_263_75_MS	0xD3	//wait time from the detection of a tap event to the start of the time window = 263,75_MS
#define	XL345_LATENT_TIME_WAIT_265_00_MS	0xD4	//wait time from the detection of a tap event to the start of the time window = 265_MS
#define	XL345_LATENT_TIME_WAIT_266_25_MS	0xD5	//wait time from the detection of a tap event to the start of the time window = 266,25_MS
#define	XL345_LATENT_TIME_WAIT_267_50_MS	0xD6	//wait time from the detection of a tap event to the start of the time window = 267,5_MS
#define	XL345_LATENT_TIME_WAIT_268_75_MS	0xD7	//wait time from the detection of a tap event to the start of the time window = 268,75_MS
#define	XL345_LATENT_TIME_WAIT_270_00_MS	0xD8	//wait time from the detection of a tap event to the start of the time window = 270_MS
#define	XL345_LATENT_TIME_WAIT_271_25_MS	0xD9	//wait time from the detection of a tap event to the start of the time window = 271,25_MS
#define	XL345_LATENT_TIME_WAIT_272_50_MS	0xDA	//wait time from the detection of a tap event to the start of the time window = 272,5_MS
#define	XL345_LATENT_TIME_WAIT_273_75_MS	0xDB	//wait time from the detection of a tap event to the start of the time window = 273,75_MS
#define	XL345_LATENT_TIME_WAIT_275_00_MS	0xDC	//wait time from the detection of a tap event to the start of the time window = 275_MS
#define	XL345_LATENT_TIME_WAIT_276_25_MS	0xDD	//wait time from the detection of a tap event to the start of the time window = 276,25_MS
#define	XL345_LATENT_TIME_WAIT_277_50_MS	0xDE	//wait time from the detection of a tap event to the start of the time window = 277,5_MS
#define	XL345_LATENT_TIME_WAIT_278_75_MS	0xDF	//wait time from the detection of a tap event to the start of the time window = 278,75_MS
#define	XL345_LATENT_TIME_WAIT_280_00_MS	0xE0	//wait time from the detection of a tap event to the start of the time window = 280_MS
#define	XL345_LATENT_TIME_WAIT_281_25_MS	0xE1	//wait time from the detection of a tap event to the start of the time window = 281,25_MS
#define	XL345_LATENT_TIME_WAIT_282_50_MS	0xE2	//wait time from the detection of a tap event to the start of the time window = 282,5_MS
#define	XL345_LATENT_TIME_WAIT_283_75_MS	0xE3	//wait time from the detection of a tap event to the start of the time window = 283,75_MS
#define	XL345_LATENT_TIME_WAIT_285_00_MS	0xE4	//wait time from the detection of a tap event to the start of the time window = 285_MS
#define	XL345_LATENT_TIME_WAIT_286_25_MS	0xE5	//wait time from the detection of a tap event to the start of the time window = 286,25_MS
#define	XL345_LATENT_TIME_WAIT_287_50_MS	0xE6	//wait time from the detection of a tap event to the start of the time window = 287,5_MS
#define	XL345_LATENT_TIME_WAIT_288_75_MS	0xE7	//wait time from the detection of a tap event to the start of the time window = 288,75_MS
#define	XL345_LATENT_TIME_WAIT_290_00_MS	0xE8	//wait time from the detection of a tap event to the start of the time window = 290_MS
#define	XL345_LATENT_TIME_WAIT_291_25_MS	0xE9	//wait time from the detection of a tap event to the start of the time window = 291,25_MS
#define	XL345_LATENT_TIME_WAIT_292_50_MS	0xEA	//wait time from the detection of a tap event to the start of the time window = 292,5_MS
#define	XL345_LATENT_TIME_WAIT_293_75_MS	0xEB	//wait time from the detection of a tap event to the start of the time window = 293,75_MS
#define	XL345_LATENT_TIME_WAIT_295_00_MS	0xEC	//wait time from the detection of a tap event to the start of the time window = 295_MS
#define	XL345_LATENT_TIME_WAIT_296_25_MS	0xED	//wait time from the detection of a tap event to the start of the time window = 296,25_MS
#define	XL345_LATENT_TIME_WAIT_297_50_MS	0xEE	//wait time from the detection of a tap event to the start of the time window = 297,5_MS
#define	XL345_LATENT_TIME_WAIT_298_75_MS	0xEF	//wait time from the detection of a tap event to the start of the time window = 298,75_MS
#define	XL345_LATENT_TIME_WAIT_300_00_MS	0xF0	//wait time from the detection of a tap event to the start of the time window = 300_MS
#define	XL345_LATENT_TIME_WAIT_301_25_MS	0xF1	//wait time from the detection of a tap event to the start of the time window = 301,25_MS
#define	XL345_LATENT_TIME_WAIT_302_50_MS	0xF2	//wait time from the detection of a tap event to the start of the time window = 302,5_MS
#define	XL345_LATENT_TIME_WAIT_303_75_MS	0xF3	//wait time from the detection of a tap event to the start of the time window = 303,75_MS
#define	XL345_LATENT_TIME_WAIT_305_00_MS	0xF4	//wait time from the detection of a tap event to the start of the time window = 305_MS
#define	XL345_LATENT_TIME_WAIT_306_25_MS	0xF5	//wait time from the detection of a tap event to the start of the time window = 306,25_MS
#define	XL345_LATENT_TIME_WAIT_307_50_MS	0xF6	//wait time from the detection of a tap event to the start of the time window = 307,5_MS
#define	XL345_LATENT_TIME_WAIT_308_75_MS	0xF7	//wait time from the detection of a tap event to the start of the time window = 308,75_MS
#define	XL345_LATENT_TIME_WAIT_310_00_MS	0xF8	//wait time from the detection of a tap event to the start of the time window = 310_MS
#define	XL345_LATENT_TIME_WAIT_311_25_MS	0xF9	//wait time from the detection of a tap event to the start of the time window = 311,25_MS
#define	XL345_LATENT_TIME_WAIT_312_50_MS	0xFA	//wait time from the detection of a tap event to the start of the time window = 312,5_MS
#define	XL345_LATENT_TIME_WAIT_313_75_MS	0xFB	//wait time from the detection of a tap event to the start of the time window = 313,75_MS
#define	XL345_LATENT_TIME_WAIT_315_00_MS	0xFC	//wait time from the detection of a tap event to the start of the time window = 315_MS
#define	XL345_LATENT_TIME_WAIT_316_25_MS	0xFD	//wait time from the detection of a tap event to the start of the time window = 316,25_MS
#define	XL345_LATENT_TIME_WAIT_317_50_MS	0xFE	//wait time from the detection of a tap event to the start of the time window = 317,5_MS
#define	XL345_LATENT_TIME_WAIT_318_75_MS	0xFF	//wait time from the detection of a tap event to the start of the time window = 318,75_MS

/*
 The window register is eight bits and contains an unsigned time
value representing the amount of time after the expiration of the
latency time (determined by the latent register) during which a
second valid tap can begin. The scale factor is 1.25 ms/LSB. A
value of 0 disables the double tap function.
 */
#define	XL345_WINDOW_DISABLE_DOUBLE_TAP  	0x00	//time after the latency time during which a second valid tap can begin = 0_MS
#define	XL345_WINDOW_TIME_WAIT_1_25_MS  	0x01	//time after the latency time during which a second valid tap can begin = 1,25_MS
#define	XL345_WINDOW_TIME_WAIT_2_50_MS  	0x02	//time after the latency time during which a second valid tap can begin = 2,5_MS
#define	XL345_WINDOW_TIME_WAIT_3_75_MS  	0x03	//time after the latency time during which a second valid tap can begin = 3,75_MS
#define	XL345_WINDOW_TIME_WAIT_5_00_MS  	0x04	//time after the latency time during which a second valid tap can begin = 5_MS
#define	XL345_WINDOW_TIME_WAIT_6_25_MS  	0x05	//time after the latency time during which a second valid tap can begin = 6,25_MS
#define	XL345_WINDOW_TIME_WAIT_7_50_MS  	0x06	//time after the latency time during which a second valid tap can begin = 7,5_MS
#define	XL345_WINDOW_TIME_WAIT_8_75_MS  	0x07	//time after the latency time during which a second valid tap can begin = 8,75_MS
#define	XL345_WINDOW_TIME_WAIT_10_00_MS 	0x08	//time after the latency time during which a second valid tap can begin = 10_MS
#define	XL345_WINDOW_TIME_WAIT_11_25_MS 	0x09	//time after the latency time during which a second valid tap can begin = 11,25_MS
#define	XL345_WINDOW_TIME_WAIT_12_50_MS 	0x0A	//time after the latency time during which a second valid tap can begin = 12,5_MS
#define	XL345_WINDOW_TIME_WAIT_13_75_MS 	0x0B	//time after the latency time during which a second valid tap can begin = 13,75_MS
#define	XL345_WINDOW_TIME_WAIT_15_00_MS 	0x0C	//time after the latency time during which a second valid tap can begin = 15_MS
#define	XL345_WINDOW_TIME_WAIT_16_25_MS 	0x0D	//time after the latency time during which a second valid tap can begin = 16,25_MS
#define	XL345_WINDOW_TIME_WAIT_17_50_MS 	0x0E	//time after the latency time during which a second valid tap can begin = 17,5_MS
#define	XL345_WINDOW_TIME_WAIT_18_75_MS 	0x0F	//time after the latency time during which a second valid tap can begin = 18,75_MS
#define	XL345_WINDOW_TIME_WAIT_20_00_MS 	0x10	//time after the latency time during which a second valid tap can begin = 20_MS
#define	XL345_WINDOW_TIME_WAIT_21_25_MS 	0x11	//time after the latency time during which a second valid tap can begin = 21,25_MS
#define	XL345_WINDOW_TIME_WAIT_22_50_MS 	0x12	//time after the latency time during which a second valid tap can begin = 22,5_MS
#define	XL345_WINDOW_TIME_WAIT_23_75_MS 	0x13	//time after the latency time during which a second valid tap can begin = 23,75_MS
#define	XL345_WINDOW_TIME_WAIT_25_00_MS 	0x14	//time after the latency time during which a second valid tap can begin = 25_MS
#define	XL345_WINDOW_TIME_WAIT_26_25_MS 	0x15	//time after the latency time during which a second valid tap can begin = 26,25_MS
#define	XL345_WINDOW_TIME_WAIT_27_50_MS 	0x16	//time after the latency time during which a second valid tap can begin = 27,5_MS
#define	XL345_WINDOW_TIME_WAIT_28_75_MS 	0x17	//time after the latency time during which a second valid tap can begin = 28,75_MS
#define	XL345_WINDOW_TIME_WAIT_30_00_MS 	0x18	//time after the latency time during which a second valid tap can begin = 30_MS
#define	XL345_WINDOW_TIME_WAIT_31_25_MS 	0x19	//time after the latency time during which a second valid tap can begin = 31,25_MS
#define	XL345_WINDOW_TIME_WAIT_32_50_MS 	0x1A	//time after the latency time during which a second valid tap can begin = 32,5_MS
#define	XL345_WINDOW_TIME_WAIT_33_75_MS 	0x1B	//time after the latency time during which a second valid tap can begin = 33,75_MS
#define	XL345_WINDOW_TIME_WAIT_35_00_MS 	0x1C	//time after the latency time during which a second valid tap can begin = 35_MS
#define	XL345_WINDOW_TIME_WAIT_36_25_MS 	0x1D	//time after the latency time during which a second valid tap can begin = 36,25_MS
#define	XL345_WINDOW_TIME_WAIT_37_50_MS 	0x1E	//time after the latency time during which a second valid tap can begin = 37,5_MS
#define	XL345_WINDOW_TIME_WAIT_38_75_MS 	0x1F	//time after the latency time during which a second valid tap can begin = 38,75_MS
#define	XL345_WINDOW_TIME_WAIT_40_00_MS 	0x20	//time after the latency time during which a second valid tap can begin = 40_MS
#define	XL345_WINDOW_TIME_WAIT_41_25_MS 	0x21	//time after the latency time during which a second valid tap can begin = 41,25_MS
#define	XL345_WINDOW_TIME_WAIT_42_50_MS 	0x22	//time after the latency time during which a second valid tap can begin = 42,5_MS
#define	XL345_WINDOW_TIME_WAIT_43_75_MS 	0x23	//time after the latency time during which a second valid tap can begin = 43,75_MS
#define	XL345_WINDOW_TIME_WAIT_45_00_MS 	0x24	//time after the latency time during which a second valid tap can begin = 45_MS
#define	XL345_WINDOW_TIME_WAIT_46_25_MS 	0x25	//time after the latency time during which a second valid tap can begin = 46,25_MS
#define	XL345_WINDOW_TIME_WAIT_47_50_MS 	0x26	//time after the latency time during which a second valid tap can begin = 47,5_MS
#define	XL345_WINDOW_TIME_WAIT_48_75_MS 	0x27	//time after the latency time during which a second valid tap can begin = 48,75_MS
#define	XL345_WINDOW_TIME_WAIT_50_00_MS 	0x28	//time after the latency time during which a second valid tap can begin = 50_MS
#define	XL345_WINDOW_TIME_WAIT_51_25_MS 	0x29	//time after the latency time during which a second valid tap can begin = 51,25_MS
#define	XL345_WINDOW_TIME_WAIT_52_50_MS 	0x2A	//time after the latency time during which a second valid tap can begin = 52,5_MS
#define	XL345_WINDOW_TIME_WAIT_53_75_MS 	0x2B	//time after the latency time during which a second valid tap can begin = 53,75_MS
#define	XL345_WINDOW_TIME_WAIT_55_00_MS 	0x2C	//time after the latency time during which a second valid tap can begin = 55_MS
#define	XL345_WINDOW_TIME_WAIT_56_25_MS 	0x2D	//time after the latency time during which a second valid tap can begin = 56,25_MS
#define	XL345_WINDOW_TIME_WAIT_57_50_MS 	0x2E	//time after the latency time during which a second valid tap can begin = 57,5_MS
#define	XL345_WINDOW_TIME_WAIT_58_75_MS 	0x2F	//time after the latency time during which a second valid tap can begin = 58,75_MS
#define	XL345_WINDOW_TIME_WAIT_60_00_MS 	0x30	//time after the latency time during which a second valid tap can begin = 60_MS
#define	XL345_WINDOW_TIME_WAIT_61_25_MS 	0x31	//time after the latency time during which a second valid tap can begin = 61,25_MS
#define	XL345_WINDOW_TIME_WAIT_62_50_MS 	0x32	//time after the latency time during which a second valid tap can begin = 62,5_MS
#define	XL345_WINDOW_TIME_WAIT_63_75_MS 	0x33	//time after the latency time during which a second valid tap can begin = 63,75_MS
#define	XL345_WINDOW_TIME_WAIT_65_00_MS 	0x34	//time after the latency time during which a second valid tap can begin = 65_MS
#define	XL345_WINDOW_TIME_WAIT_66_25_MS 	0x35	//time after the latency time during which a second valid tap can begin = 66,25_MS
#define	XL345_WINDOW_TIME_WAIT_67_50_MS 	0x36	//time after the latency time during which a second valid tap can begin = 67,5_MS
#define	XL345_WINDOW_TIME_WAIT_68_75_MS 	0x37	//time after the latency time during which a second valid tap can begin = 68,75_MS
#define	XL345_WINDOW_TIME_WAIT_70_00_MS 	0x38	//time after the latency time during which a second valid tap can begin = 70_MS
#define	XL345_WINDOW_TIME_WAIT_71_25_MS 	0x39	//time after the latency time during which a second valid tap can begin = 71,25_MS
#define	XL345_WINDOW_TIME_WAIT_72_50_MS 	0x3A	//time after the latency time during which a second valid tap can begin = 72,5_MS
#define	XL345_WINDOW_TIME_WAIT_73_75_MS 	0x3B	//time after the latency time during which a second valid tap can begin = 73,75_MS
#define	XL345_WINDOW_TIME_WAIT_75_00_MS 	0x3C	//time after the latency time during which a second valid tap can begin = 75_MS
#define	XL345_WINDOW_TIME_WAIT_76_25_MS 	0x3D	//time after the latency time during which a second valid tap can begin = 76,25_MS
#define	XL345_WINDOW_TIME_WAIT_77_50_MS 	0x3E	//time after the latency time during which a second valid tap can begin = 77,5_MS
#define	XL345_WINDOW_TIME_WAIT_78_75_MS 	0x3F	//time after the latency time during which a second valid tap can begin = 78,75_MS
#define	XL345_WINDOW_TIME_WAIT_80_00_MS 	0x40	//time after the latency time during which a second valid tap can begin = 80_MS
#define	XL345_WINDOW_TIME_WAIT_81_25_MS 	0x41	//time after the latency time during which a second valid tap can begin = 81,25_MS
#define	XL345_WINDOW_TIME_WAIT_82_50_MS 	0x42	//time after the latency time during which a second valid tap can begin = 82,5_MS
#define	XL345_WINDOW_TIME_WAIT_83_75_MS 	0x43	//time after the latency time during which a second valid tap can begin = 83,75_MS
#define	XL345_WINDOW_TIME_WAIT_85_00_MS 	0x44	//time after the latency time during which a second valid tap can begin = 85_MS
#define	XL345_WINDOW_TIME_WAIT_86_25_MS 	0x45	//time after the latency time during which a second valid tap can begin = 86,25_MS
#define	XL345_WINDOW_TIME_WAIT_87_50_MS 	0x46	//time after the latency time during which a second valid tap can begin = 87,5_MS
#define	XL345_WINDOW_TIME_WAIT_88_75_MS 	0x47	//time after the latency time during which a second valid tap can begin = 88,75_MS
#define	XL345_WINDOW_TIME_WAIT_90_00_MS 	0x48	//time after the latency time during which a second valid tap can begin = 90_MS
#define	XL345_WINDOW_TIME_WAIT_91_25_MS 	0x49	//time after the latency time during which a second valid tap can begin = 91,25_MS
#define	XL345_WINDOW_TIME_WAIT_92_50_MS 	0x4A	//time after the latency time during which a second valid tap can begin = 92,5_MS
#define	XL345_WINDOW_TIME_WAIT_93_75_MS 	0x4B	//time after the latency time during which a second valid tap can begin = 93,75_MS
#define	XL345_WINDOW_TIME_WAIT_95_00_MS 	0x4C	//time after the latency time during which a second valid tap can begin = 95_MS
#define	XL345_WINDOW_TIME_WAIT_96_25_MS 	0x4D	//time after the latency time during which a second valid tap can begin = 96,25_MS
#define	XL345_WINDOW_TIME_WAIT_97_50_MS 	0x4E	//time after the latency time during which a second valid tap can begin = 97,5_MS
#define	XL345_WINDOW_TIME_WAIT_98_75_MS 	0x4F	//time after the latency time during which a second valid tap can begin = 98,75_MS
#define	XL345_WINDOW_TIME_WAIT_100_00_MS	0x50	//time after the latency time during which a second valid tap can begin = 100_MS
#define	XL345_WINDOW_TIME_WAIT_101_25_MS	0x51	//time after the latency time during which a second valid tap can begin = 101,25_MS
#define	XL345_WINDOW_TIME_WAIT_102_50_MS	0x52	//time after the latency time during which a second valid tap can begin = 102,5_MS
#define	XL345_WINDOW_TIME_WAIT_103_75_MS	0x53	//time after the latency time during which a second valid tap can begin = 103,75_MS
#define	XL345_WINDOW_TIME_WAIT_105_00_MS	0x54	//time after the latency time during which a second valid tap can begin = 105_MS
#define	XL345_WINDOW_TIME_WAIT_106_25_MS	0x55	//time after the latency time during which a second valid tap can begin = 106,25_MS
#define	XL345_WINDOW_TIME_WAIT_107_50_MS	0x56	//time after the latency time during which a second valid tap can begin = 107,5_MS
#define	XL345_WINDOW_TIME_WAIT_108_75_MS	0x57	//time after the latency time during which a second valid tap can begin = 108,75_MS
#define	XL345_WINDOW_TIME_WAIT_110_00_MS	0x58	//time after the latency time during which a second valid tap can begin = 110_MS
#define	XL345_WINDOW_TIME_WAIT_111_25_MS	0x59	//time after the latency time during which a second valid tap can begin = 111,25_MS
#define	XL345_WINDOW_TIME_WAIT_112_50_MS	0x5A	//time after the latency time during which a second valid tap can begin = 112,5_MS
#define	XL345_WINDOW_TIME_WAIT_113_75_MS	0x5B	//time after the latency time during which a second valid tap can begin = 113,75_MS
#define	XL345_WINDOW_TIME_WAIT_115_00_MS	0x5C	//time after the latency time during which a second valid tap can begin = 115_MS
#define	XL345_WINDOW_TIME_WAIT_116_25_MS	0x5D	//time after the latency time during which a second valid tap can begin = 116,25_MS
#define	XL345_WINDOW_TIME_WAIT_117_50_MS	0x5E	//time after the latency time during which a second valid tap can begin = 117,5_MS
#define	XL345_WINDOW_TIME_WAIT_118_75_MS	0x5F	//time after the latency time during which a second valid tap can begin = 118,75_MS
#define	XL345_WINDOW_TIME_WAIT_120_00_MS	0x60	//time after the latency time during which a second valid tap can begin = 120_MS
#define	XL345_WINDOW_TIME_WAIT_121_25_MS	0x61	//time after the latency time during which a second valid tap can begin = 121,25_MS
#define	XL345_WINDOW_TIME_WAIT_122_50_MS	0x62	//time after the latency time during which a second valid tap can begin = 122,5_MS
#define	XL345_WINDOW_TIME_WAIT_123_75_MS	0x63	//time after the latency time during which a second valid tap can begin = 123,75_MS
#define	XL345_WINDOW_TIME_WAIT_125_00_MS	0x64	//time after the latency time during which a second valid tap can begin = 125_MS
#define	XL345_WINDOW_TIME_WAIT_126_25_MS	0x65	//time after the latency time during which a second valid tap can begin = 126,25_MS
#define	XL345_WINDOW_TIME_WAIT_127_50_MS	0x66	//time after the latency time during which a second valid tap can begin = 127,5_MS
#define	XL345_WINDOW_TIME_WAIT_128_75_MS	0x67	//time after the latency time during which a second valid tap can begin = 128,75_MS
#define	XL345_WINDOW_TIME_WAIT_130_00_MS	0x68	//time after the latency time during which a second valid tap can begin = 130_MS
#define	XL345_WINDOW_TIME_WAIT_131_25_MS	0x69	//time after the latency time during which a second valid tap can begin = 131,25_MS
#define	XL345_WINDOW_TIME_WAIT_132_50_MS	0x6A	//time after the latency time during which a second valid tap can begin = 132,5_MS
#define	XL345_WINDOW_TIME_WAIT_133_75_MS	0x6B	//time after the latency time during which a second valid tap can begin = 133,75_MS
#define	XL345_WINDOW_TIME_WAIT_135_00_MS	0x6C	//time after the latency time during which a second valid tap can begin = 135_MS
#define	XL345_WINDOW_TIME_WAIT_136_25_MS	0x6D	//time after the latency time during which a second valid tap can begin = 136,25_MS
#define	XL345_WINDOW_TIME_WAIT_137_50_MS	0x6E	//time after the latency time during which a second valid tap can begin = 137,5_MS
#define	XL345_WINDOW_TIME_WAIT_138_75_MS	0x6F	//time after the latency time during which a second valid tap can begin = 138,75_MS
#define	XL345_WINDOW_TIME_WAIT_140_00_MS	0x70	//time after the latency time during which a second valid tap can begin = 140_MS
#define	XL345_WINDOW_TIME_WAIT_141_25_MS	0x71	//time after the latency time during which a second valid tap can begin = 141,25_MS
#define	XL345_WINDOW_TIME_WAIT_142_50_MS	0x72	//time after the latency time during which a second valid tap can begin = 142,5_MS
#define	XL345_WINDOW_TIME_WAIT_143_75_MS	0x73	//time after the latency time during which a second valid tap can begin = 143,75_MS
#define	XL345_WINDOW_TIME_WAIT_145_00_MS	0x74	//time after the latency time during which a second valid tap can begin = 145_MS
#define	XL345_WINDOW_TIME_WAIT_146_25_MS	0x75	//time after the latency time during which a second valid tap can begin = 146,25_MS
#define	XL345_WINDOW_TIME_WAIT_147_50_MS	0x76	//time after the latency time during which a second valid tap can begin = 147,5_MS
#define	XL345_WINDOW_TIME_WAIT_148_75_MS	0x77	//time after the latency time during which a second valid tap can begin = 148,75_MS
#define	XL345_WINDOW_TIME_WAIT_150_00_MS	0x78	//time after the latency time during which a second valid tap can begin = 150_MS
#define	XL345_WINDOW_TIME_WAIT_151_25_MS	0x79	//time after the latency time during which a second valid tap can begin = 151,25_MS
#define	XL345_WINDOW_TIME_WAIT_152_50_MS	0x7A	//time after the latency time during which a second valid tap can begin = 152,5_MS
#define	XL345_WINDOW_TIME_WAIT_153_75_MS	0x7B	//time after the latency time during which a second valid tap can begin = 153,75_MS
#define	XL345_WINDOW_TIME_WAIT_155_00_MS	0x7C	//time after the latency time during which a second valid tap can begin = 155_MS
#define	XL345_WINDOW_TIME_WAIT_156_25_MS	0x7D	//time after the latency time during which a second valid tap can begin = 156,25_MS
#define	XL345_WINDOW_TIME_WAIT_157_50_MS	0x7E	//time after the latency time during which a second valid tap can begin = 157,5_MS
#define	XL345_WINDOW_TIME_WAIT_158_75_MS	0x7F	//time after the latency time during which a second valid tap can begin = 158,75_MS
#define	XL345_WINDOW_TIME_WAIT_160_00_MS	0x80	//time after the latency time during which a second valid tap can begin = 160_MS
#define	XL345_WINDOW_TIME_WAIT_161_25_MS	0x81	//time after the latency time during which a second valid tap can begin = 161,25_MS
#define	XL345_WINDOW_TIME_WAIT_162_50_MS	0x82	//time after the latency time during which a second valid tap can begin = 162,5_MS
#define	XL345_WINDOW_TIME_WAIT_163_75_MS	0x83	//time after the latency time during which a second valid tap can begin = 163,75_MS
#define	XL345_WINDOW_TIME_WAIT_165_00_MS	0x84	//time after the latency time during which a second valid tap can begin = 165_MS
#define	XL345_WINDOW_TIME_WAIT_166_25_MS	0x85	//time after the latency time during which a second valid tap can begin = 166,25_MS
#define	XL345_WINDOW_TIME_WAIT_167_50_MS	0x86	//time after the latency time during which a second valid tap can begin = 167,5_MS
#define	XL345_WINDOW_TIME_WAIT_168_75_MS	0x87	//time after the latency time during which a second valid tap can begin = 168,75_MS
#define	XL345_WINDOW_TIME_WAIT_170_00_MS	0x88	//time after the latency time during which a second valid tap can begin = 170_MS
#define	XL345_WINDOW_TIME_WAIT_171_25_MS	0x89	//time after the latency time during which a second valid tap can begin = 171,25_MS
#define	XL345_WINDOW_TIME_WAIT_172_50_MS	0x8A	//time after the latency time during which a second valid tap can begin = 172,5_MS
#define	XL345_WINDOW_TIME_WAIT_173_75_MS	0x8B	//time after the latency time during which a second valid tap can begin = 173,75_MS
#define	XL345_WINDOW_TIME_WAIT_175_00_MS	0x8C	//time after the latency time during which a second valid tap can begin = 175_MS
#define	XL345_WINDOW_TIME_WAIT_176_25_MS	0x8D	//time after the latency time during which a second valid tap can begin = 176,25_MS
#define	XL345_WINDOW_TIME_WAIT_177_50_MS	0x8E	//time after the latency time during which a second valid tap can begin = 177,5_MS
#define	XL345_WINDOW_TIME_WAIT_178_75_MS	0x8F	//time after the latency time during which a second valid tap can begin = 178,75_MS
#define	XL345_WINDOW_TIME_WAIT_180_00_MS	0x90	//time after the latency time during which a second valid tap can begin = 180_MS
#define	XL345_WINDOW_TIME_WAIT_181_25_MS	0x91	//time after the latency time during which a second valid tap can begin = 181,25_MS
#define	XL345_WINDOW_TIME_WAIT_182_50_MS	0x92	//time after the latency time during which a second valid tap can begin = 182,5_MS
#define	XL345_WINDOW_TIME_WAIT_183_75_MS	0x93	//time after the latency time during which a second valid tap can begin = 183,75_MS
#define	XL345_WINDOW_TIME_WAIT_185_00_MS	0x94	//time after the latency time during which a second valid tap can begin = 185_MS
#define	XL345_WINDOW_TIME_WAIT_186_25_MS	0x95	//time after the latency time during which a second valid tap can begin = 186,25_MS
#define	XL345_WINDOW_TIME_WAIT_187_50_MS	0x96	//time after the latency time during which a second valid tap can begin = 187,5_MS
#define	XL345_WINDOW_TIME_WAIT_188_75_MS	0x97	//time after the latency time during which a second valid tap can begin = 188,75_MS
#define	XL345_WINDOW_TIME_WAIT_190_00_MS	0x98	//time after the latency time during which a second valid tap can begin = 190_MS
#define	XL345_WINDOW_TIME_WAIT_191_25_MS	0x99	//time after the latency time during which a second valid tap can begin = 191,25_MS
#define	XL345_WINDOW_TIME_WAIT_192_50_MS	0x9A	//time after the latency time during which a second valid tap can begin = 192,5_MS
#define	XL345_WINDOW_TIME_WAIT_193_75_MS	0x9B	//time after the latency time during which a second valid tap can begin = 193,75_MS
#define	XL345_WINDOW_TIME_WAIT_195_00_MS	0x9C	//time after the latency time during which a second valid tap can begin = 195_MS
#define	XL345_WINDOW_TIME_WAIT_196_25_MS	0x9D	//time after the latency time during which a second valid tap can begin = 196,25_MS
#define	XL345_WINDOW_TIME_WAIT_197_50_MS	0x9E	//time after the latency time during which a second valid tap can begin = 197,5_MS
#define	XL345_WINDOW_TIME_WAIT_198_75_MS	0x9F	//time after the latency time during which a second valid tap can begin = 198,75_MS
#define	XL345_WINDOW_TIME_WAIT_200_00_MS	0xA0	//time after the latency time during which a second valid tap can begin = 200_MS
#define	XL345_WINDOW_TIME_WAIT_201_25_MS	0xA1	//time after the latency time during which a second valid tap can begin = 201,25_MS
#define	XL345_WINDOW_TIME_WAIT_202_50_MS	0xA2	//time after the latency time during which a second valid tap can begin = 202,5_MS
#define	XL345_WINDOW_TIME_WAIT_203_75_MS	0xA3	//time after the latency time during which a second valid tap can begin = 203,75_MS
#define	XL345_WINDOW_TIME_WAIT_205_00_MS	0xA4	//time after the latency time during which a second valid tap can begin = 205_MS
#define	XL345_WINDOW_TIME_WAIT_206_25_MS	0xA5	//time after the latency time during which a second valid tap can begin = 206,25_MS
#define	XL345_WINDOW_TIME_WAIT_207_50_MS	0xA6	//time after the latency time during which a second valid tap can begin = 207,5_MS
#define	XL345_WINDOW_TIME_WAIT_208_75_MS	0xA7	//time after the latency time during which a second valid tap can begin = 208,75_MS
#define	XL345_WINDOW_TIME_WAIT_210_00_MS	0xA8	//time after the latency time during which a second valid tap can begin = 210_MS
#define	XL345_WINDOW_TIME_WAIT_211_25_MS	0xA9	//time after the latency time during which a second valid tap can begin = 211,25_MS
#define	XL345_WINDOW_TIME_WAIT_212_50_MS	0xAA	//time after the latency time during which a second valid tap can begin = 212,5_MS
#define	XL345_WINDOW_TIME_WAIT_213_75_MS	0xAB	//time after the latency time during which a second valid tap can begin = 213,75_MS
#define	XL345_WINDOW_TIME_WAIT_215_00_MS	0xAC	//time after the latency time during which a second valid tap can begin = 215_MS
#define	XL345_WINDOW_TIME_WAIT_216_25_MS	0xAD	//time after the latency time during which a second valid tap can begin = 216,25_MS
#define	XL345_WINDOW_TIME_WAIT_217_50_MS	0xAE	//time after the latency time during which a second valid tap can begin = 217,5_MS
#define	XL345_WINDOW_TIME_WAIT_218_75_MS	0xAF	//time after the latency time during which a second valid tap can begin = 218,75_MS
#define	XL345_WINDOW_TIME_WAIT_220_00_MS	0xB0	//time after the latency time during which a second valid tap can begin = 220_MS
#define	XL345_WINDOW_TIME_WAIT_221_25_MS	0xB1	//time after the latency time during which a second valid tap can begin = 221,25_MS
#define	XL345_WINDOW_TIME_WAIT_222_50_MS	0xB2	//time after the latency time during which a second valid tap can begin = 222,5_MS
#define	XL345_WINDOW_TIME_WAIT_223_75_MS	0xB3	//time after the latency time during which a second valid tap can begin = 223,75_MS
#define	XL345_WINDOW_TIME_WAIT_225_00_MS	0xB4	//time after the latency time during which a second valid tap can begin = 225_MS
#define	XL345_WINDOW_TIME_WAIT_226_25_MS	0xB5	//time after the latency time during which a second valid tap can begin = 226,25_MS
#define	XL345_WINDOW_TIME_WAIT_227_50_MS	0xB6	//time after the latency time during which a second valid tap can begin = 227,5_MS
#define	XL345_WINDOW_TIME_WAIT_228_75_MS	0xB7	//time after the latency time during which a second valid tap can begin = 228,75_MS
#define	XL345_WINDOW_TIME_WAIT_230_00_MS	0xB8	//time after the latency time during which a second valid tap can begin = 230_MS
#define	XL345_WINDOW_TIME_WAIT_231_25_MS	0xB9	//time after the latency time during which a second valid tap can begin = 231,25_MS
#define	XL345_WINDOW_TIME_WAIT_232_50_MS	0xBA	//time after the latency time during which a second valid tap can begin = 232,5_MS
#define	XL345_WINDOW_TIME_WAIT_233_75_MS	0xBB	//time after the latency time during which a second valid tap can begin = 233,75_MS
#define	XL345_WINDOW_TIME_WAIT_235_00_MS	0xBC	//time after the latency time during which a second valid tap can begin = 235_MS
#define	XL345_WINDOW_TIME_WAIT_236_25_MS	0xBD	//time after the latency time during which a second valid tap can begin = 236,25_MS
#define	XL345_WINDOW_TIME_WAIT_237_50_MS	0xBE	//time after the latency time during which a second valid tap can begin = 237,5_MS
#define	XL345_WINDOW_TIME_WAIT_238_75_MS	0xBF	//time after the latency time during which a second valid tap can begin = 238,75_MS
#define	XL345_WINDOW_TIME_WAIT_240_00_MS	0xC0	//time after the latency time during which a second valid tap can begin = 240_MS
#define	XL345_WINDOW_TIME_WAIT_241_25_MS	0xC1	//time after the latency time during which a second valid tap can begin = 241,25_MS
#define	XL345_WINDOW_TIME_WAIT_242_50_MS	0xC2	//time after the latency time during which a second valid tap can begin = 242,5_MS
#define	XL345_WINDOW_TIME_WAIT_243_75_MS	0xC3	//time after the latency time during which a second valid tap can begin = 243,75_MS
#define	XL345_WINDOW_TIME_WAIT_245_00_MS	0xC4	//time after the latency time during which a second valid tap can begin = 245_MS
#define	XL345_WINDOW_TIME_WAIT_246_25_MS	0xC5	//time after the latency time during which a second valid tap can begin = 246,25_MS
#define	XL345_WINDOW_TIME_WAIT_247_50_MS	0xC6	//time after the latency time during which a second valid tap can begin = 247,5_MS
#define	XL345_WINDOW_TIME_WAIT_248_75_MS	0xC7	//time after the latency time during which a second valid tap can begin = 248,75_MS
#define	XL345_WINDOW_TIME_WAIT_250_00_MS	0xC8	//time after the latency time during which a second valid tap can begin = 250_MS
#define	XL345_WINDOW_TIME_WAIT_251_25_MS	0xC9	//time after the latency time during which a second valid tap can begin = 251,25_MS
#define	XL345_WINDOW_TIME_WAIT_252_50_MS	0xCA	//time after the latency time during which a second valid tap can begin = 252,5_MS
#define	XL345_WINDOW_TIME_WAIT_253_75_MS	0xCB	//time after the latency time during which a second valid tap can begin = 253,75_MS
#define	XL345_WINDOW_TIME_WAIT_255_00_MS	0xCC	//time after the latency time during which a second valid tap can begin = 255_MS
#define	XL345_WINDOW_TIME_WAIT_256_25_MS	0xCD	//time after the latency time during which a second valid tap can begin = 256,25_MS
#define	XL345_WINDOW_TIME_WAIT_257_50_MS	0xCE	//time after the latency time during which a second valid tap can begin = 257,5_MS
#define	XL345_WINDOW_TIME_WAIT_258_75_MS	0xCF	//time after the latency time during which a second valid tap can begin = 258,75_MS
#define	XL345_WINDOW_TIME_WAIT_260_00_MS	0xD0	//time after the latency time during which a second valid tap can begin = 260_MS
#define	XL345_WINDOW_TIME_WAIT_261_25_MS	0xD1	//time after the latency time during which a second valid tap can begin = 261,25_MS
#define	XL345_WINDOW_TIME_WAIT_262_50_MS	0xD2	//time after the latency time during which a second valid tap can begin = 262,5_MS
#define	XL345_WINDOW_TIME_WAIT_263_75_MS	0xD3	//time after the latency time during which a second valid tap can begin = 263,75_MS
#define	XL345_WINDOW_TIME_WAIT_265_00_MS	0xD4	//time after the latency time during which a second valid tap can begin = 265_MS
#define	XL345_WINDOW_TIME_WAIT_266_25_MS	0xD5	//time after the latency time during which a second valid tap can begin = 266,25_MS
#define	XL345_WINDOW_TIME_WAIT_267_50_MS	0xD6	//time after the latency time during which a second valid tap can begin = 267,5_MS
#define	XL345_WINDOW_TIME_WAIT_268_75_MS	0xD7	//time after the latency time during which a second valid tap can begin = 268,75_MS
#define	XL345_WINDOW_TIME_WAIT_270_00_MS	0xD8	//time after the latency time during which a second valid tap can begin = 270_MS
#define	XL345_WINDOW_TIME_WAIT_271_25_MS	0xD9	//time after the latency time during which a second valid tap can begin = 271,25_MS
#define	XL345_WINDOW_TIME_WAIT_272_50_MS	0xDA	//time after the latency time during which a second valid tap can begin = 272,5_MS
#define	XL345_WINDOW_TIME_WAIT_273_75_MS	0xDB	//time after the latency time during which a second valid tap can begin = 273,75_MS
#define	XL345_WINDOW_TIME_WAIT_275_00_MS	0xDC	//time after the latency time during which a second valid tap can begin = 275_MS
#define	XL345_WINDOW_TIME_WAIT_276_25_MS	0xDD	//time after the latency time during which a second valid tap can begin = 276,25_MS
#define	XL345_WINDOW_TIME_WAIT_277_50_MS	0xDE	//time after the latency time during which a second valid tap can begin = 277,5_MS
#define	XL345_WINDOW_TIME_WAIT_278_75_MS	0xDF	//time after the latency time during which a second valid tap can begin = 278,75_MS
#define	XL345_WINDOW_TIME_WAIT_280_00_MS	0xE0	//time after the latency time during which a second valid tap can begin = 280_MS
#define	XL345_WINDOW_TIME_WAIT_281_25_MS	0xE1	//time after the latency time during which a second valid tap can begin = 281,25_MS
#define	XL345_WINDOW_TIME_WAIT_282_50_MS	0xE2	//time after the latency time during which a second valid tap can begin = 282,5_MS
#define	XL345_WINDOW_TIME_WAIT_283_75_MS	0xE3	//time after the latency time during which a second valid tap can begin = 283,75_MS
#define	XL345_WINDOW_TIME_WAIT_285_00_MS	0xE4	//time after the latency time during which a second valid tap can begin = 285_MS
#define	XL345_WINDOW_TIME_WAIT_286_25_MS	0xE5	//time after the latency time during which a second valid tap can begin = 286,25_MS
#define	XL345_WINDOW_TIME_WAIT_287_50_MS	0xE6	//time after the latency time during which a second valid tap can begin = 287,5_MS
#define	XL345_WINDOW_TIME_WAIT_288_75_MS	0xE7	//time after the latency time during which a second valid tap can begin = 288,75_MS
#define	XL345_WINDOW_TIME_WAIT_290_00_MS	0xE8	//time after the latency time during which a second valid tap can begin = 290_MS
#define	XL345_WINDOW_TIME_WAIT_291_25_MS	0xE9	//time after the latency time during which a second valid tap can begin = 291,25_MS
#define	XL345_WINDOW_TIME_WAIT_292_50_MS	0xEA	//time after the latency time during which a second valid tap can begin = 292,5_MS
#define	XL345_WINDOW_TIME_WAIT_293_75_MS	0xEB	//time after the latency time during which a second valid tap can begin = 293,75_MS
#define	XL345_WINDOW_TIME_WAIT_295_00_MS	0xEC	//time after the latency time during which a second valid tap can begin = 295_MS
#define	XL345_WINDOW_TIME_WAIT_296_25_MS	0xED	//time after the latency time during which a second valid tap can begin = 296,25_MS
#define	XL345_WINDOW_TIME_WAIT_297_50_MS	0xEE	//time after the latency time during which a second valid tap can begin = 297,5_MS
#define	XL345_WINDOW_TIME_WAIT_298_75_MS	0xEF	//time after the latency time during which a second valid tap can begin = 298,75_MS
#define	XL345_WINDOW_TIME_WAIT_300_00_MS	0xF0	//time after the latency time during which a second valid tap can begin = 300_MS
#define	XL345_WINDOW_TIME_WAIT_301_25_MS	0xF1	//time after the latency time during which a second valid tap can begin = 301,25_MS
#define	XL345_WINDOW_TIME_WAIT_302_50_MS	0xF2	//time after the latency time during which a second valid tap can begin = 302,5_MS
#define	XL345_WINDOW_TIME_WAIT_303_75_MS	0xF3	//time after the latency time during which a second valid tap can begin = 303,75_MS
#define	XL345_WINDOW_TIME_WAIT_305_00_MS	0xF4	//time after the latency time during which a second valid tap can begin = 305_MS
#define	XL345_WINDOW_TIME_WAIT_306_25_MS	0xF5	//time after the latency time during which a second valid tap can begin = 306,25_MS
#define	XL345_WINDOW_TIME_WAIT_307_50_MS	0xF6	//time after the latency time during which a second valid tap can begin = 307,5_MS
#define	XL345_WINDOW_TIME_WAIT_308_75_MS	0xF7	//time after the latency time during which a second valid tap can begin = 308,75_MS
#define	XL345_WINDOW_TIME_WAIT_310_00_MS	0xF8	//time after the latency time during which a second valid tap can begin = 310_MS
#define	XL345_WINDOW_TIME_WAIT_311_25_MS	0xF9	//time after the latency time during which a second valid tap can begin = 311,25_MS
#define	XL345_WINDOW_TIME_WAIT_312_50_MS	0xFA	//time after the latency time during which a second valid tap can begin = 312,5_MS
#define	XL345_WINDOW_TIME_WAIT_313_75_MS	0xFB	//time after the latency time during which a second valid tap can begin = 313,75_MS
#define	XL345_WINDOW_TIME_WAIT_315_00_MS	0xFC	//time after the latency time during which a second valid tap can begin = 315_MS
#define	XL345_WINDOW_TIME_WAIT_316_25_MS	0xFD	//time after the latency time during which a second valid tap can begin = 316,25_MS
#define	XL345_WINDOW_TIME_WAIT_317_50_MS	0xFE	//time after the latency time during which a second valid tap can begin = 317,5_MS
#define	XL345_WINDOW_TIME_WAIT_318_75_MS	0xFF	//time after the latency time during which a second valid tap can begin = 318,75_MS


/*
The THRESH_ACT register is eight bits and holds the threshold
value for detecting activity. The data format is unsigned, so the
magnitude of the activity event is compared with the value in
the THRESH_ACT register. The scale factor is 62.5 mg/LSB.
A value of 0 may result in undesirable behavior if the activity
interrupt is enabled.
*/

#define	XL345_TRESH_ACT_VALUE_0_G	0x00	//result in undesirable behavior if the activity
#define	XL345_TRESH_ACT_VALUE_0_06_G	0x01	//threshold value for detecting activity = 0,0625_G
#define	XL345_TRESH_ACT_VALUE_0_13_G	0x02	//threshold value for detecting activity = 0,125_G
#define	XL345_TRESH_ACT_VALUE_0_19_G	0x03	//threshold value for detecting activity = 0,1875_G
#define	XL345_TRESH_ACT_VALUE_0_25_G	0x04	//threshold value for detecting activity = 0,25_G
#define	XL345_TRESH_ACT_VALUE_0_31_G	0x05	//threshold value for detecting activity = 0,3125_G
#define	XL345_TRESH_ACT_VALUE_0_38_G	0x06	//threshold value for detecting activity = 0,375_G
#define	XL345_TRESH_ACT_VALUE_0_44_G	0x07	//threshold value for detecting activity = 0,4375_G
#define	XL345_TRESH_ACT_VALUE_0_50_G	0x08	//threshold value for detecting activity = 0,5_G
#define	XL345_TRESH_ACT_VALUE_0_56_G	0x09	//threshold value for detecting activity = 0,5625_G
#define	XL345_TRESH_ACT_VALUE_0_63_G	0x0A	//threshold value for detecting activity = 0,625_G
#define	XL345_TRESH_ACT_VALUE_0_69_G	0x0B	//threshold value for detecting activity = 0,6875_G
#define	XL345_TRESH_ACT_VALUE_0_75_G	0x0C	//threshold value for detecting activity = 0,75_G
#define	XL345_TRESH_ACT_VALUE_0_81_G	0x0D	//threshold value for detecting activity = 0,8125_G
#define	XL345_TRESH_ACT_VALUE_0_88_G	0x0E	//threshold value for detecting activity = 0,875_G
#define	XL345_TRESH_ACT_VALUE_0_94_G	0x0F	//threshold value for detecting activity = 0,9375_G
#define	XL345_TRESH_ACT_VALUE_1_00_G	0x10	//threshold value for detecting activity = 1_G
#define	XL345_TRESH_ACT_VALUE_1_06_G	0x11	//threshold value for detecting activity = 1,0625_G
#define	XL345_TRESH_ACT_VALUE_1_13_G	0x12	//threshold value for detecting activity = 1,125_G
#define	XL345_TRESH_ACT_VALUE_1_19_G	0x13	//threshold value for detecting activity = 1,1875_G
#define	XL345_TRESH_ACT_VALUE_1_25_G	0x14	//threshold value for detecting activity = 1,25_G
#define	XL345_TRESH_ACT_VALUE_1_31_G	0x15	//threshold value for detecting activity = 1,3125_G
#define	XL345_TRESH_ACT_VALUE_1_38_G	0x16	//threshold value for detecting activity = 1,375_G
#define	XL345_TRESH_ACT_VALUE_1_44_G	0x17	//threshold value for detecting activity = 1,4375_G
#define	XL345_TRESH_ACT_VALUE_1_50_G	0x18	//threshold value for detecting activity = 1,5_G
#define	XL345_TRESH_ACT_VALUE_1_56_G	0x19	//threshold value for detecting activity = 1,5625_G
#define	XL345_TRESH_ACT_VALUE_1_63_G	0x1A	//threshold value for detecting activity = 1,625_G
#define	XL345_TRESH_ACT_VALUE_1_69_G	0x1B	//threshold value for detecting activity = 1,6875_G
#define	XL345_TRESH_ACT_VALUE_1_75_G	0x1C	//threshold value for detecting activity = 1,75_G
#define	XL345_TRESH_ACT_VALUE_1_81_G	0x1D	//threshold value for detecting activity = 1,8125_G
#define	XL345_TRESH_ACT_VALUE_1_88_G	0x1E	//threshold value for detecting activity = 1,875_G
#define	XL345_TRESH_ACT_VALUE_1_94_G	0x1F	//threshold value for detecting activity = 1,9375_G
#define	XL345_TRESH_ACT_VALUE_2_00_G	0x20	//threshold value for detecting activity = 2_G
#define	XL345_TRESH_ACT_VALUE_2_06_G	0x21	//threshold value for detecting activity = 2,0625_G
#define	XL345_TRESH_ACT_VALUE_2_13_G	0x22	//threshold value for detecting activity = 2,125_G
#define	XL345_TRESH_ACT_VALUE_2_19_G	0x23	//threshold value for detecting activity = 2,1875_G
#define	XL345_TRESH_ACT_VALUE_2_25_G	0x24	//threshold value for detecting activity = 2,25_G
#define	XL345_TRESH_ACT_VALUE_2_31_G	0x25	//threshold value for detecting activity = 2,3125_G
#define	XL345_TRESH_ACT_VALUE_2_38_G	0x26	//threshold value for detecting activity = 2,375_G
#define	XL345_TRESH_ACT_VALUE_2_44_G	0x27	//threshold value for detecting activity = 2,4375_G
#define	XL345_TRESH_ACT_VALUE_2_50_G	0x28	//threshold value for detecting activity = 2,5_G
#define	XL345_TRESH_ACT_VALUE_2_56_G	0x29	//threshold value for detecting activity = 2,5625_G
#define	XL345_TRESH_ACT_VALUE_2_63_G	0x2A	//threshold value for detecting activity = 2,625_G
#define	XL345_TRESH_ACT_VALUE_2_69_G	0x2B	//threshold value for detecting activity = 2,6875_G
#define	XL345_TRESH_ACT_VALUE_2_75_G	0x2C	//threshold value for detecting activity = 2,75_G
#define	XL345_TRESH_ACT_VALUE_2_81_G	0x2D	//threshold value for detecting activity = 2,8125_G
#define	XL345_TRESH_ACT_VALUE_2_88_G	0x2E	//threshold value for detecting activity = 2,875_G
#define	XL345_TRESH_ACT_VALUE_2_94_G	0x2F	//threshold value for detecting activity = 2,9375_G
#define	XL345_TRESH_ACT_VALUE_3_00_G	0x30	//threshold value for detecting activity = 3_G
#define	XL345_TRESH_ACT_VALUE_3_06_G	0x31	//threshold value for detecting activity = 3,0625_G
#define	XL345_TRESH_ACT_VALUE_3_13_G	0x32	//threshold value for detecting activity = 3,125_G
#define	XL345_TRESH_ACT_VALUE_3_19_G	0x33	//threshold value for detecting activity = 3,1875_G
#define	XL345_TRESH_ACT_VALUE_3_25_G	0x34	//threshold value for detecting activity = 3,25_G
#define	XL345_TRESH_ACT_VALUE_3_31_G	0x35	//threshold value for detecting activity = 3,3125_G
#define	XL345_TRESH_ACT_VALUE_3_38_G	0x36	//threshold value for detecting activity = 3,375_G
#define	XL345_TRESH_ACT_VALUE_3_44_G	0x37	//threshold value for detecting activity = 3,4375_G
#define	XL345_TRESH_ACT_VALUE_3_50_G	0x38	//threshold value for detecting activity = 3,5_G
#define	XL345_TRESH_ACT_VALUE_3_56_G	0x39	//threshold value for detecting activity = 3,5625_G
#define	XL345_TRESH_ACT_VALUE_3_63_G	0x3A	//threshold value for detecting activity = 3,625_G
#define	XL345_TRESH_ACT_VALUE_3_69_G	0x3B	//threshold value for detecting activity = 3,6875_G
#define	XL345_TRESH_ACT_VALUE_3_75_G	0x3C	//threshold value for detecting activity = 3,75_G
#define	XL345_TRESH_ACT_VALUE_3_81_G	0x3D	//threshold value for detecting activity = 3,8125_G
#define	XL345_TRESH_ACT_VALUE_3_88_G	0x3E	//threshold value for detecting activity = 3,875_G
#define	XL345_TRESH_ACT_VALUE_3_94_G	0x3F	//threshold value for detecting activity = 3,9375_G
#define	XL345_TRESH_ACT_VALUE_4_00_G	0x40	//threshold value for detecting activity = 4_G
#define	XL345_TRESH_ACT_VALUE_4_06_G	0x41	//threshold value for detecting activity = 4,0625_G
#define	XL345_TRESH_ACT_VALUE_4_13_G	0x42	//threshold value for detecting activity = 4,125_G
#define	XL345_TRESH_ACT_VALUE_4_19_G	0x43	//threshold value for detecting activity = 4,1875_G
#define	XL345_TRESH_ACT_VALUE_4_25_G	0x44	//threshold value for detecting activity = 4,25_G
#define	XL345_TRESH_ACT_VALUE_4_31_G	0x45	//threshold value for detecting activity = 4,3125_G
#define	XL345_TRESH_ACT_VALUE_4_38_G	0x46	//threshold value for detecting activity = 4,375_G
#define	XL345_TRESH_ACT_VALUE_4_44_G	0x47	//threshold value for detecting activity = 4,4375_G
#define	XL345_TRESH_ACT_VALUE_4_50_G	0x48	//threshold value for detecting activity = 4,5_G
#define	XL345_TRESH_ACT_VALUE_4_56_G	0x49	//threshold value for detecting activity = 4,5625_G
#define	XL345_TRESH_ACT_VALUE_4_63_G	0x4A	//threshold value for detecting activity = 4,625_G
#define	XL345_TRESH_ACT_VALUE_4_69_G	0x4B	//threshold value for detecting activity = 4,6875_G
#define	XL345_TRESH_ACT_VALUE_4_75_G	0x4C	//threshold value for detecting activity = 4,75_G
#define	XL345_TRESH_ACT_VALUE_4_81_G	0x4D	//threshold value for detecting activity = 4,8125_G
#define	XL345_TRESH_ACT_VALUE_4_88_G	0x4E	//threshold value for detecting activity = 4,875_G
#define	XL345_TRESH_ACT_VALUE_4_94_G	0x4F	//threshold value for detecting activity = 4,9375_G
#define	XL345_TRESH_ACT_VALUE_5_00_G	0x50	//threshold value for detecting activity = 5_G
#define	XL345_TRESH_ACT_VALUE_5_06_G	0x51	//threshold value for detecting activity = 5,0625_G
#define	XL345_TRESH_ACT_VALUE_5_13_G	0x52	//threshold value for detecting activity = 5,125_G
#define	XL345_TRESH_ACT_VALUE_5_19_G	0x53	//threshold value for detecting activity = 5,1875_G
#define	XL345_TRESH_ACT_VALUE_5_25_G	0x54	//threshold value for detecting activity = 5,25_G
#define	XL345_TRESH_ACT_VALUE_5_31_G	0x55	//threshold value for detecting activity = 5,3125_G
#define	XL345_TRESH_ACT_VALUE_5_38_G	0x56	//threshold value for detecting activity = 5,375_G
#define	XL345_TRESH_ACT_VALUE_5_44_G	0x57	//threshold value for detecting activity = 5,4375_G
#define	XL345_TRESH_ACT_VALUE_5_50_G	0x58	//threshold value for detecting activity = 5,5_G
#define	XL345_TRESH_ACT_VALUE_5_56_G	0x59	//threshold value for detecting activity = 5,5625_G
#define	XL345_TRESH_ACT_VALUE_5_63_G	0x5A	//threshold value for detecting activity = 5,625_G
#define	XL345_TRESH_ACT_VALUE_5_69_G	0x5B	//threshold value for detecting activity = 5,6875_G
#define	XL345_TRESH_ACT_VALUE_5_75_G	0x5C	//threshold value for detecting activity = 5,75_G
#define	XL345_TRESH_ACT_VALUE_5_81_G	0x5D	//threshold value for detecting activity = 5,8125_G
#define	XL345_TRESH_ACT_VALUE_5_88_G	0x5E	//threshold value for detecting activity = 5,875_G
#define	XL345_TRESH_ACT_VALUE_5_94_G	0x5F	//threshold value for detecting activity = 5,9375_G
#define	XL345_TRESH_ACT_VALUE_6_00_G	0x60	//threshold value for detecting activity = 6_G
#define	XL345_TRESH_ACT_VALUE_6_06_G	0x61	//threshold value for detecting activity = 6,0625_G
#define	XL345_TRESH_ACT_VALUE_6_13_G	0x62	//threshold value for detecting activity = 6,125_G
#define	XL345_TRESH_ACT_VALUE_6_19_G	0x63	//threshold value for detecting activity = 6,1875_G
#define	XL345_TRESH_ACT_VALUE_6_25_G	0x64	//threshold value for detecting activity = 6,25_G
#define	XL345_TRESH_ACT_VALUE_6_31_G	0x65	//threshold value for detecting activity = 6,3125_G
#define	XL345_TRESH_ACT_VALUE_6_38_G	0x66	//threshold value for detecting activity = 6,375_G
#define	XL345_TRESH_ACT_VALUE_6_44_G	0x67	//threshold value for detecting activity = 6,4375_G
#define	XL345_TRESH_ACT_VALUE_6_50_G	0x68	//threshold value for detecting activity = 6,5_G
#define	XL345_TRESH_ACT_VALUE_6_56_G	0x69	//threshold value for detecting activity = 6,5625_G
#define	XL345_TRESH_ACT_VALUE_6_63_G	0x6A	//threshold value for detecting activity = 6,625_G
#define	XL345_TRESH_ACT_VALUE_6_69_G	0x6B	//threshold value for detecting activity = 6,6875_G
#define	XL345_TRESH_ACT_VALUE_6_75_G	0x6C	//threshold value for detecting activity = 6,75_G
#define	XL345_TRESH_ACT_VALUE_6_81_G	0x6D	//threshold value for detecting activity = 6,8125_G
#define	XL345_TRESH_ACT_VALUE_6_88_G	0x6E	//threshold value for detecting activity = 6,875_G
#define	XL345_TRESH_ACT_VALUE_6_94_G	0x6F	//threshold value for detecting activity = 6,9375_G
#define	XL345_TRESH_ACT_VALUE_7_00_G	0x70	//threshold value for detecting activity = 7_G
#define	XL345_TRESH_ACT_VALUE_7_06_G	0x71	//threshold value for detecting activity = 7,0625_G
#define	XL345_TRESH_ACT_VALUE_7_13_G	0x72	//threshold value for detecting activity = 7,125_G
#define	XL345_TRESH_ACT_VALUE_7_19_G	0x73	//threshold value for detecting activity = 7,1875_G
#define	XL345_TRESH_ACT_VALUE_7_25_G	0x74	//threshold value for detecting activity = 7,25_G
#define	XL345_TRESH_ACT_VALUE_7_31_G	0x75	//threshold value for detecting activity = 7,3125_G
#define	XL345_TRESH_ACT_VALUE_7_38_G	0x76	//threshold value for detecting activity = 7,375_G
#define	XL345_TRESH_ACT_VALUE_7_44_G	0x77	//threshold value for detecting activity = 7,4375_G
#define	XL345_TRESH_ACT_VALUE_7_50_G	0x78	//threshold value for detecting activity = 7,5_G
#define	XL345_TRESH_ACT_VALUE_7_56_G	0x79	//threshold value for detecting activity = 7,5625_G
#define	XL345_TRESH_ACT_VALUE_7_63_G	0x7A	//threshold value for detecting activity = 7,625_G
#define	XL345_TRESH_ACT_VALUE_7_69_G	0x7B	//threshold value for detecting activity = 7,6875_G
#define	XL345_TRESH_ACT_VALUE_7_75_G	0x7C	//threshold value for detecting activity = 7,75_G
#define	XL345_TRESH_ACT_VALUE_7_81_G	0x7D	//threshold value for detecting activity = 7,8125_G
#define	XL345_TRESH_ACT_VALUE_7_88_G	0x7E	//threshold value for detecting activity = 7,875_G
#define	XL345_TRESH_ACT_VALUE_7_94_G	0x7F	//threshold value for detecting activity = 7,9375_G
#define	XL345_TRESH_ACT_VALUE_8_00_G	0x80	//threshold value for detecting activity = 8_G
#define	XL345_TRESH_ACT_VALUE_8_06_G	0x81	//threshold value for detecting activity = 8,0625_G
#define	XL345_TRESH_ACT_VALUE_8_13_G	0x82	//threshold value for detecting activity = 8,125_G
#define	XL345_TRESH_ACT_VALUE_8_19_G	0x83	//threshold value for detecting activity = 8,1875_G
#define	XL345_TRESH_ACT_VALUE_8_25_G	0x84	//threshold value for detecting activity = 8,25_G
#define	XL345_TRESH_ACT_VALUE_8_31_G	0x85	//threshold value for detecting activity = 8,3125_G
#define	XL345_TRESH_ACT_VALUE_8_38_G	0x86	//threshold value for detecting activity = 8,375_G
#define	XL345_TRESH_ACT_VALUE_8_44_G	0x87	//threshold value for detecting activity = 8,4375_G
#define	XL345_TRESH_ACT_VALUE_8_50_G	0x88	//threshold value for detecting activity = 8,5_G
#define	XL345_TRESH_ACT_VALUE_8_56_G	0x89	//threshold value for detecting activity = 8,5625_G
#define	XL345_TRESH_ACT_VALUE_8_63_G	0x8A	//threshold value for detecting activity = 8,625_G
#define	XL345_TRESH_ACT_VALUE_8_69_G	0x8B	//threshold value for detecting activity = 8,6875_G
#define	XL345_TRESH_ACT_VALUE_8_75_G	0x8C	//threshold value for detecting activity = 8,75_G
#define	XL345_TRESH_ACT_VALUE_8_81_G	0x8D	//threshold value for detecting activity = 8,8125_G
#define	XL345_TRESH_ACT_VALUE_8_88_G	0x8E	//threshold value for detecting activity = 8,875_G
#define	XL345_TRESH_ACT_VALUE_8_94_G	0x8F	//threshold value for detecting activity = 8,9375_G
#define	XL345_TRESH_ACT_VALUE_9_00_G	0x90	//threshold value for detecting activity = 9_G
#define	XL345_TRESH_ACT_VALUE_9_06_G	0x91	//threshold value for detecting activity = 9,0625_G
#define	XL345_TRESH_ACT_VALUE_9_13_G	0x92	//threshold value for detecting activity = 9,125_G
#define	XL345_TRESH_ACT_VALUE_9_19_G	0x93	//threshold value for detecting activity = 9,1875_G
#define	XL345_TRESH_ACT_VALUE_9_25_G	0x94	//threshold value for detecting activity = 9,25_G
#define	XL345_TRESH_ACT_VALUE_9_31_G	0x95	//threshold value for detecting activity = 9,3125_G
#define	XL345_TRESH_ACT_VALUE_9_38_G	0x96	//threshold value for detecting activity = 9,375_G
#define	XL345_TRESH_ACT_VALUE_9_44_G	0x97	//threshold value for detecting activity = 9,4375_G
#define	XL345_TRESH_ACT_VALUE_9_50_G	0x98	//threshold value for detecting activity = 9,5_G
#define	XL345_TRESH_ACT_VALUE_9_56_G	0x99	//threshold value for detecting activity = 9,5625_G
#define	XL345_TRESH_ACT_VALUE_9_63_G	0x9A	//threshold value for detecting activity = 9,625_G
#define	XL345_TRESH_ACT_VALUE_9_69_G	0x9B	//threshold value for detecting activity = 9,6875_G
#define	XL345_TRESH_ACT_VALUE_9_75_G	0x9C	//threshold value for detecting activity = 9,75_G
#define	XL345_TRESH_ACT_VALUE_9_81_G	0x9D	//threshold value for detecting activity = 9,8125_G
#define	XL345_TRESH_ACT_VALUE_9_88_G	0x9E	//threshold value for detecting activity = 9,875_G
#define	XL345_TRESH_ACT_VALUE_9_94_G	0x9F	//threshold value for detecting activity = 9,9375_G
#define	XL345_TRESH_ACT_VALUE_10_00_G	0xA0	//threshold value for detecting activity = 10_G
#define	XL345_TRESH_ACT_VALUE_10_06_G	0xA1	//threshold value for detecting activity = 10,0625_G
#define	XL345_TRESH_ACT_VALUE_10_13_G	0xA2	//threshold value for detecting activity = 10,125_G
#define	XL345_TRESH_ACT_VALUE_10_19_G	0xA3	//threshold value for detecting activity = 10,1875_G
#define	XL345_TRESH_ACT_VALUE_10_25_G	0xA4	//threshold value for detecting activity = 10,25_G
#define	XL345_TRESH_ACT_VALUE_10_31_G	0xA5	//threshold value for detecting activity = 10,3125_G
#define	XL345_TRESH_ACT_VALUE_10_38_G	0xA6	//threshold value for detecting activity = 10,375_G
#define	XL345_TRESH_ACT_VALUE_10_44_G	0xA7	//threshold value for detecting activity = 10,4375_G
#define	XL345_TRESH_ACT_VALUE_10_50_G	0xA8	//threshold value for detecting activity = 10,5_G
#define	XL345_TRESH_ACT_VALUE_10_56_G	0xA9	//threshold value for detecting activity = 10,5625_G
#define	XL345_TRESH_ACT_VALUE_10_63_G	0xAA	//threshold value for detecting activity = 10,625_G
#define	XL345_TRESH_ACT_VALUE_10_69_G	0xAB	//threshold value for detecting activity = 10,6875_G
#define	XL345_TRESH_ACT_VALUE_10_75_G	0xAC	//threshold value for detecting activity = 10,75_G
#define	XL345_TRESH_ACT_VALUE_10_81_G	0xAD	//threshold value for detecting activity = 10,8125_G
#define	XL345_TRESH_ACT_VALUE_10_88_G	0xAE	//threshold value for detecting activity = 10,875_G
#define	XL345_TRESH_ACT_VALUE_10_94_G	0xAF	//threshold value for detecting activity = 10,9375_G
#define	XL345_TRESH_ACT_VALUE_11_00_G	0xB0	//threshold value for detecting activity = 11_G
#define	XL345_TRESH_ACT_VALUE_11_06_G	0xB1	//threshold value for detecting activity = 11,0625_G
#define	XL345_TRESH_ACT_VALUE_11_13_G	0xB2	//threshold value for detecting activity = 11,125_G
#define	XL345_TRESH_ACT_VALUE_11_19_G	0xB3	//threshold value for detecting activity = 11,1875_G
#define	XL345_TRESH_ACT_VALUE_11_25_G	0xB4	//threshold value for detecting activity = 11,25_G
#define	XL345_TRESH_ACT_VALUE_11_31_G	0xB5	//threshold value for detecting activity = 11,3125_G
#define	XL345_TRESH_ACT_VALUE_11_38_G	0xB6	//threshold value for detecting activity = 11,375_G
#define	XL345_TRESH_ACT_VALUE_11_44_G	0xB7	//threshold value for detecting activity = 11,4375_G
#define	XL345_TRESH_ACT_VALUE_11_50_G	0xB8	//threshold value for detecting activity = 11,5_G
#define	XL345_TRESH_ACT_VALUE_11_56_G	0xB9	//threshold value for detecting activity = 11,5625_G
#define	XL345_TRESH_ACT_VALUE_11_63_G	0xBA	//threshold value for detecting activity = 11,625_G
#define	XL345_TRESH_ACT_VALUE_11_69_G	0xBB	//threshold value for detecting activity = 11,6875_G
#define	XL345_TRESH_ACT_VALUE_11_75_G	0xBC	//threshold value for detecting activity = 11,75_G
#define	XL345_TRESH_ACT_VALUE_11_81_G	0xBD	//threshold value for detecting activity = 11,8125_G
#define	XL345_TRESH_ACT_VALUE_11_88_G	0xBE	//threshold value for detecting activity = 11,875_G
#define	XL345_TRESH_ACT_VALUE_11_94_G	0xBF	//threshold value for detecting activity = 11,9375_G
#define	XL345_TRESH_ACT_VALUE_12_00_G	0xC0	//threshold value for detecting activity = 12_G
#define	XL345_TRESH_ACT_VALUE_12_06_G	0xC1	//threshold value for detecting activity = 12,0625_G
#define	XL345_TRESH_ACT_VALUE_12_13_G	0xC2	//threshold value for detecting activity = 12,125_G
#define	XL345_TRESH_ACT_VALUE_12_19_G	0xC3	//threshold value for detecting activity = 12,1875_G
#define	XL345_TRESH_ACT_VALUE_12_25_G	0xC4	//threshold value for detecting activity = 12,25_G
#define	XL345_TRESH_ACT_VALUE_12_31_G	0xC5	//threshold value for detecting activity = 12,3125_G
#define	XL345_TRESH_ACT_VALUE_12_38_G	0xC6	//threshold value for detecting activity = 12,375_G
#define	XL345_TRESH_ACT_VALUE_12_44_G	0xC7	//threshold value for detecting activity = 12,4375_G
#define	XL345_TRESH_ACT_VALUE_12_50_G	0xC8	//threshold value for detecting activity = 12,5_G
#define	XL345_TRESH_ACT_VALUE_12_56_G	0xC9	//threshold value for detecting activity = 12,5625_G
#define	XL345_TRESH_ACT_VALUE_12_63_G	0xCA	//threshold value for detecting activity = 12,625_G
#define	XL345_TRESH_ACT_VALUE_12_69_G	0xCB	//threshold value for detecting activity = 12,6875_G
#define	XL345_TRESH_ACT_VALUE_12_75_G	0xCC	//threshold value for detecting activity = 12,75_G
#define	XL345_TRESH_ACT_VALUE_12_81_G	0xCD	//threshold value for detecting activity = 12,8125_G
#define	XL345_TRESH_ACT_VALUE_12_88_G	0xCE	//threshold value for detecting activity = 12,875_G
#define	XL345_TRESH_ACT_VALUE_12_94_G	0xCF	//threshold value for detecting activity = 12,9375_G
#define	XL345_TRESH_ACT_VALUE_13_00_G	0xD0	//threshold value for detecting activity = 13_G
#define	XL345_TRESH_ACT_VALUE_13_06_G	0xD1	//threshold value for detecting activity = 13,0625_G
#define	XL345_TRESH_ACT_VALUE_13_13_G	0xD2	//threshold value for detecting activity = 13,125_G
#define	XL345_TRESH_ACT_VALUE_13_19_G	0xD3	//threshold value for detecting activity = 13,1875_G
#define	XL345_TRESH_ACT_VALUE_13_25_G	0xD4	//threshold value for detecting activity = 13,25_G
#define	XL345_TRESH_ACT_VALUE_13_31_G	0xD5	//threshold value for detecting activity = 13,3125_G
#define	XL345_TRESH_ACT_VALUE_13_38_G	0xD6	//threshold value for detecting activity = 13,375_G
#define	XL345_TRESH_ACT_VALUE_13_44_G	0xD7	//threshold value for detecting activity = 13,4375_G
#define	XL345_TRESH_ACT_VALUE_13_50_G	0xD8	//threshold value for detecting activity = 13,5_G
#define	XL345_TRESH_ACT_VALUE_13_56_G	0xD9	//threshold value for detecting activity = 13,5625_G
#define	XL345_TRESH_ACT_VALUE_13_63_G	0xDA	//threshold value for detecting activity = 13,625_G
#define	XL345_TRESH_ACT_VALUE_13_69_G	0xDB	//threshold value for detecting activity = 13,6875_G
#define	XL345_TRESH_ACT_VALUE_13_75_G	0xDC	//threshold value for detecting activity = 13,75_G
#define	XL345_TRESH_ACT_VALUE_13_81_G	0xDD	//threshold value for detecting activity = 13,8125_G
#define	XL345_TRESH_ACT_VALUE_13_88_G	0xDE	//threshold value for detecting activity = 13,875_G
#define	XL345_TRESH_ACT_VALUE_13_94_G	0xDF	//threshold value for detecting activity = 13,9375_G
#define	XL345_TRESH_ACT_VALUE_14_00_G	0xE0	//threshold value for detecting activity = 14_G
#define	XL345_TRESH_ACT_VALUE_14_06_G	0xE1	//threshold value for detecting activity = 14,0625_G
#define	XL345_TRESH_ACT_VALUE_14_13_G	0xE2	//threshold value for detecting activity = 14,125_G
#define	XL345_TRESH_ACT_VALUE_14_19_G	0xE3	//threshold value for detecting activity = 14,1875_G
#define	XL345_TRESH_ACT_VALUE_14_25_G	0xE4	//threshold value for detecting activity = 14,25_G
#define	XL345_TRESH_ACT_VALUE_14_31_G	0xE5	//threshold value for detecting activity = 14,3125_G
#define	XL345_TRESH_ACT_VALUE_14_38_G	0xE6	//threshold value for detecting activity = 14,375_G
#define	XL345_TRESH_ACT_VALUE_14_44_G	0xE7	//threshold value for detecting activity = 14,4375_G
#define	XL345_TRESH_ACT_VALUE_14_50_G	0xE8	//threshold value for detecting activity = 14,5_G
#define	XL345_TRESH_ACT_VALUE_14_56_G	0xE9	//threshold value for detecting activity = 14,5625_G
#define	XL345_TRESH_ACT_VALUE_14_63_G	0xEA	//threshold value for detecting activity = 14,625_G
#define	XL345_TRESH_ACT_VALUE_14_69_G	0xEB	//threshold value for detecting activity = 14,6875_G
#define	XL345_TRESH_ACT_VALUE_14_75_G	0xEC	//threshold value for detecting activity = 14,75_G
#define	XL345_TRESH_ACT_VALUE_14_81_G	0xED	//threshold value for detecting activity = 14,8125_G
#define	XL345_TRESH_ACT_VALUE_14_88_G	0xEE	//threshold value for detecting activity = 14,875_G
#define	XL345_TRESH_ACT_VALUE_14_94_G	0xEF	//threshold value for detecting activity = 14,9375_G
#define	XL345_TRESH_ACT_VALUE_15_00_G	0xF0	//threshold value for detecting activity = 15_G
#define	XL345_TRESH_ACT_VALUE_15_06_G	0xF1	//threshold value for detecting activity = 15,0625_G
#define	XL345_TRESH_ACT_VALUE_15_13_G	0xF2	//threshold value for detecting activity = 15,125_G
#define	XL345_TRESH_ACT_VALUE_15_19_G	0xF3	//threshold value for detecting activity = 15,1875_G
#define	XL345_TRESH_ACT_VALUE_15_25_G	0xF4	//threshold value for detecting activity = 15,25_G
#define	XL345_TRESH_ACT_VALUE_15_31_G	0xF5	//threshold value for detecting activity = 15,3125_G
#define	XL345_TRESH_ACT_VALUE_15_38_G	0xF6	//threshold value for detecting activity = 15,375_G
#define	XL345_TRESH_ACT_VALUE_15_44_G	0xF7	//threshold value for detecting activity = 15,4375_G
#define	XL345_TRESH_ACT_VALUE_15_50_G	0xF8	//threshold value for detecting activity = 15,5_G
#define	XL345_TRESH_ACT_VALUE_15_56_G	0xF9	//threshold value for detecting activity = 15,5625_G
#define	XL345_TRESH_ACT_VALUE_15_63_G	0xFA	//threshold value for detecting activity = 15,625_G
#define	XL345_TRESH_ACT_VALUE_15_69_G	0xFB	//threshold value for detecting activity = 15,6875_G
#define	XL345_TRESH_ACT_VALUE_15_75_G	0xFC	//threshold value for detecting activity = 15,75_G
#define	XL345_TRESH_ACT_VALUE_15_81_G	0xFD	//threshold value for detecting activity = 15,8125_G
#define	XL345_TRESH_ACT_VALUE_15_88_G	0xFE	//threshold value for detecting activity = 15,875_G
#define	XL345_TRESH_ACT_VALUE_15_94_G	0xFF	//threshold value for detecting activity = 15,9375_G


/*
The THRESH_INACT register is eight bits and holds the threshold
value for detecting inactivity. The data format is unsigned, so
the magnitude of the inactivity event is compared with the value
in the THRESH_INACT register. The scale factor is 62.5 mg/LSB.
A value of 0 may result in undesirable behavior if the inactivity
interrupt is enabled.
*/

#define	XL345_TRESH_INACT_VALUE_0_G           0x00	//threshold value for detecting inactivity = 0_G
#define	XL345_TRESH_INACT_VALUE_0_06_G	0x01	//threshold value for detecting inactivity = 0,0625_G
#define	XL345_TRESH_INACT_VALUE_0_13_G	0x02	//threshold value for detecting inactivity = 0,125_G
#define	XL345_TRESH_INACT_VALUE_0_19_G	0x03	//threshold value for detecting inactivity = 0,1875_G
#define	XL345_TRESH_INACT_VALUE_0_25_G	0x04	//threshold value for detecting inactivity = 0,25_G
#define	XL345_TRESH_INACT_VALUE_0_31_G	0x05	//threshold value for detecting inactivity = 0,3125_G
#define	XL345_TRESH_INACT_VALUE_0_38_G	0x06	//threshold value for detecting inactivity = 0,375_G
#define	XL345_TRESH_INACT_VALUE_0_44_G	0x07	//threshold value for detecting inactivity = 0,4375_G
#define	XL345_TRESH_INACT_VALUE_0_50_G	0x08	//threshold value for detecting inactivity = 0,5_G
#define	XL345_TRESH_INACT_VALUE_0_56_G	0x09	//threshold value for detecting inactivity = 0,5625_G
#define	XL345_TRESH_INACT_VALUE_0_63_G	0x0A	//threshold value for detecting inactivity = 0,625_G
#define	XL345_TRESH_INACT_VALUE_0_69_G	0x0B	//threshold value for detecting inactivity = 0,6875_G
#define	XL345_TRESH_INACT_VALUE_0_75_G	0x0C	//threshold value for detecting inactivity = 0,75_G
#define	XL345_TRESH_INACT_VALUE_0_81_G	0x0D	//threshold value for detecting inactivity = 0,8125_G
#define	XL345_TRESH_INACT_VALUE_0_88_G	0x0E	//threshold value for detecting inactivity = 0,875_G
#define	XL345_TRESH_INACT_VALUE_0_94_G	0x0F	//threshold value for detecting inactivity = 0,9375_G
#define	XL345_TRESH_INACT_VALUE_1_00_G	0x10	//threshold value for detecting inactivity = 1_G
#define	XL345_TRESH_INACT_VALUE_1_06_G	0x11	//threshold value for detecting inactivity = 1,0625_G
#define	XL345_TRESH_INACT_VALUE_1_13_G	0x12	//threshold value for detecting inactivity = 1,125_G
#define	XL345_TRESH_INACT_VALUE_1_19_G	0x13	//threshold value for detecting inactivity = 1,1875_G
#define	XL345_TRESH_INACT_VALUE_1_25_G	0x14	//threshold value for detecting inactivity = 1,25_G
#define	XL345_TRESH_INACT_VALUE_1_31_G	0x15	//threshold value for detecting inactivity = 1,3125_G
#define	XL345_TRESH_INACT_VALUE_1_38_G	0x16	//threshold value for detecting inactivity = 1,375_G
#define	XL345_TRESH_INACT_VALUE_1_44_G	0x17	//threshold value for detecting inactivity = 1,4375_G
#define	XL345_TRESH_INACT_VALUE_1_50_G	0x18	//threshold value for detecting inactivity = 1,5_G
#define	XL345_TRESH_INACT_VALUE_1_56_G	0x19	//threshold value for detecting inactivity = 1,5625_G
#define	XL345_TRESH_INACT_VALUE_1_63_G	0x1A	//threshold value for detecting inactivity = 1,625_G
#define	XL345_TRESH_INACT_VALUE_1_69_G	0x1B	//threshold value for detecting inactivity = 1,6875_G
#define	XL345_TRESH_INACT_VALUE_1_75_G	0x1C	//threshold value for detecting inactivity = 1,75_G
#define	XL345_TRESH_INACT_VALUE_1_81_G	0x1D	//threshold value for detecting inactivity = 1,8125_G
#define	XL345_TRESH_INACT_VALUE_1_88_G	0x1E	//threshold value for detecting inactivity = 1,875_G
#define	XL345_TRESH_INACT_VALUE_1_94_G	0x1F	//threshold value for detecting inactivity = 1,9375_G
#define	XL345_TRESH_INACT_VALUE_2_00_G	0x20	//threshold value for detecting inactivity = 2_G
#define	XL345_TRESH_INACT_VALUE_2_06_G	0x21	//threshold value for detecting inactivity = 2,0625_G
#define	XL345_TRESH_INACT_VALUE_2_13_G	0x22	//threshold value for detecting inactivity = 2,125_G
#define	XL345_TRESH_INACT_VALUE_2_19_G	0x23	//threshold value for detecting inactivity = 2,1875_G
#define	XL345_TRESH_INACT_VALUE_2_25_G	0x24	//threshold value for detecting inactivity = 2,25_G
#define	XL345_TRESH_INACT_VALUE_2_31_G	0x25	//threshold value for detecting inactivity = 2,3125_G
#define	XL345_TRESH_INACT_VALUE_2_38_G	0x26	//threshold value for detecting inactivity = 2,375_G
#define	XL345_TRESH_INACT_VALUE_2_44_G	0x27	//threshold value for detecting inactivity = 2,4375_G
#define	XL345_TRESH_INACT_VALUE_2_50_G	0x28	//threshold value for detecting inactivity = 2,5_G
#define	XL345_TRESH_INACT_VALUE_2_56_G	0x29	//threshold value for detecting inactivity = 2,5625_G
#define	XL345_TRESH_INACT_VALUE_2_63_G	0x2A	//threshold value for detecting inactivity = 2,625_G
#define	XL345_TRESH_INACT_VALUE_2_69_G	0x2B	//threshold value for detecting inactivity = 2,6875_G
#define	XL345_TRESH_INACT_VALUE_2_75_G	0x2C	//threshold value for detecting inactivity = 2,75_G
#define	XL345_TRESH_INACT_VALUE_2_81_G	0x2D	//threshold value for detecting inactivity = 2,8125_G
#define	XL345_TRESH_INACT_VALUE_2_88_G	0x2E	//threshold value for detecting inactivity = 2,875_G
#define	XL345_TRESH_INACT_VALUE_2_94_G	0x2F	//threshold value for detecting inactivity = 2,9375_G
#define	XL345_TRESH_INACT_VALUE_3_00_G	0x30	//threshold value for detecting inactivity = 3_G
#define	XL345_TRESH_INACT_VALUE_3_06_G	0x31	//threshold value for detecting inactivity = 3,0625_G
#define	XL345_TRESH_INACT_VALUE_3_13_G	0x32	//threshold value for detecting inactivity = 3,125_G
#define	XL345_TRESH_INACT_VALUE_3_19_G	0x33	//threshold value for detecting inactivity = 3,1875_G
#define	XL345_TRESH_INACT_VALUE_3_25_G	0x34	//threshold value for detecting inactivity = 3,25_G
#define	XL345_TRESH_INACT_VALUE_3_31_G	0x35	//threshold value for detecting inactivity = 3,3125_G
#define	XL345_TRESH_INACT_VALUE_3_38_G	0x36	//threshold value for detecting inactivity = 3,375_G
#define	XL345_TRESH_INACT_VALUE_3_44_G	0x37	//threshold value for detecting inactivity = 3,4375_G
#define	XL345_TRESH_INACT_VALUE_3_50_G	0x38	//threshold value for detecting inactivity = 3,5_G
#define	XL345_TRESH_INACT_VALUE_3_56_G	0x39	//threshold value for detecting inactivity = 3,5625_G
#define	XL345_TRESH_INACT_VALUE_3_63_G	0x3A	//threshold value for detecting inactivity = 3,625_G
#define	XL345_TRESH_INACT_VALUE_3_69_G	0x3B	//threshold value for detecting inactivity = 3,6875_G
#define	XL345_TRESH_INACT_VALUE_3_75_G	0x3C	//threshold value for detecting inactivity = 3,75_G
#define	XL345_TRESH_INACT_VALUE_3_81_G	0x3D	//threshold value for detecting inactivity = 3,8125_G
#define	XL345_TRESH_INACT_VALUE_3_88_G	0x3E	//threshold value for detecting inactivity = 3,875_G
#define	XL345_TRESH_INACT_VALUE_3_94_G	0x3F	//threshold value for detecting inactivity = 3,9375_G
#define	XL345_TRESH_INACT_VALUE_4_00_G	0x40	//threshold value for detecting inactivity = 4_G
#define	XL345_TRESH_INACT_VALUE_4_06_G	0x41	//threshold value for detecting inactivity = 4,0625_G
#define	XL345_TRESH_INACT_VALUE_4_13_G	0x42	//threshold value for detecting inactivity = 4,125_G
#define	XL345_TRESH_INACT_VALUE_4_19_G	0x43	//threshold value for detecting inactivity = 4,1875_G
#define	XL345_TRESH_INACT_VALUE_4_25_G	0x44	//threshold value for detecting inactivity = 4,25_G
#define	XL345_TRESH_INACT_VALUE_4_31_G	0x45	//threshold value for detecting inactivity = 4,3125_G
#define	XL345_TRESH_INACT_VALUE_4_38_G	0x46	//threshold value for detecting inactivity = 4,375_G
#define	XL345_TRESH_INACT_VALUE_4_44_G	0x47	//threshold value for detecting inactivity = 4,4375_G
#define	XL345_TRESH_INACT_VALUE_4_50_G	0x48	//threshold value for detecting inactivity = 4,5_G
#define	XL345_TRESH_INACT_VALUE_4_56_G	0x49	//threshold value for detecting inactivity = 4,5625_G
#define	XL345_TRESH_INACT_VALUE_4_63_G	0x4A	//threshold value for detecting inactivity = 4,625_G
#define	XL345_TRESH_INACT_VALUE_4_69_G	0x4B	//threshold value for detecting inactivity = 4,6875_G
#define	XL345_TRESH_INACT_VALUE_4_75_G	0x4C	//threshold value for detecting inactivity = 4,75_G
#define	XL345_TRESH_INACT_VALUE_4_81_G	0x4D	//threshold value for detecting inactivity = 4,8125_G
#define	XL345_TRESH_INACT_VALUE_4_88_G	0x4E	//threshold value for detecting inactivity = 4,875_G
#define	XL345_TRESH_INACT_VALUE_4_94_G	0x4F	//threshold value for detecting inactivity = 4,9375_G
#define	XL345_TRESH_INACT_VALUE_5_00_G	0x50	//threshold value for detecting inactivity = 5_G
#define	XL345_TRESH_INACT_VALUE_5_06_G	0x51	//threshold value for detecting inactivity = 5,0625_G
#define	XL345_TRESH_INACT_VALUE_5_13_G	0x52	//threshold value for detecting inactivity = 5,125_G
#define	XL345_TRESH_INACT_VALUE_5_19_G	0x53	//threshold value for detecting inactivity = 5,1875_G
#define	XL345_TRESH_INACT_VALUE_5_25_G	0x54	//threshold value for detecting inactivity = 5,25_G
#define	XL345_TRESH_INACT_VALUE_5_31_G	0x55	//threshold value for detecting inactivity = 5,3125_G
#define	XL345_TRESH_INACT_VALUE_5_38_G	0x56	//threshold value for detecting inactivity = 5,375_G
#define	XL345_TRESH_INACT_VALUE_5_44_G	0x57	//threshold value for detecting inactivity = 5,4375_G
#define	XL345_TRESH_INACT_VALUE_5_50_G	0x58	//threshold value for detecting inactivity = 5,5_G
#define	XL345_TRESH_INACT_VALUE_5_56_G	0x59	//threshold value for detecting inactivity = 5,5625_G
#define	XL345_TRESH_INACT_VALUE_5_63_G	0x5A	//threshold value for detecting inactivity = 5,625_G
#define	XL345_TRESH_INACT_VALUE_5_69_G	0x5B	//threshold value for detecting inactivity = 5,6875_G
#define	XL345_TRESH_INACT_VALUE_5_75_G	0x5C	//threshold value for detecting inactivity = 5,75_G
#define	XL345_TRESH_INACT_VALUE_5_81_G	0x5D	//threshold value for detecting inactivity = 5,8125_G
#define	XL345_TRESH_INACT_VALUE_5_88_G	0x5E	//threshold value for detecting inactivity = 5,875_G
#define	XL345_TRESH_INACT_VALUE_5_94_G	0x5F	//threshold value for detecting inactivity = 5,9375_G
#define	XL345_TRESH_INACT_VALUE_6_00_G	0x60	//threshold value for detecting inactivity = 6_G
#define	XL345_TRESH_INACT_VALUE_6_06_G	0x61	//threshold value for detecting inactivity = 6,0625_G
#define	XL345_TRESH_INACT_VALUE_6_13_G	0x62	//threshold value for detecting inactivity = 6,125_G
#define	XL345_TRESH_INACT_VALUE_6_19_G	0x63	//threshold value for detecting inactivity = 6,1875_G
#define	XL345_TRESH_INACT_VALUE_6_25_G	0x64	//threshold value for detecting inactivity = 6,25_G
#define	XL345_TRESH_INACT_VALUE_6_31_G	0x65	//threshold value for detecting inactivity = 6,3125_G
#define	XL345_TRESH_INACT_VALUE_6_38_G	0x66	//threshold value for detecting inactivity = 6,375_G
#define	XL345_TRESH_INACT_VALUE_6_44_G	0x67	//threshold value for detecting inactivity = 6,4375_G
#define	XL345_TRESH_INACT_VALUE_6_50_G	0x68	//threshold value for detecting inactivity = 6,5_G
#define	XL345_TRESH_INACT_VALUE_6_56_G	0x69	//threshold value for detecting inactivity = 6,5625_G
#define	XL345_TRESH_INACT_VALUE_6_63_G	0x6A	//threshold value for detecting inactivity = 6,625_G
#define	XL345_TRESH_INACT_VALUE_6_69_G	0x6B	//threshold value for detecting inactivity = 6,6875_G
#define	XL345_TRESH_INACT_VALUE_6_75_G	0x6C	//threshold value for detecting inactivity = 6,75_G
#define	XL345_TRESH_INACT_VALUE_6_81_G	0x6D	//threshold value for detecting inactivity = 6,8125_G
#define	XL345_TRESH_INACT_VALUE_6_88_G	0x6E	//threshold value for detecting inactivity = 6,875_G
#define	XL345_TRESH_INACT_VALUE_6_94_G	0x6F	//threshold value for detecting inactivity = 6,9375_G
#define	XL345_TRESH_INACT_VALUE_7_00_G	0x70	//threshold value for detecting inactivity = 7_G
#define	XL345_TRESH_INACT_VALUE_7_06_G	0x71	//threshold value for detecting inactivity = 7,0625_G
#define	XL345_TRESH_INACT_VALUE_7_13_G	0x72	//threshold value for detecting inactivity = 7,125_G
#define	XL345_TRESH_INACT_VALUE_7_19_G	0x73	//threshold value for detecting inactivity = 7,1875_G
#define	XL345_TRESH_INACT_VALUE_7_25_G	0x74	//threshold value for detecting inactivity = 7,25_G
#define	XL345_TRESH_INACT_VALUE_7_31_G	0x75	//threshold value for detecting inactivity = 7,3125_G
#define	XL345_TRESH_INACT_VALUE_7_38_G	0x76	//threshold value for detecting inactivity = 7,375_G
#define	XL345_TRESH_INACT_VALUE_7_44_G	0x77	//threshold value for detecting inactivity = 7,4375_G
#define	XL345_TRESH_INACT_VALUE_7_50_G	0x78	//threshold value for detecting inactivity = 7,5_G
#define	XL345_TRESH_INACT_VALUE_7_56_G	0x79	//threshold value for detecting inactivity = 7,5625_G
#define	XL345_TRESH_INACT_VALUE_7_63_G	0x7A	//threshold value for detecting inactivity = 7,625_G
#define	XL345_TRESH_INACT_VALUE_7_69_G	0x7B	//threshold value for detecting inactivity = 7,6875_G
#define	XL345_TRESH_INACT_VALUE_7_75_G	0x7C	//threshold value for detecting inactivity = 7,75_G
#define	XL345_TRESH_INACT_VALUE_7_81_G	0x7D	//threshold value for detecting inactivity = 7,8125_G
#define	XL345_TRESH_INACT_VALUE_7_88_G	0x7E	//threshold value for detecting inactivity = 7,875_G
#define	XL345_TRESH_INACT_VALUE_7_94_G	0x7F	//threshold value for detecting inactivity = 7,9375_G
#define	XL345_TRESH_INACT_VALUE_8_00_G	0x80	//threshold value for detecting inactivity = 8_G
#define	XL345_TRESH_INACT_VALUE_8_06_G	0x81	//threshold value for detecting inactivity = 8,0625_G
#define	XL345_TRESH_INACT_VALUE_8_13_G	0x82	//threshold value for detecting inactivity = 8,125_G
#define	XL345_TRESH_INACT_VALUE_8_19_G	0x83	//threshold value for detecting inactivity = 8,1875_G
#define	XL345_TRESH_INACT_VALUE_8_25_G	0x84	//threshold value for detecting inactivity = 8,25_G
#define	XL345_TRESH_INACT_VALUE_8_31_G	0x85	//threshold value for detecting inactivity = 8,3125_G
#define	XL345_TRESH_INACT_VALUE_8_38_G	0x86	//threshold value for detecting inactivity = 8,375_G
#define	XL345_TRESH_INACT_VALUE_8_44_G	0x87	//threshold value for detecting inactivity = 8,4375_G
#define	XL345_TRESH_INACT_VALUE_8_50_G	0x88	//threshold value for detecting inactivity = 8,5_G
#define	XL345_TRESH_INACT_VALUE_8_56_G	0x89	//threshold value for detecting inactivity = 8,5625_G
#define	XL345_TRESH_INACT_VALUE_8_63_G	0x8A	//threshold value for detecting inactivity = 8,625_G
#define	XL345_TRESH_INACT_VALUE_8_69_G	0x8B	//threshold value for detecting inactivity = 8,6875_G
#define	XL345_TRESH_INACT_VALUE_8_75_G	0x8C	//threshold value for detecting inactivity = 8,75_G
#define	XL345_TRESH_INACT_VALUE_8_81_G	0x8D	//threshold value for detecting inactivity = 8,8125_G
#define	XL345_TRESH_INACT_VALUE_8_88_G	0x8E	//threshold value for detecting inactivity = 8,875_G
#define	XL345_TRESH_INACT_VALUE_8_94_G	0x8F	//threshold value for detecting inactivity = 8,9375_G
#define	XL345_TRESH_INACT_VALUE_9_00_G	0x90	//threshold value for detecting inactivity = 9_G
#define	XL345_TRESH_INACT_VALUE_9_06_G	0x91	//threshold value for detecting inactivity = 9,0625_G
#define	XL345_TRESH_INACT_VALUE_9_13_G	0x92	//threshold value for detecting inactivity = 9,125_G
#define	XL345_TRESH_INACT_VALUE_9_19_G	0x93	//threshold value for detecting inactivity = 9,1875_G
#define	XL345_TRESH_INACT_VALUE_9_25_G	0x94	//threshold value for detecting inactivity = 9,25_G
#define	XL345_TRESH_INACT_VALUE_9_31_G	0x95	//threshold value for detecting inactivity = 9,3125_G
#define	XL345_TRESH_INACT_VALUE_9_38_G	0x96	//threshold value for detecting inactivity = 9,375_G
#define	XL345_TRESH_INACT_VALUE_9_44_G	0x97	//threshold value for detecting inactivity = 9,4375_G
#define	XL345_TRESH_INACT_VALUE_9_50_G	0x98	//threshold value for detecting inactivity = 9,5_G
#define	XL345_TRESH_INACT_VALUE_9_56_G	0x99	//threshold value for detecting inactivity = 9,5625_G
#define	XL345_TRESH_INACT_VALUE_9_63_G	0x9A	//threshold value for detecting inactivity = 9,625_G
#define	XL345_TRESH_INACT_VALUE_9_69_G	0x9B	//threshold value for detecting inactivity = 9,6875_G
#define	XL345_TRESH_INACT_VALUE_9_75_G	0x9C	//threshold value for detecting inactivity = 9,75_G
#define	XL345_TRESH_INACT_VALUE_9_81_G	0x9D	//threshold value for detecting inactivity = 9,8125_G
#define	XL345_TRESH_INACT_VALUE_9_88_G	0x9E	//threshold value for detecting inactivity = 9,875_G
#define	XL345_TRESH_INACT_VALUE_9_94_G	0x9F	//threshold value for detecting inactivity = 9,9375_G
#define	XL345_TRESH_INACT_VALUE_10_00_G	0xA0	//threshold value for detecting inactivity = 10_G
#define	XL345_TRESH_INACT_VALUE_10_06_G	0xA1	//threshold value for detecting inactivity = 10,0625_G
#define	XL345_TRESH_INACT_VALUE_10_13_G	0xA2	//threshold value for detecting inactivity = 10,125_G
#define	XL345_TRESH_INACT_VALUE_10_19_G	0xA3	//threshold value for detecting inactivity = 10,1875_G
#define	XL345_TRESH_INACT_VALUE_10_25_G	0xA4	//threshold value for detecting inactivity = 10,25_G
#define	XL345_TRESH_INACT_VALUE_10_31_G	0xA5	//threshold value for detecting inactivity = 10,3125_G
#define	XL345_TRESH_INACT_VALUE_10_38_G	0xA6	//threshold value for detecting inactivity = 10,375_G
#define	XL345_TRESH_INACT_VALUE_10_44_G	0xA7	//threshold value for detecting inactivity = 10,4375_G
#define	XL345_TRESH_INACT_VALUE_10_50_G	0xA8	//threshold value for detecting inactivity = 10,5_G
#define	XL345_TRESH_INACT_VALUE_10_56_G	0xA9	//threshold value for detecting inactivity = 10,5625_G
#define	XL345_TRESH_INACT_VALUE_10_63_G	0xAA	//threshold value for detecting inactivity = 10,625_G
#define	XL345_TRESH_INACT_VALUE_10_69_G	0xAB	//threshold value for detecting inactivity = 10,6875_G
#define	XL345_TRESH_INACT_VALUE_10_75_G	0xAC	//threshold value for detecting inactivity = 10,75_G
#define	XL345_TRESH_INACT_VALUE_10_81_G	0xAD	//threshold value for detecting inactivity = 10,8125_G
#define	XL345_TRESH_INACT_VALUE_10_88_G	0xAE	//threshold value for detecting inactivity = 10,875_G
#define	XL345_TRESH_INACT_VALUE_10_94_G	0xAF	//threshold value for detecting inactivity = 10,9375_G
#define	XL345_TRESH_INACT_VALUE_11_00_G	0xB0	//threshold value for detecting inactivity = 11_G
#define	XL345_TRESH_INACT_VALUE_11_06_G	0xB1	//threshold value for detecting inactivity = 11,0625_G
#define	XL345_TRESH_INACT_VALUE_11_13_G	0xB2	//threshold value for detecting inactivity = 11,125_G
#define	XL345_TRESH_INACT_VALUE_11_19_G	0xB3	//threshold value for detecting inactivity = 11,1875_G
#define	XL345_TRESH_INACT_VALUE_11_25_G	0xB4	//threshold value for detecting inactivity = 11,25_G
#define	XL345_TRESH_INACT_VALUE_11_31_G	0xB5	//threshold value for detecting inactivity = 11,3125_G
#define	XL345_TRESH_INACT_VALUE_11_38_G	0xB6	//threshold value for detecting inactivity = 11,375_G
#define	XL345_TRESH_INACT_VALUE_11_44_G	0xB7	//threshold value for detecting inactivity = 11,4375_G
#define	XL345_TRESH_INACT_VALUE_11_50_G	0xB8	//threshold value for detecting inactivity = 11,5_G
#define	XL345_TRESH_INACT_VALUE_11_56_G	0xB9	//threshold value for detecting inactivity = 11,5625_G
#define	XL345_TRESH_INACT_VALUE_11_63_G	0xBA	//threshold value for detecting inactivity = 11,625_G
#define	XL345_TRESH_INACT_VALUE_11_69_G	0xBB	//threshold value for detecting inactivity = 11,6875_G
#define	XL345_TRESH_INACT_VALUE_11_75_G	0xBC	//threshold value for detecting inactivity = 11,75_G
#define	XL345_TRESH_INACT_VALUE_11_81_G	0xBD	//threshold value for detecting inactivity = 11,8125_G
#define	XL345_TRESH_INACT_VALUE_11_88_G	0xBE	//threshold value for detecting inactivity = 11,875_G
#define	XL345_TRESH_INACT_VALUE_11_94_G	0xBF	//threshold value for detecting inactivity = 11,9375_G
#define	XL345_TRESH_INACT_VALUE_12_00_G	0xC0	//threshold value for detecting inactivity = 12_G
#define	XL345_TRESH_INACT_VALUE_12_06_G	0xC1	//threshold value for detecting inactivity = 12,0625_G
#define	XL345_TRESH_INACT_VALUE_12_13_G	0xC2	//threshold value for detecting inactivity = 12,125_G
#define	XL345_TRESH_INACT_VALUE_12_19_G	0xC3	//threshold value for detecting inactivity = 12,1875_G
#define	XL345_TRESH_INACT_VALUE_12_25_G	0xC4	//threshold value for detecting inactivity = 12,25_G
#define	XL345_TRESH_INACT_VALUE_12_31_G	0xC5	//threshold value for detecting inactivity = 12,3125_G
#define	XL345_TRESH_INACT_VALUE_12_38_G	0xC6	//threshold value for detecting inactivity = 12,375_G
#define	XL345_TRESH_INACT_VALUE_12_44_G	0xC7	//threshold value for detecting inactivity = 12,4375_G
#define	XL345_TRESH_INACT_VALUE_12_50_G	0xC8	//threshold value for detecting inactivity = 12,5_G
#define	XL345_TRESH_INACT_VALUE_12_56_G	0xC9	//threshold value for detecting inactivity = 12,5625_G
#define	XL345_TRESH_INACT_VALUE_12_63_G	0xCA	//threshold value for detecting inactivity = 12,625_G
#define	XL345_TRESH_INACT_VALUE_12_69_G	0xCB	//threshold value for detecting inactivity = 12,6875_G
#define	XL345_TRESH_INACT_VALUE_12_75_G	0xCC	//threshold value for detecting inactivity = 12,75_G
#define	XL345_TRESH_INACT_VALUE_12_81_G	0xCD	//threshold value for detecting inactivity = 12,8125_G
#define	XL345_TRESH_INACT_VALUE_12_88_G	0xCE	//threshold value for detecting inactivity = 12,875_G
#define	XL345_TRESH_INACT_VALUE_12_94_G	0xCF	//threshold value for detecting inactivity = 12,9375_G
#define	XL345_TRESH_INACT_VALUE_13_00_G	0xD0	//threshold value for detecting inactivity = 13_G
#define	XL345_TRESH_INACT_VALUE_13_06_G	0xD1	//threshold value for detecting inactivity = 13,0625_G
#define	XL345_TRESH_INACT_VALUE_13_13_G	0xD2	//threshold value for detecting inactivity = 13,125_G
#define	XL345_TRESH_INACT_VALUE_13_19_G	0xD3	//threshold value for detecting inactivity = 13,1875_G
#define	XL345_TRESH_INACT_VALUE_13_25_G	0xD4	//threshold value for detecting inactivity = 13,25_G
#define	XL345_TRESH_INACT_VALUE_13_31_G	0xD5	//threshold value for detecting inactivity = 13,3125_G
#define	XL345_TRESH_INACT_VALUE_13_38_G	0xD6	//threshold value for detecting inactivity = 13,375_G
#define	XL345_TRESH_INACT_VALUE_13_44_G	0xD7	//threshold value for detecting inactivity = 13,4375_G
#define	XL345_TRESH_INACT_VALUE_13_50_G	0xD8	//threshold value for detecting inactivity = 13,5_G
#define	XL345_TRESH_INACT_VALUE_13_56_G	0xD9	//threshold value for detecting inactivity = 13,5625_G
#define	XL345_TRESH_INACT_VALUE_13_63_G	0xDA	//threshold value for detecting inactivity = 13,625_G
#define	XL345_TRESH_INACT_VALUE_13_69_G	0xDB	//threshold value for detecting inactivity = 13,6875_G
#define	XL345_TRESH_INACT_VALUE_13_75_G	0xDC	//threshold value for detecting inactivity = 13,75_G
#define	XL345_TRESH_INACT_VALUE_13_81_G	0xDD	//threshold value for detecting inactivity = 13,8125_G
#define	XL345_TRESH_INACT_VALUE_13_88_G	0xDE	//threshold value for detecting inactivity = 13,875_G
#define	XL345_TRESH_INACT_VALUE_13_94_G	0xDF	//threshold value for detecting inactivity = 13,9375_G
#define	XL345_TRESH_INACT_VALUE_14_00_G	0xE0	//threshold value for detecting inactivity = 14_G
#define	XL345_TRESH_INACT_VALUE_14_06_G	0xE1	//threshold value for detecting inactivity = 14,0625_G
#define	XL345_TRESH_INACT_VALUE_14_13_G	0xE2	//threshold value for detecting inactivity = 14,125_G
#define	XL345_TRESH_INACT_VALUE_14_19_G	0xE3	//threshold value for detecting inactivity = 14,1875_G
#define	XL345_TRESH_INACT_VALUE_14_25_G	0xE4	//threshold value for detecting inactivity = 14,25_G
#define	XL345_TRESH_INACT_VALUE_14_31_G	0xE5	//threshold value for detecting inactivity = 14,3125_G
#define	XL345_TRESH_INACT_VALUE_14_38_G	0xE6	//threshold value for detecting inactivity = 14,375_G
#define	XL345_TRESH_INACT_VALUE_14_44_G	0xE7	//threshold value for detecting inactivity = 14,4375_G
#define	XL345_TRESH_INACT_VALUE_14_50_G	0xE8	//threshold value for detecting inactivity = 14,5_G
#define	XL345_TRESH_INACT_VALUE_14_56_G	0xE9	//threshold value for detecting inactivity = 14,5625_G
#define	XL345_TRESH_INACT_VALUE_14_63_G	0xEA	//threshold value for detecting inactivity = 14,625_G
#define	XL345_TRESH_INACT_VALUE_14_69_G	0xEB	//threshold value for detecting inactivity = 14,6875_G
#define	XL345_TRESH_INACT_VALUE_14_75_G	0xEC	//threshold value for detecting inactivity = 14,75_G
#define	XL345_TRESH_INACT_VALUE_14_81_G	0xED	//threshold value for detecting inactivity = 14,8125_G
#define	XL345_TRESH_INACT_VALUE_14_88_G	0xEE	//threshold value for detecting inactivity = 14,875_G
#define	XL345_TRESH_INACT_VALUE_14_94_G	0xEF	//threshold value for detecting inactivity = 14,9375_G
#define	XL345_TRESH_INACT_VALUE_15_00_G	0xF0	//threshold value for detecting inactivity = 15_G
#define	XL345_TRESH_INACT_VALUE_15_06_G	0xF1	//threshold value for detecting inactivity = 15,0625_G
#define	XL345_TRESH_INACT_VALUE_15_13_G	0xF2	//threshold value for detecting inactivity = 15,125_G
#define	XL345_TRESH_INACT_VALUE_15_19_G	0xF3	//threshold value for detecting inactivity = 15,1875_G
#define	XL345_TRESH_INACT_VALUE_15_25_G	0xF4	//threshold value for detecting inactivity = 15,25_G
#define	XL345_TRESH_INACT_VALUE_15_31_G	0xF5	//threshold value for detecting inactivity = 15,3125_G
#define	XL345_TRESH_INACT_VALUE_15_38_G	0xF6	//threshold value for detecting inactivity = 15,375_G
#define	XL345_TRESH_INACT_VALUE_15_44_G	0xF7	//threshold value for detecting inactivity = 15,4375_G
#define	XL345_TRESH_INACT_VALUE_15_50_G	0xF8	//threshold value for detecting inactivity = 15,5_G
#define	XL345_TRESH_INACT_VALUE_15_56_G	0xF9	//threshold value for detecting inactivity = 15,5625_G
#define	XL345_TRESH_INACT_VALUE_15_63_G	0xFA	//threshold value for detecting inactivity = 15,625_G
#define	XL345_TRESH_INACT_VALUE_15_69_G	0xFB	//threshold value for detecting inactivity = 15,6875_G
#define	XL345_TRESH_INACT_VALUE_15_75_G	0xFC	//threshold value for detecting inactivity = 15,75_G
#define	XL345_TRESH_INACT_VALUE_15_81_G	0xFD	//threshold value for detecting inactivity = 15,8125_G
#define	XL345_TRESH_INACT_VALUE_15_88_G	0xFE	//threshold value for detecting inactivity = 15,875_G
#define	XL345_TRESH_INACT_VALUE_15_94_G	0xFF	//threshold value for detecting inactivity = 15,9375_G


/*
The TIME_INACT register is eight bits and contains an unsigned
time value representing the amount of time that acceleration
must be less than the value in the THRESH_INACT register for
inactivity to be declared. The scale factor is 1 sec/LSB. Unlike
the other interrupt functions, which use unfiltered data (see the
Threshold section), the inactivity function uses filtered output
data. At least one output sample must be generated for the
inactivity interrupt to be triggered. This results in the function
appearing unresponsive if the TIME_INACT register is set to a
value less than the time constant of the output data rate. A value
of 0 results in an interrupt when the output data is less than the
value in the THRESH_INACT register.
 */

#define	XL345_TIME_INACT_VALUE_0_S	0x00	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 0_S
#define	XL345_TIME_INACT_VALUE_1_S	0x01	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 1_S
#define	XL345_TIME_INACT_VALUE_2_S	0x02	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 2_S
#define	XL345_TIME_INACT_VALUE_3_S	0x03	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 3_S
#define	XL345_TIME_INACT_VALUE_4_S	0x04	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 4_S
#define	XL345_TIME_INACT_VALUE_5_S	0x05	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 5_S
#define	XL345_TIME_INACT_VALUE_6_S	0x06	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 6_S
#define	XL345_TIME_INACT_VALUE_7_S	0x07	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 7_S
#define	XL345_TIME_INACT_VALUE_8_S	0x08	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 8_S
#define	XL345_TIME_INACT_VALUE_9_S	0x09	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 9_S
#define	XL345_TIME_INACT_VALUE_10_S	0x0A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 10_S
#define	XL345_TIME_INACT_VALUE_11_S	0x0B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 11_S
#define	XL345_TIME_INACT_VALUE_12_S	0x0C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 12_S
#define	XL345_TIME_INACT_VALUE_13_S	0x0D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 13_S
#define	XL345_TIME_INACT_VALUE_14_S	0x0E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 14_S
#define	XL345_TIME_INACT_VALUE_15_S	0x0F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 15_S
#define	XL345_TIME_INACT_VALUE_16_S	0x10	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 16_S
#define	XL345_TIME_INACT_VALUE_17_S	0x11	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 17_S
#define	XL345_TIME_INACT_VALUE_18_S	0x12	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 18_S
#define	XL345_TIME_INACT_VALUE_19_S	0x13	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 19_S
#define	XL345_TIME_INACT_VALUE_20_S	0x14	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 20_S
#define	XL345_TIME_INACT_VALUE_21_S	0x15	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 21_S
#define	XL345_TIME_INACT_VALUE_22_S	0x16	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 22_S
#define	XL345_TIME_INACT_VALUE_23_S	0x17	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 23_S
#define	XL345_TIME_INACT_VALUE_24_S	0x18	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 24_S
#define	XL345_TIME_INACT_VALUE_25_S	0x19	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 25_S
#define	XL345_TIME_INACT_VALUE_26_S	0x1A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 26_S
#define	XL345_TIME_INACT_VALUE_27_S	0x1B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 27_S
#define	XL345_TIME_INACT_VALUE_28_S	0x1C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 28_S
#define	XL345_TIME_INACT_VALUE_29_S	0x1D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 29_S
#define	XL345_TIME_INACT_VALUE_30_S	0x1E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 30_S
#define	XL345_TIME_INACT_VALUE_31_S	0x1F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 31_S
#define	XL345_TIME_INACT_VALUE_32_S	0x20	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 32_S
#define	XL345_TIME_INACT_VALUE_33_S	0x21	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 33_S
#define	XL345_TIME_INACT_VALUE_34_S	0x22	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 34_S
#define	XL345_TIME_INACT_VALUE_35_S	0x23	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 35_S
#define	XL345_TIME_INACT_VALUE_36_S	0x24	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 36_S
#define	XL345_TIME_INACT_VALUE_37_S	0x25	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 37_S
#define	XL345_TIME_INACT_VALUE_38_S	0x26	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 38_S
#define	XL345_TIME_INACT_VALUE_39_S	0x27	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 39_S
#define	XL345_TIME_INACT_VALUE_40_S	0x28	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 40_S
#define	XL345_TIME_INACT_VALUE_41_S	0x29	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 41_S
#define	XL345_TIME_INACT_VALUE_42_S	0x2A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 42_S
#define	XL345_TIME_INACT_VALUE_43_S	0x2B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 43_S
#define	XL345_TIME_INACT_VALUE_44_S	0x2C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 44_S
#define	XL345_TIME_INACT_VALUE_45_S	0x2D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 45_S
#define	XL345_TIME_INACT_VALUE_46_S	0x2E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 46_S
#define	XL345_TIME_INACT_VALUE_47_S	0x2F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 47_S
#define	XL345_TIME_INACT_VALUE_48_S	0x30	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 48_S
#define	XL345_TIME_INACT_VALUE_49_S	0x31	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 49_S
#define	XL345_TIME_INACT_VALUE_50_S	0x32	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 50_S
#define	XL345_TIME_INACT_VALUE_51_S	0x33	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 51_S
#define	XL345_TIME_INACT_VALUE_52_S	0x34	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 52_S
#define	XL345_TIME_INACT_VALUE_53_S	0x35	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 53_S
#define	XL345_TIME_INACT_VALUE_54_S	0x36	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 54_S
#define	XL345_TIME_INACT_VALUE_55_S	0x37	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 55_S
#define	XL345_TIME_INACT_VALUE_56_S	0x38	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 56_S
#define	XL345_TIME_INACT_VALUE_57_S	0x39	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 57_S
#define	XL345_TIME_INACT_VALUE_58_S	0x3A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 58_S
#define	XL345_TIME_INACT_VALUE_59_S	0x3B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 59_S
#define	XL345_TIME_INACT_VALUE_60_S	0x3C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 60_S
#define	XL345_TIME_INACT_VALUE_61_S	0x3D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 61_S
#define	XL345_TIME_INACT_VALUE_62_S	0x3E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 62_S
#define	XL345_TIME_INACT_VALUE_63_S	0x3F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 63_S
#define	XL345_TIME_INACT_VALUE_64_S	0x40	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 64_S
#define	XL345_TIME_INACT_VALUE_65_S	0x41	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 65_S
#define	XL345_TIME_INACT_VALUE_66_S	0x42	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 66_S
#define	XL345_TIME_INACT_VALUE_67_S	0x43	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 67_S
#define	XL345_TIME_INACT_VALUE_68_S	0x44	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 68_S
#define	XL345_TIME_INACT_VALUE_69_S	0x45	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 69_S
#define	XL345_TIME_INACT_VALUE_70_S	0x46	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 70_S
#define	XL345_TIME_INACT_VALUE_71_S	0x47	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 71_S
#define	XL345_TIME_INACT_VALUE_72_S	0x48	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 72_S
#define	XL345_TIME_INACT_VALUE_73_S	0x49	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 73_S
#define	XL345_TIME_INACT_VALUE_74_S	0x4A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 74_S
#define	XL345_TIME_INACT_VALUE_75_S	0x4B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 75_S
#define	XL345_TIME_INACT_VALUE_76_S	0x4C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 76_S
#define	XL345_TIME_INACT_VALUE_77_S	0x4D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 77_S
#define	XL345_TIME_INACT_VALUE_78_S	0x4E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 78_S
#define	XL345_TIME_INACT_VALUE_79_S	0x4F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 79_S
#define	XL345_TIME_INACT_VALUE_80_S	0x50	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 80_S
#define	XL345_TIME_INACT_VALUE_81_S	0x51	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 81_S
#define	XL345_TIME_INACT_VALUE_82_S	0x52	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 82_S
#define	XL345_TIME_INACT_VALUE_83_S	0x53	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 83_S
#define	XL345_TIME_INACT_VALUE_84_S	0x54	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 84_S
#define	XL345_TIME_INACT_VALUE_85_S	0x55	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 85_S
#define	XL345_TIME_INACT_VALUE_86_S	0x56	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 86_S
#define	XL345_TIME_INACT_VALUE_87_S	0x57	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 87_S
#define	XL345_TIME_INACT_VALUE_88_S	0x58	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 88_S
#define	XL345_TIME_INACT_VALUE_89_S	0x59	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 89_S
#define	XL345_TIME_INACT_VALUE_90_S	0x5A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 90_S
#define	XL345_TIME_INACT_VALUE_91_S	0x5B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 91_S
#define	XL345_TIME_INACT_VALUE_92_S	0x5C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 92_S
#define	XL345_TIME_INACT_VALUE_93_S	0x5D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 93_S
#define	XL345_TIME_INACT_VALUE_94_S	0x5E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 94_S
#define	XL345_TIME_INACT_VALUE_95_S	0x5F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 95_S
#define	XL345_TIME_INACT_VALUE_96_S	0x60	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 96_S
#define	XL345_TIME_INACT_VALUE_97_S	0x61	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 97_S
#define	XL345_TIME_INACT_VALUE_98_S	0x62	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 98_S
#define	XL345_TIME_INACT_VALUE_99_S	0x63	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 99_S
#define	XL345_TIME_INACT_VALUE_100_S	0x64	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 100_S
#define	XL345_TIME_INACT_VALUE_101_S	0x65	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 101_S
#define	XL345_TIME_INACT_VALUE_102_S	0x66	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 102_S
#define	XL345_TIME_INACT_VALUE_103_S	0x67	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 103_S
#define	XL345_TIME_INACT_VALUE_104_S	0x68	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 104_S
#define	XL345_TIME_INACT_VALUE_105_S	0x69	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 105_S
#define	XL345_TIME_INACT_VALUE_106_S	0x6A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 106_S
#define	XL345_TIME_INACT_VALUE_107_S	0x6B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 107_S
#define	XL345_TIME_INACT_VALUE_108_S	0x6C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 108_S
#define	XL345_TIME_INACT_VALUE_109_S	0x6D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 109_S
#define	XL345_TIME_INACT_VALUE_110_S	0x6E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 110_S
#define	XL345_TIME_INACT_VALUE_111_S	0x6F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 111_S
#define	XL345_TIME_INACT_VALUE_112_S	0x70	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 112_S
#define	XL345_TIME_INACT_VALUE_113_S	0x71	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 113_S
#define	XL345_TIME_INACT_VALUE_114_S	0x72	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 114_S
#define	XL345_TIME_INACT_VALUE_115_S	0x73	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 115_S
#define	XL345_TIME_INACT_VALUE_116_S	0x74	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 116_S
#define	XL345_TIME_INACT_VALUE_117_S	0x75	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 117_S
#define	XL345_TIME_INACT_VALUE_118_S	0x76	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 118_S
#define	XL345_TIME_INACT_VALUE_119_S	0x77	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 119_S
#define	XL345_TIME_INACT_VALUE_120_S	0x78	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 120_S
#define	XL345_TIME_INACT_VALUE_121_S	0x79	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 121_S
#define	XL345_TIME_INACT_VALUE_122_S	0x7A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 122_S
#define	XL345_TIME_INACT_VALUE_123_S	0x7B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 123_S
#define	XL345_TIME_INACT_VALUE_124_S	0x7C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 124_S
#define	XL345_TIME_INACT_VALUE_125_S	0x7D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 125_S
#define	XL345_TIME_INACT_VALUE_126_S	0x7E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 126_S
#define	XL345_TIME_INACT_VALUE_127_S	0x7F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 127_S
#define	XL345_TIME_INACT_VALUE_128_S	0x80	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 128_S
#define	XL345_TIME_INACT_VALUE_129_S	0x81	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 129_S
#define	XL345_TIME_INACT_VALUE_130_S	0x82	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 130_S
#define	XL345_TIME_INACT_VALUE_131_S	0x83	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 131_S
#define	XL345_TIME_INACT_VALUE_132_S	0x84	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 132_S
#define	XL345_TIME_INACT_VALUE_133_S	0x85	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 133_S
#define	XL345_TIME_INACT_VALUE_134_S	0x86	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 134_S
#define	XL345_TIME_INACT_VALUE_135_S	0x87	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 135_S
#define	XL345_TIME_INACT_VALUE_136_S	0x88	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 136_S
#define	XL345_TIME_INACT_VALUE_137_S	0x89	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 137_S
#define	XL345_TIME_INACT_VALUE_138_S	0x8A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 138_S
#define	XL345_TIME_INACT_VALUE_139_S	0x8B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 139_S
#define	XL345_TIME_INACT_VALUE_140_S	0x8C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 140_S
#define	XL345_TIME_INACT_VALUE_141_S	0x8D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 141_S
#define	XL345_TIME_INACT_VALUE_142_S	0x8E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 142_S
#define	XL345_TIME_INACT_VALUE_143_S	0x8F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 143_S
#define	XL345_TIME_INACT_VALUE_144_S	0x90	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 144_S
#define	XL345_TIME_INACT_VALUE_145_S	0x91	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 145_S
#define	XL345_TIME_INACT_VALUE_146_S	0x92	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 146_S
#define	XL345_TIME_INACT_VALUE_147_S	0x93	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 147_S
#define	XL345_TIME_INACT_VALUE_148_S	0x94	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 148_S
#define	XL345_TIME_INACT_VALUE_149_S	0x95	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 149_S
#define	XL345_TIME_INACT_VALUE_150_S	0x96	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 150_S
#define	XL345_TIME_INACT_VALUE_151_S	0x97	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 151_S
#define	XL345_TIME_INACT_VALUE_152_S	0x98	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 152_S
#define	XL345_TIME_INACT_VALUE_153_S	0x99	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 153_S
#define	XL345_TIME_INACT_VALUE_154_S	0x9A	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 154_S
#define	XL345_TIME_INACT_VALUE_155_S	0x9B	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 155_S
#define	XL345_TIME_INACT_VALUE_156_S	0x9C	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 156_S
#define	XL345_TIME_INACT_VALUE_157_S	0x9D	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 157_S
#define	XL345_TIME_INACT_VALUE_158_S	0x9E	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 158_S
#define	XL345_TIME_INACT_VALUE_159_S	0x9F	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 159_S
#define	XL345_TIME_INACT_VALUE_160_S	0xA0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 160_S
#define	XL345_TIME_INACT_VALUE_161_S	0xA1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 161_S
#define	XL345_TIME_INACT_VALUE_162_S	0xA2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 162_S
#define	XL345_TIME_INACT_VALUE_163_S	0xA3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 163_S
#define	XL345_TIME_INACT_VALUE_164_S	0xA4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 164_S
#define	XL345_TIME_INACT_VALUE_165_S	0xA5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 165_S
#define	XL345_TIME_INACT_VALUE_166_S	0xA6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 166_S
#define	XL345_TIME_INACT_VALUE_167_S	0xA7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 167_S
#define	XL345_TIME_INACT_VALUE_168_S	0xA8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 168_S
#define	XL345_TIME_INACT_VALUE_169_S	0xA9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 169_S
#define	XL345_TIME_INACT_VALUE_170_S	0xAA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 170_S
#define	XL345_TIME_INACT_VALUE_171_S	0xAB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 171_S
#define	XL345_TIME_INACT_VALUE_172_S	0xAC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 172_S
#define	XL345_TIME_INACT_VALUE_173_S	0xAD	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 173_S
#define	XL345_TIME_INACT_VALUE_174_S	0xAE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 174_S
#define	XL345_TIME_INACT_VALUE_175_S	0xAF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 175_S
#define	XL345_TIME_INACT_VALUE_176_S	0xB0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 176_S
#define	XL345_TIME_INACT_VALUE_177_S	0xB1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 177_S
#define	XL345_TIME_INACT_VALUE_178_S	0xB2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 178_S
#define	XL345_TIME_INACT_VALUE_179_S	0xB3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 179_S
#define	XL345_TIME_INACT_VALUE_180_S	0xB4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 180_S
#define	XL345_TIME_INACT_VALUE_181_S	0xB5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 181_S
#define	XL345_TIME_INACT_VALUE_182_S	0xB6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 182_S
#define	XL345_TIME_INACT_VALUE_183_S	0xB7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 183_S
#define	XL345_TIME_INACT_VALUE_184_S	0xB8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 184_S
#define	XL345_TIME_INACT_VALUE_185_S	0xB9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 185_S
#define	XL345_TIME_INACT_VALUE_186_S	0xBA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 186_S
#define	XL345_TIME_INACT_VALUE_187_S	0xBB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 187_S
#define	XL345_TIME_INACT_VALUE_188_S	0xBC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 188_S
#define	XL345_TIME_INACT_VALUE_189_S	0xBD	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 189_S
#define	XL345_TIME_INACT_VALUE_190_S	0xBE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 190_S
#define	XL345_TIME_INACT_VALUE_191_S	0xBF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 191_S
#define	XL345_TIME_INACT_VALUE_192_S	0xC0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 192_S
#define	XL345_TIME_INACT_VALUE_193_S	0xC1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 193_S
#define	XL345_TIME_INACT_VALUE_194_S	0xC2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 194_S
#define	XL345_TIME_INACT_VALUE_195_S	0xC3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 195_S
#define	XL345_TIME_INACT_VALUE_196_S	0xC4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 196_S
#define	XL345_TIME_INACT_VALUE_197_S	0xC5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 197_S
#define	XL345_TIME_INACT_VALUE_198_S	0xC6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 198_S
#define	XL345_TIME_INACT_VALUE_199_S	0xC7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 199_S
#define	XL345_TIME_INACT_VALUE_200_S	0xC8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 200_S
#define	XL345_TIME_INACT_VALUE_201_S	0xC9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 201_S
#define	XL345_TIME_INACT_VALUE_202_S	0xCA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 202_S
#define	XL345_TIME_INACT_VALUE_203_S	0xCB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 203_S
#define	XL345_TIME_INACT_VALUE_204_S	0xCC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 204_S
#define	XL345_TIME_INACT_VALUE_205_S	0xCD	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 205_S
#define	XL345_TIME_INACT_VALUE_206_S	0xCE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 206_S
#define	XL345_TIME_INACT_VALUE_207_S	0xCF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 207_S
#define	XL345_TIME_INACT_VALUE_208_S	0xD0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 208_S
#define	XL345_TIME_INACT_VALUE_209_S	0xD1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 209_S
#define	XL345_TIME_INACT_VALUE_210_S	0xD2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 210_S
#define	XL345_TIME_INACT_VALUE_211_S	0xD3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 211_S
#define	XL345_TIME_INACT_VALUE_212_S	0xD4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 212_S
#define	XL345_TIME_INACT_VALUE_213_S	0xD5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 213_S
#define	XL345_TIME_INACT_VALUE_214_S	0xD6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 214_S
#define	XL345_TIME_INACT_VALUE_215_S	0xD7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 215_S
#define	XL345_TIME_INACT_VALUE_216_S	0xD8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 216_S
#define	XL345_TIME_INACT_VALUE_217_S	0xD9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 217_S
#define	XL345_TIME_INACT_VALUE_218_S	0xDA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 218_S
#define	XL345_TIME_INACT_VALUE_219_S	0xDB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 219_S
#define	XL345_TIME_INACT_VALUE_220_S	0xDC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 220_S
#define	XL345_TIME_INACT_VALUE_221_S	0xDD	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 221_S
#define	XL345_TIME_INACT_VALUE_222_S	0xDE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 222_S
#define	XL345_TIME_INACT_VALUE_223_S	0xDF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 223_S
#define	XL345_TIME_INACT_VALUE_224_S	0xE0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 224_S
#define	XL345_TIME_INACT_VALUE_225_S	0xE1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 225_S
#define	XL345_TIME_INACT_VALUE_226_S	0xE2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 226_S
#define	XL345_TIME_INACT_VALUE_227_S	0xE3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 227_S
#define	XL345_TIME_INACT_VALUE_228_S	0xE4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 228_S
#define	XL345_TIME_INACT_VALUE_229_S	0xE5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 229_S
#define	XL345_TIME_INACT_VALUE_230_S	0xE6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 230_S
#define	XL345_TIME_INACT_VALUE_231_S	0xE7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 231_S
#define	XL345_TIME_INACT_VALUE_232_S	0xE8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 232_S
#define	XL345_TIME_INACT_VALUE_233_S	0xE9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 233_S
#define	XL345_TIME_INACT_VALUE_234_S	0xEA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 234_S
#define	XL345_TIME_INACT_VALUE_235_S	0xEB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 235_S
#define	XL345_TIME_INACT_VALUE_236_S	0xEC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 236_S
#define	XL345_TIME_INACT_VALUE_237_S	0xED	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 237_S
#define	XL345_TIME_INACT_VALUE_238_S	0xEE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 238_S
#define	XL345_TIME_INACT_VALUE_239_S	0xEF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 239_S
#define	XL345_TIME_INACT_VALUE_240_S	0xF0	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 240_S
#define	XL345_TIME_INACT_VALUE_241_S	0xF1	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 241_S
#define	XL345_TIME_INACT_VALUE_242_S	0xF2	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 242_S
#define	XL345_TIME_INACT_VALUE_243_S	0xF3	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 243_S
#define	XL345_TIME_INACT_VALUE_244_S	0xF4	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 244_S
#define	XL345_TIME_INACT_VALUE_245_S	0xF5	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 245_S
#define	XL345_TIME_INACT_VALUE_246_S	0xF6	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 246_S
#define	XL345_TIME_INACT_VALUE_247_S	0xF7	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 247_S
#define	XL345_TIME_INACT_VALUE_248_S	0xF8	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 248_S
#define	XL345_TIME_INACT_VALUE_249_S	0xF9	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 249_S
#define	XL345_TIME_INACT_VALUE_250_S	0xFA	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 250_S
#define	XL345_TIME_INACT_VALUE_251_S	0xFB	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 251_S
#define	XL345_TIME_INACT_VALUE_252_S	0xFC	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 252_S
#define	XL345_TIME_INACT_VALUE_253_S	0xFD	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 253_S
#define	XL345_TIME_INACT_VALUE_254_S	0xFE	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 254_S
#define	XL345_TIME_INACT_VALUE_255_S	0xFF	//time that acceleration must be less than THRESH_INACT_VALUE to detect inactivity = 255_S

/*
The THRESH_FF register is eight bits and holds the threshold
value, in unsigned format, for free-fall detection. The acceleration on
all axes is compared with the value in THRESH_FF to determine if
a free-fall event occurred. The scale factor is 62.5 mg/LSB. Note
that a value of 0 mg may result in undesirable behavior if the free-
fall interrupt is enabled.
*/

/* !! Values between 300 mg and 600 mg (0x05 to 0x09) are recommended !!*/

#define	XL345_TRESH_FF_VALUE_0_G	0x00	//result in undesirable behavior if the free fall interrupt is enabled = 0_G
#define	XL345_TRESH_FF_VALUE_0_06_G	0x01	//threshold value for free-fall detection = 0,0625_G
#define	XL345_TRESH_FF_VALUE_0_13_G	0x02	//threshold value for free-fall detection = 0,125_G
#define	XL345_TRESH_FF_VALUE_0_19_G	0x03	//threshold value for free-fall detection = 0,1875_G
#define	XL345_TRESH_FF_VALUE_0_25_G	0x04	//threshold value for free-fall detection = 0,25_G
#define	XL345_TRESH_FF_VALUE_0_31_G	0x05	//threshold value for free-fall detection = 0,3125_G
#define	XL345_TRESH_FF_VALUE_0_38_G	0x06	//threshold value for free-fall detection = 0,375_G
#define	XL345_TRESH_FF_VALUE_0_44_G	0x07	//threshold value for free-fall detection = 0,4375_G
#define	XL345_TRESH_FF_VALUE_0_50_G	0x08	//threshold value for free-fall detection = 0,5_G
#define	XL345_TRESH_FF_VALUE_0_56_G	0x09	//threshold value for free-fall detection = 0,5625_G

#define	XL345_TRESH_FF_VALUE_0_63_G	0x0A	//threshold value for free-fall detection = 0,625_G
#define	XL345_TRESH_FF_VALUE_0_69_G	0x0B	//threshold value for free-fall detection = 0,6875_G
#define	XL345_TRESH_FF_VALUE_0_75_G	0x0C	//threshold value for free-fall detection = 0,75_G
#define	XL345_TRESH_FF_VALUE_0_81_G	0x0D	//threshold value for free-fall detection = 0,8125_G
#define	XL345_TRESH_FF_VALUE_0_88_G	0x0E	//threshold value for free-fall detection = 0,875_G
#define	XL345_TRESH_FF_VALUE_0_94_G	0x0F	//threshold value for free-fall detection = 0,9375_G
#define	XL345_TRESH_FF_VALUE_1_00_G	0x10	//threshold value for free-fall detection = 1_G
#define	XL345_TRESH_FF_VALUE_1_06_G	0x11	//threshold value for free-fall detection = 1,0625_G
#define	XL345_TRESH_FF_VALUE_1_13_G	0x12	//threshold value for free-fall detection = 1,125_G
#define	XL345_TRESH_FF_VALUE_1_19_G	0x13	//threshold value for free-fall detection = 1,1875_G
#define	XL345_TRESH_FF_VALUE_1_25_G	0x14	//threshold value for free-fall detection = 1,25_G
#define	XL345_TRESH_FF_VALUE_1_31_G	0x15	//threshold value for free-fall detection = 1,3125_G
#define	XL345_TRESH_FF_VALUE_1_38_G	0x16	//threshold value for free-fall detection = 1,375_G
#define	XL345_TRESH_FF_VALUE_1_44_G	0x17	//threshold value for free-fall detection = 1,4375_G
#define	XL345_TRESH_FF_VALUE_1_50_G	0x18	//threshold value for free-fall detection = 1,5_G
#define	XL345_TRESH_FF_VALUE_1_56_G	0x19	//threshold value for free-fall detection = 1,5625_G
#define	XL345_TRESH_FF_VALUE_1_63_G	0x1A	//threshold value for free-fall detection = 1,625_G
#define	XL345_TRESH_FF_VALUE_1_69_G	0x1B	//threshold value for free-fall detection = 1,6875_G
#define	XL345_TRESH_FF_VALUE_1_75_G	0x1C	//threshold value for free-fall detection = 1,75_G
#define	XL345_TRESH_FF_VALUE_1_81_G	0x1D	//threshold value for free-fall detection = 1,8125_G
#define	XL345_TRESH_FF_VALUE_1_88_G	0x1E	//threshold value for free-fall detection = 1,875_G
#define	XL345_TRESH_FF_VALUE_1_94_G	0x1F	//threshold value for free-fall detection = 1,9375_G
#define	XL345_TRESH_FF_VALUE_2_00_G	0x20	//threshold value for free-fall detection = 2_G
#define	XL345_TRESH_FF_VALUE_2_06_G	0x21	//threshold value for free-fall detection = 2,0625_G
#define	XL345_TRESH_FF_VALUE_2_13_G	0x22	//threshold value for free-fall detection = 2,125_G
#define	XL345_TRESH_FF_VALUE_2_19_G	0x23	//threshold value for free-fall detection = 2,1875_G
#define	XL345_TRESH_FF_VALUE_2_25_G	0x24	//threshold value for free-fall detection = 2,25_G
#define	XL345_TRESH_FF_VALUE_2_31_G	0x25	//threshold value for free-fall detection = 2,3125_G
#define	XL345_TRESH_FF_VALUE_2_38_G	0x26	//threshold value for free-fall detection = 2,375_G
#define	XL345_TRESH_FF_VALUE_2_44_G	0x27	//threshold value for free-fall detection = 2,4375_G
#define	XL345_TRESH_FF_VALUE_2_50_G	0x28	//threshold value for free-fall detection = 2,5_G
#define	XL345_TRESH_FF_VALUE_2_56_G	0x29	//threshold value for free-fall detection = 2,5625_G
#define	XL345_TRESH_FF_VALUE_2_63_G	0x2A	//threshold value for free-fall detection = 2,625_G
#define	XL345_TRESH_FF_VALUE_2_69_G	0x2B	//threshold value for free-fall detection = 2,6875_G
#define	XL345_TRESH_FF_VALUE_2_75_G	0x2C	//threshold value for free-fall detection = 2,75_G
#define	XL345_TRESH_FF_VALUE_2_81_G	0x2D	//threshold value for free-fall detection = 2,8125_G
#define	XL345_TRESH_FF_VALUE_2_88_G	0x2E	//threshold value for free-fall detection = 2,875_G
#define	XL345_TRESH_FF_VALUE_2_94_G	0x2F	//threshold value for free-fall detection = 2,9375_G
#define	XL345_TRESH_FF_VALUE_3_00_G	0x30	//threshold value for free-fall detection = 3_G
#define	XL345_TRESH_FF_VALUE_3_06_G	0x31	//threshold value for free-fall detection = 3,0625_G
#define	XL345_TRESH_FF_VALUE_3_13_G	0x32	//threshold value for free-fall detection = 3,125_G
#define	XL345_TRESH_FF_VALUE_3_19_G	0x33	//threshold value for free-fall detection = 3,1875_G
#define	XL345_TRESH_FF_VALUE_3_25_G	0x34	//threshold value for free-fall detection = 3,25_G
#define	XL345_TRESH_FF_VALUE_3_31_G	0x35	//threshold value for free-fall detection = 3,3125_G
#define	XL345_TRESH_FF_VALUE_3_38_G	0x36	//threshold value for free-fall detection = 3,375_G
#define	XL345_TRESH_FF_VALUE_3_44_G	0x37	//threshold value for free-fall detection = 3,4375_G
#define	XL345_TRESH_FF_VALUE_3_50_G	0x38	//threshold value for free-fall detection = 3,5_G
#define	XL345_TRESH_FF_VALUE_3_56_G	0x39	//threshold value for free-fall detection = 3,5625_G
#define	XL345_TRESH_FF_VALUE_3_63_G	0x3A	//threshold value for free-fall detection = 3,625_G
#define	XL345_TRESH_FF_VALUE_3_69_G	0x3B	//threshold value for free-fall detection = 3,6875_G
#define	XL345_TRESH_FF_VALUE_3_75_G	0x3C	//threshold value for free-fall detection = 3,75_G
#define	XL345_TRESH_FF_VALUE_3_81_G	0x3D	//threshold value for free-fall detection = 3,8125_G
#define	XL345_TRESH_FF_VALUE_3_88_G	0x3E	//threshold value for free-fall detection = 3,875_G
#define	XL345_TRESH_FF_VALUE_3_94_G	0x3F	//threshold value for free-fall detection = 3,9375_G
#define	XL345_TRESH_FF_VALUE_4_00_G	0x40	//threshold value for free-fall detection = 4_G
#define	XL345_TRESH_FF_VALUE_4_06_G	0x41	//threshold value for free-fall detection = 4,0625_G
#define	XL345_TRESH_FF_VALUE_4_13_G	0x42	//threshold value for free-fall detection = 4,125_G
#define	XL345_TRESH_FF_VALUE_4_19_G	0x43	//threshold value for free-fall detection = 4,1875_G
#define	XL345_TRESH_FF_VALUE_4_25_G	0x44	//threshold value for free-fall detection = 4,25_G
#define	XL345_TRESH_FF_VALUE_4_31_G	0x45	//threshold value for free-fall detection = 4,3125_G
#define	XL345_TRESH_FF_VALUE_4_38_G	0x46	//threshold value for free-fall detection = 4,375_G
#define	XL345_TRESH_FF_VALUE_4_44_G	0x47	//threshold value for free-fall detection = 4,4375_G
#define	XL345_TRESH_FF_VALUE_4_50_G	0x48	//threshold value for free-fall detection = 4,5_G
#define	XL345_TRESH_FF_VALUE_4_56_G	0x49	//threshold value for free-fall detection = 4,5625_G
#define	XL345_TRESH_FF_VALUE_4_63_G	0x4A	//threshold value for free-fall detection = 4,625_G
#define	XL345_TRESH_FF_VALUE_4_69_G	0x4B	//threshold value for free-fall detection = 4,6875_G
#define	XL345_TRESH_FF_VALUE_4_75_G	0x4C	//threshold value for free-fall detection = 4,75_G
#define	XL345_TRESH_FF_VALUE_4_81_G	0x4D	//threshold value for free-fall detection = 4,8125_G
#define	XL345_TRESH_FF_VALUE_4_88_G	0x4E	//threshold value for free-fall detection = 4,875_G
#define	XL345_TRESH_FF_VALUE_4_94_G	0x4F	//threshold value for free-fall detection = 4,9375_G
#define	XL345_TRESH_FF_VALUE_5_00_G	0x50	//threshold value for free-fall detection = 5_G
#define	XL345_TRESH_FF_VALUE_5_06_G	0x51	//threshold value for free-fall detection = 5,0625_G
#define	XL345_TRESH_FF_VALUE_5_13_G	0x52	//threshold value for free-fall detection = 5,125_G
#define	XL345_TRESH_FF_VALUE_5_19_G	0x53	//threshold value for free-fall detection = 5,1875_G
#define	XL345_TRESH_FF_VALUE_5_25_G	0x54	//threshold value for free-fall detection = 5,25_G
#define	XL345_TRESH_FF_VALUE_5_31_G	0x55	//threshold value for free-fall detection = 5,3125_G
#define	XL345_TRESH_FF_VALUE_5_38_G	0x56	//threshold value for free-fall detection = 5,375_G
#define	XL345_TRESH_FF_VALUE_5_44_G	0x57	//threshold value for free-fall detection = 5,4375_G
#define	XL345_TRESH_FF_VALUE_5_50_G	0x58	//threshold value for free-fall detection = 5,5_G
#define	XL345_TRESH_FF_VALUE_5_56_G	0x59	//threshold value for free-fall detection = 5,5625_G
#define	XL345_TRESH_FF_VALUE_5_63_G	0x5A	//threshold value for free-fall detection = 5,625_G
#define	XL345_TRESH_FF_VALUE_5_69_G	0x5B	//threshold value for free-fall detection = 5,6875_G
#define	XL345_TRESH_FF_VALUE_5_75_G	0x5C	//threshold value for free-fall detection = 5,75_G
#define	XL345_TRESH_FF_VALUE_5_81_G	0x5D	//threshold value for free-fall detection = 5,8125_G
#define	XL345_TRESH_FF_VALUE_5_88_G	0x5E	//threshold value for free-fall detection = 5,875_G
#define	XL345_TRESH_FF_VALUE_5_94_G	0x5F	//threshold value for free-fall detection = 5,9375_G
#define	XL345_TRESH_FF_VALUE_6_00_G	0x60	//threshold value for free-fall detection = 6_G
#define	XL345_TRESH_FF_VALUE_6_06_G	0x61	//threshold value for free-fall detection = 6,0625_G
#define	XL345_TRESH_FF_VALUE_6_13_G	0x62	//threshold value for free-fall detection = 6,125_G
#define	XL345_TRESH_FF_VALUE_6_19_G	0x63	//threshold value for free-fall detection = 6,1875_G
#define	XL345_TRESH_FF_VALUE_6_25_G	0x64	//threshold value for free-fall detection = 6,25_G
#define	XL345_TRESH_FF_VALUE_6_31_G	0x65	//threshold value for free-fall detection = 6,3125_G
#define	XL345_TRESH_FF_VALUE_6_38_G	0x66	//threshold value for free-fall detection = 6,375_G
#define	XL345_TRESH_FF_VALUE_6_44_G	0x67	//threshold value for free-fall detection = 6,4375_G
#define	XL345_TRESH_FF_VALUE_6_50_G	0x68	//threshold value for free-fall detection = 6,5_G
#define	XL345_TRESH_FF_VALUE_6_56_G	0x69	//threshold value for free-fall detection = 6,5625_G
#define	XL345_TRESH_FF_VALUE_6_63_G	0x6A	//threshold value for free-fall detection = 6,625_G
#define	XL345_TRESH_FF_VALUE_6_69_G	0x6B	//threshold value for free-fall detection = 6,6875_G
#define	XL345_TRESH_FF_VALUE_6_75_G	0x6C	//threshold value for free-fall detection = 6,75_G
#define	XL345_TRESH_FF_VALUE_6_81_G	0x6D	//threshold value for free-fall detection = 6,8125_G
#define	XL345_TRESH_FF_VALUE_6_88_G	0x6E	//threshold value for free-fall detection = 6,875_G
#define	XL345_TRESH_FF_VALUE_6_94_G	0x6F	//threshold value for free-fall detection = 6,9375_G
#define	XL345_TRESH_FF_VALUE_7_00_G	0x70	//threshold value for free-fall detection = 7_G
#define	XL345_TRESH_FF_VALUE_7_06_G	0x71	//threshold value for free-fall detection = 7,0625_G
#define	XL345_TRESH_FF_VALUE_7_13_G	0x72	//threshold value for free-fall detection = 7,125_G
#define	XL345_TRESH_FF_VALUE_7_19_G	0x73	//threshold value for free-fall detection = 7,1875_G
#define	XL345_TRESH_FF_VALUE_7_25_G	0x74	//threshold value for free-fall detection = 7,25_G
#define	XL345_TRESH_FF_VALUE_7_31_G	0x75	//threshold value for free-fall detection = 7,3125_G
#define	XL345_TRESH_FF_VALUE_7_38_G	0x76	//threshold value for free-fall detection = 7,375_G
#define	XL345_TRESH_FF_VALUE_7_44_G	0x77	//threshold value for free-fall detection = 7,4375_G
#define	XL345_TRESH_FF_VALUE_7_50_G	0x78	//threshold value for free-fall detection = 7,5_G
#define	XL345_TRESH_FF_VALUE_7_56_G	0x79	//threshold value for free-fall detection = 7,5625_G
#define	XL345_TRESH_FF_VALUE_7_63_G	0x7A	//threshold value for free-fall detection = 7,625_G
#define	XL345_TRESH_FF_VALUE_7_69_G	0x7B	//threshold value for free-fall detection = 7,6875_G
#define	XL345_TRESH_FF_VALUE_7_75_G	0x7C	//threshold value for free-fall detection = 7,75_G
#define	XL345_TRESH_FF_VALUE_7_81_G	0x7D	//threshold value for free-fall detection = 7,8125_G
#define	XL345_TRESH_FF_VALUE_7_88_G	0x7E	//threshold value for free-fall detection = 7,875_G
#define	XL345_TRESH_FF_VALUE_7_94_G	0x7F	//threshold value for free-fall detection = 7,9375_G
#define	XL345_TRESH_FF_VALUE_8_00_G	0x80	//threshold value for free-fall detection = 8_G
#define	XL345_TRESH_FF_VALUE_8_06_G	0x81	//threshold value for free-fall detection = 8,0625_G
#define	XL345_TRESH_FF_VALUE_8_13_G	0x82	//threshold value for free-fall detection = 8,125_G
#define	XL345_TRESH_FF_VALUE_8_19_G	0x83	//threshold value for free-fall detection = 8,1875_G
#define	XL345_TRESH_FF_VALUE_8_25_G	0x84	//threshold value for free-fall detection = 8,25_G
#define	XL345_TRESH_FF_VALUE_8_31_G	0x85	//threshold value for free-fall detection = 8,3125_G
#define	XL345_TRESH_FF_VALUE_8_38_G	0x86	//threshold value for free-fall detection = 8,375_G
#define	XL345_TRESH_FF_VALUE_8_44_G	0x87	//threshold value for free-fall detection = 8,4375_G
#define	XL345_TRESH_FF_VALUE_8_50_G	0x88	//threshold value for free-fall detection = 8,5_G
#define	XL345_TRESH_FF_VALUE_8_56_G	0x89	//threshold value for free-fall detection = 8,5625_G
#define	XL345_TRESH_FF_VALUE_8_63_G	0x8A	//threshold value for free-fall detection = 8,625_G
#define	XL345_TRESH_FF_VALUE_8_69_G	0x8B	//threshold value for free-fall detection = 8,6875_G
#define	XL345_TRESH_FF_VALUE_8_75_G	0x8C	//threshold value for free-fall detection = 8,75_G
#define	XL345_TRESH_FF_VALUE_8_81_G	0x8D	//threshold value for free-fall detection = 8,8125_G
#define	XL345_TRESH_FF_VALUE_8_88_G	0x8E	//threshold value for free-fall detection = 8,875_G
#define	XL345_TRESH_FF_VALUE_8_94_G	0x8F	//threshold value for free-fall detection = 8,9375_G
#define	XL345_TRESH_FF_VALUE_9_00_G	0x90	//threshold value for free-fall detection = 9_G
#define	XL345_TRESH_FF_VALUE_9_06_G	0x91	//threshold value for free-fall detection = 9,0625_G
#define	XL345_TRESH_FF_VALUE_9_13_G	0x92	//threshold value for free-fall detection = 9,125_G
#define	XL345_TRESH_FF_VALUE_9_19_G	0x93	//threshold value for free-fall detection = 9,1875_G
#define	XL345_TRESH_FF_VALUE_9_25_G	0x94	//threshold value for free-fall detection = 9,25_G
#define	XL345_TRESH_FF_VALUE_9_31_G	0x95	//threshold value for free-fall detection = 9,3125_G
#define	XL345_TRESH_FF_VALUE_9_38_G	0x96	//threshold value for free-fall detection = 9,375_G
#define	XL345_TRESH_FF_VALUE_9_44_G	0x97	//threshold value for free-fall detection = 9,4375_G
#define	XL345_TRESH_FF_VALUE_9_50_G	0x98	//threshold value for free-fall detection = 9,5_G
#define	XL345_TRESH_FF_VALUE_9_56_G	0x99	//threshold value for free-fall detection = 9,5625_G
#define	XL345_TRESH_FF_VALUE_9_63_G	0x9A	//threshold value for free-fall detection = 9,625_G
#define	XL345_TRESH_FF_VALUE_9_69_G	0x9B	//threshold value for free-fall detection = 9,6875_G
#define	XL345_TRESH_FF_VALUE_9_75_G	0x9C	//threshold value for free-fall detection = 9,75_G
#define	XL345_TRESH_FF_VALUE_9_81_G	0x9D	//threshold value for free-fall detection = 9,8125_G
#define	XL345_TRESH_FF_VALUE_9_88_G	0x9E	//threshold value for free-fall detection = 9,875_G
#define	XL345_TRESH_FF_VALUE_9_94_G	0x9F	//threshold value for free-fall detection = 9,9375_G
#define	XL345_TRESH_FF_VALUE_10_00_G	0xA0	//threshold value for free-fall detection = 10_G
#define	XL345_TRESH_FF_VALUE_10_06_G	0xA1	//threshold value for free-fall detection = 10,0625_G
#define	XL345_TRESH_FF_VALUE_10_13_G	0xA2	//threshold value for free-fall detection = 10,125_G
#define	XL345_TRESH_FF_VALUE_10_19_G	0xA3	//threshold value for free-fall detection = 10,1875_G
#define	XL345_TRESH_FF_VALUE_10_25_G	0xA4	//threshold value for free-fall detection = 10,25_G
#define	XL345_TRESH_FF_VALUE_10_31_G	0xA5	//threshold value for free-fall detection = 10,3125_G
#define	XL345_TRESH_FF_VALUE_10_38_G	0xA6	//threshold value for free-fall detection = 10,375_G
#define	XL345_TRESH_FF_VALUE_10_44_G	0xA7	//threshold value for free-fall detection = 10,4375_G
#define	XL345_TRESH_FF_VALUE_10_50_G	0xA8	//threshold value for free-fall detection = 10,5_G
#define	XL345_TRESH_FF_VALUE_10_56_G	0xA9	//threshold value for free-fall detection = 10,5625_G
#define	XL345_TRESH_FF_VALUE_10_63_G	0xAA	//threshold value for free-fall detection = 10,625_G
#define	XL345_TRESH_FF_VALUE_10_69_G	0xAB	//threshold value for free-fall detection = 10,6875_G
#define	XL345_TRESH_FF_VALUE_10_75_G	0xAC	//threshold value for free-fall detection = 10,75_G
#define	XL345_TRESH_FF_VALUE_10_81_G	0xAD	//threshold value for free-fall detection = 10,8125_G
#define	XL345_TRESH_FF_VALUE_10_88_G	0xAE	//threshold value for free-fall detection = 10,875_G
#define	XL345_TRESH_FF_VALUE_10_94_G	0xAF	//threshold value for free-fall detection = 10,9375_G
#define	XL345_TRESH_FF_VALUE_11_00_G	0xB0	//threshold value for free-fall detection = 11_G
#define	XL345_TRESH_FF_VALUE_11_06_G	0xB1	//threshold value for free-fall detection = 11,0625_G
#define	XL345_TRESH_FF_VALUE_11_13_G	0xB2	//threshold value for free-fall detection = 11,125_G
#define	XL345_TRESH_FF_VALUE_11_19_G	0xB3	//threshold value for free-fall detection = 11,1875_G
#define	XL345_TRESH_FF_VALUE_11_25_G	0xB4	//threshold value for free-fall detection = 11,25_G
#define	XL345_TRESH_FF_VALUE_11_31_G	0xB5	//threshold value for free-fall detection = 11,3125_G
#define	XL345_TRESH_FF_VALUE_11_38_G	0xB6	//threshold value for free-fall detection = 11,375_G
#define	XL345_TRESH_FF_VALUE_11_44_G	0xB7	//threshold value for free-fall detection = 11,4375_G
#define	XL345_TRESH_FF_VALUE_11_50_G	0xB8	//threshold value for free-fall detection = 11,5_G
#define	XL345_TRESH_FF_VALUE_11_56_G	0xB9	//threshold value for free-fall detection = 11,5625_G
#define	XL345_TRESH_FF_VALUE_11_63_G	0xBA	//threshold value for free-fall detection = 11,625_G
#define	XL345_TRESH_FF_VALUE_11_69_G	0xBB	//threshold value for free-fall detection = 11,6875_G
#define	XL345_TRESH_FF_VALUE_11_75_G	0xBC	//threshold value for free-fall detection = 11,75_G
#define	XL345_TRESH_FF_VALUE_11_81_G	0xBD	//threshold value for free-fall detection = 11,8125_G
#define	XL345_TRESH_FF_VALUE_11_88_G	0xBE	//threshold value for free-fall detection = 11,875_G
#define	XL345_TRESH_FF_VALUE_11_94_G	0xBF	//threshold value for free-fall detection = 11,9375_G
#define	XL345_TRESH_FF_VALUE_12_00_G	0xC0	//threshold value for free-fall detection = 12_G
#define	XL345_TRESH_FF_VALUE_12_06_G	0xC1	//threshold value for free-fall detection = 12,0625_G
#define	XL345_TRESH_FF_VALUE_12_13_G	0xC2	//threshold value for free-fall detection = 12,125_G
#define	XL345_TRESH_FF_VALUE_12_19_G	0xC3	//threshold value for free-fall detection = 12,1875_G
#define	XL345_TRESH_FF_VALUE_12_25_G	0xC4	//threshold value for free-fall detection = 12,25_G
#define	XL345_TRESH_FF_VALUE_12_31_G	0xC5	//threshold value for free-fall detection = 12,3125_G
#define	XL345_TRESH_FF_VALUE_12_38_G	0xC6	//threshold value for free-fall detection = 12,375_G
#define	XL345_TRESH_FF_VALUE_12_44_G	0xC7	//threshold value for free-fall detection = 12,4375_G
#define	XL345_TRESH_FF_VALUE_12_50_G	0xC8	//threshold value for free-fall detection = 12,5_G
#define	XL345_TRESH_FF_VALUE_12_56_G	0xC9	//threshold value for free-fall detection = 12,5625_G
#define	XL345_TRESH_FF_VALUE_12_63_G	0xCA	//threshold value for free-fall detection = 12,625_G
#define	XL345_TRESH_FF_VALUE_12_69_G	0xCB	//threshold value for free-fall detection = 12,6875_G
#define	XL345_TRESH_FF_VALUE_12_75_G	0xCC	//threshold value for free-fall detection = 12,75_G
#define	XL345_TRESH_FF_VALUE_12_81_G	0xCD	//threshold value for free-fall detection = 12,8125_G
#define	XL345_TRESH_FF_VALUE_12_88_G	0xCE	//threshold value for free-fall detection = 12,875_G
#define	XL345_TRESH_FF_VALUE_12_94_G	0xCF	//threshold value for free-fall detection = 12,9375_G
#define	XL345_TRESH_FF_VALUE_13_00_G	0xD0	//threshold value for free-fall detection = 13_G
#define	XL345_TRESH_FF_VALUE_13_06_G	0xD1	//threshold value for free-fall detection = 13,0625_G
#define	XL345_TRESH_FF_VALUE_13_13_G	0xD2	//threshold value for free-fall detection = 13,125_G
#define	XL345_TRESH_FF_VALUE_13_19_G	0xD3	//threshold value for free-fall detection = 13,1875_G
#define	XL345_TRESH_FF_VALUE_13_25_G	0xD4	//threshold value for free-fall detection = 13,25_G
#define	XL345_TRESH_FF_VALUE_13_31_G	0xD5	//threshold value for free-fall detection = 13,3125_G
#define	XL345_TRESH_FF_VALUE_13_38_G	0xD6	//threshold value for free-fall detection = 13,375_G
#define	XL345_TRESH_FF_VALUE_13_44_G	0xD7	//threshold value for free-fall detection = 13,4375_G
#define	XL345_TRESH_FF_VALUE_13_50_G	0xD8	//threshold value for free-fall detection = 13,5_G
#define	XL345_TRESH_FF_VALUE_13_56_G	0xD9	//threshold value for free-fall detection = 13,5625_G
#define	XL345_TRESH_FF_VALUE_13_63_G	0xDA	//threshold value for free-fall detection = 13,625_G
#define	XL345_TRESH_FF_VALUE_13_69_G	0xDB	//threshold value for free-fall detection = 13,6875_G
#define	XL345_TRESH_FF_VALUE_13_75_G	0xDC	//threshold value for free-fall detection = 13,75_G
#define	XL345_TRESH_FF_VALUE_13_81_G	0xDD	//threshold value for free-fall detection = 13,8125_G
#define	XL345_TRESH_FF_VALUE_13_88_G	0xDE	//threshold value for free-fall detection = 13,875_G
#define	XL345_TRESH_FF_VALUE_13_94_G	0xDF	//threshold value for free-fall detection = 13,9375_G
#define	XL345_TRESH_FF_VALUE_14_00_G	0xE0	//threshold value for free-fall detection = 14_G
#define	XL345_TRESH_FF_VALUE_14_06_G	0xE1	//threshold value for free-fall detection = 14,0625_G
#define	XL345_TRESH_FF_VALUE_14_13_G	0xE2	//threshold value for free-fall detection = 14,125_G
#define	XL345_TRESH_FF_VALUE_14_19_G	0xE3	//threshold value for free-fall detection = 14,1875_G
#define	XL345_TRESH_FF_VALUE_14_25_G	0xE4	//threshold value for free-fall detection = 14,25_G
#define	XL345_TRESH_FF_VALUE_14_31_G	0xE5	//threshold value for free-fall detection = 14,3125_G
#define	XL345_TRESH_FF_VALUE_14_38_G	0xE6	//threshold value for free-fall detection = 14,375_G
#define	XL345_TRESH_FF_VALUE_14_44_G	0xE7	//threshold value for free-fall detection = 14,4375_G
#define	XL345_TRESH_FF_VALUE_14_50_G	0xE8	//threshold value for free-fall detection = 14,5_G
#define	XL345_TRESH_FF_VALUE_14_56_G	0xE9	//threshold value for free-fall detection = 14,5625_G
#define	XL345_TRESH_FF_VALUE_14_63_G	0xEA	//threshold value for free-fall detection = 14,625_G
#define	XL345_TRESH_FF_VALUE_14_69_G	0xEB	//threshold value for free-fall detection = 14,6875_G
#define	XL345_TRESH_FF_VALUE_14_75_G	0xEC	//threshold value for free-fall detection = 14,75_G
#define	XL345_TRESH_FF_VALUE_14_81_G	0xED	//threshold value for free-fall detection = 14,8125_G
#define	XL345_TRESH_FF_VALUE_14_88_G	0xEE	//threshold value for free-fall detection = 14,875_G
#define	XL345_TRESH_FF_VALUE_14_94_G	0xEF	//threshold value for free-fall detection = 14,9375_G
#define	XL345_TRESH_FF_VALUE_15_00_G	0xF0	//threshold value for free-fall detection = 15_G
#define	XL345_TRESH_FF_VALUE_15_06_G	0xF1	//threshold value for free-fall detection = 15,0625_G
#define	XL345_TRESH_FF_VALUE_15_13_G	0xF2	//threshold value for free-fall detection = 15,125_G
#define	XL345_TRESH_FF_VALUE_15_19_G	0xF3	//threshold value for free-fall detection = 15,1875_G
#define	XL345_TRESH_FF_VALUE_15_25_G	0xF4	//threshold value for free-fall detection = 15,25_G
#define	XL345_TRESH_FF_VALUE_15_31_G	0xF5	//threshold value for free-fall detection = 15,3125_G
#define	XL345_TRESH_FF_VALUE_15_38_G	0xF6	//threshold value for free-fall detection = 15,375_G
#define	XL345_TRESH_FF_VALUE_15_44_G	0xF7	//threshold value for free-fall detection = 15,4375_G
#define	XL345_TRESH_FF_VALUE_15_50_G	0xF8	//threshold value for free-fall detection = 15,5_G
#define	XL345_TRESH_FF_VALUE_15_56_G	0xF9	//threshold value for free-fall detection = 15,5625_G
#define	XL345_TRESH_FF_VALUE_15_63_G	0xFA	//threshold value for free-fall detection = 15,625_G
#define	XL345_TRESH_FF_VALUE_15_69_G	0xFB	//threshold value for free-fall detection = 15,6875_G
#define	XL345_TRESH_FF_VALUE_15_75_G	0xFC	//threshold value for free-fall detection = 15,75_G
#define	XL345_TRESH_FF_VALUE_15_81_G	0xFD	//threshold value for free-fall detection = 15,8125_G
#define	XL345_TRESH_FF_VALUE_15_88_G	0xFE	//threshold value for free-fall detection = 15,875_G
#define	XL345_TRESH_FF_VALUE_16_94_G	0xFF	//threshold value for free-fall detection = 15,9375_G

/*
The TIME_FF register is eight bits and stores an unsigned time
value representing the minimum time that the value of all axes
must be less than THRESH_FF to generate a free-fall interrupt.
The scale factor is 5 ms/LSB. A value of 0 may result in undesirable
behavior if the free-fall interrupt is enabled. Values between 100 ms
and 350 ms (0x14 to 0x46) are recommended.
 */

#define	XL345_TIME_FF_VALUE_0_MS	0x00	//result in undesirable behavior if the free fall interrupt is enabled = 0_MS
#define	XL345_TIME_FF_VALUE_5_MS	0x01	//threshold value for free-fall detection = 5_MS
#define	XL345_TIME_FF_VALUE_10_MS	0x02	//threshold value for free-fall detection = 10_MS
#define	XL345_TIME_FF_VALUE_15_MS	0x03	//threshold value for free-fall detection = 15_MS
#define	XL345_TIME_FF_VALUE_20_MS	0x04	//threshold value for free-fall detection = 20_MS
#define	XL345_TIME_FF_VALUE_25_MS	0x05	//threshold value for free-fall detection = 25_MS
#define	XL345_TIME_FF_VALUE_30_MS	0x06	//threshold value for free-fall detection = 30_MS
#define	XL345_TIME_FF_VALUE_35_MS	0x07	//threshold value for free-fall detection = 35_MS
#define	XL345_TIME_FF_VALUE_40_MS	0x08	//threshold value for free-fall detection = 40_MS
#define	XL345_TIME_FF_VALUE_45_MS	0x09	//threshold value for free-fall detection = 45_MS
#define	XL345_TIME_FF_VALUE_50_MS	0x0A	//threshold value for free-fall detection = 50_MS
#define	XL345_TIME_FF_VALUE_55_MS	0x0B	//threshold value for free-fall detection = 55_MS
#define	XL345_TIME_FF_VALUE_60_MS	0x0C	//threshold value for free-fall detection = 60_MS
#define	XL345_TIME_FF_VALUE_65_MS	0x0D	//threshold value for free-fall detection = 65_MS
#define	XL345_TIME_FF_VALUE_70_MS	0x0E	//threshold value for free-fall detection = 70_MS
#define	XL345_TIME_FF_VALUE_75_MS	0x0F	//threshold value for free-fall detection = 75_MS
#define	XL345_TIME_FF_VALUE_80_MS	0x10	//threshold value for free-fall detection = 80_MS
#define	XL345_TIME_FF_VALUE_85_MS	0x11	//threshold value for free-fall detection = 85_MS
#define	XL345_TIME_FF_VALUE_90_MS	0x12	//threshold value for free-fall detection = 90_MS
#define	XL345_TIME_FF_VALUE_95_MS	0x13	//threshold value for free-fall detection = 95_MS

#define	XL345_TIME_FF_VALUE_100_MS	0x14	//threshold value for free-fall detection = 100_MS
#define	XL345_TIME_FF_VALUE_105_MS	0x15	//threshold value for free-fall detection = 105_MS
#define	XL345_TIME_FF_VALUE_110_MS	0x16	//threshold value for free-fall detection = 110_MS
#define	XL345_TIME_FF_VALUE_115_MS	0x17	//threshold value for free-fall detection = 115_MS
#define	XL345_TIME_FF_VALUE_120_MS	0x18	//threshold value for free-fall detection = 120_MS
#define	XL345_TIME_FF_VALUE_125_MS	0x19	//threshold value for free-fall detection = 125_MS
#define	XL345_TIME_FF_VALUE_130_MS	0x1A	//threshold value for free-fall detection = 130_MS
#define	XL345_TIME_FF_VALUE_135_MS	0x1B	//threshold value for free-fall detection = 135_MS
#define	XL345_TIME_FF_VALUE_140_MS	0x1C	//threshold value for free-fall detection = 140_MS
#define	XL345_TIME_FF_VALUE_145_MS	0x1D	//threshold value for free-fall detection = 145_MS
#define	XL345_TIME_FF_VALUE_150_MS	0x1E	//threshold value for free-fall detection = 150_MS
#define	XL345_TIME_FF_VALUE_155_MS	0x1F	//threshold value for free-fall detection = 155_MS
#define	XL345_TIME_FF_VALUE_160_MS	0x20	//threshold value for free-fall detection = 160_MS
#define	XL345_TIME_FF_VALUE_165_MS	0x21	//threshold value for free-fall detection = 165_MS
#define	XL345_TIME_FF_VALUE_170_MS	0x22	//threshold value for free-fall detection = 170_MS
#define	XL345_TIME_FF_VALUE_175_MS	0x23	//threshold value for free-fall detection = 175_MS
#define	XL345_TIME_FF_VALUE_180_MS	0x24	//threshold value for free-fall detection = 180_MS
#define	XL345_TIME_FF_VALUE_185_MS	0x25	//threshold value for free-fall detection = 185_MS
#define	XL345_TIME_FF_VALUE_190_MS	0x26	//threshold value for free-fall detection = 190_MS
#define	XL345_TIME_FF_VALUE_195_MS	0x27	//threshold value for free-fall detection = 195_MS
#define	XL345_TIME_FF_VALUE_200_MS	0x28	//threshold value for free-fall detection = 200_MS
#define	XL345_TIME_FF_VALUE_205_MS	0x29	//threshold value for free-fall detection = 205_MS
#define	XL345_TIME_FF_VALUE_210_MS	0x2A	//threshold value for free-fall detection = 210_MS
#define	XL345_TIME_FF_VALUE_215_MS	0x2B	//threshold value for free-fall detection = 215_MS
#define	XL345_TIME_FF_VALUE_220_MS	0x2C	//threshold value for free-fall detection = 220_MS
#define	XL345_TIME_FF_VALUE_225_MS	0x2D	//threshold value for free-fall detection = 225_MS
#define	XL345_TIME_FF_VALUE_230_MS	0x2E	//threshold value for free-fall detection = 230_MS
#define	XL345_TIME_FF_VALUE_235_MS	0x2F	//threshold value for free-fall detection = 235_MS
#define	XL345_TIME_FF_VALUE_240_MS	0x30	//threshold value for free-fall detection = 240_MS
#define	XL345_TIME_FF_VALUE_245_MS	0x31	//threshold value for free-fall detection = 245_MS
#define	XL345_TIME_FF_VALUE_250_MS	0x32	//threshold value for free-fall detection = 250_MS
#define	XL345_TIME_FF_VALUE_255_MS	0x33	//threshold value for free-fall detection = 255_MS
#define	XL345_TIME_FF_VALUE_260_MS	0x34	//threshold value for free-fall detection = 260_MS
#define	XL345_TIME_FF_VALUE_265_MS	0x35	//threshold value for free-fall detection = 265_MS
#define	XL345_TIME_FF_VALUE_270_MS	0x36	//threshold value for free-fall detection = 270_MS
#define	XL345_TIME_FF_VALUE_275_MS	0x37	//threshold value for free-fall detection = 275_MS
#define	XL345_TIME_FF_VALUE_280_MS	0x38	//threshold value for free-fall detection = 280_MS
#define	XL345_TIME_FF_VALUE_285_MS	0x39	//threshold value for free-fall detection = 285_MS
#define	XL345_TIME_FF_VALUE_290_MS	0x3A	//threshold value for free-fall detection = 290_MS
#define	XL345_TIME_FF_VALUE_295_MS	0x3B	//threshold value for free-fall detection = 295_MS
#define	XL345_TIME_FF_VALUE_300_MS	0x3C	//threshold value for free-fall detection = 300_MS
#define	XL345_TIME_FF_VALUE_305_MS	0x3D	//threshold value for free-fall detection = 305_MS
#define	XL345_TIME_FF_VALUE_310_MS	0x3E	//threshold value for free-fall detection = 310_MS
#define	XL345_TIME_FF_VALUE_315_MS	0x3F	//threshold value for free-fall detection = 315_MS
#define	XL345_TIME_FF_VALUE_320_MS	0x40	//threshold value for free-fall detection = 320_MS
#define	XL345_TIME_FF_VALUE_325_MS	0x41	//threshold value for free-fall detection = 325_MS
#define	XL345_TIME_FF_VALUE_330_MS	0x42	//threshold value for free-fall detection = 330_MS
#define	XL345_TIME_FF_VALUE_335_MS	0x43	//threshold value for free-fall detection = 335_MS
#define	XL345_TIME_FF_VALUE_340_MS	0x44	//threshold value for free-fall detection = 340_MS
#define	XL345_TIME_FF_VALUE_345_MS	0x45	//threshold value for free-fall detection = 345_MS
#define	XL345_TIME_FF_VALUE_350_MS	0x46	//threshold value for free-fall detection = 350_MS

#define	XL345_TIME_FF_VALUE_355_MS	0x47	//threshold value for free-fall detection = 355_MS
#define	XL345_TIME_FF_VALUE_360_MS	0x48	//threshold value for free-fall detection = 360_MS
#define	XL345_TIME_FF_VALUE_365_MS	0x49	//threshold value for free-fall detection = 365_MS
#define	XL345_TIME_FF_VALUE_370_MS	0x4A	//threshold value for free-fall detection = 370_MS
#define	XL345_TIME_FF_VALUE_375_MS	0x4B	//threshold value for free-fall detection = 375_MS
#define	XL345_TIME_FF_VALUE_380_MS	0x4C	//threshold value for free-fall detection = 380_MS
#define	XL345_TIME_FF_VALUE_385_MS	0x4D	//threshold value for free-fall detection = 385_MS
#define	XL345_TIME_FF_VALUE_390_MS	0x4E	//threshold value for free-fall detection = 390_MS
#define	XL345_TIME_FF_VALUE_395_MS	0x4F	//threshold value for free-fall detection = 395_MS
#define	XL345_TIME_FF_VALUE_400_MS	0x50	//threshold value for free-fall detection = 400_MS
#define	XL345_TIME_FF_VALUE_405_MS	0x51	//threshold value for free-fall detection = 405_MS
#define	XL345_TIME_FF_VALUE_410_MS	0x52	//threshold value for free-fall detection = 410_MS
#define	XL345_TIME_FF_VALUE_415_MS	0x53	//threshold value for free-fall detection = 415_MS
#define	XL345_TIME_FF_VALUE_420_MS	0x54	//threshold value for free-fall detection = 420_MS
#define	XL345_TIME_FF_VALUE_425_MS	0x55	//threshold value for free-fall detection = 425_MS
#define	XL345_TIME_FF_VALUE_430_MS	0x56	//threshold value for free-fall detection = 430_MS
#define	XL345_TIME_FF_VALUE_435_MS	0x57	//threshold value for free-fall detection = 435_MS
#define	XL345_TIME_FF_VALUE_440_MS	0x58	//threshold value for free-fall detection = 440_MS
#define	XL345_TIME_FF_VALUE_445_MS	0x59	//threshold value for free-fall detection = 445_MS
#define	XL345_TIME_FF_VALUE_450_MS	0x5A	//threshold value for free-fall detection = 450_MS
#define	XL345_TIME_FF_VALUE_455_MS	0x5B	//threshold value for free-fall detection = 455_MS
#define	XL345_TIME_FF_VALUE_460_MS	0x5C	//threshold value for free-fall detection = 460_MS
#define	XL345_TIME_FF_VALUE_465_MS	0x5D	//threshold value for free-fall detection = 465_MS
#define	XL345_TIME_FF_VALUE_470_MS	0x5E	//threshold value for free-fall detection = 470_MS
#define	XL345_TIME_FF_VALUE_475_MS	0x5F	//threshold value for free-fall detection = 475_MS
#define	XL345_TIME_FF_VALUE_480_MS	0x60	//threshold value for free-fall detection = 480_MS
#define	XL345_TIME_FF_VALUE_485_MS	0x61	//threshold value for free-fall detection = 485_MS
#define	XL345_TIME_FF_VALUE_490_MS	0x62	//threshold value for free-fall detection = 490_MS
#define	XL345_TIME_FF_VALUE_495_MS	0x63	//threshold value for free-fall detection = 495_MS
#define	XL345_TIME_FF_VALUE_500_MS	0x64	//threshold value for free-fall detection = 500_MS
#define	XL345_TIME_FF_VALUE_505_MS	0x65	//threshold value for free-fall detection = 505_MS
#define	XL345_TIME_FF_VALUE_510_MS	0x66	//threshold value for free-fall detection = 510_MS
#define	XL345_TIME_FF_VALUE_515_MS	0x67	//threshold value for free-fall detection = 515_MS
#define	XL345_TIME_FF_VALUE_520_MS	0x68	//threshold value for free-fall detection = 520_MS
#define	XL345_TIME_FF_VALUE_525_MS	0x69	//threshold value for free-fall detection = 525_MS
#define	XL345_TIME_FF_VALUE_530_MS	0x6A	//threshold value for free-fall detection = 530_MS
#define	XL345_TIME_FF_VALUE_535_MS	0x6B	//threshold value for free-fall detection = 535_MS
#define	XL345_TIME_FF_VALUE_540_MS	0x6C	//threshold value for free-fall detection = 540_MS
#define	XL345_TIME_FF_VALUE_545_MS	0x6D	//threshold value for free-fall detection = 545_MS
#define	XL345_TIME_FF_VALUE_550_MS	0x6E	//threshold value for free-fall detection = 550_MS
#define	XL345_TIME_FF_VALUE_555_MS	0x6F	//threshold value for free-fall detection = 555_MS
#define	XL345_TIME_FF_VALUE_560_MS	0x70	//threshold value for free-fall detection = 560_MS
#define	XL345_TIME_FF_VALUE_565_MS	0x71	//threshold value for free-fall detection = 565_MS
#define	XL345_TIME_FF_VALUE_570_MS	0x72	//threshold value for free-fall detection = 570_MS
#define	XL345_TIME_FF_VALUE_575_MS	0x73	//threshold value for free-fall detection = 575_MS
#define	XL345_TIME_FF_VALUE_580_MS	0x74	//threshold value for free-fall detection = 580_MS
#define	XL345_TIME_FF_VALUE_585_MS	0x75	//threshold value for free-fall detection = 585_MS
#define	XL345_TIME_FF_VALUE_590_MS	0x76	//threshold value for free-fall detection = 590_MS
#define	XL345_TIME_FF_VALUE_595_MS	0x77	//threshold value for free-fall detection = 595_MS
#define	XL345_TIME_FF_VALUE_600_MS	0x78	//threshold value for free-fall detection = 600_MS
#define	XL345_TIME_FF_VALUE_605_MS	0x79	//threshold value for free-fall detection = 605_MS
#define	XL345_TIME_FF_VALUE_610_MS	0x7A	//threshold value for free-fall detection = 610_MS
#define	XL345_TIME_FF_VALUE_615_MS	0x7B	//threshold value for free-fall detection = 615_MS
#define	XL345_TIME_FF_VALUE_620_MS	0x7C	//threshold value for free-fall detection = 620_MS
#define	XL345_TIME_FF_VALUE_625_MS	0x7D	//threshold value for free-fall detection = 625_MS
#define	XL345_TIME_FF_VALUE_630_MS	0x7E	//threshold value for free-fall detection = 630_MS
#define	XL345_TIME_FF_VALUE_635_MS	0x7F	//threshold value for free-fall detection = 635_MS
#define	XL345_TIME_FF_VALUE_640_MS	0x80	//threshold value for free-fall detection = 640_MS
#define	XL345_TIME_FF_VALUE_645_MS	0x81	//threshold value for free-fall detection = 645_MS
#define	XL345_TIME_FF_VALUE_650_MS	0x82	//threshold value for free-fall detection = 650_MS
#define	XL345_TIME_FF_VALUE_655_MS	0x83	//threshold value for free-fall detection = 655_MS
#define	XL345_TIME_FF_VALUE_660_MS	0x84	//threshold value for free-fall detection = 660_MS
#define	XL345_TIME_FF_VALUE_665_MS	0x85	//threshold value for free-fall detection = 665_MS
#define	XL345_TIME_FF_VALUE_670_MS	0x86	//threshold value for free-fall detection = 670_MS
#define	XL345_TIME_FF_VALUE_675_MS	0x87	//threshold value for free-fall detection = 675_MS
#define	XL345_TIME_FF_VALUE_680_MS	0x88	//threshold value for free-fall detection = 680_MS
#define	XL345_TIME_FF_VALUE_685_MS	0x89	//threshold value for free-fall detection = 685_MS
#define	XL345_TIME_FF_VALUE_690_MS	0x8A	//threshold value for free-fall detection = 690_MS
#define	XL345_TIME_FF_VALUE_695_MS	0x8B	//threshold value for free-fall detection = 695_MS
#define	XL345_TIME_FF_VALUE_700_MS	0x8C	//threshold value for free-fall detection = 700_MS
#define	XL345_TIME_FF_VALUE_705_MS	0x8D	//threshold value for free-fall detection = 705_MS
#define	XL345_TIME_FF_VALUE_710_MS	0x8E	//threshold value for free-fall detection = 710_MS
#define	XL345_TIME_FF_VALUE_715_MS	0x8F	//threshold value for free-fall detection = 715_MS
#define	XL345_TIME_FF_VALUE_720_MS	0x90	//threshold value for free-fall detection = 720_MS
#define	XL345_TIME_FF_VALUE_725_MS	0x91	//threshold value for free-fall detection = 725_MS
#define	XL345_TIME_FF_VALUE_730_MS	0x92	//threshold value for free-fall detection = 730_MS
#define	XL345_TIME_FF_VALUE_735_MS	0x93	//threshold value for free-fall detection = 735_MS
#define	XL345_TIME_FF_VALUE_740_MS	0x94	//threshold value for free-fall detection = 740_MS
#define	XL345_TIME_FF_VALUE_745_MS	0x95	//threshold value for free-fall detection = 745_MS
#define	XL345_TIME_FF_VALUE_750_MS	0x96	//threshold value for free-fall detection = 750_MS
#define	XL345_TIME_FF_VALUE_755_MS	0x97	//threshold value for free-fall detection = 755_MS
#define	XL345_TIME_FF_VALUE_760_MS	0x98	//threshold value for free-fall detection = 760_MS
#define	XL345_TIME_FF_VALUE_765_MS	0x99	//threshold value for free-fall detection = 765_MS
#define	XL345_TIME_FF_VALUE_770_MS	0x9A	//threshold value for free-fall detection = 770_MS
#define	XL345_TIME_FF_VALUE_775_MS	0x9B	//threshold value for free-fall detection = 775_MS
#define	XL345_TIME_FF_VALUE_780_MS	0x9C	//threshold value for free-fall detection = 780_MS
#define	XL345_TIME_FF_VALUE_785_MS	0x9D	//threshold value for free-fall detection = 785_MS
#define	XL345_TIME_FF_VALUE_790_MS	0x9E	//threshold value for free-fall detection = 790_MS
#define	XL345_TIME_FF_VALUE_795_MS	0x9F	//threshold value for free-fall detection = 795_MS
#define	XL345_TIME_FF_VALUE_800_MS	0xA0	//threshold value for free-fall detection = 800_MS
#define	XL345_TIME_FF_VALUE_805_MS	0xA1	//threshold value for free-fall detection = 805_MS
#define	XL345_TIME_FF_VALUE_810_MS	0xA2	//threshold value for free-fall detection = 810_MS
#define	XL345_TIME_FF_VALUE_815_MS	0xA3	//threshold value for free-fall detection = 815_MS
#define	XL345_TIME_FF_VALUE_820_MS	0xA4	//threshold value for free-fall detection = 820_MS
#define	XL345_TIME_FF_VALUE_825_MS	0xA5	//threshold value for free-fall detection = 825_MS
#define	XL345_TIME_FF_VALUE_830_MS	0xA6	//threshold value for free-fall detection = 830_MS
#define	XL345_TIME_FF_VALUE_835_MS	0xA7	//threshold value for free-fall detection = 835_MS
#define	XL345_TIME_FF_VALUE_840_MS	0xA8	//threshold value for free-fall detection = 840_MS
#define	XL345_TIME_FF_VALUE_845_MS	0xA9	//threshold value for free-fall detection = 845_MS
#define	XL345_TIME_FF_VALUE_850_MS	0xAA	//threshold value for free-fall detection = 850_MS
#define	XL345_TIME_FF_VALUE_855_MS	0xAB	//threshold value for free-fall detection = 855_MS
#define	XL345_TIME_FF_VALUE_860_MS	0xAC	//threshold value for free-fall detection = 860_MS
#define	XL345_TIME_FF_VALUE_865_MS	0xAD	//threshold value for free-fall detection = 865_MS
#define	XL345_TIME_FF_VALUE_870_MS	0xAE	//threshold value for free-fall detection = 870_MS
#define	XL345_TIME_FF_VALUE_875_MS	0xAF	//threshold value for free-fall detection = 875_MS
#define	XL345_TIME_FF_VALUE_880_MS	0xB0	//threshold value for free-fall detection = 880_MS
#define	XL345_TIME_FF_VALUE_885_MS	0xB1	//threshold value for free-fall detection = 885_MS
#define	XL345_TIME_FF_VALUE_890_MS	0xB2	//threshold value for free-fall detection = 890_MS
#define	XL345_TIME_FF_VALUE_895_MS	0xB3	//threshold value for free-fall detection = 895_MS
#define	XL345_TIME_FF_VALUE_900_MS	0xB4	//threshold value for free-fall detection = 900_MS
#define	XL345_TIME_FF_VALUE_905_MS	0xB5	//threshold value for free-fall detection = 905_MS
#define	XL345_TIME_FF_VALUE_910_MS	0xB6	//threshold value for free-fall detection = 910_MS
#define	XL345_TIME_FF_VALUE_915_MS	0xB7	//threshold value for free-fall detection = 915_MS
#define	XL345_TIME_FF_VALUE_920_MS	0xB8	//threshold value for free-fall detection = 920_MS
#define	XL345_TIME_FF_VALUE_925_MS	0xB9	//threshold value for free-fall detection = 925_MS
#define	XL345_TIME_FF_VALUE_930_MS	0xBA	//threshold value for free-fall detection = 930_MS
#define	XL345_TIME_FF_VALUE_935_MS	0xBB	//threshold value for free-fall detection = 935_MS
#define	XL345_TIME_FF_VALUE_940_MS	0xBC	//threshold value for free-fall detection = 940_MS
#define	XL345_TIME_FF_VALUE_945_MS	0xBD	//threshold value for free-fall detection = 945_MS
#define	XL345_TIME_FF_VALUE_950_MS	0xBE	//threshold value for free-fall detection = 950_MS
#define	XL345_TIME_FF_VALUE_955_MS	0xBF	//threshold value for free-fall detection = 955_MS
#define	XL345_TIME_FF_VALUE_960_MS	0xC0	//threshold value for free-fall detection = 960_MS
#define	XL345_TIME_FF_VALUE_965_MS	0xC1	//threshold value for free-fall detection = 965_MS
#define	XL345_TIME_FF_VALUE_970_MS	0xC2	//threshold value for free-fall detection = 970_MS
#define	XL345_TIME_FF_VALUE_975_MS	0xC3	//threshold value for free-fall detection = 975_MS
#define	XL345_TIME_FF_VALUE_980_MS	0xC4	//threshold value for free-fall detection = 980_MS
#define	XL345_TIME_FF_VALUE_985_MS	0xC5	//threshold value for free-fall detection = 985_MS
#define	XL345_TIME_FF_VALUE_990_MS	0xC6	//threshold value for free-fall detection = 990_MS
#define	XL345_TIME_FF_VALUE_995_MS	0xC7	//threshold value for free-fall detection = 995_MS
#define	XL345_TIME_FF_VALUE_1000_MS	0xC8	//threshold value for free-fall detection = 1000_MS
#define	XL345_TIME_FF_VALUE_1005_MS	0xC9	//threshold value for free-fall detection = 1005_MS
#define	XL345_TIME_FF_VALUE_1010_MS	0xCA	//threshold value for free-fall detection = 1010_MS
#define	XL345_TIME_FF_VALUE_1015_MS	0xCB	//threshold value for free-fall detection = 1015_MS
#define	XL345_TIME_FF_VALUE_1020_MS	0xCC	//threshold value for free-fall detection = 1020_MS
#define	XL345_TIME_FF_VALUE_1025_MS	0xCD	//threshold value for free-fall detection = 1025_MS
#define	XL345_TIME_FF_VALUE_1030_MS	0xCE	//threshold value for free-fall detection = 1030_MS
#define	XL345_TIME_FF_VALUE_1035_MS	0xCF	//threshold value for free-fall detection = 1035_MS
#define	XL345_TIME_FF_VALUE_1040_MS	0xD0	//threshold value for free-fall detection = 1040_MS
#define	XL345_TIME_FF_VALUE_1045_MS	0xD1	//threshold value for free-fall detection = 1045_MS
#define	XL345_TIME_FF_VALUE_1050_MS	0xD2	//threshold value for free-fall detection = 1050_MS
#define	XL345_TIME_FF_VALUE_1055_MS	0xD3	//threshold value for free-fall detection = 1055_MS
#define	XL345_TIME_FF_VALUE_1060_MS	0xD4	//threshold value for free-fall detection = 1060_MS
#define	XL345_TIME_FF_VALUE_1065_MS	0xD5	//threshold value for free-fall detection = 1065_MS
#define	XL345_TIME_FF_VALUE_1070_MS	0xD6	//threshold value for free-fall detection = 1070_MS
#define	XL345_TIME_FF_VALUE_1075_MS	0xD7	//threshold value for free-fall detection = 1075_MS
#define	XL345_TIME_FF_VALUE_1080_MS	0xD8	//threshold value for free-fall detection = 1080_MS
#define	XL345_TIME_FF_VALUE_1085_MS	0xD9	//threshold value for free-fall detection = 1085_MS
#define	XL345_TIME_FF_VALUE_1090_MS	0xDA	//threshold value for free-fall detection = 1090_MS
#define	XL345_TIME_FF_VALUE_1095_MS	0xDB	//threshold value for free-fall detection = 1095_MS
#define	XL345_TIME_FF_VALUE_1100_MS	0xDC	//threshold value for free-fall detection = 1100_MS
#define	XL345_TIME_FF_VALUE_1105_MS	0xDD	//threshold value for free-fall detection = 1105_MS
#define	XL345_TIME_FF_VALUE_1110_MS	0xDE	//threshold value for free-fall detection = 1110_MS
#define	XL345_TIME_FF_VALUE_1115_MS	0xDF	//threshold value for free-fall detection = 1115_MS
#define	XL345_TIME_FF_VALUE_1120_MS	0xE0	//threshold value for free-fall detection = 1120_MS
#define	XL345_TIME_FF_VALUE_1125_MS	0xE1	//threshold value for free-fall detection = 1125_MS
#define	XL345_TIME_FF_VALUE_1130_MS	0xE2	//threshold value for free-fall detection = 1130_MS
#define	XL345_TIME_FF_VALUE_1135_MS	0xE3	//threshold value for free-fall detection = 1135_MS
#define	XL345_TIME_FF_VALUE_1140_MS	0xE4	//threshold value for free-fall detection = 1140_MS
#define	XL345_TIME_FF_VALUE_1145_MS	0xE5	//threshold value for free-fall detection = 1145_MS
#define	XL345_TIME_FF_VALUE_1150_MS	0xE6	//threshold value for free-fall detection = 1150_MS
#define	XL345_TIME_FF_VALUE_1155_MS	0xE7	//threshold value for free-fall detection = 1155_MS
#define	XL345_TIME_FF_VALUE_1160_MS	0xE8	//threshold value for free-fall detection = 1160_MS
#define	XL345_TIME_FF_VALUE_1165_MS	0xE9	//threshold value for free-fall detection = 1165_MS
#define	XL345_TIME_FF_VALUE_1170_MS	0xEA	//threshold value for free-fall detection = 1170_MS
#define	XL345_TIME_FF_VALUE_1175_MS	0xEB	//threshold value for free-fall detection = 1175_MS
#define	XL345_TIME_FF_VALUE_1180_MS	0xEC	//threshold value for free-fall detection = 1180_MS
#define	XL345_TIME_FF_VALUE_1185_MS	0xED	//threshold value for free-fall detection = 1185_MS
#define	XL345_TIME_FF_VALUE_1190_MS	0xEE	//threshold value for free-fall detection = 1190_MS
#define	XL345_TIME_FF_VALUE_1195_MS	0xEF	//threshold value for free-fall detection = 1195_MS
#define	XL345_TIME_FF_VALUE_1200_MS	0xF0	//threshold value for free-fall detection = 1200_MS
#define	XL345_TIME_FF_VALUE_1205_MS	0xF1	//threshold value for free-fall detection = 1205_MS
#define	XL345_TIME_FF_VALUE_1210_MS	0xF2	//threshold value for free-fall detection = 1210_MS
#define	XL345_TIME_FF_VALUE_1215_MS	0xF3	//threshold value for free-fall detection = 1215_MS
#define	XL345_TIME_FF_VALUE_1220_MS	0xF4	//threshold value for free-fall detection = 1220_MS
#define	XL345_TIME_FF_VALUE_1225_MS	0xF5	//threshold value for free-fall detection = 1225_MS
#define	XL345_TIME_FF_VALUE_1230_MS	0xF6	//threshold value for free-fall detection = 1230_MS
#define	XL345_TIME_FF_VALUE_1235_MS	0xF7	//threshold value for free-fall detection = 1235_MS
#define	XL345_TIME_FF_VALUE_1240_MS	0xF8	//threshold value for free-fall detection = 1240_MS
#define	XL345_TIME_FF_VALUE_1245_MS	0xF9	//threshold value for free-fall detection = 1245_MS
#define	XL345_TIME_FF_VALUE_1250_MS	0xFA	//threshold value for free-fall detection = 1250_MS
#define	XL345_TIME_FF_VALUE_1255_MS	0xFB	//threshold value for free-fall detection = 1255_MS
#define	XL345_TIME_FF_VALUE_1260_MS	0xFC	//threshold value for free-fall detection = 1260_MS
#define	XL345_TIME_FF_VALUE_1265_MS	0xFD	//threshold value for free-fall detection = 1265_MS
#define	XL345_TIME_FF_VALUE_1270_MS	0xFE	//threshold value for free-fall detection = 1270_MS
#define	XL345_TIME_FF_VALUE_1275_MS	0xFF	//threshold value for free-fall detection = 1275_MS

extern int mz;//globale variable, wird mit 1xtap erhöht und 2xtap (bzw xachsentap jetzt) verringert
extern int wait;//globale variable, verhindert 2xhintereinander 1xtaps

extern unsigned char xl345read(unsigned char readbyte);
extern char xl345read_signed(unsigned char readbyte);
extern void xl345write(unsigned char reg, unsigned char val);
extern void xl345test();
extern int xl345datax();
extern int xl345datax();
extern int xl345datax();
extern long int xl345fulldata(int wahl);
extern void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);
extern void init_xl345_c1();
extern void init_xl345_c2();
extern void init_xl345_c3();


#endif	/* ADXL345_V2_H */

