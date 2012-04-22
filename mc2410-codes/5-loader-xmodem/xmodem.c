#include "uart.h"
#include "stdio.h"

#define SOH  0x01
#define STX  0x02
#define EOT  0x04	//����������֪ͨ���շ�
#define ACK  0x06	//������ȷ
#define NAK  0x15	//��ʼ����һ�������ط�
#define CAN  0x18	//������ֹͣ����
#define CTRLZ 0x1A	//���㲿�����

void delay()
{
	int i,j;
	for(i = 0; i < 2; i++)
		for(j = 0; j < 1000000; j++);	
}

int xmodem_recv(int addr)
{
	int i = 0;
	char cnt;
	char buf[128 + 4];
	int size = 0;
	
	puts("Download will start when count to zero!\n");
	for(cnt = '9'; cnt >= '0'; cnt--)
	{
		uart_putchar(cnt);
		puts("\n");
		delay();	
	}
	uart_putchar(NAK);
	while((buf[0] = uart_getchar()) != EOT)
	{
		for(i = 1; i < 128 + 4; i++)
			buf[i] = uart_getchar();
		for(i = 0; i < 128; i++)
		{
			*(char *)(addr + size) = buf[i + 3];
			size++;
		}
		uart_putchar(ACK);
	}
	uart_putchar(ACK);
	
	return size;
}