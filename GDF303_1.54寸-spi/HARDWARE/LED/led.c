#include "led.h"
#include "delay.h"


//lcd接口初始化
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC
	|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,PE端口时钟
	
	//GPIOD初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_0
								  |GPIO_Pin_15|GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_10;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	//GPIOE初始化	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11
								  |GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//GPIOB初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
	//GPIOC初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	
	//GPIOA初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}


/***************************写数据总线******************************************/
void LCD_Writ_Bus(char data_1,char data_2)
{
	u8 i;
	u8 temp1;
	LCD_CS = 0;
	LCD_WR = 1;
	
	#if (LCD_BIT==8)  //使用的是8位数据线
	for(i=0;i<8;i++)
	{
		temp1 = (data_1>>i)&0x01;
		switch(i)
		{
			case 0: DB8 = temp1;break;
			case 1: DB9 = temp1;break;
			case 2: DB10 = temp1;break;
			case 3: DB11 = temp1;break;
			case 4: DB12 = temp1;break;
			case 5: DB13 = temp1;break;
			case 6: DB14 = temp1;break;
			case 7: DB15 = temp1;break;
		}
	}
	LCD_WR = 0;
	LCD_WR = 1;
	for(i=0;i<8;i++)
	{
		temp1 = (data_2>>i)&0x01;
		switch(i)
		{
			case 0: DB8 = temp1;break;
			case 1: DB9 = temp1;break;
			case 2: DB10 = temp1;break;
			case 3: DB11 = temp1;break;
			case 4: DB12 = temp1;break;
			case 5: DB13 = temp1;break;
			case 6: DB14 = temp1;break;
			case 7: DB15 = temp1;break;
		}
	}
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;
	#else
	for(i=0;i<8;i++)
	{
		temp1 = (data_1>>i)&0x01;
		switch(i)
		{
			case 0: DB8 = temp1;break;
			case 1: DB9 = temp1;break;
			case 2: DB10 = temp1;break;
			case 3: DB11 = temp1;break;
			case 4: DB12 = temp1;break;
			case 5: DB13 = temp1;break;
			case 6: DB14 = temp1;break;
			case 7: DB15 = temp1;break;
		}
	}
	for(i=0;i<8;i++)
	{
		temp1 = (data_2>>i)&0x01;
		switch(i)
		{
			case 0: DB0 = temp1;break;
			case 1: DB1 = temp1;break;
			case 2: DB2 = temp1;break;
			case 3: DB3 = temp1;break;
			case 4: DB4 = temp1;break;
			case 5: DB5 = temp1;break;
			case 6: DB6 = temp1;break;
			case 7: DB7 = temp1;break;
		}
	}
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;
	#endif
}
/***************************写数据**********************************************/
void LCD_WR_DATA(int da)   
{
    LCD_RS=1;
	LCD_Writ_Bus(da>>8,da);
}
/***************************写命令**************************************************/
void LCD_WR_REG(int reg)
{
	LCD_RS = 0;
	LCD_Writ_Bus(reg>>8,reg);
}
/****************************写命令和数据**********************************************/
void LCD_WR_REG_DATA(int reg,int da)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}
//lcd初始化函数
void Lcd_Initialize(void)
{
	LCD_RST = 0;
	delay_ms(200);
	LCD_RST = 1;
	delay_ms(20);
	
	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delay_ms(5);
	LCD_CS = 0;
	
//下面是初始代码，不需要知道全部细节，一般由厂家提供
	//需要修改时要参考数据手册,初始化程序不一样显示效果也不一样
		LCD_WR_REG_DATA(0x0702, 0x3008);// Set internal timing, don?ˉt change this value
		LCD_WR_REG_DATA(0x0705, 0x0036);// Set internal timing, don?ˉt change this value
		LCD_WR_REG_DATA(0x070B, 0x1213);// Set internal timing, don?ˉt change this value
		LCD_WR_REG_DATA(0x0001, 0x0100); // set SS and SM bit
		LCD_WR_REG_DATA(0x0002, 0x0100); // set 1 line inversion
	//	LCD_WR_REG_DATA(0x0003, 0x1008); // set GRAM write direction and BGR=1. //1030
		LCD_WR_REG_DATA(0x0003, 0x0030);
		LCD_WR_REG_DATA(0x0008, 0x0202); // set the back porch and front porch
		LCD_WR_REG_DATA(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		LCD_WR_REG_DATA(0x000C, 0x0000); // RGB interface setting
		LCD_WR_REG_DATA(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		LCD_WR_REG_DATA(0x0100, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WR_REG_DATA(0x0102, 0x0000); // VREG1OUT voltage
		LCD_WR_REG_DATA(0x0103, 0x0000); // VDV[4:0] for VCOM amplitude
		delay_ms(200); // Dis-charge capacitor power voltage
		LCD_WR_REG_DATA(0x0100, 0x1190); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WR_REG_DATA(0x0101, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		delay_ms(50); // Delay 50ms
		LCD_WR_REG_DATA(0x0102, 0x001D); // VREG1OUT voltage
		delay_ms(50); // Delay 50ms
		LCD_WR_REG_DATA(0x0103, 0x2000); // VDV[4:0] for VCOM amplitude
		LCD_WR_REG_DATA(0x0281, 0x0001); // VCM[5:0] for VCOMH
		LCD_WR_REG_DATA(0x020b, 0x0000);
		delay_ms(50);
		LCD_WR_REG_DATA(0x0200, 0x0000); // GRAM horizontal Address
		LCD_WR_REG_DATA(0x0201, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WR_REG_DATA(0x0300, 0x0000);
		LCD_WR_REG_DATA(0x0301, 0x0202);
		LCD_WR_REG_DATA(0x0302, 0x0202);
		LCD_WR_REG_DATA(0x0305, 0x0202);
		LCD_WR_REG_DATA(0x0306, 0x0202);
		LCD_WR_REG_DATA(0x0307, 0x0202);
		LCD_WR_REG_DATA(0x0308, 0x0202);
		LCD_WR_REG_DATA(0x0309, 0x0202);
		LCD_WR_REG_DATA(0x030C, 0x0202);
		LCD_WR_REG_DATA(0x030D, 0x0202);
		//------------------ Set GRAM area ---------------//
		LCD_WR_REG_DATA(0x0210, 0x0000); // Horizontal  Start Address
		LCD_WR_REG_DATA(0x0211, 0x00EF); // Horizontal  End Address
		LCD_WR_REG_DATA(0x0212, 0x0000); // Vertical  Start Address
		LCD_WR_REG_DATA(0x0213, 0x018F); // Vertical  End Address
		LCD_WR_REG_DATA(0x0400, 0x3100); // Gate Scan Line
		LCD_WR_REG_DATA(0x0401, 0x0001); // NDL,VLE, REV
		LCD_WR_REG_DATA(0x0404, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		LCD_WR_REG_DATA(0x0500, 0x0000);//Partial Image 1 Display Position
		LCD_WR_REG_DATA(0x0501, 0x0000); //Partial Image 1 RAM Start/End Address
		LCD_WR_REG_DATA(0x0502, 0x0000); //Partial Image 1 RAM Start/End Address
		LCD_WR_REG_DATA(0x0503, 0x0000); //Partial Image 2 Display Position
		LCD_WR_REG_DATA(0x0504, 0x0000);//Partial Image 2 RAM Start/End Address
		LCD_WR_REG_DATA(0x0505, 0x0000); //Partial Image 2 RAM Start/End Address
		//-------------- Panel Control -------------------//
		LCD_WR_REG_DATA(0x0010, 0x0010); //DIVI[1:0];RTNI[4:0]
		LCD_WR_REG_DATA(0x0011, 0x0600); //NOWI[2:0];SDTI[2:0]
		LCD_WR_REG_DATA(0x0020, 0x0002); //DIVE[1:0];RTNE[5:0]
		LCD_WR_REG_DATA(0x0007, 0x0173); // 262K color and display ON

		LCD_WR_REG(0x0202);
		delay_ms(20); 
}

/*************************三色函数**********************************************/
void LCD_Clear(void)
{
	u16 i,j;
	
	LCD_RS = 1;  //写数据
	LCD_CS = 0;
	for (i = 0; i < 133; i++) 
	{
		for(j=0;j<240;j++)
		{
			LCD_WR_DATA(red);
		}
	}
	for (i = 0; i < 133; i++) 
	{
		for(j=0;j<240;j++)
		{
			LCD_WR_DATA(green);
		}
	}
	for (i = 0; i < 134; i++) 
	{
		for(j=0;j<240;j++)
		{
			LCD_WR_DATA(blue);
		}
	}
	
}
//IC4551需要
void SLEEPEXIT(void)
{
	LCD_WR_REG_DATA(0x10, 0x0008);						 
	LCD_WR_REG_DATA(0x15, 0x7040);							
	LCD_WR_REG_DATA(0x11, 0x0510);	   //0x0110
	LCD_WR_REG_DATA(0x10, 0x3628);	 
	LCD_WR_REG_DATA(0x12, 0x0006);	 
	LCD_WR_REG_DATA(0x13, 0x0c2f);	  
	delay_ms(40); 
	LCD_WR_REG_DATA(0x12, 0x0015); //0x0016		 
	delay_ms(40);				
	LCD_WR_REG_DATA(0x10, 0x3640);	//0x3620  //0x3640	  
	LCD_WR_REG_DATA(0x13, 0x2b28);		//0x2D24  0x2C2f
	delay_ms(20); 
	LCD_WR_REG_DATA(0x07, 0x0001);
    LCD_WR_REG_DATA(0x07, 0x0021);
    LCD_WR_REG_DATA(0x07, 0x0023);
	LCD_WR_REG_DATA(0x07, 0x0033);
	LCD_WR_REG_DATA(0x07, 0x0133);

}

void SLEEPON(void)
{

    LCD_WR_REG_DATA(0x07, 0x0032);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0022);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0002);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0000);
    delay_ms(10);
    LCD_WR_REG_DATA(0x17, 0x0001);
    LCD_WR_REG_DATA(0x13, 0x0000);
    LCD_WR_REG_DATA(0x12, 0x0000);
    LCD_WR_REG_DATA(0x10, 0x0008);
    delay_ms(10);
    LCD_WR_REG_DATA(0x10, 0x000A);

}
//IC4551需要
void address(void)
{
	LCD_WR_REG_DATA(0x50,0x0000);
	LCD_WR_REG_DATA(0x51,0x00ef);
	LCD_WR_REG_DATA(0x52,0x0000);
	LCD_WR_REG_DATA(0x53,0x018f);
	LCD_WR_REG_DATA(0x20,0x0000);
	LCD_WR_REG_DATA(0x21,0x0000);
	LCD_WR_REG(0x22);
}

void Lcd_Initialize_4551(void)
{
	LCD_RST = 0;
	delay_ms(200);
	LCD_RST = 1;
	delay_ms(20);
	
	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delay_ms(5);
	LCD_CS = 0;
	
//下面是初始代码，不需要知道全部细节，一般由厂家提供
	//需要修改时要参考数据手册,初始化程序不一样显示效果也不一样
		LCD_WR_REG_DATA(0x15, 0x0030);							 
		LCD_WR_REG_DATA(0x11, 0x0010);	   //0x0110
		LCD_WR_REG_DATA(0x10, 0x3628);	 
		LCD_WR_REG_DATA(0x12, 0x0005);	 
		LCD_WR_REG_DATA(0x13, 0x0E40);	  
		delay_ms(40); 
		LCD_WR_REG_DATA(0x12, 0x0015); //0x0016		 
		delay_ms(40);				
		LCD_WR_REG_DATA(0x10, 0x3620);	//0x3620  //0x3640	  
		LCD_WR_REG_DATA(0x13, 0x2E40);		//0x2D24  0x2C2f
		delay_ms(20); 
		LCD_WR_REG_DATA(0x30, 0x0007);	
		LCD_WR_REG_DATA(0x31, 0x0602);		
		LCD_WR_REG_DATA(0x32, 0x0106);
		LCD_WR_REG_DATA(0x33, 0x0405);
		LCD_WR_REG_DATA(0x34, 0x0203);				
		LCD_WR_REG_DATA(0x35, 0x0602);		
		LCD_WR_REG_DATA(0x36, 0x0007);		
		LCD_WR_REG_DATA(0x37, 0x0504);	
		LCD_WR_REG_DATA(0x38, 0x0809);		
		LCD_WR_REG_DATA(0x39, 0x0809);
		delay_ms(20);
		LCD_WR_REG_DATA(0x01, 0x0100);	   
		LCD_WR_REG_DATA(0x02, 0x0300);
		LCD_WR_REG_DATA(0x03, 0x1030);
		LCD_WR_REG_DATA(0x08, 0x0808);	   
		LCD_WR_REG_DATA(0x0A, 0x0008);	
		LCD_WR_REG_DATA(0x60, 0x3100);		
		LCD_WR_REG_DATA(0x61, 0x0001);		
		LCD_WR_REG_DATA(0x90, 0x0054); //0x003c(60)//0x0044(68)  //0x0058(90)
		LCD_WR_REG_DATA(0x92, 0x010F);
		LCD_WR_REG_DATA(0x93, 0x0501);
		LCD_WR_REG_DATA(0x9A, 0x0009);
		LCD_WR_REG_DATA(0xA3, 0x0010);
		LCD_WR_REG_DATA(0x07, 0x0001);
		LCD_WR_REG_DATA(0x07, 0x0021);
		LCD_WR_REG_DATA(0x07, 0x0023);
		LCD_WR_REG_DATA(0x07, 0x0033);
		LCD_WR_REG_DATA(0x07, 0x0133);
		delay_ms(20); 
}