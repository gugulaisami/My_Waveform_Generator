#ifndef __LD3320_TEST_H
#define __LD3320_TEST_H



///LD3320������ض���
#define LD3320RST_PIN					GPIO_Pin_11		
#define LD3320RST_GPIO_PORT		GPIOB
#define LD3320RST_GPIO_CLK		RCC_APB2Periph_GPIOB
#define LD_RST_H() 						GPIO_SetBits(GPIOB, GPIO_Pin_11)//��ΪPB11
#define LD_RST_L() 						GPIO_ResetBits(GPIOB, GPIO_Pin_11)

#define LD3320CS_PIN					GPIO_Pin_10	  //������ԱȲ��ԣ�����������������������
#define LD3320CS_GPIO_PORT		GPIOB
#define LD3320CS_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LD_CS_H()							GPIO_SetBits(GPIOB, GPIO_Pin_10)//PB10
#define LD_CS_L()							GPIO_ResetBits(GPIOB, GPIO_Pin_10)


#define ETH_CS_H()							GPIO_SetBits(GPIOB, GPIO_Pin_12)//W5500��spiʹ��   PB12    !!!!!!!!!!!!!!!!
#define ETH_CS_L()							GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define VS_CS_H()							GPIO_SetBits(GPIOF, GPIO_Pin_7)//VS1053��spiʹ��  PF7
#define VS_CS_L()							GPIO_ResetBits(GPIOF, GPIO_Pin_7)



///LD3320EXTI�����������
#define LD3320_IRQ_GPIO_CLK		  RCC_APB2Periph_GPIOA           //�����жϣ���Ϊ��ѵʽ �����ﱣ�ֲ���
#define LD3320_IRQ_PIN					GPIO_Pin_2         //PA2
#define LD3320_IRQ_GPIO_PORT		GPIOA
#define LD3320_IRQEXIT_PORTSOURCE		GPIO_PortSourceGPIOA
#define LD3320_IRQPINSOURCE		GPIO_PinSource2
#define LD3320_IRQEXITLINE			EXTI_Line2
#define LD3320_IRQN						 EXTI2_IRQn
#define LD3320_IRQHandler     EXTI2_IRQHandler

#define LD3320WR_PIN					GPIO_Pin_8              //WR/SPIS    ��ΪPB8
#define LD3320WR_GPIO_PORT		GPIOB
#define LD3320WR_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LD_WR_H()							GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define LD_WR_L()							GPIO_ResetBits(GPIOB, GPIO_Pin_8)



///LD3320SPI�����������
#define	LD3320_SPI							  SPI1
#define LD3320_SPI_CLK				  	RCC_APB2Periph_SPI1						

#define LD3320_SPIMISO_PIN					GPIO_Pin_6           //PA6
#define LD3320_SPIMISO_GPIO_PORT		GPIOA
#define LD3320_SPIMISO_GPIO_CLK		  RCC_APB2Periph_GPIOA

#define LD3320_SPIMOSI_PIN					GPIO_Pin_7           //PA7
#define LD3320_SPIMOSI_GPIO_PORT		GPIOA
#define LD3320_SPIMOSI_GPIO_CLK		  RCC_APB2Periph_GPIOA

#define LD3320_SPISCK_PIN					GPIO_Pin_5           //PA5
#define LD3320_SPISCK_GPIO_PORT		GPIOA
#define LD3320_SPISCK_GPIO_CLK		RCC_APB2Periph_GPIOA

////�Ҹĵģ���PA5�ĳ�PA3
//#define LD3320_SPISCK_PIN					GPIO_Pin_3
//#define LD3320_SPISCK_GPIO_PORT		GPIOA
//#define LD3320_SPISCK_GPIO_CLK		RCC_APB2Periph_GPIOA

#define LD_SPIS_H()  					    GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define LD_SPIS_L()  					    GPIO_ResetBits(GPIOB, GPIO_Pin_8)


#define CLK_IN   					20  /* user need modify this value according to clock in */   //���ݾ������ã���������������������
#define LD_PLL_11					(uint8_t)((CLK_IN/2.0)-1)
#define LD_PLL_MP3_19			0x0f
#define LD_PLL_MP3_1B			0x18
#define LD_PLL_MP3_1D   	(uint8_t)(((90.0*((LD_PLL_11)+1))/(CLK_IN))-1)

#define LD_PLL_ASR_19 		(uint8_t)(CLK_IN*32.0/(LD_PLL_11+1) - 0.51)
#define LD_PLL_ASR_1B 		0x48
#define LD_PLL_ASR_1D 		0x1f

#define MIC_VOL 0x20


void  LD3320_Task(void);
void  EXTI_Hander(void);
void  LD_Test(void);
void  Glide_LED(void);
void  Flicker_LED(void);
void  Open_LED(void); 
void  Off_LED(void);


#endif /* __LD3320_TEST_H */
