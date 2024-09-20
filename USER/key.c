///////////////////////////////////////////////////////////////////////////////
//���󰴼�����  
////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "key.h"
#include "led.h"
#include "sys.h" 
#include "delay.h"

u16 keyz=0;

void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//KEY0-KEY3 ������̵���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY4-KEY7 ������̵���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//GPIO_SetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
	

}



u8 keyscan(void)
{ 
	uint8_t LIE,HANG,k,i=0;
	
	GPIO_Write(GPIOC, 0xF0);                            //D0-D3����,D4-D7����
	if((GPIO_ReadInputData(GPIOC)&0xF0)!=0xF0)          //�а�������
	{
	  delay_ms(40);                                     //ȥ��
	   if((GPIO_ReadInputData(GPIOC)&0xF0)!=0xF0)       //�ٴ��ж��Ƿ���
	   {
		   LIE=GPIO_ReadInputData(GPIOC);                 //��ȡ�������º�õ��Ĵ���
		   HANG=LIE;                                      //�����븴�Ƹ���
		   LIE=~LIE;                                      //������ȡ�������磺����ĳ�����õ�0111 0000��ȡ����õ�1000 1111
		   LIE=LIE&0XF0;                                  //�õ���1000 1111&1111 0000�õ�1000 0000,�õ�����
		   
			 for(i=0;i<4&&((HANG&0xF0)!=0xF0);i++)          //��ν������ߣ��ж�������ԭ����͵�λ�Ƿ���
		   {                                              //����֮ǰ��⵽Ϊ�͵��б�����Ƴ�
		       GPIO_Write(GPIOC, (HANG&0xF0)|(0x01<<i));  //������ɨ�裬��ν��п������ߣ��б���Ϊ���µ�״̬
		       HANG=GPIO_ReadInputData(GPIOC);            //��ȡIO�ڣ������ж��Ƿ�ɨ�赽������		   
		   }
		   HANG&=0x0F;                                    //����ֵȡ��
		   k=LIE|HANG;                                    //���������õ�����
			 
			 
			 
		   GPIO_Write(GPIOC, 0xF0);                       //D0-D3����,D4-D7����,�˴���������״̬��ʼ��Ϊδ����ʱ��״̬
	     while((GPIO_ReadInputData(GPIOC)&0xF0)!=0xF0)  //���ͷ�
		   {
		        delay_ms(40);                             //����������ʱ����Ҫ��һ��
		   }
		   return k;                                      //���ؼ���
	   }
	}	
	return (0);                                         //�޼����£�����0
}


 u8 keyhandle(void)
{ 
	uint8_t key_1=0;
	
	keyz=keyscan();
	if(keyz!=0)
		{ 
			switch(keyz)
			{
				case 0x11: key_1=1;break; 
				case 0x21: key_1=5;break; 
				case 0x41: key_1=9;break; 
				case 0x81: key_1=13;break; 
				case 0x12: key_1=2;break; 
				case 0x22: key_1=6;break; 
				case 0x42: key_1=10;break; 
				case 0x82: key_1=14;break;
				case 0x14: key_1=3;break;
				case 0x24: key_1=7;break;
        case 0x44: key_1=11;break;	
		    case 0x84: key_1=15;break;				
				case 0x18: key_1=4;break;
				case 0x28: key_1=8;break;
        case 0x48: key_1=12;break;	
		    case 0x88: key_1=16;break;		
				default:break;
			}
		
	}
	return key_1;
	
}




