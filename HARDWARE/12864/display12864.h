#include "stm32f10x.h"

/********** 以下是相关引脚定义 **************/
//此次所用IO为：数据引脚为 GPIOC的0--7
#define DisDataIO1	        GPIOD                                 //定义12864要使用的I/O端口。
#define DisDataClk1         RCC_APB2Periph_GPIOD                  //定义12864要使用的I/O端口时钟。 
#define Data1 			    GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15

#define DisDataIO2	        GPIOE                                 //定义12864要使用的I/O端口。
#define DisDataClk2         RCC_APB2Periph_GPIOE                  //定义12864要使用的I/O端口时钟。 
#define Data2 			    GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10

//定义12864使用的数据引脚。
//以下为控制引脚，为PG 13 14 15
#define DisCtrlIO	        GPIOE                                 //定义12864要使用的I/O端口。
#define DisCtrlClk          RCC_APB2Periph_GPIOE                  //定义12864要使用的I/O端口时钟。
#define RS				    GPIO_Pin_11                          //1高电平 data  选择数据  低 无用
#define RW			  	    GPIO_Pin_12                          //高读低写
#define EN 		            GPIO_Pin_13                          //使能信号   定义使能端使用的引脚。

void IOInitOut(void);                                       //把 所有端口 初始化为输出模式的函数。
void IOInitIn(void);	                                      //把 数据data引脚 0--7 初始化为浮空输入的函数。
/*********基础时序操作  *****************/
void WaitBusy(void);      	                                //等待12864的忙状态结束的函数。
void WriteCmd(u8 cmd);                                      //写命令函数。
void WriteData(u8 data);                                    //写数据函数。
/*********初始化函数  *******************/
void InitDis(void);                                         //所有的 初始化 12864 和要用到的 STM 32 的引脚。

/*********基础功能函数  *****************/
void lcd_locate(u8 X,u8 Y);                                 //设定显示位置：  先设定显示位置函数，再设定要显示的字符

void DisStr(u8 *s);                                         //显示字符串的函数。
void DisInt(long int num);                                  //显示整型变量的函数,最多显示16位的整数。
void DisFloat(float fnum);                                  //显示有4位小数的浮点数，总位数不超过16位。
void lcd_clear(void);                                       //清屏函数,写入清屏命令

/********* 高级功能函数  ****************/
void lcd_DisStr(u8 X,u8 Y,u8 *s);                           //按起始位置显示字符串函数：X取1--4，Y取 1--8

