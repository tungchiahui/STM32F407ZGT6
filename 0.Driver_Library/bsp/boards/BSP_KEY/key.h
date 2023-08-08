#ifndef __KEY_H_
#define __KEY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"

	
#define WK_UP_GPIO_PORT GPIOA
#define KW_UP_Pin GPIO_PIN_0
	
#define KEY0_GPIO_PORT GPIOE
#define KEY0_Pin GPIO_PIN_4
	
#define KEY1_GPIO_PORT GPIOE
#define KEY1_Pin GPIO_PIN_3

#define __HAL_RCC_WK_UP_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */
#define __HAL_RCC_KEY0_GPIO_PORT_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define __HAL_RCC_KEY1_GPIO_PORT_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define WK_UP_EXTI_IRQn                  EXTI0_IRQn
#define WK_UP_EXTI_IRQHandler            EXTI0_IRQHandler

#define KEY0_EXTI_IRQn                   EXTI4_IRQn
#define KEY0_EXTI_IRQHandler             EXTI4_IRQHandler

#define KEY1_EXTI_IRQn                   EXTI3_IRQn
#define KEY1_EXTI_IRQHandler             EXTI3_IRQHandler

#define WK_UP_IN PAin(0)
#define KEY0_IN PEin(4)
#define KEY1_IN PEin(3)

namespace BSP_KEY
{
		void KEY_Init();
		void WK_UP_Init();
		void KEY0_Init();
		void KEY1_Init();

		bool WK_UP_Level();
		bool KEY0_Level();
		bool KEY1_Level();
		void WK_UP_EXTI_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void KEY0_EXTI_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void KEY1_EXTI_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
	
		void HAL_GPIO_EXTI_Callback_USER(uint16_t GPIO_Pin);
}

#ifdef __cplusplus
}
#endif

#endif
