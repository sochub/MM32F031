#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "wwdg.h"
/********************************************************************************************************
**函数信息 ：int main (void)                          
**功能描述 ：开机后，ARMLED闪动
**输入参数 ：
**输出参数 ：
********************************************************************************************************/

int main(void)
{
    
    delay_init();
    uart_initwBaudRate(115200);	 //串口初始化为115200
    printf("uart ok!\r\n");
    
    /*窗口看门狗打开,微秒至毫秒级复位,与喂狗函数WWDG_SetCounter()并用*/
    Wwdg_reset_ON(0x7e,0x7f);                      //窗口看门狗FUN_2,短时内无喂狗动作复位
    
    while(1)                                       //无限循环
    {
        //WWDG->CR = 0x7e;                  //无喂狗程序进入死循环,反正系统一直打印串口数据
        delay_ms(1);
    }	
}



