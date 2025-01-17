/**
******************************************************************************
* @file    system_MM32F003_q.c
* @version V1.0.1
* @date    2018/09/14
* @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
* 
* 1.  This file provides two functions and one global variable to be called from 
*     user application:
*      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
*                      factors, AHB/APBx prescalers and Flash settings). 
*                      This function is called at startup just after reset and 
*                      before branch to main program. This call is made inside
*                      the "startup_MM32F003_q.s" file.
*
*      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
*                                  by the user application to setup the SysTick 
*                                  timer or configure other parameters.
*                                     
*      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
*                                 be called whenever the core clock is changed
*                                 during program execution.
*
* 2. After each device reset the HSI (8 MHz) is used as system clock source.
*    Then SystemInit() function is called, in "startup_MM32F003_q.s" file, to
*    configure the system clock before to branch to main program.
*
* 3. If the system clock source selected by user fails to startup, the SystemInit()
*    function will do nothing and HSI still used as system clock source. User can 
*    add some code to deal with this issue inside the SetSysClock() function.
*
* 4. The default value of HSE crystal is set to 8 MHz (or 25 MHz, depedning on
*    the product used), refer to "HSE_VALUE" define in "MM32F003_q.h" file. 
*    When HSE is used as system clock source, directly or through PLL, and you
*    are using different crystal you have to adapt the HSE value to your own
*    configuration.
*        
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MINDMOTION SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
******************************************************************************
*/

/** @addtogroup CMSIS
* @{
*/
#include "HAL_device.h"


/**
* @}
*/

/**
* @}
*/

/*!< Uncomment the line corresponding to the desired System clock (SYSCLK)
frequency (after reset the HSI is used as SYSCLK source)

IMPORTANT NOTE:
============== 
1. After each device reset the HSI is used as System clock source.

2. Please make sure that the selected System clock doesn't exceed your device's
maximum frequency.

3. If none of the define below is enabled, the HSI is used as System clock
source.

4. The System clock configuration functions provided within this file assume that:
- For Low, Medium and High density Value line devices an external 8MHz 
crystal is used to drive the System clock.
- For Low, Medium and High density devices an external 8MHz crystal is
used to drive the System clock.
- For Connectivity line devices an external 25MHz crystal is used to drive
the System clock.
If you are using different crystal you have to adapt those functions accordingly.
*/

//#define SYSCLK_FREQ_HSE    HSE_VALUE

#define SYSCLK_HSI_48MHz  48000000


/**
* @}
*/

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_HSI_48MHz
uint32_t SystemCoreClock         = SYSCLK_HSI_48MHz;        /*!< System Clock Frequency (Core Clock) */
#else /*!< HSI Selected as System Clock source */
uint32_t SystemCoreClock         = HSI_VALUE;        /*!< System Clock Frequency (Core Clock) */
#endif

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
/**
* @}
*/

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void);
#elif defined SYSCLK_HSI_48MHz
static void SetSysClockTo48_HSI(void);
#endif

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtl(void); 
#endif /* DATA_IN_ExtSRAM */

/**
* @}
*/

/**
* @brief  Setup the microcontroller system
*         Initialize the Embedded Flash Interface, the PLL and update the 
*         SystemCoreClock variable.
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
void SystemInit (void)
{
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;
    
    /* Reset SW, HPRE, PPRE1, PPRE2 and MCO bits */
    RCC->CFGR &= (uint32_t)0xF0FF0000;
    
    /* Reset HSEON, CSSON bits */
    RCC->CR &= (uint32_t)0xFFF6FFFF;
    
    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;
   
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
    
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
}

/**
* @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
* @param  None
* @retval None
*/
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_HSI_48MHz
    SetSysClockTo48_HSI();
#endif
    
    /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

#ifdef SYSCLK_FREQ_HSE
/**
* @brief  Selects HSE as System clock source and configure HCLK, PCLK2
*          and PCLK1 prescalers.
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	int i;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
        i = 1000;
        while (i--)
            ;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        
        /* Select HSE as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;    
        
        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }  
}


#elif defined SYSCLK_HSI_48MHz
void SetSysClockTo48_HSI(void)
{
    uint32_t temp = 0;   
    
    RCC->CR |= RCC_CR_HSION;  
    
    while (!(RCC->CR & RCC_CR_HSIRDY))
        ;
    
    RCC->CR &= (uint32_t)(~(1<<20));//
    
    RCC->CR &= (uint32_t)(~(1<<2));
  
    RCC->CFGR = RCC_CFGR_PPRE1_2;
    FLASH->KEYR = ((uint32_t)0x45670123);
    FLASH->KEYR = ((uint32_t)0xCDEF89AB);
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;
    
    RCC->CFGR &= ~RCC_CFGR_SW;
    
    RCC->CFGR |= 0x02;
    
    while( 1)
    {
        temp = (RCC->CFGR) >> 2;
        temp = temp& 0x03;
        if(temp ==0x2) break;
    }
}

#endif

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/    
/*-------------------------(C) COPYRIGHT 2018 MindMotion ----------------------*/
