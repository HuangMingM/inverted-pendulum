#include "control.h"		
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define ZHONGZHI 1052
#define ORIGIN 3225

int Balance_Pwm,Count_P2,Position_Pwm,Moto_qb,Count_Moto;
u8 Flag_Target,Flag_qb,Flag_qb2;
int Voltage_Temp,Voltage_Count,Voltage_All;
double Count_qb,Ratio=1;
u32 Count_Position;
u8 Flag_Position;
u16 target = 1080,Tar_pos=10000;
u16 angle0,angle1;             //����Ϊ��ǰ�Ƕȣ��ϴνǶȣ��ϴ�λ��    
int all_pwm,target_a;                   //����Ϊ��Ϻ��pwmֵ���������Ԥ��ֵ
int pos0,pos1,speed,pos_pwm,pos_angle; //λ�ã��ٶȣ�λ�û��֣�λ��pid��λ��ż�ϳɵĽǶ�ֵ
int ap_error,ad_error,ai_error;                //�ǶȲ�Ǽ��ٶ�
int nu=0;							//�������ִ���
u8 func2=0;   							//����2�ı�־λ
//����˼·��ͨ����λ��pid�ó��Ĳ������ϵ��Ƕ���ʵ����ǶȻ������
u8 func=0,X_flag=0;
int local_pos;
u16 kpa=24,kia=53,kda=150;//�ǶȻ���pid����
u16 kpv=15,kdv=150;  //λ�û���pd����

void pid(void)
{
	angle0=Get_Adc_Average(3,12);         //�����Ƕ�ֵ  
	
//	if(count>count_exp+500) count=count_exp;        //�޷�
//  else if(count<count_exp-500)	count=count_exp;
	Encoder = Read_Encoder(4);
	
	if(X_flag==1)
	{
		
		Tar_pos+=1;
		if(Encoder-local_pos>1800)
		{
			X_flag=0;
		}
	}
	pos0=Encoder-Tar_pos;                //������ǰλ�ò� pos0
	speed=pos0-pos1;                 //λ�õ�΢�� ���ٶ�
	pos_pwm=kpv*pos0+kdv*speed;      //λ��pid
	
	pos_angle=pos_pwm/32;               //���ϳɽǶ�

	if(pos_angle>170) pos_angle=170;        //������ֵ�޷�
	else if(pos_angle<-170) pos_angle=-170;
	target_a=target-pos_angle;          //�����µ�Ԥ��ֵ

	ap_error=target_a-angle0;             //��Ϻ�ǶȲ�
	ad_error=angle0-angle1;	              //�Ƕ�΢��  
	
	if(myabs(target-angle0)<300)      
	{	
		ai_error=ai_error+target-angle0;    //�ǶȻ���
		all_pwm=kpa*ap_error+kia*ai_error/100-kda*ad_error;    //��Ϻ��pid����
	}
	else  all_pwm=0;
	angle1=angle0;
	pos1=pos0;               //��ֵ
	nu++;                                 //�����������ƴ�������ֹ���޴�
	if(nu==200) ai_error=0,nu=0;
}

void TIM3_IRQHandler(void)              //��ʱ��5�жϺ���
{
	static u8 SpCount=0,LedCount=0,count0;//SpCount�ٶȻ����ڼ�����LedCount״̬�Ƶ��ڼ���
	static s16 Angle_Pwm,Speed_Pwm;//�ǶȻ����ٶȻ�PWM���
	 
	if(TIM3->SR&0X0001)//����ж�
	{	
		pid();
		Set_Pwm(all_pwm);
		Led_Flash(100);                         //===LED��˸ָʾϵͳ�������� 
		Voltage_Temp=Get_battery_volt();		    //=====��ȡ��ص�ѹ		
		Voltage_Count++;                        //=====ƽ��ֵ������
		Voltage_All+=Voltage_Temp;               //=====��β����ۻ�
		if(Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//=====��ƽ��ֵ		
	}	
  TIM3->SR&=~(1<<0);
}	
	u8 i =0;
void function(void)//����������չ����1����ڣ�������2���ڱ���ת1Ȧ��ʵ�ֺ���
{
	switch(func)
	{
		case(10):
			TIM_Cmd(TIM3,DISABLE); 
			for(i=0;i<3;i++)
			{
				Set_Pwm(2000);
				delay_ms(500);
				Set_Pwm(-2000);
				delay_ms(500);
			}
			//TIM_Cmd(TIM3,ENABLE); 
			Set_Pwm(0);
			func=0;
		break;
		case(20):
			TIM_Cmd(TIM3,DISABLE); 
			for(i=0;i<3;i++)
			{
				Set_Pwm(3000);
				delay_ms(500);
				Set_Pwm(-2000);
				delay_ms(200);
			}
			//TIM_Cmd(TIM3,ENABLE);
			Set_Pwm(0);			
			func=0;
		break;

		case(30):
			TIM_Cmd(TIM3,ENABLE); 
			Tar_pos= TIM4->CNT;
			func=0;
		break;
        case(40):
			TIM_Cmd(TIM3,DISABLE); 
			Set_Pwm(3000);
			delay_ms(430);
			Set_Pwm(-1700);
			delay_ms(160);
			TIM_Cmd(TIM3,ENABLE); 
			delay_ms(300);
			Tar_pos= TIM4->CNT;
			func=0;
		break;
		case(50):
			TIM_Cmd(TIM3,ENABLE);
			Tar_pos= TIM4->CNT;		
			func=0;
		case(60):
			TIM_Cmd(TIM3,ENABLE); 
			local_pos=TIM4->CNT;
			X_flag=1;
			func=0;
		break;
        
        default:break;
    }
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int moto)
{
    	if(moto<0)			AIN2=1,			AIN1=0;
			else 	          AIN2=0,			AIN1=1;
			PWMA=myabs(moto);//�򵥵�TB6612 ����
}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
