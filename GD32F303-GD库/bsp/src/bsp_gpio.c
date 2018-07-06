#include "bsp_gpio.h"

void gd_led_init(void)
{
	//GPIOAʱ��ʹ��
	rcu_periph_clock_enable(RCU_GPIOA);
	
	//��ʼ��LED����-A0
	gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0);
	
	//��λA0����
	GPIO_BC(GPIOA) = 0x01;
}