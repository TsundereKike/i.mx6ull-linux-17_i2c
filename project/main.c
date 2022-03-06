#include "imx6u.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
unsigned char led_state = OFF;
char buf[160];
rtc_date_time_t rtcdate;
int main(void)
{

    int_init();
    imx6u_clk_init();
    clk_enable();
    delay_init();
    uart_init();
    led_init();
    beep_init();
    key_init();
    exti_init();
    epit1_init(0,66000000/100);/*初始化定时器1,1分频66MHz,定时时间为10ms,用于按键消抖*/
    lcd_init();
    rtc_init();

    lcd_show_string(10,10,360,32,32,"this tmh's rtc test");
    memset(buf,0,sizeof(buf));

	while(1)					
	{	
		rtc_get_date_time(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
        lcd_fill(50,110,300,126,LCD_WHITE);
        lcd_show_string(50, 110, 250, 16, 16,(char*)buf);  /* 显示字符串 */
		
        led_state = !led_state;
        led_switch(LED0,led_state);
        delay_ms(1000);
    }
    return 0;
}
