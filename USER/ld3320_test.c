#include ".\ld3320_test.h"
#include ".\bsp_usart.h"
#include ".\bsp_SysTick.h"
#include "stm32f10x.h"
#include <stdio.h>
#include ".\ld3320.h"
#include ".\bsp_led.h"

uint8_t   direct=0,process=0,flag=0; /*process语音识别模块工作状态,flag中断标志位,direct语音识别指令信息*/


/**
  * @brief  LD3320测试
  * @param  无
  * @retval 无
  */
void   LD3320_Task(void)
{
  uint8_t  i=0;	
  uint8_t  LD_ASR_Candi_Num; //从中断代码拿过来的
	uint8_t  j=1;
	uint8_t  buf[20];
	

	//测试读取寄存器	
	printf("LD3320_Task...\r\n");
  
   LD_WriteReg(0x29,0) ;   /*关闭中断*/
   LD_WriteReg(0x02,0) ;   
	
  	
   //1 空闲状态；2 识别成功状态；3 识别失败状态。
 
  while(1)
  {  
	  
    switch(process)
    { 
      case  0:         /*ld3320处于空闲状态*/
      i++;
      //process=LD_Run();  
      if(i==4)
      {
        printf("语音识别模块内部故障，请检查硬件连接 \r\n");
        return;
      }
      break;

      case  1:          /*ld3320语音准备OK*/
	  
	  
      if(flag)          /*中断判断*/  //判断识别是否成功
      {          
        switch(direct)  /*对结果执行相关操作*/         
        {
          case 1:       /*命令“流水灯”*/
          printf(" 流水灯 指令识别成功\r\n");
          break;

          case 2:	      /*命令“闪烁”*/
          printf(" 闪烁 指令识别成功\r\n"); 
          break;

          case 3:	      /*命令“按键触发”*/
          printf(" 开灯/点灯  指令识别成功\r\n"); 
          break;

          case 4:		    /*命令“全灭”*/
          printf(" 全灭 指令识别成功\r\n");
          break;
		  
		  case 5:		    /*命令“正弦波”*/
          printf(" 正弦波 指令识别成功\r\n");
          break;

		  case 6:		    /*命令“方波”*/
          printf(" 方波 指令识别成功\r\n");
          break;

		  case 7:		    /*命令“锯齿波”*/
          printf(" 锯齿波 指令识别成功\r\n");
          break;

		  case 8:		    /*命令“三角波”*/
          printf(" 三角波 指令识别成功\r\n");
          break;
		  
          default:     
          break;
        } 
        process=flag=0;        
      }
      break;
      
      case  2:         /*ld3320语音识别失败*/
      i=0;
      if(flag)         /*中断判断*/
      {
        printf("未识别到有效信息或没有声音\r\n");
        process=flag=0;            
      } 
      break;      
                     
      default:
      break;  
    }
	
	
	  if((process==1)&&(LD_ReadReg(0xB2)==0x21) && (LD_ReadReg(0xbf)==0x35))	
	  {
		  printf("进入判断 原中断处理 \r\n");	
		  
		  flag=1;     //！！！！！！
		  
				LD_ASR_Candi_Num = LD_ReadReg(0xba); 
				if(LD_ASR_Candi_Num>0 && LD_ASR_Candi_Num<=4) 
				{ 
					direct = LD_ReadReg(0xc5);					
					process=1;    //识别成功    
					 
					printf("接收到的语音信息 %d \r\n",direct );  
				}else
				process=2;  //识别失败
	  
	  /*完成一次语音识别后重新配置寄存器*/
		LD_WriteReg(0x2b,0);
		LD_WriteReg(0x1C,0);//写0:ADC不可用
		LD_WriteReg(0x29,0);
		LD_WriteReg(0x02,0);
		LD_WriteReg(0x2B,0);
		LD_WriteReg(0xBA,0);	
		LD_WriteReg(0xBC,0);	
		LD_WriteReg(0x08,1);//清除FIFO_DATA
		LD_WriteReg(0x08,0);//清除FIFO_DATA后 再次写0   	
	  }
//     else
//	 process=2;  //识别失败

    LD_Test();
	
	
	
   }
}
   
   
/**
  * @brief  中断处理
  * @param  无
  * @retval 无
  */
void  EXTI_Hander(void)
{

 
  
}
//提前声明
void W1(void);
void W2(void);
void W3(void);
void W4(void);

void  LD_Test(void)
{
  
  switch(direct)  //对结果执行相关操作
	{
		case 1:  //命令“流水灯” 
			Glide_LED();
		break;
    
		case 2:	  //命令“闪烁”
			Flicker_LED();
		break;
    
		case 3:	//命令“按键触发”  
			Open_LED();
		break;
    
		case 4:		//命令“全灭”
			Off_LED();
		break;
		
		//我加的
		case 5:		    /*命令“正弦波”*/
			W1();
        break;

		case 6:		    /*命令“方波”*/
			W2();
        break;

		case 7:		    /*命令“锯齿波”*/
			W3();
        break;

		case 8:		    /*命令“三角波”*/
			W4();
        break;
		  
		default:
    break;
	}	
}


/**
  * @brief  流水灯效果
  * @param  无
  * @retval 无
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
  * @brief  灯闪烁
  * @param  无
  * @retval 无
  */
void Flicker_LED(void)

{ 
  LED2_OFF;
	Delayms(200);
  LED2_ON;
	Delayms(200);	
}

/**
  * @brief  开灯
  * @param  无
  * @retval 无
  */
void Open_LED(void)
{
  LED2_ON;
}

/**
  * @brief  等全部熄灭
  * @param  无
  * @retval 无
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



