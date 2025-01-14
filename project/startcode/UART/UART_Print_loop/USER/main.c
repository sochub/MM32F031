/**
******************************************************************************
* @file     main.c
* @author   AE team
* @version  V1.1.1
* @date     15/05/2019
* @brief
******************************************************************************
*/

#include "HAL_device.h"
#include "HAL_conf.h"
#include "stdio.h"

#define RS_DIR_PORT         (GPIOA)
#define RS_DIR_PIN          (GPIO_Pin_11)
#define        RS485_R      GPIO_ResetBits(RS_DIR_PORT,RS_DIR_PIN);GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define      RS485_W         GPIO_SetBits(RS_DIR_PORT,RS_DIR_PIN);GPIO_SetBits(GPIOB,GPIO_Pin_7)

void UartInit_Loop(void);
void UartSendGroup(u8* buf, u16 len);
void Uart1RxTest(UART_TypeDef* UARTx);
unsigned char inbyte(UART_TypeDef* UARTx);

char printBuf[100];
static __IO uint32_t TimingDelay;
/********************************************************************************************************
**函数信息 ：int main (void)
**功能描述 ：开机后，ARMLED闪动
**输入参数 ：
**输出参数 ：
********************************************************************************************************/
void delay(u16 cnt)
{
    __IO uint32_t i = 0;
    for (i = cnt; i != 0; i--) 
    {
    }
}
/*******************************************************************************
**函数信息 ：void delay_init(void)
**功能描述 ：初始化延迟函数
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void delay_init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000)) {
        /* Capture error */
        while (1);
    }
    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);//SysTick中断优先级设置
}
/********************************************************************************************************
**函数信息 ：delay_ms(__IO uint32_t nTime)
**功能描述 ：程序应用调用延时，使用systick
**输入参数 ：nTime：延时
**输出参数 ：无
********************************************************************************************************/
void delay_ms(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while(TimingDelay != 0);
}

int main(void)
{
		delay_init();
    UartInit_Loop();                                        //UART1的发送，可以通过串口软件打印UART OK
    while(1) 
    {
//				RS485_W;
//			delay_ms(300);
////				delay(1000);
//				RS485_R;
//				delay(1000);
				delay_ms(500);
        UartSendGroup((u8*)printBuf, sprintf(printBuf, "UART OK!\r\n"));
//        delay(1000);
//        Uart1RxTest(UART1);  //UART1的接收，在串口软件中输入字符，可以通过打印验证接收的数据是否正确
    }
}

/********************************************************************************************************
**函数信息 ：UartInit_Loop(void)
**功能描述 ：初始化串口
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void UartInit_Loop(void)
{

    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;
    //485控制使能
 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);                       //使能UART1时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);                         //开启GPIOA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);                         //开启GPIOB时钟
    //UART 初始化设置
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);	
	
    UART_InitStructure.UART_BaudRate = 9600;                                  //串口波特率
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;                    //字长为8位数据格式
    UART_InitStructure.UART_StopBits = UART_StopBits_1;                         //一个停止位
    UART_InitStructure.UART_Parity = UART_Parity_No;                            //无奇偶校验位
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//无硬件数据流控制
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	                //收发模式

    UART_Init(UART1, &UART_InitStructure);                                      //初始化串口1
    UART_Cmd(UART1, ENABLE);                                                    //使能串口1

    //UART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                   //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;                             //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      //初始化GPIOA.9

    //UART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                  //PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                       	//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      //初始化GPIOA.10
		

		
    GPIO_InitStructure.GPIO_Pin  =  RS_DIR_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(RS_DIR_PORT, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
    UartSendGroup((u8*)printBuf, sprintf(printBuf, "UART OK!\r\n"));
}

/********************************************************************************************************
**函数信息 ：void Uart1RxTest(UART_TypeDef* UARTx)
**功能描述 ：串口接收函数测试
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：无
********************************************************************************************************/

void Uart1RxTest(UART_TypeDef* UARTx)
{
    unsigned char temp;
    temp = inbyte(UARTx);
    if(temp != 0) 
    {
        UartSendGroup((u8*)printBuf, sprintf(printBuf, "%c\r\n", temp));
    }
}

/********************************************************************************************************
**函数信息 ：unsigned char inbyte(UART_TypeDef* UARTx)
**功能描述 ：串口接收函数
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：unsigned char 串口接收返回的字节
********************************************************************************************************/
unsigned char inbyte(UART_TypeDef* UARTx)
{
    unsigned char temp;
    RS485_R;
    while(1) 
    {
        if(UART_GetITStatus(UARTx, UART_IT_RXIEN)) {
            UART_ClearITPendingBit(UARTx, UART_IT_RXIEN);                       //清除接受中断位
            break;
        }
    }
    temp = (uint8_t)UART_ReceiveData(UARTx);
    if(temp == 0xd) 
		{                                                           	//清除错误接收的数据
        return 0;
    }
    return temp;
}

/********************************************************************************************************
**函数信息 ：void UartSendByte(u8 dat)
**功能描述 ：UART发送数据
**输入参数 ：dat
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void UartSendByte(u8 dat)
{
    UART_SendData(UART1, dat);
    while(!UART_GetFlagStatus(UART1, UART_FLAG_TXEPT));
}

/********************************************************************************************************
**函数信息 ：void UartSendGroup(u8* buf,u16 len)
**功能描述 ：UART发送数据
**输入参数 ：buf,len
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void UartSendGroup(u8* buf, u16 len)
{
    RS485_W;
		delay(1);
    while(len--) UartSendByte(*buf++);
		delay(1);
    RS485_R;
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

