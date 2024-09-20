#include ".\ld3320_test.h"
#include ".\bsp_usart.h"
#include ".\bsp_SysTick.h"
#include "stm32f10x.h"
#include <stdio.h>
#include ".\ld3320.h"
#include ".\bsp_led.h"

uint8_t   direct=0,process=0,flag=0; /*process����ʶ��ģ�鹤��״̬,flag�жϱ�־λ,direct����ʶ��ָ����Ϣ*/


/**
  * @brief  LD3320����
  * @param  ��
  * @retval ��
  */
void   LD3320_Task(void)
{
  uint8_t  i=0;	
  uint8_t  LD_ASR_Candi_Num; //���жϴ����ù�����
	uint8_t  j=1;
	uint8_t  buf[20];
	

	//���Զ�ȡ�Ĵ���	
	printf("LD3320_Task...\r\n");
  
   LD_WriteReg(0x29,0) ;   /*�ر��ж�*/
   LD_WriteReg(0x02,0) ;   
	
  	
   //1 ����״̬��2 ʶ��ɹ�״̬��3 ʶ��ʧ��״̬��
 
  while(1)
  {  
	  
    switch(process)
    { 
      case  0:         /*ld3320���ڿ���״̬*/
      i++;
      //process=LD_Run();  
      if(i==4)
      {
        printf("����ʶ��ģ���ڲ����ϣ�����Ӳ������ \r\n");
        return;
      }
      break;

      case  1:          /*ld3320����׼��OK*/
	  
	  
      if(flag)          /*�ж��ж�*/  //�ж�ʶ���Ƿ�ɹ�
      {          
        switch(direct)  /*�Խ��ִ����ز���*/         
        {
          case 1:       /*�����ˮ�ơ�*/
          printf(" ��ˮ�� ָ��ʶ��ɹ�\r\n");
          break;

          case 2:	      /*�����˸��*/
          printf(" ��˸ ָ��ʶ��ɹ�\r\n"); 
          break;

          case 3:	      /*�������������*/
          printf(" ����/���  ָ��ʶ��ɹ�\r\n"); 
          break;

          case 4:		    /*���ȫ��*/
          printf(" ȫ�� ָ��ʶ��ɹ�\r\n");
          break;
		  
		  case 5:		    /*������Ҳ���*/
          printf(" ���Ҳ� ָ��ʶ��ɹ�\r\n");
          break;

		  case 6:		    /*���������*/
          printf(" ���� ָ��ʶ��ɹ�\r\n");
          break;

		  case 7:		    /*�����ݲ���*/
          printf(" ��ݲ� ָ��ʶ��ɹ�\r\n");
          break;

		  case 8:		    /*������ǲ���*/
          printf(" ���ǲ� ָ��ʶ��ɹ�\r\n");
          break;
		  
          default:     
          break;
        } 
        process=flag=0;        
      }
      break;
      
      case  2:         /*ld3320����ʶ��ʧ��*/
      i=0;
      if(flag)         /*�ж��ж�*/
      {
        printf("δʶ����Ч��Ϣ��û������\r\n");
        process=flag=0;            
      } 
      break;      
                     
      default:
      break;  
    }
	
	
	  if((process==1)&&(LD_ReadReg(0xB2)==0x21) && (LD_ReadReg(0xbf)==0x35))	
	  {
		  printf("�����ж� ԭ�жϴ��� \r\n");	
		  
		  flag=1;     //������������
		  
				LD_ASR_Candi_Num = LD_ReadReg(0xba); 
				if(LD_ASR_Candi_Num>0 && LD_ASR_Candi_Num<=4) 
				{ 
					direct = LD_ReadReg(0xc5);					
					process=1;    //ʶ��ɹ�    
					 
					printf("���յ���������Ϣ %d \r\n",direct );  
				}else
				process=2;  //ʶ��ʧ��
	  
	  /*���һ������ʶ����������üĴ���*/
		LD_WriteReg(0x2b,0);
		LD_WriteReg(0x1C,0);//д0:ADC������
		LD_WriteReg(0x29,0);
		LD_WriteReg(0x02,0);
		LD_WriteReg(0x2B,0);
		LD_WriteReg(0xBA,0);	
		LD_WriteReg(0xBC,0);	
		LD_WriteReg(0x08,1);//���FIFO_DATA
		LD_WriteReg(0x08,0);//���FIFO_DATA�� �ٴ�д0   	
	  }
//     else
//	 process=2;  //ʶ��ʧ��

    LD_Test();
	
	
	
   }
}
   
   
/**
  * @brief  �жϴ���
  * @param  ��
  * @retval ��
  */
void  EXTI_Hander(void)
{

 
  
}
//��ǰ����
void W1(void);
void W2(void);
void W3(void);
void W4(void);

void  LD_Test(void)
{
  
  switch(direct)  //�Խ��ִ����ز���
	{
		case 1:  //�����ˮ�ơ� 
			Glide_LED();
		break;
    
		case 2:	  //�����˸��
			Flicker_LED();
		break;
    
		case 3:	//�������������  
			Open_LED();
		break;
    
		case 4:		//���ȫ��
			Off_LED();
		break;
		
		//�Ҽӵ�
		case 5:		    /*������Ҳ���*/
			W1();
        break;

		case 6:		    /*���������*/
			W2();
        break;

		case 7:		    /*�����ݲ���*/
			W3();
        break;

		case 8:		    /*������ǲ���*/
			W4();
        break;
		  
		default:
    break;
	}	
}


/**
  * @brief  ��ˮ��Ч��
  * @param  ��
  * @retval ��
  */
 void Glide_LED(void)
 {
  LED1_ON;
	Delayms(100);
	LED2_ON;
	Delayms(100);
	LED3_ON;
	Delayms(100);
   
  LED1_OFF;
	Delayms(100);
  LED2_OFF;
	Delayms(100); 
	LED3_OFF;
	Delayms(100);
  
 }

/**
  * @brief  ����˸
  * @param  ��
  * @retval ��
  */
void Flicker_LED(void)

{ 
  LED2_OFF;
	Delayms(200);
  LED2_ON;
	Delayms(200);	
}

/**
  * @brief  ����
  * @param  ��
  * @retval ��
  */
void Open_LED(void)
{
  LED2_ON;
}

/**
  * @brief  ��ȫ��Ϩ��
  * @param  ��
  * @retval ��
  */
void  Off_LED(void)
{

    LED1_OFF;
	LED2_OFF;
	LED3_OFF;

} 

void  W1(void)
{
    LED1_OFF;
	LED2_OFF;
	LED3_OFF;
} 

void  W2(void)
{

    LED1_OFF;
	LED2_OFF;
	LED3_OFF;

} 
void  W3(void)
{

    LED1_OFF;
	LED2_OFF;
	LED3_OFF;

} 
void  W4(void)
{
    LED1_OFF;
	LED2_OFF;
	LED3_OFF;
} 



