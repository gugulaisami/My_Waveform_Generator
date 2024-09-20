#include "..\HARDWARE\OTHERS\bsp_dac.h"


/* 波形数据 ---------------------------------------------------------*/
const uint16_t Sine12bit[POINT_NUM] = 	//正弦波
{
	2048	, 2460	, 2856	, 3218	, 3532	, 3786	, 3969	, 4072	,
	4093	, 4031	, 3887	, 3668	, 3382	, 3042	,	2661	, 2255	, 
	1841	, 1435	, 1054	, 714		, 428		, 209		, 65		, 3			,
	24		, 127		, 310		, 564		, 878		, 1240	, 1636	, 2048
};


//const uint16_t Square12bit[POINT_NUM] = 	//方波
//{
//	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
//	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
//	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
//	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
//};

const uint16_t Square12bit0[POINT_NUM] = 	//方波
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	0	    , 0	    , 0	    , 0	    , 0	    , 0	    ,	0	    , 0	    , 
	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Square12bit1[POINT_NUM] = 	//方波
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
	0	    , 0   	, 0	    , 0	   	, 0		  , 0		  , 0	  	, 0			,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Square12bit2[POINT_NUM] = 	//方波
{
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	, 4095	,
	4095	, 4095	, 4095	, 4095	, 4095	, 4095	,	4095	, 4095	, 
	4095  , 4095  , 4095	, 4095	, 4095  , 4095  , 4095	, 4095	,
	0		  , 0	  	, 0	  	, 0	  	, 0	  	, 0   	, 0	    , 0
};

const uint16_t Triangular12bit[POINT_NUM] = //三角波
{
	0	, 132	, 264	, 396	, 528	, 660	, 792	, 924	,
	1056	, 1188	, 1320	, 1452	, 1584	, 1716	,	1848	, 1980	, 
	2112	, 2244	, 2376	, 2508		, 2640	, 2772		, 2904		, 3036			,
	3168		, 3300		, 3432		, 3564		, 3696		, 3828	, 3960	, 4092
};

const uint16_t Sawtooth12bit[POINT_NUM] = //锯齿波
{
	0	, 273	, 546	, 819	, 1092	, 1365	, 1638	, 1911	,
	2184	, 2457	, 2730	, 3003	, 3276	, 3549	,	3822	, 4095	, 
	4095	, 3822	, 3549	, 3276		, 3033		, 2730		, 2457		, 2184			,
	1911		, 1638		, 1365		, 1092		, 819		, 546	, 273	, 0
};


const uint16_t Null12bit[POINT_NUM] = //锯齿波
{
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	, 
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
	0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	,
};




uint32_t Dual12bit[POINT_NUM];
uint16_t timeset=560;


/**
  * @brief  使能DAC的时钟，初始化GPIO
  * @param  无
  * @retval 无
  */
static void DAC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;

  /* 使能GPIOA时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	/* 使能DAC时钟 */	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
//  /* DAC的GPIO配置，模拟输入 */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//我改的，PA5改成PA3
  /* DAC的GPIO配置，模拟输入 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	


  /* 配置DAC 通道1 */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;						//使用TIM2作为触发源
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//不使用波形发生器
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//不使用DAC输出缓冲
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* 配置DAC 通道2 */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* 使能通道1 由PA4输出 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* 使能通道2 由PA5输出 */
  DAC_Cmd(DAC_Channel_2, ENABLE);

  /* 使能DAC的DMA请求 */
  DAC_DMACmd(DAC_Channel_2, ENABLE);
}


/**
  * @brief  配置TIM
  * @param  无
  * @retval 无
  */
void DAC_TIM_Config(void)
{
	
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	
	/* 使能TIM2时钟，TIM2CLK 为72M */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
  /* TIM2基本定时器配置 */
 // TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = (timeset-1);       									//定时周期 20  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       							//预分频，不分频 72M / (0+1) = 72M
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    						//时钟分频系数
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* 配置TIM2触发源 */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

	/* 使能TIM2 */
  TIM_Cmd(TIM2, ENABLE);

}

/**
  * @brief  配置DMA
  * @param  无
  * @retval 无
  */
static void DAC_DMA_Config(void)
{	
	DMA_InitTypeDef  DMA_InitStructure;

	/* 使能DMA2时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	/* 配置DMA2 */
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_ADDRESS;					//外设数据地址 寄存器 DHR12RD 的地址12位、右对齐、双通道
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Dual12bit ;				//内存数据地址 DualSine12bit
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;											//数据传输方向内存至外设
  DMA_InitStructure.DMA_BufferSize = POINT_NUM;														//缓存大小为POINT_NUM字节	
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//外设数据地址固定	
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;									//内存数据地址自增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//外设数据以字为单位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;					//内存数据以字为单位	
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;													//循环模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;											//高DMA通道优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;														//非内存至内存模式	

  DMA_Init(DMA2_Channel4, &DMA_InitStructure);
	
  /* 使能DMA2-14通道 */
  DMA_Cmd(DMA2_Channel4, ENABLE);
}


/**
  * @brief  DAC初始化函数
  * @param  无
  * @retval 无
  */
void DAC_Mode_Init(void)
{

	DAC_Config();
	DAC_TIM_Config();	
	
	/* 填充正弦波形数据，双通道右对齐*/

	
	DAC_DMA_Config();
}






























