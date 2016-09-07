/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

/* Includes */
#define GREENLED LED4
#define ORANGELED LED6
#include "defines.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Timer_Configuration(void);
void NVIC_Configuration(void);



/*******************************************************************************
* TIM3_IRQHandler
* @brief	This function handles TIM3 global interrupt request.
* @param    None
* @retval   None
*******************************************************************************/
//void TIM3_IRQHandler(void)
//{
//	/* Check if interrupt has occured */
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//	{
//		/* Clear interrupt pending bit */
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//
//		/* WHAT EVER YOU NEED TO DO IN THE INTERRUPT HANDLER GOES HERE */
//	}
//}

/**
  * @brief  Main program.
  * @param  None
  * @retval Int
  */
int main(void)
{
	SystemInit();

	TM_HD44780_Init(16,2);  // 16 cols * 2 rows

//	TM_HD44780_Puts(0, 0, "Rockin Rythms!!!");
//	Delayms(3000);
	RCC_Configuration();

	GPIO_Configuration();
	/* Forever loop */
	STM_EVAL_LEDInit(GREENLED);
	STM_EVAL_LEDInit(ORANGELED);

	for (;;)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_PIN_9))
		{
			STM_EVAL_LEDOff(GREENLED);
		}
		else
		{
			STM_EVAL_LEDOn(GREENLED);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "10:00");
			Delayms(300);
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_PIN_8))
		{
			STM_EVAL_LEDOff(ORANGELED);
		}
		else
		{
			STM_EVAL_LEDOn(ORANGELED);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "BUTTON2");
			Delayms(300);
		}
		/* DOES NOTHING HERE */
	}

	/* Program will never get here... */
	return 0;
}

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
