#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 

//2.4��/2.8��/3.5��/4.3��/7�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963��		    

//********************************************************************************
//V1.2�޸�˵��
//֧����SPFD5408������,�����Һ��IDֱ�Ӵ�ӡ��HEX��ʽ.����鿴LCD����IC.
//V1.3
//�����˿���IO��֧��
//�޸��˱�����Ƶļ��ԣ�������V1.8���Ժ�Ŀ�����汾��
//����1.8�汾֮ǰ(������1.8)��Һ��ģ��,���޸�LCD_Init������LCD_LED=1;ΪLCD_LED=1;
//V1.4
//�޸���LCD_ShowChar������ʹ�û��㹦�ܻ��ַ���
//�����˺�������ʾ��֧��
//V1.5 20110730
//1,�޸���B505Һ������ɫ�����bug.
//2,�޸��˿���IO�������������÷�ʽ.
//V1.6 20111116
//1,�����LGDP4535Һ��������֧��
//V1.7 20120713
//1,����LCD_RD_DATA����
//2,���Ӷ�ILI9341��֧��
//3,����ILI9325�Ķ�����������
//4,����LCD_Scan_Dir����(����ʹ��)	  
//6,�����޸��˲���ԭ���ĺ���,����Ӧ9341�Ĳ���
//V1.8 20120905
//1,����LCD��Ҫ�������ýṹ��lcddev
//2,����LCD_Display_Dir����,֧�����ߺ������л�
//V1.9 20120911
//1,����RM68042������ID:6804��������6804��֧�ֺ�����ʾ����ԭ�򣺸ı�ɨ�跽ʽ��
//����6804��������ʧЧ���Թ��ܶ෽�������У���ʱ�޽⡣
//V2.0 20120924
//�ڲ�Ӳ����λ�������,ILI9341��ID��ȡ�ᱻ�����9300,�޸�LCD_Init,���޷�ʶ��
//�����������IDΪ9300/�Ƿ�ID��,ǿ��ָ������ICΪILI9341��ִ��9341�ĳ�ʼ����
//V2.1 20120930
//����ILI9325����ɫ��bug��
//V2.2 20121007
//����LCD_Scan_Dir��bug��
//V2.3 20130120
//����6804֧�ֺ�����ʾ
//V2.4 20131120
//1,����NT35310��ID:5310����������֧��
//2,����LCD_Set_Window����,�������ô���,�Կ������,�Ƚ�����,���Ǹú����ں���ʱ,��֧��6804.
//V2.5 20140211
//1,����NT35510��ID:5510����������֧��
//V2.6 20140504
//1,����ASCII 24*24�����֧��(���������û������������)  
//2,�޸Ĳ��ֺ�������,��֧��MDK -O2�Ż�
//3,���9341/35310/35510,дʱ������Ϊ���,�����ܵ�����ٶ�
//4,ȥ����SSD1289��֧��,��Ϊ1289ʵ����̫����,������Ҫ1us...��ֱ����.���ʺ�F4ʹ��
//5,����68042��C505��IC�Ķ���ɫ������bug.
//V2.7 20140710
//1,����LCD_Color_Fill������һ��bug. 
//2,����LCD_Scan_Dir������һ��bug.
//V2.8 20140721
//1,���MDKʹ��-O2�Ż�ʱLCD_ReadPoint��������ʧЧ������.
//2,����LCD_Scan_Dir����ʱ���õ�ɨ�跽ʽ��ʾ��ȫ��bug.
//V2.9 20141130
//1,������SSD1963 LCD��֧��.
//2,����LCD_SSD_BackLightSet����
//3,ȡ��ILI93XX��Rxx�Ĵ�������
//V3.0 20150423
//�޸�SSD1963 LCD������������.
//////////////////////////////////////////////////////////////////////////////////	 

  
//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ�� 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
  


//LCD��ַ�ṹ��
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR R2L_D2U// L2R_U2D  //Ĭ�ϵ�ɨ�跽��   

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_DrawPoint(u16 x,u16 y);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//���ٻ���
u16  LCD_ReadPoint(u16 x,u16 y); 											//���� 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//��ʾһ���ַ���,12/16����

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_SSD_BackLightSet(u8 pwm);							//SSD1963 �������
void LCD_Scan_Dir(u8 dir);									//������ɨ�跽��
void LCD_Display_Dir(u8 dir);								//������Ļ��ʾ����
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);	//���ô���					   						   																			 
//LCD�ֱ�������
#define SSD_HOR_RESOLUTION		800		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		480		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
//��ʾ����
const unsigned char chinese[16][36]={
{0x01,0x80,0x0F,0xFF,0x70,0x00,0x00,0xBE,0x72,0xA4,0x12,0xA4,0x15,0xBE,0x00,0x00},/*"��",0*/

{0x00,0x00,0x01,0x00,0x3F,0xE0,0x45,0x20,0x45,0x22,0x3D,0x3E,0x01,0x00,0x00,0x00},/*"��",1*/

{0x00,0x02,0x38,0x0C,0x05,0x72,0x7E,0xC4,0x05,0x38,0x24,0xE4,0x04,0x02,0x00,0x02},/*"��",2*/

{0x00,0x80,0x0F,0x02,0x14,0x42,0x04,0x42,0x7F,0xFE,0x04,0x42,0x08,0x42,0x00,0x02},/*"��",3*/

{0x00,0x10,0x3D,0x3E,0x25,0xE4,0x3F,0x3E,0x3D,0xBE,0x27,0x64,0x3F,0x3E,0x00,0x00},/*"��",4*/

{0x00,0x00,0x3F,0xFE,0x30,0xF4,0x13,0x98,0x3C,0xE2,0x17,0x9C,0x10,0x98,0x00,0x00},/*"��",5*/

{0x00,0x06,0x02,0x78,0x7F,0xFC,0x12,0x22,0x11,0xF2,0x12,0x0A,0x1E,0x0A,0x00,0x30},/*"��",6*/

{0x00,0x0E,0x02,0xF0,0x3F,0xFC,0x12,0x42,0x0F,0xEE,0x7F,0xF2,0x39,0x92,0x08,0x60},/*"Խ",7*/

//{0x00,0x80,0x01,0x00,0x06,0x00,0x1F,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x24,0x9F},
//{0x24,0x92,0xA4,0x92,0x64,0x92,0x24,0x92,0x24,0x92,0x24,0x9F,0x20,0x00,0x00,0x00},/*"��",0*/

//{0x01,0x00,0x01,0x00,0x01,0x00,0x7D,0x60,0x45,0xA0,0x45,0x20,0x45,0x20,0x45,0x20},
//{0x45,0x22,0x45,0x21,0x45,0x22,0x7D,0x3C,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00},/*"��",1*/

//{0x00,0x00,0x00,0x04,0x18,0x08,0x68,0x31,0x08,0xC1,0x0B,0x01,0x1D,0x82,0xE9,0x62},
//{0x09,0x14,0x09,0x08,0x09,0x14,0x49,0x22,0x29,0xC2,0x08,0x01,0x00,0x01,0x00,0x00},/*"��",2*/

//{0x01,0x02,0x02,0x02,0x0C,0x42,0x78,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0xFF,0xFE},
//{0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x42,0x08,0x02,0x00,0x02,0x00,0x00},/*"��",3*/

//{0x01,0x10,0x01,0x10,0x79,0x2F,0x49,0x29,0x49,0x49,0x49,0x49,0x79,0x8F,0x07,0x00},
//{0x01,0x80,0x79,0x4F,0x4D,0x49,0x4B,0x29,0x49,0x29,0x79,0x1F,0x01,0x10,0x00,0x00},/*"��",4*/

//{0x00,0x00,0x7F,0xFF,0x44,0x20,0x5A,0x10,0x61,0xE0,0x10,0x04,0x11,0x88,0x16,0xB0},
//{0x18,0x82,0xF0,0x81,0x17,0xFE,0x10,0x80,0x10,0xA0,0x10,0x90,0x10,0x0C,0x00,0x00},/*"��",5*/

//{0x02,0x01,0x12,0x06,0x12,0xF8,0x12,0x04,0xFF,0xFE,0x12,0x22,0x12,0x22,0x00,0x02},
//{0x23,0xF2,0x22,0x0A,0x22,0x0A,0x22,0x0A,0x3F,0x0A,0x00,0x3A,0x00,0x02,0x00,0x00},/*"��",6*/

//{0x02,0x01,0x12,0x7E,0x12,0x08,0xFF,0xFC,0x12,0x22,0x12,0x22,0x00,0x02,0x1F,0xF2},
//{0x10,0x22,0x10,0x0A,0xFF,0x92,0x10,0x62,0x91,0x92,0x56,0x3A,0x00,0x02,0x00,0x00},/*"Խ",7*/

	};

void Chinese_Show_one(u8 x, u8 y, u8 num, u8 size, u8 mode)
{
    u8 temp,t,t1;
    u8 y0=y;
    u8 csize=(size/8 + ((size%8)?1:0)) * size;     //     16/8+1
    for(t=0;t<csize;t++)
    {  
        if(size==16)     
					temp = chinese[num][t];     
        else 
					return;      
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x80) 
							LCD_Fast_DrawPoint(x,y,POINT_COLOR);
            else 
							LCD_Fast_DrawPoint(x,y,BACK_COLOR);
            temp<<=1;
            y++;
            if((y-y0)==size)
            {
                y=y0;
                x++;
                break;
            } 
         }  
     }  
}




