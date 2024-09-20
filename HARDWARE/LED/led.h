#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//LED驱动代码	   
									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PCout(0)// PC0
#define LED1 PCout(1)// 
#define LED2 PCout(2)// 
#define LED3 PCout(3)// 
#define LED4 PCout(4)// 
#define LED5 PCout(5)// 
#define LED6 PCout(6)// 
#define LED7 PCout(7)// PC0

//定义数码管数据端口  
#define DX0 PDout(14)// 
#define DX1 PDout(15)// 
#define DX2 PDout(0)// 
#define DX3 PDout(1)// 
#define DX4 PEout(7)// 
#define DX5 PEout(8)// 
#define DX6 PEout(9)// 
#define DX7 PEout(10)// 

#define LSA PEout(11)     //控制脚
#define LSB PEout(12)     //控制脚
#define LSC PEout(13)     //控制脚

void LED_Init(void);//初始化
void Display(u8 index);
		 				    
#endif
