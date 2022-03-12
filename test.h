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

extern u8 CanSendBuf[8];                   //CANͨ�ż�ⷢ�͵�����
extern u8 CanReceiveLieHao;                //CANͨ���յ����к� 
extern u8 CanReceiveliehao[2];             //CANͨ���յ����к�2λ��ʾ
extern u8 CanReceiveBuf[255][8];           //CANͨ���յ�������
extern u8 Com1ReceiveLieHao;               //USART1���ܵ����к�
extern u8 ThisColumnNumber;
extern u8 thiscolumnnumber[2];
extern u8 VersionNumber[];
extern u8 OK[];
extern u8 RN[];
extern u8 recflag;

void Test(void);
void Testinit(void);
void delay_s(u16 s);

#define FLASH_SAVE_ThisColumnNumber  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)


#endif
