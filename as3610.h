/* 
 * File:   as3610.h
 * Author: emu
 *
 * Created on 08. November 2013, 22:03
 */

#ifndef AS3610_H
#define	AS3610_H

#define AS3610_CHARGER_CONTROL_1_REGISTER           0x00    //This register controls the mode of the charger and the charger state machine.
#define AS3610_CHARGER_VOLTAGE_CONTROL_REGISTER     0x01    //This register controls the charger voltages.
#define AS3610_CHARGER_CURRENT_CONTROL_REGISTER     0x02    //This register controls the charger currents.
#define AS3610_NTC_SUPERVISION_REGISTER             0x03    //These bits define the battery temperature supervision.
#define AS3610_CHARGER_SUPERVISION_REGISTER         0x04    //These bits define charging timer settings.
#define AS3610_CHARGER_STATUS_1_REGISTER            0x05    //These bits show the status of the charger.
#define AS3610_CHARGER_STATUS_2_REGISTER            0x06    //These bits show the status of the charger.
#define AS3610_ASIC_ID1_REGISTER                    0x3E
#define AS3610_ASIC_ID2_REGISTER                    0x3F

/* Charger Control Register :Addr: 0x00
This register controls the mode of the charger and the charger state machine.*/

//bit 0:
/* ON/OFF control of USB charger input*/
#define AS3610_CHG_DIS                      0x00 //Charger disabled
#define AS3610_CHG_EN                       0x01 //Charger enabled, if XON=0

//bit 1:
/* ON/OFF control of Step up for USB OTG; Normal operation (usb current=0..6)*/
#define AS3610_BOOST_DIS                    0x00 //Step up disabled
#define AS3610_BOOST_EN                     0x02 //Step up enabled

//bit 2-4:
/* USB input current limit, AS3610 I2C version only*/
#define	USB_CURRENT_VALUE_100_OR_500_MA     0x00	//100mA, if pin USB500=0 or 500mA, if pin USB500=1
#define	USB_CURRENT_VALUE_100_MA            0x04	//100mA
#define	USB_CURRENT_VALUE_500_MA_LIMIT      0x08	//500mA limit
#define	USB_CURRENT_VALUE_900_MA_LIMIT      0x0C	//900mA limit
#define	USB_CURRENT_VALUE_UNLIMITED_1       0x10	//no limit
#define	USB_CURRENT_VALUE_NA                0x14	//NOT ASSIGNED!
#define	USB_CURRENT_VALUE_UNLIMITED_2       0x18	//no limit
#define	USB_CURRENT_VALUE_STAND_ALONE       0x1C	//AS3611 stand alone charger only w/o I2C
/* AS3611 stand alone charger only w/o I2C
 CHG_DET=1 and USB500=0 ? 100mA limit
 CHG_DET=1 and USB500=1 ? 500mA limit
 CHG_DET=0 and USB500=1 ? unlimited current */

//bit 5:
#define AS3610_PRECHG_DIS                   0x00
/* Pre-charge (trickle charge) disabled. Charger starts with
constant current, if VBAT>2.0V (current set by resistor I_SET)*/
#define AS3610_PRECHG_EN                    0x20
/* Pre-charge (trickle charge) enabled. Charger starts with
trickle current, if 2.9V>VBAT>2.0V (Current set by resistor I_term) */

//bit 6:
#define AS3610_ENABLE_TOFF                  0x00
/* Off time of step down charger enabled. If 100% pmos on
mode is needed, off pulses are skipped */
#define AS3610_DISABLE_TOFF                 0x40
/* Off time of step down charger disabled. Smooth transition
to 100% pmos on if needed (VBUS-VBAT is small) */

//bit 7:
#define AS3610_NO_BAT_DET_DIS               0x00 //Nobat detection disabled.
#define AS3610_NO_BAT_DET_EN                0x80
/* Nobat detection enabled. If No Battery is detected a small
current through NTC (approx. 0.5?A), checks if a battery
is connected again. A NTC is necessary for that setting. */

/* Charger Voltage Control Register (Address 0x01).
 This register controls the charger voltages. */

//bit 0-5:
/* End of charge voltage on VBAT */
#define	AS3610_VEOC_3_50_V	            0x00    //End of charge voltage on VBAT = 3.5V
#define	AS3610_VEOC_3_52_V	            0x01    //End of charge voltage on VBAT = 3.52V
#define	AS3610_VEOC_3_54_V	            0x02    //End of charge voltage on VBAT = 3.54V
#define	AS3610_VEOC_3_56_V	            0x03    //End of charge voltage on VBAT = 3.56V
#define	AS3610_VEOC_3_58_V	            0x04    //End of charge voltage on VBAT = 3.58V
#define	AS3610_VEOC_3_60_V	            0x05    //End of charge voltage on VBAT = 3.6V
#define	AS3610_VEOC_3_62_V	            0x06    //End of charge voltage on VBAT = 3.62V
#define	AS3610_VEOC_3_64_V	            0x07    //End of charge voltage on VBAT = 3.64V
#define	AS3610_VEOC_3_66_V	            0x08    //End of charge voltage on VBAT = 3.66V
#define	AS3610_VEOC_3_68_V	            0x09    //End of charge voltage on VBAT = 3.68V
#define	AS3610_VEOC_3_70_V	            0x0A    //End of charge voltage on VBAT = 3.7V
#define	AS3610_VEOC_3_72_V	            0x0B    //End of charge voltage on VBAT = 3.72V
#define	AS3610_VEOC_3_74_V	            0x0C    //End of charge voltage on VBAT = 3.74V
#define	AS3610_VEOC_3_76_V	            0x0D    //End of charge voltage on VBAT = 3.76V
#define	AS3610_VEOC_3_78_V	            0x0E    //End of charge voltage on VBAT = 3.78V
#define	AS3610_VEOC_3_80_V	            0x0F    //End of charge voltage on VBAT = 3.8V
#define	AS3610_VEOC_3_82_V	            0x10    //End of charge voltage on VBAT = 3.82V
#define	AS3610_VEOC_3_84_V	            0x11    //End of charge voltage on VBAT = 3.84V
#define	AS3610_VEOC_3_86_V	            0x12    //End of charge voltage on VBAT = 3.86V
#define	AS3610_VEOC_3_88_V	            0x13    //End of charge voltage on VBAT = 3.88V
#define	AS3610_VEOC_3_90_V	            0x14    //End of charge voltage on VBAT = 3.9V
#define	AS3610_VEOC_3_92_V	            0x15    //End of charge voltage on VBAT = 3.92V
#define	AS3610_VEOC_3_94_V	            0x16    //End of charge voltage on VBAT = 3.94V
#define	AS3610_VEOC_3_96_V	            0x17    //End of charge voltage on VBAT = 3.96V
#define	AS3610_VEOC_3_98_V	            0x18    //End of charge voltage on VBAT = 3.98V
#define	AS3610_VEOC_4_00_V	            0x19    //End of charge voltage on VBAT = 4V
#define	AS3610_VEOC_4_02_V	            0x1A    //End of charge voltage on VBAT = 4.02V
#define	AS3610_VEOC_4_04_V	            0x1B    //End of charge voltage on VBAT = 4.04V
#define	AS3610_VEOC_4_06_V	            0x1C    //End of charge voltage on VBAT = 4.06V
#define	AS3610_VEOC_4_08_V	            0x1D    //End of charge voltage on VBAT = 4.08V
#define	AS3610_VEOC_4_10_V	            0x1E    //End of charge voltage on VBAT = 4.1V
#define	AS3610_VEOC_4_12_V	            0x1F    //End of charge voltage on VBAT = 4.12V
#define	AS3610_VEOC_4_14_V	            0x20    //End of charge voltage on VBAT = 4.14V
#define	AS3610_VEOC_4_16_V	            0x21    //End of charge voltage on VBAT = 4.16V
#define	AS3610_VEOC_4_18_V	            0x22    //End of charge voltage on VBAT = 4.18V
#define	AS3610_VEOC_4_20_V	            0x23    //End of charge voltage on VBAT = 4.2V
#define	AS3610_VEOC_4_22_V	            0x24    //End of charge voltage on VBAT = 4.22V
#define	AS3610_VEOC_4_24_V	            0x25    //End of charge voltage on VBAT = 4.24V
#define	AS3610_VEOC_4_26_V	            0x26    //End of charge voltage on VBAT = 4.26V
#define	AS3610_VEOC_4_28_V	            0x27    //End of charge voltage on VBAT = 4.28V
#define	AS3610_VEOC_4_30_V	            0x28    //End of charge voltage on VBAT = 4.3V
#define	AS3610_VEOC_4_32_V	            0x29    //End of charge voltage on VBAT = 4.32V
#define	AS3610_VEOC_4_34_V	            0x2A    //End of charge voltage on VBAT = 4.34V
#define	AS3610_VEOC_4_36_V	            0x2B    //End of charge voltage on VBAT = 4.36V
#define	AS3610_VEOC_4_38_V	            0x2C    //End of charge voltage on VBAT = 4.38V
#define	AS3610_VEOC_4_40_V	            0x2D    //End of charge voltage on VBAT = 4.4V
#define	AS3610_VEOC_4_42_V	            0x2E    //End of charge voltage on VBAT = 4.42V
#define	AS3610_VEOC_4_44_V                  0x2F    //End of charge voltage on VBAT = 4.44V
//Values 0x30 - 0x3F: NA

//bit 6-7:
/* Minimum charger (VBUS) voltage. Current is regulated down, if VBUS
voltage drops below this level: */
#define AS3610_VCHG_MIN_LT_3_9_V            0x00    //VBAT < 3.9V
#define AS3610_VCHG_MIN_LT_4_2_V            0x40    //VBAT < 4.2V
#define AS3610_VCHG_MIN_LT_4_5_V            0x80    //VBAT < 4.5V
#define AS3610_VCHG_MIN_LT_4_7_V            0xC0    //VBAT < 4.7V

/* Charger Current Control Register (Address 0x02). */

//bit 0:
/* Current ratio selection between trickle and EOC current
(defined by resistor RTERM) */
#define AS3610_ECCURR_ITERM                 0x00    //EOC current = ITERM, Trickle current = ITERM
#define AS3610_ECCURR_0_5_ITERM             0x01    //EOC current = ITERM / 2, Trickle current = ITERM

//bit 1-2:
/* ConstantCurrent setting */
#define AS3610_CONSTCURR_1xICHARGE          0x00    //Constant Current = ICHARGE
#define AS3610_CONSTCURR_0_81xICHARGE       0x02    //Constant Current = 0.81*ICHARGE
#define AS3610_CONSTCURR_0_60xICHARGE       0x04    //Constant Current = 0.60*ICHARGE
#define AS3610_CONSTCURR_0_40xICHARGE       0x06    //Constant Current = 0.40*ICHARGE

//bit 3:
/* Current selection for boost mode */
#define AS3610_BOOST_LOWCURR_500_MA         0x00    //500mA maximum current
#define AS3610_BOOST_LOWCURR_200_MA         0x08    //200mA maximum current

//bit 4:
//0x10 --> NA

//bit 5:
/*Enables 100% on mode of PMOS */
#define AS3610_DIS_PON                      0x00    //100% mode disabled (smooth 100% mode, if disable_toff=1)
#define AS3610_EN_PON                       0x20    //100% mode enabled.

//bit 6-7:
/* Select debounce timer */
#define AS3610_DEB_TIMER_30_MSEC            0x00    //30msec debounce timer for comparator output
#define AS3610_DEB_TIMER_3_MSEC             0x40    //3msec debounce timer
//0x80 --> NA
//0xC0 --> NA

/* NTC Supervision Register (Address 0x03). */
/* These bits define the battery temperature supervision. */

//bit 0:
/* ON/OFF control of battery NTC supervision */
#define AS3610_NTC_OFF                      0x00    //Disable
#define AS3610_NTC_ON                       0x01    //Enable

//bit 1:
//Select NTC resistor type
#define AS3610_NTC_100_K                    0x00    //Select NTC resistor type to 100k
#define AS3610_NTC_10_K                     0x02    //Select NTC resistor type to 10k

//bit 2:
/* Select NTC temperature shutdown */
#define AS3610_NTC_TEMP_50_OR_55_C          0x00    //high temperature range (50 or 55 �C)
#define AS3610_NTC_TEMP_45_OR_50_C          0x04    //low temperature range (45 or 50 �C)

/* Charger Supervision Register (Address 0x04). */
/* These bits define charging timer settings. */

//bit 0-3:
/* Charging timeout timer */
#define	CH_TIMEOUT_DISABLE                  0x00	//Charging timer disabled
#define	CH_TIMEOUT_0_50_H	            0x01	//0.5 hour
#define	CH_TIMEOUT_1_00_H	            0x02	//1 hour
#define	CH_TIMEOUT_1_50_H	            0x03	//1.5 hour
#define	CH_TIMEOUT_2_00_H	            0x04	//2 hour
#define	CH_TIMEOUT_2_50_H	            0x05	//2.5 hour
#define	CH_TIMEOUT_3_00_H	            0x06	//3 hour
#define	CH_TIMEOUT_3_50_H	            0x07	//3.5 hour
#define	CH_TIMEOUT_4_00_H	            0x08	//4 hour
#define	CH_TIMEOUT_4_50_H	            0x09	//4.5 hour
#define	CH_TIMEOUT_5_00_H	            0x0A	//5 hour
#define	CH_TIMEOUT_5_50_H	            0x0B	//5.5 hour
#define	CH_TIMEOUT_6_00_H	            0x0C	//6 hour
#define	CH_TIMEOUT_6_50_H	            0x0D	//6.5 hour
#define	CH_TIMEOUT_7_00_H	            0x0E	//7 hour
#define	CH_TIMEOUT_7_50_H	            0x0F	//7.5 hour

//bit 4:
#define CHARGING_TMAX_RESET                 0x00    //reset charger timeout counter
#define CHARGING_TMAX                       0x10    //tCHARGING,MAX timeout reached and charging stopped

//bit 5-7
//Function of Status pin:
#define STAT_MODE_0                         0x00    //always off
#define STAT_MODE_1                         0x20    //ch_det=ON
#define STAT_MODE_2                         0x40    //ch_det=ON, stop_charging or boost_error=5Hz blinking
#define STAT_MODE_3                         0x60    //Charging=ON, stop_charging or boost_error=5Hz blinking
#define STAT_MODE_4                         0x80    //Charging=ON, EOC=1Hz blinking, stop_charging or boost_error=5Hz blinking
#define STAT_MODE_5                         0xA0    //ch_det =ON, EOC=1Hz blinking, stop_charging or boost_error=5Hz blinking

/* Charger Status1 Register (Address 0x05). */
/* These bits show the status of the charger. */
/*  - READ ONLY - */

//bit 0:
#define AS3610_CHDET                        0x01    //Bit is set when charge adapter has been detected on pin VBUS
//bit 1:
#define AS3610_CCM                          0x02    //Bit is set when charger is in Constant current mode
//bit 2:
#define AS3610_RESUME                       0x04    //Bit is set when battery voltage has dropped below resume level
//bit 3:
#define AS3610_TRICKLE                      0x08    //Bit is set when charger is in trickle charge mode
//bit 4:
#define AS3610_CVM                          0x10    //Bit is set when charger is in top-off charge mode (constant voltage mode)
//bit 5:
#define AS3610_EOC                          0x20
/* Bit is set when charging has been terminated. Bit is cleared automatically when chg_en is cleared or charging is resumed. */
//bit 6:
#define AS3610_BATTEMP_HI                   0x40
/* Bit is set, if temperature is greater than 50 or 55 deg C. Bit is evaluated if charger is detected. */
//bit 7:
#define AS3610_NO_BAT                       0x80
/* Bit is set when battery detection circuit indicates that no battery is
connected to the system. This is done by measuring the NTC value.
ntc_on has to be 1. */

/* Charger Status2 Register (Address 0x06). */
/* These bits show the status of the charger. */

//bit 0:
#define AS3610_LOW_BAT                      0x01    //Set, if VBAT<2V
//bit 1:
#define AS3610_OV_BAT                       0x02    //Set, if VBAT> 1.17*VCHARGE
//bit 2:
#define AS3610_LOW_BUS                      0x04    //Set, if VBUS<3.8V
//bit 3:
#define AS3610_OV_BUS                       0x08    //Set, if VBUS>6.5V
//bit 4:
#define AS3610_UVL_BUS                      0x10    //Set, if VBUS<3.3V
//bit 5:
#define AS3610_BOOST_ACT                    0x20    //Set, if boost mode active
//bit 6:
#define AS3610_BOOST_ERR                    0x40
/*Set, if boost error active. (Overcurrent of booster for more than
debounce time, VBAT<2.5V, VBUS>6.5V or current limit is active */
//bit 7:
#define AS3610_STOP_CHARGING                0x80
/*Set if charger is stopped because of the following reason:
- Timeout timer expired
- NTC temperature error (Hightemp)
- OVBus set
- OVBat set
- UVLBus set
- Die temp>140deg (ov_temp_140 set) */


extern unsigned char as3610read(unsigned char readbyte);
extern void init_as3610_c1();
extern void init_as3610_standalone_100k_ntc();
extern void init_as3610_standalone_10k_ntc();

#endif	/* AS3610_H */

