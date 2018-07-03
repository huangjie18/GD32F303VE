#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "spi.h"
#include "system_gd32f30x.h"

//int main(void)
//{
//	delay_init();	    //延时函数初始化
//	LCD_GPIO_Init();
//	SPI2_Init();
//	LCD_Init(); //要初始化两次
//	LCD_Init();
//	display_test(BLACK); //显示测试函数
//	
//	

//	while(1)
//	{
//		//红色
//		display_test(RED);
//		delay_ms(300);
//		//绿色
//		display_test(GREEN);
//		delay_ms(300);
//		//蓝色
//		display_test(BLUE);
//		delay_ms(300);
//	}
//}

//改为120M主频,要宏定义GD32F30X_HD
#define LED PAout(0)

int main(void)
{
	
	
	gd32f30x_SystemInit();  //120M主频
	
	gd_delay_init(120);     //用到延时一定要添加这个,因为延时用到了滴答定时器
	
	#if (spi_mode == 0)
	SPI1_Init();            //SPI初始化
	#else
	gd_gpio_init();         //GPIO初始化
	#endif
	
	gd_lcd_init();
	gd_lcd_init();
	gd_display_rgb(MAGENTA);
	while(1)
	{
		//红色
		PAout(0) = ~PAout(0);
		gd_display_rgb(RED);
		gd_delay_ms(1000);
		//绿色
		PAout(0) = ~PAout(0);
		gd_display_rgb(GREEN);
		gd_delay_ms(1000);
		//蓝色
		PAout(0) = ~PAout(0);
		gd_display_rgb(BLUE);
		gd_delay_ms(1000);



	}
}