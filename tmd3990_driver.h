#ifndef TMD3990_DRIVER_H
#define	TMD3990_DRIVER_H

#define TMD3990_I2C_ADDR 0x72

typedef struct tColor
{
    u16 R;
    u16 G;
    u16 B;
    u16 C;
    u16 Lux;
}tColors;

int tmd3990BlockRead(int i2cmod, unsigned char reg, unsigned char *val, unsigned char count);
int  tmd3990WriteRegister(int i2cmod, unsigned char reg, unsigned char val);
void tmd3990SetProxGain(int i2cmod, u8 gain );
void tmd3990SetProxCount(int i2cmod, u8 count );
void tmd3990Initialize(int i2cmod);
void tmd_shut_down(int i2cmod);
void tmd3990clearInt(int i2cmod);
u8 tmd3990GetReg(int i2caddr, u8 reg);
u16  tmd3990GetClear(int i2cmod);
u16  tmd3990GetLux(int i2cmod);
u8   tmd3990GetProx(int i2cmod);

#ifdef	__cplusplus
}
#endif

#endif	/* TMD3990_DRIVER_H */

