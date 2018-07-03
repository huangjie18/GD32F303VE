#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LCD_BIT 16
//串口定义说明
/****************************************
1  - 地
10(TE) - PB1
13(DB0) - RD			(PD4)
14(DB1) - RW			(PD5)
15(DB2) - DB0			(PD14)
16(DB3) - LCDRST		(PD13)
17(DB4) - DB2			(PD0)
18(DB5) - DB1			(PD15)
19(DB6) - DB4			(PE7)
20(DB7) - DB3			(PD1)
21(RD) - DB6			(PE9)
22(WR) - DB5			(PE8)
23(RS) - DB8			(PE11)
24(CS) - DB7			(PE10)
25(DB8) - DB10			(PE13)
26(DB9) - DB9			(PE12)
27(DB10) - DB12			(PE15)
28(DB11) - DB11			(PE14)
29(DB12) - DB14			(PD9)
30(DB13) - DB13			(PD8)
31(DB14) - TP_BUSY		(PC5)
32(DB15) - DB15			(PD10)
33(GND) - SPI_SCK		(PB13)
34(VCC) - SPI_CS	    (PB12)
35(VCC) - SPI_MOSI   	(PB15)
36(RESET) - SPI_MISO    (PB14)
37(GND) - LED_PWM		(PA1)
38(GND) - TP_INT		(PC4)
****************************************/
#define red  0x001f
#define black 0x0000
#define white 0xffff
#define green  0x07e0
#define blue 0xf800

#define DB0   PDout(4)
#define DB1   PDout(5)
#define DB2   PDout(14)
#define DB3   PDout(13)
#define DB4   PDout(0)
#define DB5   PDout(15)
#define DB6   PEout(7)
#define DB7   PDout(1)
#define DB8   PEout(13)
#define DB9   PEout(12)
#define DB10  PEout(15)
#define DB11  PEout(14)
#define DB12  PDout(9)
#define DB13  PDout(8)
#define DB14  PCout(5)
#define DB15  PDout(10)
#define LCD_RD  PEout(9)
#define LCD_BK  PCout(4)
#define LCD_WR  PEout(8)
#define LCD_RS  PEout(11)
#define LCD_CS  PEout(10)
#define LCD_RST PBout(14)

void LED_Init(void);//初始化
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
#endif
