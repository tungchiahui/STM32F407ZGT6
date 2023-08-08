#include "./BSP_LED/led.h"

void BSP_LED::LED0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  __HAL_RCC_LED0_GPIO_PORT_CLK_ENABLE();                         /* LED0ʱ��ʹ�� */

  GPIO_InitStruct.Pin = LED0_Pin;                     /* LED0���� */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;           /* ������� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                   /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;          /* ���� */
  HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);               /* ��ʼ��LED0���� */

	HAL_GPIO_WritePin(LED0_GPIO_PORT,LED0_Pin,GPIO_PIN_SET);     //Ĭ�ϵ���
}

void BSP_LED::LED1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  __HAL_RCC_LED1_GPIO_PORT_CLK_ENABLE();                          /* LED1ʱ��ʹ�� */

  GPIO_InitStruct.Pin = LED1_Pin;                     /* LED1���� */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;           /* ���� */
  HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);                /* ��ʼ��LED1���� */
	
	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_Pin,GPIO_PIN_SET);     //Ĭ�ϵ���
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
		LED0_OUT = 0;   //�͵�ƽ������
	}
	else
	{
		LED0_OUT = 1;   //�ߵ�ƽ�����
	}
}

void BSP_LED::LED1_Switch(bool switch_status)
{
	if(switch_status == true)
	{
		LED1_OUT = 0;   //�͵�ƽ������
	}
	else
	{
		LED1_OUT = 1;   //�ߵ�ƽ�����
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
