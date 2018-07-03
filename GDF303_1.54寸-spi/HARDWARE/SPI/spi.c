#include "spi.h"
#include "delay.h"

#if (spi_init == 0)
void SPI2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,
                           ENABLE); //ʹ��PB,PE�˿�ʱ��
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ��,APB1���36M

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB,
              &GPIO_InitStructure);                  //�����趨������ʼ��GPIOB.5

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //SPI��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15����
	
	
	//��ΪоƬ�����ֲ�˵SPI�������Ϊ18Mbit/s,APB1/2=18M�����Կ�����Ϊ2��Ƶ
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
	
//	SPI2_ReadWriteByte(0xff);//��������	
}

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}

/***************************gd32f303_SPI1��ʼ��***********************************************/
void SPI1_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��PA�˿�ʱ��
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );//SPI1ʱ��ʹ��,ʵ��ʹ��gd��APB2ʱ����
														   //APB2=120M
	//��ͨIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_0;    //LED0-->PA.6 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure);                  //�����趨������ʼ��GPIOA.6



    //SPI��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PA5/6����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7);  //PB5/7����
	
	//SPI���Ϊ30M������APB2/4=30M,���ﲻ��ʹ��2��Ƶ
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
	
//	SPI2_ReadWriteByte(0xff);//��������	
}

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
//		{
//			retry++;
//			if(retry>200)return 0;

//		}	

//	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
//	retry=0;
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
//		{
//		retry++;
//		if(retry>200)return 0;
//		}	  						    
//	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
	
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); //��鷢���Ƿ����
//	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	//�����ʱ�������ˢ���ٶȱ�����������ȱ��
	/****************************************************
	***��������:
		��Ϊ��Ӳ��spi��������������ָ���MCU��ȥִ����һ����䣬
		SPIӲ���Զ�������ݴ��䣬��������Խ����һ�����ݻ�û�������
		�ֿ�ʼ��һ�����ݴ���ĵȴ�while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI������ֿ�ʼ��һ�����ݴ��䣬��LCD��Ҫһ��ʱ�䴦�����ݣ����ݻ�û������
		SPI�ͻ����LCDҪ��������ݡ����Է�ƵԽ����Ҫ�ȴ���ʱ��Խ���������ʱ����
		Ҫ���SPI�Ĵ����LCD�������ݣ�����ʱ��Ҫ����SCL
	****************************************************/
//	for(retry=0;retry<4;retry++);  
								
}
/********************************END***********************************************/



#elif (spi_init == 1)
void SPI2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,
                           ENABLE); //ʹ��PB,PE�˿�ʱ��
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;               //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB,
              &GPIO_InitStructure);                  //�����趨������ʼ��GPIOB.5

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

u8 SPI2_ReadWriteByte(u8 TxData)
{
    int i;
	for(i=0;i<8;i++)
	{
		if(TxData&0x80)
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		SCL = 0;
		SCL = 1;

		TxData<<=1;
	}
}

#endif