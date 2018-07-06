#include "bsp_delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果需要使用OS,则包括下面的头文件即可.




/**************************对应于gd32f303的延时*************************************/
//static u8  gd_fac_us=0;							//us延时倍乘数			   
//static u16 gd_fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

////该初始化没有用到滴答定时器的中断来作延时
////参数为  主频/1M
//void gd_delay_init(int SYSCLK)
//{
//	
//	//选择外部时钟  HCLK/8,即是即是一次计时是1/(HCLK/8)=8/HCLK秒
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
//	//需要计时1us,相当于需要1/(1M)秒，计数次数=(1/(1M)) / (8/HCLK) = HCLK/8M
//	gd_fac_us = SYSCLK/8;
//	gd_fac_ms = (u16) gd_fac_us*1000;
//}

////延时us
////参数为要延时的us数
////最大值为gd_us*gd_fac_us<0xffffff,gd_us<(0xffffff/gd_fac_us)=1118481
//void gd_delay_us(u32 gd_us)
//{
//	u32 temp;	    	 
//	SysTick->LOAD=gd_us*gd_fac_us; 				//时间加载	  		 
//	SysTick->VAL=0x00;        					//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;  
//}


///************************************************
//函数名称 ： gd_delay_ms
//功    能 ： 延时ms级
//参    数 ： 延时多少ms
//返 回 值 ： 无
//注    意 ： SysTick->LOAD为24位寄存器，即是(nms*1000*(SYSTICK/8))<=0XFFFFFF
//			当72M条件下，nms<=1864
//			所以采用分段延时来增大可延时范围
//*************************************************/
//void gd_delay_ms(u32 ms)
//{
//	u8 repeat=ms/1000;    //得到要延时多少秒
//	u16 remain = ms%1000;
//	while(repeat)
//	{
//		gd_delay_us(1000000); //1s
//		repeat--;
//	}
//	if(remain)
//	{
//		gd_delay_us(remain*1000); //延时多少ms
//	}
//}




volatile static uint32_t delay;

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_delay_init(void)
{
    /* setup systick timer for 1000Hz interrupts 1ms中断*/
    if (SysTick_Config(SystemCoreClock / 1000U)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void gd_delay_ms(uint32_t count)
{
    delay = count;

    while(0U != delay){
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    if (0U != delay){
        delay--;
    }
}





























