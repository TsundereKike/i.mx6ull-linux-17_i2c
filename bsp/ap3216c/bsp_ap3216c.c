#include "bsp_ap3216c.h"
#include "bsp_i2c.h"
#include "bsp_gpio.h"
void ap3216_init(void)
{
    /*引脚gpio初始化*/
    IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL,1);/*引脚复用为i2c_SCL*/
    IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA,1);/*已经爱哦复用为i2c_SDA*/

    IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL,0x701b);
    IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA,0x701b);
    /*i2c初始化*/
    i2c_init(I2C1);
    /*ap3216c初始化*/

}