#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//LED��������	   
									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PCout(0)// PC0
#define LED1 PCout(1)// 
#define LED2 PCout(2)// 
#define LED3 PCout(3)// 
#define LED4 PCout(4)// 
#define LED5 PCout(5)// 
#define LED6 PCout(6)// 
#define LED7 PCout(7)// PC0

//������������ݶ˿�  
#define DX0 PDout(14)// 
#define DX1 PDout(15)// 
#define DX2 PDout(0)// 
#define DX3 PDout(1)// 
#define DX4 PEout(7)// 
#define DX5 PEout(8)// 
#define DX6 PEout(9)// 
#define DX7 PEout(10)// 

#define LSA PEout(11)     //���ƽ�
#define LSB PEout(12)     //���ƽ�
#define LSC PEout(13)     //���ƽ�

void LED_Init(void);//��ʼ��
void Display(u8 index);
		 				    
#endif
