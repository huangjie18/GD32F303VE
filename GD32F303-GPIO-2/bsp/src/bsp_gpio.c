#include "bsp_gpio.h"

void gd_led_init(void)
{
	//GPIOA时钟使能
	rcu_periph_clock_enable(RCU_GPIOA);
	
	//初始化LED引脚-A0
	gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0);
	
	//复位A0引脚
	GPIO_BC(GPIOA) = 0x01;
}