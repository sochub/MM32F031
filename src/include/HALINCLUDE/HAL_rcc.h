/**
******************************************************************************
* @file     HAL_rcc.h
* @author   AE team
* @version  V1.0.1
* @date     23/11/2018
* @brief    This file contains all the functions prototypes for the RCC 
*           firmware library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2018 MindMotion</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_RCC_H
#define __HAL_RCC_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup RCC
* @{
*/

/** @defgroup RCC_Exported_Types
* @{
*/

typedef struct
{
    uint32_t SYSCLK_Frequency;
    uint32_t HCLK_Frequency;
    uint32_t PCLK1_Frequency;
    uint32_t PCLK2_Frequency;
} RCC_ClocksTypeDef;

/**
* @}
*/

/** @defgroup RCC_Exported_Constants
* @{
*/

/** @defgroup HSE_configuration 
* @{
*/

#define RCC_HSE_OFF ((uint32_t)0x00000000)
#define RCC_HSE_ON ((uint32_t)0x00010000)
#define RCC_HSE_Bypass ((uint32_t)0x00040000)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/**
* @}
*/

/** @defgroup System_clock_source 
* @{
*/

#define RCC_SYSCLKSource_HSI_DIV6 ((uint32_t)0x00000000)
#define RCC_SYSCLKSource_HSE ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_HSI ((uint32_t)0x00000002)
#define RCC_SYSCLKSource_LSI ((uint32_t)0x00000003)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI_DIV6) || \
((SOURCE) == RCC_SYSCLKSource_HSE) || \
    ((SOURCE) == RCC_SYSCLKSource_HSI)) || \
		((SOURCE) == RCC_SYSCLKSource_LSI))
/**
* @}
*/

/** @defgroup AHB_clock_source 
* @{
*/

#define RCC_SYSCLK_Div1 ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2 ((uint32_t)0x00000080)
#define RCC_SYSCLK_Div4 ((uint32_t)0x00000090)
#define RCC_SYSCLK_Div8 ((uint32_t)0x000000A0)
#define RCC_SYSCLK_Div16 ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div64 ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div128 ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div256 ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div512 ((uint32_t)0x000000F0)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) ||     \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) ||     \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) ||   \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))
/**
* @}
*/

/** @defgroup APB1_APB2_clock_source 
* @{
*/

#define RCC_HCLK_Div1 ((uint32_t)0x00000000)
#define RCC_HCLK_Div2 ((uint32_t)0x00000400)
#define RCC_HCLK_Div4 ((uint32_t)0x00000500)
#define RCC_HCLK_Div8 ((uint32_t)0x00000600)
#define RCC_HCLK_Div16 ((uint32_t)0x00000700)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))

/**
* @}
*/

/**
* @}
*/

/** @defgroup RCC_Interrupt_source 
* @{
*/

#define RCC_IT_LSIRDY ((uint8_t)0x01)
#define RCC_IT_HSIRDY ((uint8_t)0x04)
#define RCC_IT_HSERDY ((uint8_t)0x08)
#define RCC_IT_CSS ((uint8_t)0x80)
#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0xE0) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) ||                            \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_CSS))

#define IS_RCC_CLEAR_IT(IT) ((((IT) & (uint8_t)0x60) == 0x00) && ((IT) != 0x00))
/**
* @}
*/

/** @defgroup AHB_peripheral 
* @{
*/
#define RCC_AHBPeriph_DMA1 ((uint32_t)0x00000001)

#define RCC_AHBPeriph_SRAM ((uint32_t)0x00000004)
#define RCC_AHBPeriph_FLITF ((uint32_t)0x00000010)
#define RCC_AHBPeriph_CRC ((uint32_t)0x00000040)

#define RCC_AHBPeriph_GPIOA ((uint32_t)0x00020000)
#define RCC_AHBPeriph_GPIOB ((uint32_t)0x00040000)
#define RCC_AHBPeriph_GPIOC ((uint32_t)0x00080000)
#define RCC_AHBPeriph_GPIOD ((uint32_t)0x00100000)

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH)&0xFFE1FF6A) == 0x00) && ((PERIPH) != 0x00))
/**
* @}
*/

/** @defgroup APB2_peripheral 
* @{
*/

#define RCC_APB2Periph_SYSCFG ((uint32_t)0x00000001)
#define RCC_APB2Periph_ADC1 ((uint32_t)0x00000200)

#define RCC_APB2Periph_TIM1 ((uint32_t)0x00000800)
#define RCC_APB2Periph_TIM14 ((uint32_t)0x00010000)
#define RCC_APB2Periph_TIM16 ((uint32_t)0x00020000)
#define RCC_APB2Periph_TIM17 ((uint32_t)0x00040000)
#define RCC_APB2Periph_DBGMCU ((uint32_t)0x00400000)
#define RCC_APB2Periph_PWM ((uint32_t)0x00800000)
#define RCC_APB2Periph_ALL ((uint32_t)0x00C7DA01)
#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH)&0xFFB825FE) == 0x00) && ((PERIPH) != 0x00))
/**
* @}
*/

/** @defgroup APB1_peripheral 
* @{
*/

#define RCC_APB1Periph_TIM2 ((uint32_t)0x00000001)
#define RCC_APB1Periph_TIM3 ((uint32_t)0x00000002)

#define RCC_APB1Periph_WWDG ((uint32_t)0x00000800)
#define RCC_APB1Periph_SPI2 ((uint32_t)0x00004000)

#define RCC_APB1Periph_UART2 ((uint32_t)0x00020000)

#define RCC_APB1Periph_I2C1 ((uint32_t)0x00200000)

#define RCC_APB1Periph_PWR ((uint32_t)0x10000000)

#define RCC_APB1Periph_ALL ((uint32_t)0x10224803)

#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH)&0xE55DB7FC) == 0x00) && ((PERIPH) != 0x00))
/**
* @}
*/

/** @defgroup Clock_source_to_output_on_MCO_pin 
* @{
*/

#define RCC_MCO_NoClock ((uint8_t)0x00)
#define RCC_MCO_LSI ((uint8_t)0x02)
#define RCC_MCO_SYSCLK ((uint8_t)0x04)
#define RCC_MCO_HSI_Div4 ((uint8_t)0x05)
#define RCC_MCO_HSE ((uint8_t)0x06)
#define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) ||     \
                         ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) ||     \
                         ((MCO) == RCC_MCO_LSI)     || ((MCO) == RCC_MCO_LSE))
/**
* @}
*/

/** @defgroup RCC_Flag 
* @{
*/

#define RCC_FLAG_HSIRDY ((uint8_t)0x21)
#define RCC_FLAG_HSERDY ((uint8_t)0x31)
#define RCC_FLAG_LSIRDY ((uint8_t)0x61)
#define RCC_FLAG_PINRST ((uint8_t)0x7A)
#define RCC_FLAG_PORRST ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST ((uint8_t)0x7F)
#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) ||   \
                           ((FLAG) == RCC_FLAG_LSERDY) ||                                  \
                           ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) ||   \
                           ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) ||   \
                           ((FLAG) == RCC_FLAG_IWDGRST) || ((FLAG) == RCC_FLAG_WWDGRST) || \
                           ((FLAG) == RCC_FLAG_LPWRRST))

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)
/**
* @}
*/

/**
* @}
*/

/** @defgroup RCC_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup RCC_Exported_Functions
* @{
*/

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
void RCC_LSICmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);

//redefine    
#define RCC_APB2Periph_ADC               RCC_APB2Periph_ADC1
#define RCC_APB1Periph_SPI               RCC_APB1Periph_SPI2
#define RCC_APB1Periph_UART              RCC_APB1Periph_UART2
#define RCC_APB1Periph_I2C               RCC_APB1Periph_I2C1
#define RCC_AHBPeriph_DMA               RCC_AHBPeriph_DMA1
#endif /* __HAL_RCC_H */
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
