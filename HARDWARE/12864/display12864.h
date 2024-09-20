#include "stm32f10x.h"

/********** ������������Ŷ��� **************/
//�˴�����IOΪ����������Ϊ GPIOC��0--7
#define DisDataIO1	        GPIOD                                 //����12864Ҫʹ�õ�I/O�˿ڡ�
#define DisDataClk1         RCC_APB2Periph_GPIOD                  //����12864Ҫʹ�õ�I/O�˿�ʱ�ӡ� 
#define Data1 			    GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15

#define DisDataIO2	        GPIOE                                 //����12864Ҫʹ�õ�I/O�˿ڡ�
#define DisDataClk2         RCC_APB2Periph_GPIOE                  //����12864Ҫʹ�õ�I/O�˿�ʱ�ӡ� 
#define Data2 			    GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10

//����12864ʹ�õ��������š�
//����Ϊ�������ţ�ΪPG 13 14 15
#define DisCtrlIO	        GPIOE                                 //����12864Ҫʹ�õ�I/O�˿ڡ�
#define DisCtrlClk          RCC_APB2Periph_GPIOE                  //����12864Ҫʹ�õ�I/O�˿�ʱ�ӡ�
#define RS				    GPIO_Pin_11                          //1�ߵ�ƽ data  ѡ������  �� ����
#define RW			  	    GPIO_Pin_12                          //�߶���д
#define EN 		            GPIO_Pin_13                          //ʹ���ź�   ����ʹ�ܶ�ʹ�õ����š�

void IOInitOut(void);                                       //�� ���ж˿� ��ʼ��Ϊ���ģʽ�ĺ�����
void IOInitIn(void);	                                      //�� ����data���� 0--7 ��ʼ��Ϊ��������ĺ�����
/*********����ʱ�����  *****************/
void WaitBusy(void);      	                                //�ȴ�12864��æ״̬�����ĺ�����
void WriteCmd(u8 cmd);                                      //д�������
void WriteData(u8 data);                                    //д���ݺ�����
/*********��ʼ������  *******************/
void InitDis(void);                                         //���е� ��ʼ�� 12864 ��Ҫ�õ��� STM 32 �����š�

/*********�������ܺ���  *****************/
void lcd_locate(u8 X,u8 Y);                                 //�趨��ʾλ�ã�  ���趨��ʾλ�ú��������趨Ҫ��ʾ���ַ�

void DisStr(u8 *s);                                         //��ʾ�ַ����ĺ�����
void DisInt(long int num);                                  //��ʾ���ͱ����ĺ���,�����ʾ16λ��������
void DisFloat(float fnum);                                  //��ʾ��4λС���ĸ���������λ��������16λ��
void lcd_clear(void);                                       //��������,д����������

/********* �߼����ܺ���  ****************/
void lcd_DisStr(u8 X,u8 Y,u8 *s);                           //����ʼλ����ʾ�ַ���������Xȡ1--4��Yȡ 1--8

