#include "./BSP_LED/led.h"

void BSP_LED::LED0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  __HAL_RCC_LED0_GPIO_PORT_CLK_ENABLE();                         /* LED0时钟使能 */

  GPIO_InitStruct.Pin = LED0_Pin;                     /* LED0引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;           /* 推挽输出 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                   /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;          /* 低速 */
  HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);               /* 初始化LED0引脚 */

	HAL_GPIO_WritePin(LED0_GPIO_PORT,LED0_Pin,GPIO_PIN_SET);     //默认灯灭
}

void BSP_LED::LED1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  __HAL_RCC_LED1_GPIO_PORT_CLK_ENABLE();                          /* LED1时钟使能 */

  GPIO_InitStruct.Pin = LED1_Pin;                     /* LED1引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;           /* 低速 */
  HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);                /* 初始化LED1引脚 */
	
	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_Pin,GPIO_PIN_SET);     //默认灯灭
}

void BSP_LED::LED_Init()
{
	LED0_Init();
	LED1_Init();
}

void BSP_LED::LED0_Switch(bool switch_status)
{
	if(switch_status == true)
	{
		LED0_OUT = 0;   //低电平，亮灯
	}
	else
	{
		LED0_OUT = 1;   //高电平，灭灯
	}
}

void BSP_LED::LED1_Switch(bool switch_status)
{
	if(switch_status == true)
	{
		LED1_OUT = 0;   //低电平，亮灯
	}
	else
	{
		LED1_OUT = 1;   //高电平，灭灯
	}
}

void BSP_LED::LED0_Toggle()
{
	LED0_OUT = ! LED0_OUT;
}

void BSP_LED::LED1_Toggle()
{
	LED1_OUT = ! LED1_OUT;
}
