#include "lcd.h"
#include "delay.h"
#include "spi.h"

//lcd接口初始化
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);//使能GPIOD和GPIOE的时钟线
	
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);  //GND
	GPIO_SetBits(GPIOE,GPIO_Pin_13);    //VCC
}


/****************写命令函数*******************/
static void LcdWriCommand(unsigned char command)
{
	#if (spi_mode != 0)
	u8 i;
	DC = 0; //4线SPI

	for(i=0;i<8;i++)
	{
		if(command&0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;
		SCL = 1;

		command<<=1;
	}
	#else
	LCD_DC = 0;
	SPI2_ReadWriteByte(command);
	#endif
}

/****************写数据函数*******************/
static void LcdWriData(unsigned char Data)
{
	#if (spi_mode != 0)
	u8 i;
	DC = 1; //4线SPI
	
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;
		SCL = 1;
		
		Data<<=1;
	}
	#else
	LCD_DC = 1;
	SPI2_ReadWriteByte(Data);
	#endif
}

//开显示区函数
static void address_1(void)
{             
	LcdWriCommand(0x2A);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0xef);
	
	LcdWriCommand(0x2B);
	LcdWriData(0x00);
	LcdWriData(0x00);//3B
	LcdWriData(0x0);
	LcdWriData(0xef);

	LcdWriCommand(0x2C);
}

//LCD初始化函数
void LCD_Init(void)
{
	RES = 1;
	LCD_RST = 1;
	delay_ms(100);
	RES = 0; //LCD复位
	LCD_RST = 0;
	delay_ms(100);
	RES = 1;
	LCD_RST = 1;
	delay_ms(120);
	
	LcdWriCommand(0x11);
	delay_ms(200);
	
	LcdWriCommand(0x36);  //扫描方式
	LcdWriData(0x00);
	LcdWriCommand(0x3a); 
	LcdWriData(0x05); 
	
	LcdWriCommand(0xb2); 
	LcdWriData(0x0c); 
	LcdWriData(0x0c); 
	LcdWriData(0x00); 
	LcdWriData(0x33); 
	LcdWriData(0x33); 
	
	LcdWriCommand(0xb7); 
	LcdWriData(0x35); 
	
	//---------------------------------ST7789S Power setting--------------------------------------// 
	
	LcdWriCommand(0xbb); 
	LcdWriData(0x2C); 

	
	LcdWriCommand(0xc0); 
	LcdWriData(0x2c); 
	
	LcdWriCommand(0xc2); 
	LcdWriData(0x01); 
	
	LcdWriCommand(0xc3); 
	LcdWriData(0x0b); 

	
	LcdWriCommand(0xc4); 
	LcdWriData(0x20); 
	
	LcdWriCommand(0xc6); 
	LcdWriData(0x0f); 
	
	LcdWriCommand(0xd0); 
	LcdWriData(0xa4); 
	LcdWriData(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	LcdWriCommand(0xe0); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0e); 
	LcdWriData(0x0e); 
	LcdWriData(0x08); 
	LcdWriData(0x32); 
	LcdWriData(0x44); 
	LcdWriData(0x40); 
	LcdWriData(0x08); 
	LcdWriData(0x10); 
	LcdWriData(0x0f); 
	LcdWriData(0x15); 
	LcdWriData(0x19); 
	
	LcdWriCommand(0xe1); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0f); 
	LcdWriData(0x0e); 
	LcdWriData(0x09); 
	LcdWriData(0x2f); 
	LcdWriData(0x54); 
	LcdWriData(0x44); 
	LcdWriData(0x0f); 
	LcdWriData(0x1d); 
	LcdWriData(0x1a); 
	LcdWriData(0x16); 
	LcdWriData(0x19); 
	
	LcdWriCommand(0x21);	//display inversion on
	LcdWriCommand(0x29);//display on

	delay_ms(120);
	address_1();
	
}



static void WriteDAT(unsigned char DH,unsigned char DL)		
{
	LcdWriData(DH);
	LcdWriData(DL);	
}
//测试程序
void display_test(u16 color)
{
	u8 i,j;
//	for(i=0;i<120;i++)
//	{
//		for(j=0;j<240;j++)
//		{
//			if(j<=80)
//			{
//				WriteDAT(RED>>8,RED&0xff);
//			}
//			else if(j<=160)
//			{
//				WriteDAT(GREEN>>8,GREEN&0xff);
//			}
//			else
//			{
//				WriteDAT(BLUE>>8,BLUE&0xff);
//			}
//		}
//	}
//	for(i=0;i<120;i++)
//	{
//		for(j=0;j<240;j++)
//		{
//			if(j<=80)
//			{
//				WriteDAT(WHITE>>8,WHITE&0xff);
//			}
//			else if(j<=160)
//			{
//				WriteDAT(BLACK>>8,BLACK&0xff);
//			}
//			else
//			{
//				WriteDAT(GRAY>>8,GRAY&0xff);
//			}
//		}
//	}

	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 240; j++)
		{
			WriteDAT(color>>8,color&0xff);
		}
	}
	
}



/********************************测试GDF303*****************************************/
static void gd32_LcdWriCommand(unsigned char command);
static void gd32_LcdWriData(unsigned char Data);

void gd_gpio_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOD和GPIOE的时钟线
	
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
}

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
	#if (spi_mode != 0)
	u8 i;
	gd32_dc = 0; //4线SPI

	for(i=0;i<8;i++)
	{
		if(command&0x80)
		{
			gd32_mosi = 1;
		}
		else
		{
			gd32_mosi = 0;
		}
		gd32_sck = 0;
		gd32_sck = 1;

		command<<=1;
	}
	#else
	gd32_dc = 0;
	SPI_I2S_SendData(SPI1, command); //通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); //检查发送是否完成
	#endif
}

void gd32_LcdWriData(unsigned char Data)
{
	#if (spi_mode != 0)
	u8 i;
	gd32_dc = 1; //4线SPI
	
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
		{
			gd32_mosi = 1;
		}
		else
		{
			gd32_mosi = 0;
		}
		gd32_sck = 0;
		gd32_sck = 1;
		
		Data<<=1;
	}
	#else
	gd32_dc = 1;
	SPI_I2S_SendData(SPI1, Data); //通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); //检查发送是否完成
	#endif
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