#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 

//LED驱动代码	   
								  
////////////////////////////////////////////////////////////////////////////////// 

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化

u8 seg_tab[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //表： 真值表0-9

//void LED_Init(void)
//{
// 
// GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
//	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PC0~7 端口配置
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
// GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
//	
// GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 						 // 输出高 
// 
//}

void LED_Init(void)            //数码管初始化函数
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PD PE端口时钟	
	
	//PD14 15  PD0 1   PE789 10
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15;//PD14 15  PD0 1  端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;//PE789 10  端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOE
	
}

void Display(u8 index)	//数码管显示函数
{
	DX0 = seg_tab[index]&0x01;
	DX1 = (seg_tab[index]>>1)&0x01;
	DX2 = (seg_tab[index]>>2)&0x01;
	DX3 = (seg_tab[index]>>3)&0x01;
	DX4 = (seg_tab[index]>>4)&0x01;
	DX5 = (seg_tab[index]>>5)&0x01;
	DX6 = (seg_tab[index]>>6)&0x01;
	DX7 = (seg_tab[index]>>7)&0x01;
} 