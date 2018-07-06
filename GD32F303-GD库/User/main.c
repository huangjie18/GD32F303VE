/**************************************************
--gd32f30x_it.c     �Ը����жϷ��������¶���
**************************************************/

#include "gd32f30x.h"  //�Ĵ���ӳ���ַ
#include "bsp_gpio.h"
#include "bsp_delay.h"
#include "bsp_lcd.h"

#define LED  PAout(0)
unsigned int count = 0;  //������ʾˢ��ʱ��

void rcu_config(void);
void gpio_config(void);
void dma_config(void);
void spi_config(void);

//main����
int main(void)
{
	//��ʱ������ʼ��
	gd_delay_init();
	//����ʱ�ӳ�ʼ��
	rcu_config();
	//gpio��ʼ��
	gpio_config();
	gd_led_init();
	//SPIӲ����ʼ��
	spi_config();
	
	 /* SPI enable */
	spi_enable(SPI0);
	
	//LCD��ʼ��
	gd_lcd_init();
	gd_lcd_init();
	//��ʾ��ɫ
	gd_display_rgb(MAGENTA);
	
	while(1)
	{
		LED = ~LED;
		count = 0;
		gd_display_rgb(RED);
		gd_delay_ms(1000);
		
		LED = ~LED;
		count = 0;
		gd_display_rgb(GREEN);
		gd_delay_ms(1000);
		
		LED = ~LED;
		count = 0;
		gd_display_rgb(BLUE);
		gd_delay_ms(1000);
	}
	
}

void rcu_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_SPI0);
}

void gpio_config(void)
{
    /* SPI0 GPIO config: NSS/PA4, SCK/PA5, MOSI/PA7 */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,  GPIO_PIN_5 | GPIO_PIN_7);
    /* SPI0 GPIO config: MISO/PA6 ��ΪLCD��RS����;PA8��ΪLCD��RST����*/
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_8);
    
//    /* SPI1 GPIO config: NSS/PB12, SCK/PB13, MOSI/PB15 */
//    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_12 | GPIO_PIN_13 |GPIO_PIN_15);
//    /* SPI1 GPIO config: MISO/PB14 */
//    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
}
//SPI���ú���
void spi_config(void)
{
    spi_parameter_struct spi_init_struct;

    /* SPI0 parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT; //8λģʽ
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT; //���ģʽ
    spi_init_struct.prescale             = SPI_PSC_4;    //4��Ƶ
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);    //����SPI0

    
}

//�˺���������system_gd32f30x.c��
//void SystemInit(void)
//{
//}