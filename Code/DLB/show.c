#include "show.h"

unsigned char i,temp;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
float Vol;
int Clear_Count;
extern u16 angle0;
u8 mark=10;

/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/

void oled_show(void)
{

		OLED_ShowString(15,0,"JC1");
		OLED_ShowString(15,10,"JC2");
		OLED_ShowString(15,20,"JC3");
		OLED_ShowString(15,30,"FH1");
		OLED_ShowString(15,40,"FH2");
		OLED_ShowString(15,50,"FH3");
		OLED_ShowString(15,50,"FH3");
		OLED_ShowString(80,50,"FUN:");
		OLED_ShowNumber(110,50,mark/10,2,12);
	//=============��������ʾ��ѹ��Ŀ��λ��=======================//			
		OLED_ShowString(80,40,"T:");	  
		OLED_ShowNumber(95,40,Encoder,5,12) ; 
		OLED_ShowString(80,0,"VOL:");
		OLED_ShowString(90,10,".");
		OLED_ShowString(110,10,"V");
		OLED_ShowNumber(80,10,Voltage/100,2,12);
		OLED_ShowNumber(95,10,Voltage%100,2,12);
//		 if(Voltage%100<10) 	OLED_ShowNumber(45,40,0,2,12);
		//=============��������ʾ��λ�ƴ������ͱ���������=======================//
		//OLED_ShowString(80,50,"DLB");    
		OLED_ShowString(80,20,"ADC:");  
		OLED_ShowNumber(80,30,angle0,4,12);
		//=============ˢ��=======================//
		OLED_Refresh_Gram();	
}			
	


