#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#define spi_mode 0  //0使用硬件SPI，1使用模拟SPI
#define spi_init 0  //初始化模式，0使用硬件spi模式

#define LCD_DC  PBout(2) //控制数据还是命令指令
#define LCD_RST PCout(6) //控制oled的复位
#define SCL PBout(13) 
#define SDA PBout(15)
 
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

/*******************gd32f303************************/
void SPI1_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
#endif