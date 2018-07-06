/**************************************************
--gd32f30x_it.c     对个别中断服务函数重新定义
**************************************************/

#include "gd32f30x.h"  //寄存器映射地址
#include "bsp_gpio.h"
#include "bsp_delay.h"
#include "bsp_lcd.h"

#define LED  PAout(0)
unsigned int count = 0;  //用来显示刷屏时间

void rcu_config(void);
void gpio_config(void);
void dma_config(void);
void spi_config(void);

//main函数
int main(void)
{
	//延时函数初始化
	gd_delay_init();
	//外设时钟初始化
	rcu_config();
	//gpio初始化
	gpio_config();
	gd_led_init();
	//SPI硬件初始化
	spi_config();
	
	 /* SPI enable */
	spi_enable(SPI0);
	
	//LCD初始化
	gd_lcd_init();
	gd_lcd_init();
	//显示颜色
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
    /* SPI0 GPIO config: MISO/PA6 作为LCD的RS引脚;PA8作为LCD的RST引脚*/
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_8);
    
//    /* SPI1 GPIO config: NSS/PB12, SCK/PB13, MOSI/PB15 */
//    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_12 | GPIO_PIN_13 |GPIO_PIN_15);
//    /* SPI1 GPIO config: MISO/PB14 */
//    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
}
//SPI配置函数
void spi_config(void)
{
    spi_parameter_struct spi_init_struct;

    /* SPI0 parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT; //8位模式
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT; //软件模式
    spi_init_struct.prescale             = SPI_PSC_4;    //4分频
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);    //启动SPI0

    
}

//此函数包含在system_gd32f30x.c中
//void SystemInit(void)
//{
//}