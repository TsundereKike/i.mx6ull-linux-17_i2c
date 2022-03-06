#include "bsp_i2c.h"
/*初始化i2c*/
void i2c_init(I2C_Type *base)
{
    base->I2CR &= ~(1<<7);/*关闭i2c*/
    base->IFDR = 0x15;/*PERCLK_CLK_ROOT时钟640分频 = 66MHz/640 = 103.125KHz*/
    base->I2CR |= (1<<7);/*开启i2c*/
    base->I2CR &= ~(1<<6);/*关闭中断产生*/
}
/*start信号产生以及从机地址的发送*/
unsigned int i2c_master_start(I2C_Type *base, unsigned char address, enum i2c_transfer_direction direction)
{
    if(base->I2SR & (1<<5))
        return I2C_STATUS_BUSY;
    /*设置为主机发送模式*/
    base->I2CR |= (1<<5) | (1<<4);
    /*产生start信号*/
    base->I2DR = ((unsigned int)address << 1) | ((direction == kI2C_Read)?1:0);
    return I2C_STATUS_OK;
}
/*stop信号的产生*/
unsigned int i2c_master_stop(I2C_Type *base)
{
    unsigned short timeout = 0xffff;
    /*清除I2CR寄存器的bit5:3*/
    base->I2CR &= ~((1<<5)|(1<<4)|(1<<3));
    /*等待i2c忙结束*/
    while((base->I2SR & (1<<5)))
    {
        timeout--;
        if(timeout==0)
            return I2C_STATUS_TIMEOUT;
    }
    return I2C_STATUS_OK;
}
/*repeat start信号产生*/
unsigned int i2c_master_repeat_start(I2C_Type *base, unsigned char address, enum i2c_transfer_direction direction)
{
    /*检测I2C是否忙或处于从机模式下*/
    while((base->I2SR & (1<<5)) || ((base->I2CR & (1<<5))==0))
        return I2C_STATUS_BUSY;
    /*设置为发送模式及产生repeat_start信号*/
    base->I2CR |= (1<<4) | (1<<2);
    base->I2DR = ((unsigned int)address << 1) | ((direction==kI2C_Read)?1:0);
    return I2C_STATUS_OK;
}
/*错误检查与清除*/
unsigned int i2c_check_and_clear_error(I2C_Type *base, unsigned int status)
{
    if(status & (1<<4))/*先检查是否为仲裁丢失*/
    {
        base->I2SR &= ~(1<<4);
        base->I2CR &= ~(1<<7);
        base->I2CR &= ~(1<<7);
        return I2C_STATUS_ARBITRATIONAL_LOST;
    }
    else if(status & (1<<0))/*从机未应答*/
    {
        return I2C_STATUS_NAK;
    }
    else
    {
        return I2C_STATUS_OK;
    }
}