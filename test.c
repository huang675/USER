/*
 * @Author: your name
 * @Date: 2022-03-12 22:28:01
 * @LastEditTime: 2022-03-12 22:48:01
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\test.c
 */
#include "test.h"

u8 CanSendBuf[8];                   //CANͨ�ŷ��͵�����
u8 CanReceiveLieHao;                //CANͨ���յ����к� 
u8 CanReceiveliehao[2];             //CANͨ���յ����к�2λ��ʾ
u8 CanReceiveBuf[255][8]={0,0,0,0,0,0,0,0};                //CANͨ���յ�������
u8 Com1ReceiveLieHao;               //USART1���ܵ����к�

u8 recflag = 0;

u8 ThisColumnNumber=2;
u8 thiscolumnnumber[2];
u8 VersionNumber[]="Rev0.0.2";
u8 OK[]="OK        ";
u8 RN[]="\r\n";

void Test(void)
{
   u8 key;
	u8 i=0;
	u8 cnt=0x31;
	

 	while(1)
	{
		key=KEY_Scan(0);
       if(USART_RX_STA&0x8000)
		{ 
			Usart1_Check_Cmd();
			USART_RX_STA=0;
		}
		if(key==KEY0_PRES)//KEY0����,����һ������	
		{
         LED0=!LED0;
			for(i=0;i<9;i++)
			{
				CanSendBuf[i]=cnt+i;//��䷢�ͻ�����
 			}
			Can_Send_Msg(CanSendBuf,22);//����8���ֽ�					
		}
        while(recflag)
        {	   
			  can_run_cmd(recflag);
			  recflag--;
        }	
	}
}

void Testinit (void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��		 	  
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_2tq,24,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������250Kbps  
    
    TIM2_PWM_Init(64,0);	//��ʼ��PWM
	TIM2_DMA_Init();		//��ʼ��DMA

    TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz  ����12.5us   ���Ƶ��  
	ThisColumnNumber=ReadFLASH(FLASH_SAVE_ThisColumnNumber,2);
}

void delay_s(u16 s)
{
    while(s--)delay_ms(1000);
}

