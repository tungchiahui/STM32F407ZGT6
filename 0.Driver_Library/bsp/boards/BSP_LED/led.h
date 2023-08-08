#ifndef __LED_H_
#define __LED_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"

	
#define LED0_GPIO_PORT GPIOF
#define LED0_Pin GPIO_PIN_9

#define LED1_GPIO_PORT GPIOF
#define LED1_Pin GPIO_PIN_10
	
#define __HAL_RCC_LED0_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PF口时钟使能 */
#define __HAL_RCC_LED1_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PF口时钟使能 */

#define LED0_OUT PFout(9)
#define LED1_OUT PFout(10)

namespace BSP_LED
{
		void LED_Init(void);
		void LED0_Init(void);
		void LED1_Init(void);
		void LED0_Switch(bool switch_status);
		void LED1_Switch(bool switch_status);
		void LED0_Toggle(void);
		void LED1_Toggle(void);
}



#ifdef __cplusplus
}
#endif

#endif
