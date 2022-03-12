/*
 * @Author: your name
 * @Date: 2022-03-12 22:28:01
 * @LastEditTime: 2022-03-12 22:48:01
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\test.c
 */
#include "test.h"

u8 CanSendBuf[8];                   //CAN通信发送的数据
u8 CanReceiveLieHao;                //CAN通信收到的列号 
u8 CanReceiveliehao[2];             //CAN通信收到的列号2位显示
u8 CanReceiveBuf[255][8]={0,0,0,0,0,0,0,0};                //CAN通信收到的数据
u8 Com1ReceiveLieHao;               //USART1接受到的列号

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
		if(key==KEY0_PRES)//KEY0按下,发送一次数据	
		{
         LED0=!LED0;
			for(i=0;i<9;i++)
			{
				CanSendBuf[i]=cnt+i;//填充发送缓冲区
 			}
			Can_Send_Msg(CanSendBuf,22);//发送8个字节					
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为
	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();				//按键初始化		 	  
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_2tq,24,CAN_Mode_Normal);//CAN初始化环回模式,波特率250Kbps  
    
    TIM2_PWM_Init(64,0);	//初始化PWM
	TIM2_DMA_Init();		//初始化DMA

    TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz  周期12.5us   控制电机  
	ThisColumnNumber=ReadFLASH(FLASH_SAVE_ThisColumnNumber,2);
}

void delay_s(u16 s)
{
    while(s--)delay_ms(1000);
}

