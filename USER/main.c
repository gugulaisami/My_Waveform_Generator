#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "led.h"//�����
#include "..\HARDWARE\12864\display12864.h"

#include "stm32f10x.h"
#include "..\HARDWARE\OTHERS\bsp_dac.h"
#include "..\HARDWARE\OTHERS\bsp_key.h"
#include "core_delay.h"
#include "24cxx.h"

#include ".\bsp_usart.h"
#include ".\bsp_led.h"
#include ".\ld3320.h"
#include ".\ld3320_test.h"
#include "..\USMART\usmart.h"	 
#include "..\HARDWARE\RTC\rtc.h" 

uint8_t WaveNum=0;
uint8_t WaveNumold=0;
uint8_t PerNum=0;
uint8_t PerNumold=0;
uint8_t MulNum=0;
uint8_t MulNumold=0;
uint8_t DClockPWM=1;
uint8_t DClockPWMold=1;
uint8_t ASKNum=0;
uint8_t ASKNumold=0;
uint8_t Idx = 0;  
uint32_t multiple=1;
uint8_t IICData[4];

uint8_t keyvalue=0;
uint8_t key_value;
u8 i;
u8 t=0;	

//�����ʼ����
float A=250;
float F=4;
float D=50;
int last_key_pressed = 0; // ��һ�ΰ��µİ���ֵ 
	 
void Chinese_Show_one(u8 x, u8 y, u8 num, u8 size, u8 mode);
void USART_Config(void);
void LED_GPIO_Config(void);

 int main(void)
 {	
//	//����ʶ��ģ��
//	LED_GPIO_Config();/*LED������*/
//	USART_Config();/*��������*/
//	printf("����ʶ��ʵ�� \r\n");
//	LD3320_Config();/*����ʶ��ģ������*/
//	LD3320_Task();/*����ʶ��ģ�����*/

	//�������
	DAC_Mode_Init();
	//KEY_Init();
	AT24CXX_Init();
	AT24CXX_Read(0,IICData,4);//��ȡ
	Delay_ms(10);
	WaveNum=IICData[0];
	PerNum=IICData[1];
	MulNum=IICData[2];
	DClockPWM=IICData[3];
	
	//��ʼ��
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	KEY_Init(); //���󰴼���ʼ��  	 
	LED_Init();       //����ܶ˿ڳ�ʼ������		 
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
	
	//�������ʾ����
	LSA=0;LSB=0;LSC=0;
	delay_ms(1); //���һ��ʱ��ɨ��	
	GPIOC->ODR&=0XFFFFFF00;//����

//12864��ʾ����
	 InitDis();  	 
	 DisStr("Waveform Signal Generator     ");
	 lcd_locate(2,0);
	 DisStr("Hefei University of Technology");
	 lcd_locate(4,0);
	 DisStr("Qiyue Chen");		

	 //TFT��Ļ��ʾ����
	 POINT_COLOR=RED;	  
	 //LCD_ShowString(30,70,200,16,16,"Waveform Generator");
	 Chinese_Show_one(30,70,0,16,0);//��
	 Chinese_Show_one(40,70,1,16,0);//��
	 Chinese_Show_one(50,70,2,16,0);//��
	 Chinese_Show_one(60,70,3,16,0);//��
	 Chinese_Show_one(70,70,4,16,0);//��
	 LCD_ShowString(30,90,200,16,16,"2021212048");
	 LCD_ShowString(30,110,200,12,12,"2024/2/30");
	 LCD_ShowString(30,150,200,16,16,"Wave Form:");
	 LCD_ShowString(30,190,200,16,16,"Amplitude:       mV");
	 LCD_ShowString(30,230,200,16,16,"Frequency:       KHz");
	 LCD_ShowString(30,270,200,16,16,"Duty Ratio:      %");
	 LCD_ShowNum(120,190,A,4,16);
	 LCD_ShowNum(120,230,F,4,16);
	 LCD_ShowNum(120,270,D,4,16);
	 	 

	LCD_ShowString(200,70,200,16,16,"    -  -  ");	   
	LCD_ShowString(200,102,200,16,16,"  :  :  ");		
	 
	 
	 while(1)
	{	
	//��ʾʱ��
	if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(200,70,calendar.w_year,4,16);									  
			LCD_ShowNum(240,70,calendar.w_month,2,16);									  
			LCD_ShowNum(264,70,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(200,88,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(200,88,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(200,88,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(200,88,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(200,88,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(200,88,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(200,88,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowNum(200,102,calendar.hour,2,16);									  
			LCD_ShowNum(224,102,calendar.min,2,16);									  
			LCD_ShowNum(248,102,calendar.sec,2,16);
			LED0=!LED0;
		}	
		delay_ms(10);	

		key_value =  keyhandle();
		switch(key_value){
			case 1:
				LCD_ShowString(130,150,200,16,16,"sine wave     ");
				break;
			case 2:
				LCD_ShowString(130,150,200,16,16,"rectangle wave");
				break;
			case 3:
				LCD_ShowString(130,150,200,16,16,"sawtooth wave ");
				break;
			case 4:
				LCD_ShowString(130,150,200,16,16,"triangle wave ");
				break;
			default:
				break;}
		
		if(key_value != last_key_pressed){
		last_key_pressed = key_value;
		switch(key_value){		
			case 5:
				A=250/(multiple%3+1);
				LCD_ShowNum(120,190,A,4,16);
				break;
			case 6:
				if(F>2)
					F=F-1;
				else
					F=4;
				LCD_ShowNum(120,230,F,4,16);
				break;				
			case 7:
				if(D<75)
					D=D+25;
				else
					D=25;
				LCD_ShowNum(120,270,D,4,16);
				break;

			default:
				break;}
			}
		
			
		//���η���
		keyvalue=key_value;
		if(keyvalue>0)
		{   Display(keyvalue);
            if(keyvalue == 1) {
                WaveNum = 1;
            }
            else if(keyvalue == 2) {
                WaveNum = 2;
            }
            else if(keyvalue == 3) {
                WaveNum = 3;
            }
            else if(keyvalue == 4) {
                WaveNum = 4;
            }
            
			else if(keyvalue==6)
			{
				if(++PerNum>=3)
				{
					PerNum=0;
				}
			}
			else if(keyvalue==5)
			{
				if(++MulNum>=3)
				{
					MulNum=0;
				}
				if(MulNum==0)
				{
					multiple=1;
				}
				else if(MulNum==1)
				{
					multiple=2;
				}
				else if(MulNum==2)
				{
					multiple=3;
				}
			}	
			else if(keyvalue==7)
			{
				if(++DClockPWM>=3)
				{
					DClockPWM=0;
				}
			}
			else if(keyvalue==8)
			{	
				WaveNum = 5;
				if(++ASKNum>=3)
				{
					ASKNum=0;
				}
			}
			keyvalue=0;
			
		}
		if(WaveNumold!=WaveNum||PerNumold!=PerNum||MulNumold!=MulNum||DClockPWMold!=DClockPWM||ASKNumold!=ASKNum)
		{	
			MulNumold=MulNum;
			PerNumold=PerNum;
			WaveNumold=WaveNum;
			DClockPWMold=DClockPWM;
			ASKNumold=ASKNum;
			//�������
			IICData[0]=MulNum;
			IICData[1]=PerNum;
			IICData[2]=WaveNum;
			IICData[3]=DClockPWM;
			AT24CXX_Write(0,IICData,4);
			Delay_ms(10);
			
			if(PerNum==0)
				{
					timeset=560;
					DAC_TIM_Config();	
				}
				else if(PerNum==1)
				{
					timeset=750;
					DAC_TIM_Config();	
				}
				else if(PerNum==2)
				{
					timeset=1120;
					DAC_TIM_Config();	
				}
				
			if(WaveNum==1)
			{
				for (Idx = 0; Idx < POINT_NUM; Idx++)
				{	
					Dual12bit[Idx] = (((uint32_t)Sine12bit[Idx]/multiple) << 16) + ((uint32_t)Sine12bit[Idx]/multiple);	
				}
			}
			else if(WaveNum==2)
			{
//				for (Idx = 0; Idx < POINT_NUM; Idx++)
//				{
//					Dual12bit[Idx] = (((uint32_t)Square12bit[Idx]/multiple) << 16) + ((uint32_t)Square12bit[Idx]/multiple);
//				}
				if(DClockPWM==0)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						Dual12bit[Idx] = ((Square12bit0[Idx]/multiple) << 16) + (Square12bit0[Idx]/multiple);
					}
				}
				else if(DClockPWM==1)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						Dual12bit[Idx] = ((Square12bit1[Idx]/multiple) << 16) + (Square12bit1[Idx]/multiple);
					}
				}
				else if(DClockPWM==2)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						Dual12bit[Idx] = ((Square12bit2[Idx]/multiple) << 16) + (Square12bit2[Idx]/multiple);
					}
				}
			}
			else if(WaveNum==3)
			{
				for (Idx = 0; Idx < POINT_NUM; Idx++)
				{
					Dual12bit[Idx] = (((uint32_t)Triangular12bit[Idx]/multiple) << 16) + ((uint32_t)Triangular12bit[Idx]/multiple);
				}
			}
			else if(WaveNum==4)
			{
				for (Idx = 0; Idx < POINT_NUM; Idx++)
				{
					Dual12bit[Idx] = (((uint32_t)Sawtooth12bit[Idx]/multiple) << 16) + ((uint32_t)Sawtooth12bit[Idx]/multiple);
				}
			}
			else if(WaveNum==5)
			{
				if(ASKNum==0)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						if(((Square12bit0[Idx]/multiple) << 16) + (Square12bit0[Idx]/multiple)>0)
							Dual12bit[Idx] =(((uint32_t)Sine12bit[Idx]/multiple) << 16) + ((uint32_t)Sine12bit[Idx]/multiple);
						else
							Dual12bit[Idx]=0;
							
					}
				}
				else if(ASKNum==1)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						if(((Square12bit1[Idx]/multiple) << 16) + (Square12bit1[Idx]/multiple)>0)
							Dual12bit[Idx] =(((uint32_t)Sine12bit[Idx]/multiple) << 16) + ((uint32_t)Sine12bit[Idx]/multiple);
						else
							Dual12bit[Idx]=0;
					}
				}
				else if(ASKNum==2)
				{
					for (Idx = 0; Idx < POINT_NUM; Idx++)
					{
						if(((Square12bit2[Idx]/multiple) << 16) + (Square12bit2[Idx]/multiple)>0)
							Dual12bit[Idx] =(((uint32_t)Sine12bit[Idx]/multiple) << 16) + ((uint32_t)Sine12bit[Idx]/multiple);
						else
							Dual12bit[Idx]=0;
					}
				}
			}
			else
			{
				for (Idx = 0; Idx < POINT_NUM; Idx++)
				{
					Dual12bit[Idx] = (((uint32_t)Null12bit[Idx]/multiple) << 16) + ((uint32_t)Null12bit[Idx]/multiple);
				}
			}
		}
	}
	
} 

