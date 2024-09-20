#include "..\HARDWARE\OTHERS\bsp_dac.h"


/* �������� ---------------------------------------------------------*/
const uint16_t Sine12bit[POINT_NUM] = 	//���Ҳ�
{
	2048	, 2460	, 2856	, 3218	, 3532	, 3786	, 3969	, 4072	,
	4093	, 4031	, 3887	, 3668	, 3382	, 3042	,	2661	, 2255	, 
	1841	, 1435	, 1054	, 714		, 428		, 209		, 65		, 3			,
	24		, 127		, 310		, 564		, 878		, 1240	, 1636	, 2048
};


//const uint16_t Square12bit[POINT_NUM] = 	//����
//{
//	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
//	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
//	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
//	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
//};

const uint16_t Square12bit0[POINT_NUM] = 	//����
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	0	    , 0	    , 0	    , 0	    , 0	    , 0	    ,	0	    , 0	    , 
	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Square12bit1[POINT_NUM] = 	//����
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Square12bit2[POINT_NUM] = 	//����
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
	4095  , 4095  , 4095	, 4095	, 4095  , 4095  , 4095	, 4095	,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Triangular12bit[POINT_NUM] = //���ǲ�
{
	0	, 132	, 264	, 396	, 528	, 660	, 792	, 924	,
	1056	, 1188	, 1320	, 1452	, 1584	, 1716	,	1848	, 1980	, 
	2112	, 2244	, 2376	, 2508		, 2640	, 2772		, 2904		, 3036			,
	3168		, 3300		, 3432		, 3564		, 3696		, 3828	, 3960	, 4092
};

const uint16_t Sawtooth12bit[POINT_NUM] = //��ݲ�
{
	0	, 273	, 546	, 819	, 1092	, 1365	, 1638	, 1911	,
	2184	, 2457	, 2730	, 3003	, 3276	, 3549	,	3822	, 4095	, 
	4095	, 3822	, 3549	, 3276		, 3033		, 2730		, 2457		, 2184			,
	1911		, 1638		, 1365		, 1092		, 819		, 546	, 273	, 0
};


const uint16_t Null12bit[POINT_NUM] = //��ݲ�
{
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	, 
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
};




uint32_t Dual12bit[POINT_NUM];
uint16_t timeset=560;


/**
  * @brief  ʹ��DAC��ʱ�ӣ���ʼ��GPIO
  * @param  ��
  * @retval ��
  */
static void DAC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;

  /* ʹ��GPIOAʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	/* ʹ��DACʱ�� */	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
//  /* DAC��GPIO���ã�ģ������ */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//�Ҹĵģ�PA5�ĳ�PA3
  /* DAC��GPIO���ã�ģ������ */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	


  /* ����DAC ͨ��1 */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;						//ʹ��TIM2��Ϊ����Դ
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//��ʹ�ò��η�����
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//��ʹ��DAC�������
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* ����DAC ͨ��2 */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* ʹ��ͨ��1 ��PA4��� */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* ʹ��ͨ��2 ��PA5��� */
  DAC_Cmd(DAC_Channel_2, ENABLE);

  /* ʹ��DAC��DMA���� */
  DAC_DMACmd(DAC_Channel_2, ENABLE);
}


/**
  * @brief  ����TIM
  * @param  ��
  * @retval ��
  */
void DAC_TIM_Config(void)
{
	
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	
	/* ʹ��TIM2ʱ�ӣ�TIM2CLK Ϊ72M */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
  /* TIM2������ʱ������ */
 // TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = (timeset-1);       									//��ʱ���� 20  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       							//Ԥ��Ƶ������Ƶ 72M / (0+1) = 72M
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    						//ʱ�ӷ�Ƶϵ��
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* ����TIM2����Դ */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

	/* ʹ��TIM2 */
  TIM_Cmd(TIM2, ENABLE);

}

/**
  * @brief  ����DMA
  * @param  ��
  * @retval ��
  */
static void DAC_DMA_Config(void)
{	
	DMA_InitTypeDef  DMA_InitStructure;

	/* ʹ��DMA2ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	/* ����DMA2 */
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_ADDRESS;					//�������ݵ�ַ �Ĵ��� DHR12RD �ĵ�ַ12λ���Ҷ��롢˫ͨ��
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Dual12bit ;				//�ڴ����ݵ�ַ DualSine12bit
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;											//���ݴ��䷽���ڴ�������
  DMA_InitStructure.DMA_BufferSize = POINT_NUM;														//�����СΪPOINT_NUM�ֽ�	
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//�������ݵ�ַ�̶�	
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;									//�ڴ����ݵ�ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//������������Ϊ��λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;					//�ڴ���������Ϊ��λ	
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;													//ѭ��ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;											//��DMAͨ�����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;														//���ڴ����ڴ�ģʽ	

  DMA_Init(DMA2_Channel4, &DMA_InitStructure);
	
  /* ʹ��DMA2-14ͨ�� */
  DMA_Cmd(DMA2_Channel4, ENABLE);
}


/**
  * @brief  DAC��ʼ������
  * @param  ��
  * @retval ��
  */
void DAC_Mode_Init(void)
{

	DAC_Config();
	DAC_TIM_Config();	
	
	/* ������Ҳ������ݣ�˫ͨ���Ҷ���*/

	
	DAC_DMA_Config();
}






























