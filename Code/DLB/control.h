#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
s16 SpeedPID(s16 Speed);
s16 AnglePID(void);
extern s16 Speed;

float Speed_Integral;//�ٶȻ��Ļ�����

void pid(void);
extern	int Balance_Pwm,Velocity_Pwm;
void TIM3_IRQHandler(void);
int balance(float angle);
int Position(int Encoder);
void Set_Pwm(int moto);
void Key(void);
void Xianfu_Pwm(void);
u8 Turn_Off(int voltage);
int myabs(int a);
int Incremental_PI (int Encoder,float Target);
int Position_PID (int Encoder,int Target);
void Run(u8 Way);
#endif
