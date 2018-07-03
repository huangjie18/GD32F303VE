/**************************************************
--gd32f30x_it.c     对个别中断服务函数重新定义
**************************************************/

#include "gd32f30x.h"  //寄存器映射地址
#include "bsp_gpio.h"

#define LED  PAout(0)
//main函数
int main(void)
{
	gd_led_init();
	LED = 1; //点亮LED
	while(1)
	{
	}
	
}



//此函数包含在system_gd32f30x.c中
//void SystemInit(void)
//{
//}