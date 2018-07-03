#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "spi.h"
#include "system_gd32f30x.h"

//int main(void)
//{
//	delay_init();	    //��ʱ������ʼ��
//	LCD_GPIO_Init();
//	SPI2_Init();
//	LCD_Init(); //Ҫ��ʼ������
//	LCD_Init();
//	display_test(BLACK); //��ʾ���Ժ���
//	
//	

//	while(1)
//	{
//		//��ɫ
//		display_test(RED);
//		delay_ms(300);
//		//��ɫ
//		display_test(GREEN);
//		delay_ms(300);
//		//��ɫ
//		display_test(BLUE);
//		delay_ms(300);
//	}
//}

//��Ϊ120M��Ƶ,Ҫ�궨��GD32F30X_HD
#define LED PAout(0)

int main(void)
{
	
	
	gd32f30x_SystemInit();  //120M��Ƶ
	
	gd_delay_init(120);     //�õ���ʱһ��Ҫ������,��Ϊ��ʱ�õ��˵δ�ʱ��
	
	#if (spi_mode == 0)
	SPI1_Init();            //SPI��ʼ��
	#else
	gd_gpio_init();         //GPIO��ʼ��
	#endif
	
	gd_lcd_init();
	gd_lcd_init();
	gd_display_rgb(MAGENTA);
	while(1)
	{
		//��ɫ
		PAout(0) = ~PAout(0);
		gd_display_rgb(RED);
		gd_delay_ms(1000);
		//��ɫ
		PAout(0) = ~PAout(0);
		gd_display_rgb(GREEN);
		gd_delay_ms(1000);
		//��ɫ
		PAout(0) = ~PAout(0);
		gd_display_rgb(BLUE);
		gd_delay_ms(1000);



	}
}