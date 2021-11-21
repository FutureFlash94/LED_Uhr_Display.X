/*
 * File:   adxl345_v2.c
 * Author: emu
 *
 * Created on
 */

#include "adxl345_v2.h"
#include <p24Fxxxx.h>
#include "i2c_driver.h"
#include "uart_irq_driver.h"

unsigned char xl345read(unsigned char readbyte)
{
    i2cSwitchModule(I2C2_MODULE);
    unsigned char buffer;
    //_CNIE = 0;
    i2cRx(XL345_ALT_WRITE, &readbyte, 1, &buffer, 1);
    //_CNIE = 1;
    return buffer;
}

char xl345read_signed(const unsigned char readbyte)
{
    char buffer;
    //_CNIE = 0;
    i2cRx(XL345_ALT_WRITE, &readbyte, 1, &buffer, 1);
    //_CNIE = 1;
    return buffer;
}

void xl345write(unsigned char reg, unsigned char val)
{
    i2cSwitchModule(I2C2_MODULE);
    unsigned char buf[2];
    buf[0] = reg;
    buf[1] = val;
    i2cTx(XL345_ALT_WRITE, buf, 2);
}

int xl345datax()
{
    //zum auslesen von 10bit adxlwert, kann evt auch als burst verw. werden
    return (xl345read(XL345_DATAX0)<<8|xl345read(XL345_DATAX1));//Da man über i2c nur byteweise lesen kann, ist der 10bit wert aufgesplittet.
}

int xl345datay()
{
    return (xl345read(XL345_DATAY0)<<8|xl345read(XL345_DATAY1));//Da man über i2c nur byteweise lesen kann, ist der 10bit wert aufgesplittet.
}

int xl345dataz()
{
    return (xl345read(XL345_DATAZ0)<<8|xl345read(XL345_DATAZ1));//Da man über i2c nur byteweise lesen kann, ist der 10bit wert aufgesplittet.
}

long int xl345fulldata(int wahl)
{
    long int wert2;
    int pos;

    if(wahl==1)
    {
        wert2=xl345datax();
        pos=xl345read_signed(XL345_DATAX1);//-1 links neigung, 0 rechts neigung
    }
        else if(wahl==2)
    {
        wert2=xl345datay();
        pos=xl345read_signed(XL345_DATAY1);//-1 links neigung, 0 rechts neigung
    }
        else if(wahl==3)
    {
        wert2=xl345dataz();
        pos=xl345read_signed(XL345_DATAZ1);//-1 links neigung, 0 rechts neigung
    }

    if(pos==0)
    {//Sensor ist Rechts geneigt
        if(wert2<0)//wenn ich bei ca über 45° bin und wert ins - springt
        {
            wert2=(wert2+65536>65536 ? 65536 : wert2+65536);

        }
        else if(wert2>-65536)
        {
            wert2=-65536;
        }
    }
    else if(pos==-1)
    {//Sensor ist links geneigt
        if(wert2>0)
        {
            wert2=(wert2-65536<-65536 ? -65536 : wert2-65536);
        }
        else if(wert2<-65536)
        {
            wert2=-65536;
        }
    }
}

int mz=-1;//globale variable, wird mit 1xtap erhöht und 2xtap verringert, default in Zeitdarstellung(-1)
int wait=0;

//void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void)
////void _ISR _CNInterrupt(void)
//{
//    /*interrupt state am gsensor wird erst ausgeschaltet, wenn dieses
//     *Register gelesen wird:
//     *
//     * Ein Problem ergibt sich: - beim gsensor kann es dazu kommen, dass
//     * nach einen 2xtap - event immer noch eine genügend große schwingung
//     * am Sensor bzw Hand vorhanden ist, dass er nach einen 2xtap noch einen
//     * 1xtap erkennt - das ist natürlich sehr ärgerlich wenn z.b. 1xtap im
//     * menü einen schritt vorwärts bedeutet und 2xtap wieder zurück.
//     *
//     * beim Tippen gilt es 3 Register zu berücksichtigen:
//     *
//     * XL345_DUR:
//     * Deffiniert die Zeit, die ein Tip - Ereignis dauern darf
//     *
//     * XL345_LATENT:
//     * Latent = Nicht steigend, d.h. die Zeit, die der Sensor nach einem
//     * 1xtipp auf ein 2xtipp wartet, (passiert innerhalb dieser Zeit nichts, so
//     * wird ein 1xtipp detektiert, wird in dieser Zeit noch ein weiterer
//     * Tipp erkannt wird es als 2xtipp erkannt)
//     *
//     * XL345_WINDOW:
//     * Die Zeit, die der Sensor wartet, bis er erst ein weiteres Tap Ereignis
//     * detektieren kann, damit es eben nicht zu verfälschungen kommt, dass nach
//     * einen 2xtap sofort ein 1xtap erkannt wird und er erneut ins ISR geht...
//     * (ist anscheinend zu kurz.)
//     *
//     * Ich könnnte noch das XL345_THRESH_TAP register erhöhen, d.h. die
//     * Kraft, die beim Tippen aufgewendet werden muss erhöhen (..)
//     *
//     * eventuell ist polling des int source registers doch zuverlässiger
//     */
//
//    /*
//     * Ein weiteres Problem tritt auf:
//     * während ich vom Gsensor Werte messe, bin ich also andauernd
//     * in einer I2C Routine. Unterbreche ich diese Routin nun mit einem
//     * Interrupt, kann es dazu kommen (bzw kommt es dazu), dass der
//     * Gsensor gerade im I2C Senden modus ist und ich aber ein Register
//     * auslesen will, also stürzt das Programm dadurch ?chlimmstenfalls
//     * ab... (vlt löst polling mein problem)
//     *
//     * Einfach eine I2CSTOP anweisung zu schicken löst nicht mein Problem,
//     * da der eventuell daten erwarten könnte, jedoch dann ein NACK erhalten
//     * könnte - das würde zu fehlverhalten führen...
//     *
//     * Lösung:
//     * jedes mal, bevor ich am gsensor etwas lese, drehe ich den
//     * interrupt ab, nachdem ich fertig gelesen habe, drehe ich
//     * ihn wieder auf...
//     */
//    unsigned char tapdata=xl345read(XL345_ACT_TAP_STATUS);//hier steht drin, ob der 1xtap bzw 2ytap ein x,y,z tap war
//    unsigned char var=xl345read(XL345_INT_SOURCE);//1tip:195,2tip:227
//
//    //unsigned char var2=var&32;
//    //if(var2==32) mz--;
//    //else mz++;
//    if(wait==0)
//    {
//        if(tapdata==1) //wenn ytap
//        {
//            mz=(mz<2 ? mz+1 : mz);
//            wait=50;
//        }
//        else //tapdata == 4 d.h xtaü
//        {
//            mz=(mz>-2 ? mz-1 : mz);
//            wait=50;
//        }
//    }
//
//    IFS1bits.CNIF = 0;
//}

void init_xl345_c1()//hier ist einmaltipp u zweimaltipp enabled (auf z achse)
{
        int i;
        unsigned char daten2[]={
                    XL345_THRESH_TAP,
                    XL345_OFSX,
                    XL345_OFSY,
                    XL345_OFSZ,
                    XL345_DUR,
                    XL345_LATENT,
                    XL345_WINDOW,
                    XL345_THRESH_ACT,
                    XL345_THRESH_INACT,
                    XL345_TIME_INACT,
                    XL345_ACT_INACT_CTL,
                    XL345_THRESH_FF,
                    XL345_TIME_FF,
                    XL345_TAP_AXES,
                    XL345_BW_RATE,
                    XL345_POWER_CTL,
                    XL345_INT_ENABLE,
                    XL345_INT_MAP,
                    XL345_DATA_FORMAT,
                    XL345_FIFO_CTL, '\0'};
        unsigned char daten3[]={//no fifo
                    XL345_THRESH_TAP_VALUE_10_00_G, //Set the Tap Threshold to 10g
                    XL345_OFSX_VALUE_NO_OFFSET, //no offset
                    XL345_OFSY_VALUE_NO_OFFSET, //no offset
                    XL345_OFSZ_VALUE_NO_OFFSET, //no offset
                    XL345_DUR_TAP_EVENT_50_00_MS, //enable the single tap/double tap functions. 50ms time
                    XL345_LATENT_TIME_WAIT_100_00_MS, //100ms Latency before the second tap can occur.
                    XL345_WINDOW_TIME_WAIT_318_75_MS, //enable the double tap function. 5ms
                    XL345_TRESH_ACT_VALUE_2_00_G, //62.5mg/LSB, 0x20=2g, wenn wert groesser als der im thresact ist, aktiviert sich der g-sensor
                    XL345_TRESH_INACT_VALUE_0_19_G, //0x03=0.1875g, wenn wert kleiner als dieser ist --> g-sensor inaktiv
                    XL345_TIME_INACT_VALUE_160_S, //1s/LSB, 0x0A=10s //nach 10 sek inaktivitaet ist sensor inaktiv
                    XL345_INACT_Z_ENABLE | XL345_INACT_Y_ENABLE| XL345_INACT_X_ENABLE | XL345_INACT_AC | XL345_ACT_Z_ENABLE | XL345_ACT_Y_ENABLE | XL345_ACT_X_ENABLE | XL345_ACT_DC, //;
                    XL345_TRESH_FF_VALUE_0_31_G, //ab dann freier fall!
                    XL345_TIME_FF_VALUE_50_MS, //free fall time
                    XL345_TAP_X_DISABLE|XL345_TAP_Y_DISABLE|XL345_TAP_Z_ENABLE, //zaxis tap enable, supress enable
                    XL345_RATE_100_HZ|XL345_NORMAL_POWER, //no power safe mode i.e. normal mode, 100Hz bandwith
                    XL345_WAKEUP_8_HZ|XL345_AUTO_SLEEP|XL345_MEASURE|XL345_ACT_INACT_CONCURRENT, //
                    XL345_INT_DISABLE_OVERRUN|XL345_INT_DISABLE_WATERMARK|XL345_INT_DISABLE_FREEFALL|XL345_INT_DISABLE_INACTIVITY|XL345_INT_DISABLE_ACTIVITY|XL345_INT_ENABLE_DOUBLETAP|XL345_INT_ENABLE_SINGLETAP|XL345_INT_DISABLE_DATAREADY,
                    XL345_INT_MAP_OVERRUN_ON_INT0|XL345_INT_MAP_WATERMARK_ON_INT0|XL345_INT_MAP_FREEFALL_ON_INT0|XL345_INT_MAP_INACTIVITY_ON_INT0|XL345_INT_MAP_ACTIVITY_ON_INT0|XL345_INT_MAP_DOUBLETAP_ON_INT0|XL345_INT_MAP_SINGLETAP_ON_INT0|XL345_INT_MAP_DATAREADY_ON_INT0,
                    XL345_RANGE_16G|XL345_DATA_JUST_RIGHT|XL345_FULL_RESOLUTION|XL345_INT_HIGH|XL345_SPI4WIRE, //Full resolution, +-16 range //vorher 0x0b
                    XL345_TRIGGER_INT1|XL345_FIFO_MODE_BYPASS|XL345_FIFO_RESET, '\0'}; //fifo mode not used
        for(i=0;i<20;i++)//20 register
	{
            xl345write(daten2[i],daten3[i]);
	}
}

void init_xl345_c2()//hier sind alle tip funktionen deaktivert
{
    //xl345test();
        int i;
        unsigned char daten2[]={
                    XL345_THRESH_TAP,
                    XL345_OFSX,
                    XL345_OFSY,
                    XL345_OFSZ,
                    XL345_DUR,
                    XL345_LATENT,
                    XL345_WINDOW,
                    XL345_THRESH_ACT,
                    XL345_THRESH_INACT,
                    XL345_TIME_INACT,
                    XL345_ACT_INACT_CTL,
                    XL345_THRESH_FF,
                    XL345_TIME_FF,
                    XL345_TAP_AXES,
                    XL345_BW_RATE,
                    XL345_POWER_CTL,
                    XL345_INT_ENABLE,
                    XL345_INT_MAP,
                    XL345_DATA_FORMAT,
                    XL345_FIFO_CTL, '\0'};

            unsigned char daten3[]={
                    XL345_THRESH_TAP_VALUE_15_94_G, //62.5 mg/LSB = 16g
                    XL345_OFSX_VALUE_NO_OFFSET, //no offset
                    XL345_OFSY_VALUE_NO_OFFSET, //no offset
                    XL345_OFSZ_VALUE_NO_OFFSET, //no offset
                    XL345_DUR_TAP_EVENT_DISABLE, //disables the single tap/double tap functions. Fï¿½RS ERSTE!
                    XL345_LATENT_DISABLE_DOUBLE_TAP, //disables the double tap function.
                    XL345_WINDOW_DISABLE_DOUBLE_TAP, //disables the double tap function.
                    XL345_TRESH_ACT_VALUE_2_00_G, //62.5mg/LSB, 0x20=2g, wenn wert grï¿½ï¿½er als der im thresact ist, aktiviert sich der g-sensor
                    XL345_TRESH_INACT_VALUE_0_19_G, //62.5mg/LSB, 0x03=0.1875g, wenn wert kleiner als dieser ist --> g-sensor inaktiv
                    XL345_TIME_INACT_VALUE_10_S, //1s/LSB, 0x0A=10s //nach 10 sek inaktiviï¿½t ist sensor inaktiv
                    XL345_INACT_Z_ENABLE | XL345_INACT_Y_ENABLE| XL345_INACT_X_ENABLE | XL345_INACT_AC | XL345_ACT_Z_ENABLE | XL345_ACT_Y_ENABLE | XL345_ACT_X_ENABLE | XL345_ACT_DC, //XL345_INACT_Z_ENABLE | XL345_INACT_Y_ENABLE| XL345_INACT_X_ENABLE | XL345_INACT_AC | XL345_ACT_Z_ENABLE | XL345_ACT_Y_ENABLE | XL345_ACT_X_ENABLE | XL345_ACT_DC;
                    XL345_TRESH_FF_VALUE_0_75_G, //62.5mg/LSB, 0x0C=0.75g, ab dann freier fall!
                    XL345_TIME_FF_VALUE_30_MS, //5ms/LSB, 0x06=30ms, free fall time
                    XL345_TAP_X_DISABLE|XL345_TAP_Y_DISABLE|XL345_TAP_Z_DISABLE, //tap axis deaktiviert
                    XL345_RATE_100_HZ|XL345_NORMAL_POWER, //no power safe mode i.e. normal mode, 100Hz bandwith
                    XL345_WAKEUP_8_HZ|XL345_AUTO_SLEEP|XL345_MEASURE|XL345_ACT_INACT_CONCURRENT, //bzw 0x08 ohne autosleep
                    XL345_INT_DISABLE_OVERRUN|XL345_INT_DISABLE_WATERMARK|XL345_INT_DISABLE_FREEFALL|XL345_INT_DISABLE_INACTIVITY|XL345_INT_DISABLE_ACTIVITY|XL345_INT_DISABLE_DOUBLETAP|XL345_INT_DISABLE_SINGLETAP|XL345_INT_DISABLE_DATAREADY, //alle interrupts deaktiviert
                    XL345_INT_MAP_OVERRUN_ON_INT0|XL345_INT_MAP_WATERMARK_ON_INT0|XL345_INT_MAP_FREEFALL_ON_INT0|XL345_INT_MAP_INACTIVITY_ON_INT0|XL345_INT_MAP_ACTIVITY_ON_INT0|XL345_INT_MAP_DOUBLETAP_ON_INT0|XL345_INT_MAP_SINGLETAP_ON_INT0|XL345_INT_MAP_DATAREADY_ON_INT0, //alles auf Int0 (der noch nicht angeschlossen ist!)
                    XL345_RANGE_16G|XL345_DATA_JUST_RIGHT|XL345_FULL_RESOLUTION|XL345_INT_HIGH|XL345_SPI4WIRE, //Full resolution, +-16 range
                    XL345_TRIGGER_INT1|XL345_FIFO_MODE_BYPASS|XL345_FIFO_RESET, '\0'}; //fifo mode not used#

    for(i=0;i<20;i++)//20 register
    {
            xl345write(daten2[i],daten3[i]);
    }
}

void init_xl345_c3()
{
    int i;
    unsigned char daten2[]={
        XL345_THRESH_TAP,
        XL345_OFSX,
        XL345_OFSY,
        XL345_OFSZ,
        XL345_DUR,
        XL345_LATENT,
        XL345_WINDOW,
        XL345_THRESH_ACT,
        XL345_THRESH_INACT,
        XL345_TIME_INACT,
        XL345_ACT_INACT_CTL,
        XL345_THRESH_FF,
        XL345_TIME_FF,
        XL345_TAP_AXES,
        XL345_BW_RATE,
        XL345_POWER_CTL,
        XL345_INT_MAP,
        XL345_INT_ENABLE,
        XL345_DATA_FORMAT,
        XL345_FIFO_CTL, '\0'};
unsigned char daten3[]={//no fifo
    XL345_THRESH_TAP_VALUE_3_00_G,
    XL345_OFSX_VALUE_NO_OFFSET,
    XL345_OFSY_VALUE_NO_OFFSET,
    XL345_OFSZ_VALUE_NO_OFFSET,
    XL345_DUR_TAP_EVENT_100_00_MS,// gesamt dauer des Tap-Ereignisses
    XL345_LATENT_DISABLE_DOUBLE_TAP,//zeit, die nichts passieren darf (nach 1xtap, sonst 2xtap)
    XL345_WINDOW_DISABLE_DOUBLE_TAP,//zeit die er nach tap ereignis warten soll
    XL345_TRESH_ACT_VALUE_2_00_G,
    XL345_TRESH_INACT_VALUE_0_19_G,
    XL345_TIME_INACT_VALUE_160_S,
    XL345_INACT_Z_DISABLE|XL345_INACT_Y_DISABLE|XL345_INACT_X_DISABLE|XL345_INACT_AC|XL345_ACT_Z_DISABLE|XL345_ACT_Y_DISABLE|XL345_ACT_X_DISABLE|XL345_ACT_DC, //;
    XL345_TRESH_FF_VALUE_0_38_G, //ab dann freier fall!
    XL345_TIME_FF_VALUE_10_MS, //free fall time
    XL345_TAP_X_ENABLE|XL345_TAP_Y_DISABLE|XL345_TAP_Z_ENABLE,
    XL345_RATE_100_HZ|XL345_NORMAL_POWER,
    XL345_WAKEUP_8_HZ|XL345_AUTO_SLEEP|XL345_MEASURE|XL345_ACT_INACT_CONCURRENT, //
    XL345_INT_MAP_OVERRUN_ON_INT0|XL345_INT_MAP_WATERMARK_ON_INT0|XL345_INT_MAP_FREEFALL_ON_INT0|XL345_INT_MAP_INACTIVITY_ON_INT0|XL345_INT_MAP_ACTIVITY_ON_INT0|XL345_INT_MAP_DOUBLETAP_ON_INT0|XL345_INT_MAP_SINGLETAP_ON_INT0|XL345_INT_MAP_DATAREADY_ON_INT0,
    XL345_INT_DISABLE_OVERRUN|XL345_INT_DISABLE_WATERMARK|XL345_INT_ENABLE_FREEFALL|XL345_INT_DISABLE_INACTIVITY|XL345_INT_DISABLE_ACTIVITY|XL345_INT_DISABLE_DOUBLETAP|XL345_INT_ENABLE_SINGLETAP|XL345_INT_DISABLE_DATAREADY,
    XL345_RANGE_16G|XL345_DATA_JUST_RIGHT|XL345_FULL_RESOLUTION|XL345_INT_LOW|XL345_SPI4WIRE,
    XL345_TRIGGER_INT1|XL345_FIFO_MODE_BYPASS|XL345_FIFO_RESET, '\0'}; //fifo mode not used

        for(i=0;i<20;i++)//20 register
	{
            xl345write(daten2[i],daten3[i]);
	}
}