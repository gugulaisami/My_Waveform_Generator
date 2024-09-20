#ifndef __DAC_H
#define	__DAC_H


#include "stm32f10x.h"

#define POINT_NUM 32

//DAC DHR12RD寄存器，12位、右对齐、双通道
#define DAC_DHR12RD_ADDRESS      (DAC_BASE+0x20) 

extern uint16_t timeset;

/* 波形数据 ---------------------------------------------------------*/
extern void DAC_TIM_Config(void);

extern const uint16_t Sine12bit[POINT_NUM];

extern const uint16_t Square12bit0[POINT_NUM];

extern const uint16_t Square12bit1[POINT_NUM];

extern const uint16_t Square12bit2[POINT_NUM];

extern const uint16_t Triangular12bit[POINT_NUM];

extern const uint16_t Sawtooth12bit[POINT_NUM];//锯齿波

extern const uint16_t Null12bit[POINT_NUM];

extern uint32_t Dual12bit[POINT_NUM];

void DAC_Mode_Init(void);


#endif /* __DAC_H */

