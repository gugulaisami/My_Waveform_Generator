#include "stm32f10x.h"
#include "delay.h"
#include "display12864.h"
#include "sys.h"

#define u16 unsigned short  //Ϊ�˿���ֲ�Ժã��������� STM 32 �Ѿ�������ı������ٶ���һ�Ρ�
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

/*********����GPIO�ṹ�� ********************/

GPIO_InitTypeDef  GPIOStru;                             //���źţ��ٶȣ�ģʽ���������ڶ�����������Ϊ����ı�����

/****��ʼ�� ���ж˿� Ϊ�������ģʽ  *********/
void IOInitOut(void)                                    //�� ���ж˿� ��ʼ��Ϊ�������ģʽ�ĺ�����
{
    GPIOStru.GPIO_Mode = GPIO_Mode_Out_PP;              //����ģʽ �������е�����Ϊ��������ı�����ʼ����
    GPIOStru.GPIO_Speed = GPIO_Speed_50MHz;             //ʱ��Ƶ��

    GPIOStru.GPIO_Pin = Data1;                           //���ź�
    RCC_APB2PeriphClockCmd(DisDataClk1,ENABLE);              //ʹ�� PC���� ��ʱ��
    GPIO_Init(DisDataIO1,&GPIOStru);                        	//���ų�ʼ��

    GPIOStru.GPIO_Pin = Data2;                           //���ź�
    RCC_APB2PeriphClockCmd(DisDataClk2,ENABLE);              //ʹ�� PC���� ��ʱ��
    GPIO_Init(DisDataIO2,&GPIOStru);                        	//���ų�ʼ��

    GPIOStru.GPIO_Pin = RS|RW|EN;                           //���ź�
    RCC_APB2PeriphClockCmd(DisCtrlClk,ENABLE);              //ʹ�� PG���� ��ʱ��
    GPIO_Init(DisCtrlIO,&GPIOStru);                        	//���ų�ʼ��

}

/****��ʼ������data����Ϊ��������ģʽ  *******/

/****�ȴ�12864��æ״̬���� ******************/
void WaitBusy(void)                                     //�ȴ�12864��æ״̬�����ĺ�����
{
    delay_ms(2);
}

/*********д�����   *********************/
void WriteCmd(u8 cmd)                                   //д�������
{
    WaitBusy();                                         //�ȴ�12864æ״̬����
    GPIO_ResetBits(DisCtrlIO,RS);                           //RS = 0.
    GPIO_ResetBits(DisCtrlIO,RW);                           //RW = 0.
    GPIO_SetBits(DisCtrlIO,EN);                             //EN = 1.

    write8bit(cmd);             //�˴���ֻ��ֱ�Ӳ����Ĵ�������
    //�ﵽ��ֻ�ı� ������ݼĴ���ODR �ĵ�8λ������λ
    //�����Ŀ�ġ���Ϊ��ֻ�е�8λ���������ţ�
    //����λ�����ǿ������ţ����ܸı䡣
    delay_ms(2);
    GPIO_ResetBits(DisCtrlIO,EN);                           //EN = 0;
    delay_ms(2);
}

/*********д���ݺ���   *********************/
void WriteData(u8 data)                                 //д���ݺ�����
{
    WaitBusy();
    GPIO_SetBits(DisCtrlIO,RS);                             //RS = 1.
    GPIO_ResetBits(DisCtrlIO,RW);                           //RW = 0.
    GPIO_SetBits(DisCtrlIO,EN);                             //EN = 1.
    write8bit(data);             //ͬ�ϡ�
    delay_ms(2);
    GPIO_ResetBits(DisCtrlIO,EN);                           //EN = 0;
    delay_ms(2);
}

/***��ʼ��12864 ��Ҫ�õ���STM32 ��GPIO******/
void InitDis(void)                                      //��ʼ�� 12864 ��Ҫ�õ��� STM 32 �����š�
{
    IOInitOut();

    delay_ms(2);
    WriteCmd(0x30);                                     //ѡ�����ָ����ͣ�8λ����ģʽ��
    delay_ms(2);
    WriteCmd(0x0c);                                     //����ʾ,���α�,������.
    delay_ms(2);
    WriteCmd(0x01);                                     //�����ʾ������ DDRAM �ĵ�ַ������ AC ��Ϊ 00H.
    delay_ms(2);
    WriteCmd(0x06);                                     //���ã��ⲿ��д���ݺ�,��ַ������ AC ���Զ��� 1��
    delay_ms(2);
    WriteCmd(0x80);                                     //�� DDRAM ��ַ������ AC ��Ϊ 0.
    delay_ms(2);
}

/*********��ʾ�ַ����ĺ���  ****************/
void DisStr(u8 *s)                                      //��ʾ�ַ����ĺ�����
{
    while(*s != '\0')
    {
        WriteData(*s);
        s++;
        delay_ms(2);                                    //����ÿһ���ַ�֮����ʾ��ʱ�� ���
    }
}

/*********��ʾ���ͱ����ĺ���  **************/
void DisInt(long int num)                               //��ʾ���ͱ����ĺ���,�����ʾ16λ��������ֻ����ʾ������
{
    u8 temp[17];
    u8 str[17];
    int i=0,j=0;
    while(num != 0)	                                      //���ﲻ����num%10 != 0�����num��10����������
        //���磬100�������ͻ���������Ͳ��ܽ���ѭ���塣
    {
        temp[i] = (num%10)+0x30;
        num/=10;                                            //num ���� 10 = ʣ�µ���������  124/10=12
        i++;
    }
    i--;                                                  //��Ϊi���˳�ѭ��֮ǰ���Լ���һ�Σ���ʱ��
    //ָ�����һ���洢����ֵ��Ԫ�صĺ�һ��λ�á�
    while(i != -1)	                                      //��Ϊi=0ʱ��temp[0]��������ֵ��
    {
        str[j] = temp[i];
        j++;
        i--;
    }
    str[j]='\0';                                          //��Ϊi���˳�ѭ��֮ǰ���Լ���һ�Σ���ʱ��
    //ָ�����һ���洢����ֵ��Ԫ�صĺ�һ��λ�á�
    DisStr(str);
}

/********��ʾ��4λС���ĸ�����  *************/
void DisFloat(float fnum)                               //��ʾ��4λС���ĸ���������λ��������16λ��
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
        if(i == 4)	                                        //4λС��������󣬼���С���㡣
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

/********��ȫ������  ***********************/
void lcd_clear(void)
{
    WriteCmd(0x01);
}

/********��ʼ��ʾλ���趨����  **************/
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

/********λ����ʾ�ַ�������  ****************/
void lcd_DisStr(u8 X,u8 Y,u8 *s)
{
    lcd_locate( X, Y);
    DisStr( s );
}


