#include "bsp_lcd.h"
#include "bsp_delay.h"
/********************************测试GDF303*****************************************/
static void gd32_LcdWriCommand(unsigned char command);
static void gd32_LcdWriData(unsigned char Data);

void gd_lcd_init(void)
{
	gd32_reset = 1;
	gd_delay_ms(100);
	gd32_reset = 0; //LCD复位
	gd_delay_ms(100);
	gd32_reset = 1;
	gd_delay_ms(120);
	
	gd32_LcdWriCommand(0x11);
	gd_delay_ms(200);
	
	gd32_LcdWriCommand(0x36);  //扫描方式
	gd32_LcdWriData(0x00);
	gd32_LcdWriCommand(0x3a); 
	gd32_LcdWriData(0x05); 

	gd32_LcdWriCommand(0xb2); 
	gd32_LcdWriData(0x0c); 
	gd32_LcdWriData(0x0c); 
	gd32_LcdWriData(0x00); 
	gd32_LcdWriData(0x33); 
	gd32_LcdWriData(0x33); 

	gd32_LcdWriCommand(0xb7); 
	gd32_LcdWriData(0x35); 

	//---------------------------------ST7789S Power setting--------------------------------------// 

	gd32_LcdWriCommand(0xbb); 
	gd32_LcdWriData(0x2C); 

	gd32_LcdWriCommand(0xc0); 
	gd32_LcdWriData(0x2c); 

	gd32_LcdWriCommand(0xc2); 
	gd32_LcdWriData(0x01); 

	gd32_LcdWriCommand(0xc3); 
	gd32_LcdWriData(0x0b); 

	gd32_LcdWriCommand(0xc4); 
	gd32_LcdWriData(0x20); 

	gd32_LcdWriCommand(0xc6); 
	gd32_LcdWriData(0x0f); 

	gd32_LcdWriCommand(0xd0); 
	gd32_LcdWriData(0xa4); 
	gd32_LcdWriData(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	gd32_LcdWriCommand(0xe0); 
	gd32_LcdWriData(0xd0); 
	gd32_LcdWriData(0x06); 
	gd32_LcdWriData(0x01); 
	gd32_LcdWriData(0x0e); 
	gd32_LcdWriData(0x0e); 
	gd32_LcdWriData(0x08); 
	gd32_LcdWriData(0x32); 
	gd32_LcdWriData(0x44); 
	gd32_LcdWriData(0x40); 
	gd32_LcdWriData(0x08); 
	gd32_LcdWriData(0x10); 
	gd32_LcdWriData(0x0f); 
	gd32_LcdWriData(0x15); 
	gd32_LcdWriData(0x19); 

	gd32_LcdWriCommand(0xe1); 
	gd32_LcdWriData(0xd0); 
	gd32_LcdWriData(0x06); 
	gd32_LcdWriData(0x01); 
	gd32_LcdWriData(0x0f); 
	gd32_LcdWriData(0x0e); 
	gd32_LcdWriData(0x09); 
	gd32_LcdWriData(0x2f); 
	gd32_LcdWriData(0x54); 
	gd32_LcdWriData(0x44); 
	gd32_LcdWriData(0x0f); 
	gd32_LcdWriData(0x1d); 
	gd32_LcdWriData(0x1a); 
	gd32_LcdWriData(0x16); 
	gd32_LcdWriData(0x19); 
	
	gd32_LcdWriCommand(0x21);	//display inversion on
	gd32_LcdWriCommand(0x29);//display on

	gd_delay_ms(120);
	
	//开区
	gd32_LcdWriCommand(0x2A);
	gd32_LcdWriData(0x00);
	gd32_LcdWriData(0x00);
	gd32_LcdWriData(0x00);
	gd32_LcdWriData(0xef);

	gd32_LcdWriCommand(0x2B);
	gd32_LcdWriData(0x00);
	gd32_LcdWriData(0x00);//3B
	gd32_LcdWriData(0x0);
	gd32_LcdWriData(0xef);

	gd32_LcdWriCommand(0x2C);
}

void gd32_LcdWriCommand(unsigned char command)
{
	u8 retry=0;
	gd32_dc = 0;
	spi_i2s_data_transmit(SPI0, command); //通过外设SPIx发送一个数据
	while (spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET)
	{
	}; //检查发送是否完成
//	for(retry=0;retry<200;retry++); 
}

void gd32_LcdWriData(unsigned char Data)
{
	u8 retry=0;
	gd32_dc = 1;
	spi_i2s_data_transmit(SPI0, Data); //通过外设SPIx发送一个数据
	while (spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET)
	{
	}; //检查发送是否完成
//	for(retry=0;retry<200;retry++); 
}

static void gd_WriteDAT(unsigned char DH,unsigned char DL)		
{
	gd32_LcdWriData(DH);
	gd32_LcdWriData(DL);	
}

void gd_display_rgb(u16 color)
{
	int i,j;
	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 240; j++)
		{
			gd_WriteDAT(color>>8,color&0xff);
		}
	}
}