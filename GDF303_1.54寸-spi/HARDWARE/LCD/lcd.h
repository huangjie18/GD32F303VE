#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//串口定义说明
/****************************************
MCU标号    LCD    MCU实际引脚

D0   -     BLK   (PD14)
D2   -     DC    (PD0)
D4   -     RES   (PE7)
D6   -     SDA   (PE9)
D8   -     SCL   (PE11)
D10  -     VCC   (PE13)
D12  -     GND   (PE15)
****************************************/
#define  saomiao   0x68
#define  red       0xf800
#define  green     0x07e0
#define  blue      0x001f
#define  black     0x0000
#define  white     0xFFFF
#define  purple    0xf81f
#define  yellow    0xffe0
#define  cyan      0x07ff
#define  orange    0xfc08
#define  gray      0x8400  //RGB各50%


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

#define BLK  PDout(14)
#define DC   PDout(0)
#define RES  PEout(7)
#define SDA  PEout(9)
#define SCL  PEout(11)




void LCD_Init(void);//初始化
void LCD_GPIO_Init(void); //LCD接口初始化
void LCD_WR_REG_DATA(int reg,int da);
void LCD_WR_REG(int reg);
void LCD_WR_DATA(int da);
void LCD_Writ_Bus(char data_1,char data_2);	
void Lcd_Initialize(void);   //IC9326
void LCD_Clear(void);

//IC4551必须要的
void Lcd_Initialize_4551(void);
void address(void);
void SLEEPEXIT(void);
void SLEEPON(void);
void display_test(u16 color); //测试程序

/******gdf303********/
#define gd32_cs    PAout(4)
#define gd32_sck   PAout(5)
#define gd32_dc    PAout(6)
#define gd32_mosi  PAout(7)
#define gd32_reset PAout(8)

void gd_gpio_init(void);
void gd_lcd_init(void);
void gd_display_rgb(u16 color);
/*******END********/

#endif
