#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "gd32f30x.h"


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
#define BROWN 			 0XBC40 //×ØÉ«
#define BRRED 			 0XFC07 //×ØºìÉ«
#define GRAY  			 0X8430 //»ÒÉ«


/******gdf303********/
#define gd32_sck   PAout(5)
#define gd32_dc    PAout(6)
#define gd32_mosi  PAout(7)
#define gd32_reset PAout(8)

void gd_lcd_init(void);
void gd_display_rgb(u16 color);
#endif
