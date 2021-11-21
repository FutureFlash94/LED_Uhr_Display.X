#include "i2c_driver.h"
#include "tmd3990_driver.h"

#include "errno.h"
#include "stdio.h"
#include "AS1119_driver.h"

static int tmd3990ReadRegister(int i2cmod, unsigned char reg, unsigned char *val) {
    if(i2cmod == 1)
    {
        i2cSwitchModule(I2C2_MODULE);
    }
    else if(i2cmod == 2)
    {
        i2cSwitchModule(I2C1_MODULE);
    }
    if (i2cRx(TMD3990_I2C_ADDR, &reg, 1, val, 1) != 1)
        return ERR_IO;
    else
        return ERR_NONE;
}

int tmd3990BlockRead(int i2cmod, unsigned char reg, unsigned char *val, unsigned char count) {
    if(i2cmod == 1)
    {
        i2cSwitchModule(I2C2_MODULE);
    }
    else if(i2cmod == 2)
    {
        i2cSwitchModule(I2C1_MODULE);
    }
    if (i2cRx(TMD3990_I2C_ADDR, &reg, 1, val, count) != count)
    {
        i2cIdle();
        return ERR_IO;
    }
    else
        return ERR_NONE;
}

int tmd3990WriteRegister(int i2cmod, unsigned char reg, unsigned char val) {
    if(i2cmod == 1)
    {
        i2cSwitchModule(I2C2_MODULE);
    }
    else if(i2cmod == 2)
    {
        i2cSwitchModule(I2C1_MODULE);
    }
    u8 buf[2];
    buf[0] = reg;
    buf[1] = val;

    if (i2cTx(TMD3990_I2C_ADDR, buf, 2) != 2)
        return ERR_IO;
    else
        return ERR_NONE;
}

void tmd3990SetProxGain(int i2cmod, u8 gain ){
    tmd3990WriteRegister(i2cmod, 0x8F , (gain<<2)&0x0C );    // Config Register [ LDR_DRIV [7~6], NC [5~4}, PGAIN [3~2}, AGAIN[1~0]
}

void tmd3990SetProxCount(int i2cmod, u8 count ){
    tmd3990WriteRegister(i2cmod, 0x8E , count    );    // Pulse Prox counter
}

void tmd3990Initialize(int i2cmod){
    tmd3990WriteRegister(i2cmod, 0x80 , 0b00110111 );    // Enable IC, no Prox, no ALS
    tmd3990WriteRegister(i2cmod, 0x81 , 0xB8 );    // 41,7mS
    tmd3990WriteRegister(i2cmod, 0x82 , 0xFF );    // Wait time = 2.78mS
    tmd3990WriteRegister(i2cmod, 0x84 , 0x00 );    // Clear Channel Low Lower Byte Threshold
    tmd3990WriteRegister(i2cmod, 0x85 , 0x00 );    // Clear Channel Low Higher Byte Threshold
    tmd3990WriteRegister(i2cmod, 0x86 , 0x00 );    // Clear Channel High Lower Byte Threshold
    tmd3990WriteRegister(i2cmod, 0x87 , 0x00 );    // Clear Channel High Higher Byte Threshold
    tmd3990WriteRegister(i2cmod, 0x89 , 0x00 );    // Prox Threshod Lower Byte
    tmd3990WriteRegister(i2cmod, 0x8B , 0x00 );    // Prox Threshold High Byte
    tmd3990WriteRegister(i2cmod, 0x8C , 0x00 );    // Interrupt Register
    tmd3990WriteRegister(i2cmod, 0x8D , 0x40 );    // Configuration Register
    tmd3990WriteRegister(i2cmod, 0x8E , 8    );    // Pulse Prox counter
    tmd3990WriteRegister(i2cmod, 0x8F , 0x06 );    // Config Register [ LDR_DRIV [7~6], NC [5~4}, PGAIN [3~2}, AGAIN[1~0] , ALS Gain = 16x
    tmd3990WriteRegister(i2cmod, 0x90 , 0x00 );    // Aux Register
    tmd3990WriteRegister(i2cmod, 0x9E , 0x00 );    // Prox Offset
    tmd3990WriteRegister(i2cmod, 0x80 , 0b00100111 );    // Enable IC, no Prox, no ALS
}

void tmd_shut_down(int i2cmod){
    tmd3990WriteRegister(i2cmod, 0x80 , 0b00110110);    //Power off
}

void tmd3990clearInt(int i2cmod){
    tmd3990WriteRegister(i2cmod, 0xE7 , 0x00);
}

u16 tmd3990GetClear(int i2cmod){
    u8 buffer[2];
    tColors values;
    if(tmd3990BlockRead(i2cmod, 0x94,buffer,2) == -3){
        return 0x81;
    }
    else{
        values.C = buffer[0] + (buffer[1]<<8);
        if(values.C < 0){
            values.C = values.C + 65535;
        }
    }
    return values.C;
}

u8 tmd3990GetReg(int i2caddr, u8 reg){
    u8 buffer = 0x00;
    tmd3990ReadRegister(i2caddr, reg,&buffer);
    return buffer;
}

u16 tmd3990GetLux(int i2cmod){
    u8 buffer[9];
    tColors values;
    tmd3990BlockRead(i2cmod, 0x94,buffer,8);
    values.C = buffer[0] + (buffer[1]<<8);
    values.R = buffer[2] + (buffer[3]<<8);
    values.G = buffer[4] + (buffer[5]<<8);
    values.B = buffer[6] + (buffer[7]<<8);
    
    s32 Rc = 115;
    s32 Gc = 1000;
    s32 Bc = -461;
        
    s32 C1 = ((Rc+Gc+Bc)*95)/100;
    s32 R1 = -Gc-Bc;
    s32 G1 = -Rc-Bc;
    s32 B1 = -Gc-Rc;
    
    s32 Again = 1;
    s32 Atime = 200;
    s32 DGF = 135;
    
    s32 lux = values.C*C1 - values.R * R1 - values.G * G1 - values.B * B1;
    lux *= DGF;
    lux /= Again*Atime;
    lux /= 1000;
    
    values.Lux = lux;

    return 0;
}

u8 tmd3990GetProx(int i2cmod){
    u8 buffer;
    tmd3990ReadRegister(i2cmod, 0x9C,&buffer);
   
    return buffer;
}
