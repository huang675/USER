#ifndef __TEST_H
#define __TEST_H 

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "can.h" 
#include "stm32f10x.h"
#include "ws2812b.h"
#include "timer.h"
#include "stmflash.h"

extern u8 CanSendBuf[8];                   //CAN通信监测发送的数据
extern u8 CanReceiveLieHao;                //CAN通信收到的列号 
extern u8 CanReceiveliehao[2];             //CAN通信收到的列号2位显示
extern u8 CanReceiveBuf[255][8];           //CAN通信收到的数据
extern u8 Com1ReceiveLieHao;               //USART1接受到的列号
extern u8 ThisColumnNumber;
extern u8 thiscolumnnumber[2];
extern u8 VersionNumber[];
extern u8 OK[];
extern u8 RN[];
extern u8 recflag;

void Test(void);
void Testinit(void);
void delay_s(u16 s);

#define FLASH_SAVE_ThisColumnNumber  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)


#endif
