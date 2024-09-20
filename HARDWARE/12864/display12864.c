#include "stm32f10x.h"
#include "delay.h"
#include "display12864.h"
#include "sys.h"

#define u16 unsigned short  //为了可移植性好，对这两个 STM 32 已经定义过的变量，再定义一次。
#define u8 unsigned char

void write8bit(unsigned char dat)
{
//    unsigned char ret;
    unsigned char i;

    for(i=0; i<8; i++)
    {
        if(dat&0x80)
        {
            switch(i)
            {
            case 0:
                PEout(10)=1;
                break;
            case 1:
                PEout(9)=1;
                break;
            case 2:
                PEout(8)=1;
                break;
            case 3:
                PEout(7)=1;
                break;
            case 4:
                PDout(1)=1;
                break;
            case 5:
                PDout(0)=1;
                break;
            case 6:
                PDout(15)=1;
                break;
            case 7:
                PDout(14)=1;
                break;
            }
        }
        else
        {
            switch(i)
            {
            case 0:
                PEout(10)=0;
                break;
            case 1:
                PEout(9)=0;
                break;
            case 2:
                PEout(8)=0;
                break;
            case 3:
                PEout(7)=0;
                break;
            case 4:
                PDout(1)=0;
                break;
            case 5:
                PDout(0)=0;
                break;
            case 6:
                PDout(15)=0;
                break;
            case 7:
                PDout(14)=0;
                break;
            }
        }

        dat<<=1;
    }
}

/*********定义GPIO结构体 ********************/

GPIO_InitTypeDef  GPIOStru;                             //引脚号，速度，模式，定义用于定义所以引脚为输出的变量。

/****初始化 所有端口 为推挽输出模式  *********/
void IOInitOut(void)                                    //把 所有端口 初始化为推挽输出模式的函数。
{
    GPIOStru.GPIO_Mode = GPIO_Mode_Out_PP;              //引脚模式 定义所有的引脚为推挽输出的变量初始化。
    GPIOStru.GPIO_Speed = GPIO_Speed_50MHz;             //时钟频率

    GPIOStru.GPIO_Pin = Data1;                           //引脚号
    RCC_APB2PeriphClockCmd(DisDataClk1,ENABLE);              //使能 PC引脚 的时钟
    GPIO_Init(DisDataIO1,&GPIOStru);                        	//引脚初始化

    GPIOStru.GPIO_Pin = Data2;                           //引脚号
    RCC_APB2PeriphClockCmd(DisDataClk2,ENABLE);              //使能 PC引脚 的时钟
    GPIO_Init(DisDataIO2,&GPIOStru);                        	//引脚初始化

    GPIOStru.GPIO_Pin = RS|RW|EN;                           //引脚号
    RCC_APB2PeriphClockCmd(DisCtrlClk,ENABLE);              //使能 PG引脚 的时钟
    GPIO_Init(DisCtrlIO,&GPIOStru);                        	//引脚初始化

}

/****初始化数据data引脚为浮空输入模式  *******/

/****等待12864的忙状态结束 ******************/
void WaitBusy(void)                                     //等待12864的忙状态结束的函数。
{
    delay_ms(2);
}

/*********写命令函数   *********************/
void WriteCmd(u8 cmd)                                   //写命令函数。
{
    WaitBusy();                                         //等待12864忙状态结束
    GPIO_ResetBits(DisCtrlIO,RS);                           //RS = 0.
    GPIO_ResetBits(DisCtrlIO,RW);                           //RW = 0.
    GPIO_SetBits(DisCtrlIO,EN);                             //EN = 1.

    write8bit(cmd);             //此处，只有直接操作寄存器才能
    //达到，只改变 输出数据寄存器ODR 的低8位，其它位
    //不变的目的。因为，只有低8位是数据引脚，
    //其它位可能是控制引脚，不能改变。
    delay_ms(2);
    GPIO_ResetBits(DisCtrlIO,EN);                           //EN = 0;
    delay_ms(2);
}

/*********写数据函数   *********************/
void WriteData(u8 data)                                 //写数据函数。
{
    WaitBusy();
    GPIO_SetBits(DisCtrlIO,RS);                             //RS = 1.
    GPIO_ResetBits(DisCtrlIO,RW);                           //RW = 0.
    GPIO_SetBits(DisCtrlIO,EN);                             //EN = 1.
    write8bit(data);             //同上。
    delay_ms(2);
    GPIO_ResetBits(DisCtrlIO,EN);                           //EN = 0;
    delay_ms(2);
}

/***初始化12864 和要用到的STM32 的GPIO******/
void InitDis(void)                                      //初始化 12864 和要用到的 STM 32 的引脚。
{
    IOInitOut();

    delay_ms(2);
    WriteCmd(0x30);                                     //选择基本指令集，和，8位数据模式。
    delay_ms(2);
    WriteCmd(0x0c);                                     //开显示,无游标,不反白.
    delay_ms(2);
    WriteCmd(0x01);                                     //清除显示，并将 DDRAM 的地址计数器 AC 设为 00H.
    delay_ms(2);
    WriteCmd(0x06);                                     //设置，外部读写数据后,地址记数器 AC 会自动加 1。
    delay_ms(2);
    WriteCmd(0x80);                                     //将 DDRAM 地址计数器 AC 设为 0.
    delay_ms(2);
}

/*********显示字符串的函数  ****************/
void DisStr(u8 *s)                                      //显示字符串的函数。
{
    while(*s != '\0')
    {
        WriteData(*s);
        s++;
        delay_ms(2);                                    //控制每一个字符之间显示的时间 间隔
    }
}

/*********显示整型变量的函数  **************/
void DisInt(long int num)                               //显示整型变量的函数,最多显示16位的整数。只能显示正数。
{
    u8 temp[17];
    u8 str[17];
    int i=0,j=0;
    while(num != 0)	                                      //这里不能用num%10 != 0，如果num是10的整数倍，
        //例如，100，这样就会出错，根本就不能进入循环体。
    {
        temp[i] = (num%10)+0x30;
        num/=10;                                            //num 除以 10 = 剩下的树的整数  124/10=12
        i++;
    }
    i--;                                                  //因为i在退出循环之前还自加了一次，此时，
    //指向最后一个存储有用值的元素的后一个位置。
    while(i != -1)	                                      //因为i=0时，temp[0]还是有用值。
    {
        str[j] = temp[i];
        j++;
        i--;
    }
    str[j]='\0';                                          //因为i在退出循环之前还自加了一次，此时，
    //指向最后一个存储有用值的元素的后一个位置。
    DisStr(str);
}

/********显示有4位小数的浮点数  *************/
void DisFloat(float fnum)                               //显示有4位小数的浮点数，总位数不超过16位。
{
    long int num = fnum*10000;
    u8 temp[17];
    u8 str[17];
    int i=0,j=0;
    while(num != 0)
    {
        temp[i] = (num%10)+0x30;
        num/=10;
        i++;
        if(i == 4)	                                        //4位小数处理完后，加入小数点。
        {
            temp[i] = '.';
            i++;
        }
    }
    i--;
    while(i != -1)
    {
        str[j] = temp[i];
        j++;
        i--;
    }
    str[j]='\0';
    DisStr(str);
}

/********清全屏函数  ***********************/
void lcd_clear(void)
{
    WriteCmd(0x01);
}

/********起始显示位置设定函数  **************/
void lcd_locate(u8 X,u8 Y)
{
    switch(X)
    {
    case 1:
        WriteCmd(0x80+Y);
        break;
    case 2:
        WriteCmd(0x90+Y);
        break;
    case 3:
        WriteCmd(0x88+Y);
        break;
    case 4:
        WriteCmd(0x98+Y);
        break;
    }
}

/********位置显示字符串函数  ****************/
void lcd_DisStr(u8 X,u8 Y,u8 *s)
{
    lcd_locate( X, Y);
    DisStr( s );
}


