#include "bsp_delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//�����Ҫʹ��OS,����������ͷ�ļ�����.




/**************************��Ӧ��gd32f303����ʱ*************************************/
//static u8  gd_fac_us=0;							//us��ʱ������			   
//static u16 gd_fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

////�ó�ʼ��û���õ��δ�ʱ�����ж�������ʱ
////����Ϊ  ��Ƶ/1M
//void gd_delay_init(int SYSCLK)
//{
//	
//	//ѡ���ⲿʱ��  HCLK/8,���Ǽ���һ�μ�ʱ��1/(HCLK/8)=8/HCLK��
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
//	//��Ҫ��ʱ1us,�൱����Ҫ1/(1M)�룬��������=(1/(1M)) / (8/HCLK) = HCLK/8M
//	gd_fac_us = SYSCLK/8;
//	gd_fac_ms = (u16) gd_fac_us*1000;
//}

////��ʱus
////����ΪҪ��ʱ��us��
////���ֵΪgd_us*gd_fac_us<0xffffff,gd_us<(0xffffff/gd_fac_us)=1118481
//void gd_delay_us(u32 gd_us)
//{
//	u32 temp;	    	 
//	SysTick->LOAD=gd_us*gd_fac_us; 				//ʱ�����	  		 
//	SysTick->VAL=0x00;        					//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
//	do
//	{
//		temp=SysTick->CTRL;
//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;  
//}


///************************************************
//�������� �� gd_delay_ms
//��    �� �� ��ʱms��
//��    �� �� ��ʱ����ms
//�� �� ֵ �� ��
//ע    �� �� SysTick->LOADΪ24λ�Ĵ���������(nms*1000*(SYSTICK/8))<=0XFFFFFF
//			��72M�����£�nms<=1864
//			���Բ��÷ֶ���ʱ���������ʱ��Χ
//*************************************************/
//void gd_delay_ms(u32 ms)
//{
//	u8 repeat=ms/1000;    //�õ�Ҫ��ʱ������
//	u16 remain = ms%1000;
//	while(repeat)
//	{
//		gd_delay_us(1000000); //1s
//		repeat--;
//	}
//	if(remain)
//	{
//		gd_delay_us(remain*1000); //��ʱ����ms
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
    /* setup systick timer for 1000Hz interrupts 1ms�ж�*/
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





























