#ifndef __BSP_I2C_H
#define __BSP_I2C_H
#include "imx6u.h"
/*i2c相关宏定义*/
#define I2C_STATUS_OK                   (0)
#define I2C_STATUS_BUSY                 (1)
#define I2C_STATUS_IDLE                 (2)
#define I2C_STATUS_NAK                  (3)/*从机未返回应答信号*/
#define I2C_STATUS_ARBITRATIONAL_LOST   (4)/*仲裁丢失情况发生*/
#define I2C_STATUS_TIMEOUT              (5)
#define I2C_ADDR_NAK                    (6)
enum i2c_transfer_direction
{
    kI2C_Write = 0x1,   /*主机向从机大宋数据*/
    kI2C_Read = 0x2,    /*主机从从机读取数据*/
};
void i2c_init(I2C_Type *base);
unsigned int i2c_master_start(I2C_Type *base, unsigned char address, enum i2c_transfer_direction direction);
unsigned int i2c_master_stop(I2C_Type *base);
unsigned int i2c_master_repeat_start(I2C_Type *base, unsigned char address, enum i2c_transfer_direction direction);
unsigned int i2c_check_and_clear_error(I2C_Type *base, unsigned int status);
#endif