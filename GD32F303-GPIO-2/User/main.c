/**************************************************
--gd32f30x_it.c     �Ը����жϷ��������¶���
**************************************************/

#include "gd32f30x.h"  //�Ĵ���ӳ���ַ
#include "bsp_gpio.h"

#define LED  PAout(0)
//main����
int main(void)
{
	gd_led_init();
	LED = 1; //����LED
	while(1)
	{
	}
	
}



//�˺���������system_gd32f30x.c��
//void SystemInit(void)
//{
//}