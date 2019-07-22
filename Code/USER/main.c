#include "sys.h"


int Encoder=10000,Position_Zero=10000,Velocity;            //���������������
int Moto=0;                                   //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Voltage;                                //��ص�ѹ������صı���
float Balance_KP=30,Balance_KD=110,Balance_Ratio=0.01,Position_KP=45,Position_KD=120;  //PIDϵ��
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash�������
u8 Flag_OLED,State;  //State�ǵ�����״̬ 1������״̬  0���ǵ���״̬
//u8 func=0,X_flag=0;
//int local_pos;
int main(void)
{ 
	Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init();                 //=====��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	delay_ms(1000);                 //=====��ʱ�������ȴ�ϵͳ�ȶ�
	delay_ms(1000);                 //=====��ʱ�������ȴ�ϵͳ�ȶ� ��2s
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	EXTII_Init();                    //=====������ʼ��(�ⲿ�жϵ���ʽ)
	OLED_Init();                    //=====OLED��ʼ��
	uart_init(115200);    
	//uart3_init(115200);
	//=====��ʼ������1
	Moto_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ������������� 
	Encoder_Init_TIM4();            //=====��ʼ����������TIM2�ı������ӿ�ģʽ�� 
	Angle_Adc_Init();               //=====��λ�ƴ�����ģ�����ɼ���ʼ��
	Baterry_Adc_Init();             //=====��ص�ѹģ�����ɼ���ʼ��
	//Flash_Read();                   //=====��Flash�����ȡ����
	Timer1_Init(49,7199);           //=====��ʱ�жϳ�ʼ�� 
	while(1)
	{
		function();
		oled_show();              //===��ʾ����	  	
	} 
}
