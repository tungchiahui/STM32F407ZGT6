#include "./BSP_KEY/key.h"


/**
 * @brief       �жϷ����������Ҫ��������
 *              ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
 void BSP_KEY::HAL_GPIO_EXTI_Callback_USER(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == KW_UP_Pin)
	{
		
	}
	else if(GPIO_Pin == KEY0_Pin)
	{
		
	}
	else if(GPIO_Pin == KEY1_Pin)
	{
		
	}
}


/**
 * @brief       WK_UP �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
extern "C"
void WK_UP_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KW_UP_Pin);        /* �����жϴ����ú��� ���WK_UP�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KW_UP_Pin);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY0 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
extern "C"
void KEY0_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);        /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_Pin);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY1 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
extern "C"
void KEY1_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);        /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_Pin);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}


void BSP_KEY::KEY_Init()
{
	WK_UP_Init();
	KEY0_Init();
	KEY1_Init();
}

void BSP_KEY::WK_UP_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_WK_UP_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KW_UP_Pin;                        /* WKUP���� */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* ���� */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                    /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(WK_UP_GPIO_PORT, &GPIO_InitStruct);                 /* WKUP����ģʽ����,�������� */
}

void BSP_KEY::KEY0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_KEY0_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY0_Pin;                        /* KEY0���� */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* ���� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                     /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);                 /* KEY0����ģʽ����,�������� */
}

void BSP_KEY::KEY1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_KEY1_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY1_Pin;                        /* KEY1���� */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* ���� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                     /* ���� */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);                 /* KEY1����ģʽ����,�������� */
}

void BSP_KEY::WK_UP_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_WK_UP_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KW_UP_Pin;                        /* WKUP���� */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* ˫���ؼ�� */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* �Ȳ�����Ҳ������ */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(WK_UP_GPIO_PORT, &GPIO_InitStruct);                 /* WKUP����ģʽ����,˫���ؼ�� */
	
	HAL_NVIC_SetPriority(WK_UP_EXTI_IRQn,PreemptPriority,SubPriority);          /* ��ռ���ȼ��������ȼ� */
  HAL_NVIC_EnableIRQ(WK_UP_EXTI_IRQn);                       /* ʹ���ж���0 */
}

void BSP_KEY::KEY0_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_KEY0_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY0_Pin;                        /* KEY0���� */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* ˫���ؼ�� */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* �Ȳ�����Ҳ������ */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);                 /* KEY0����ģʽ����,˫���ؼ�� */
	
	HAL_NVIC_SetPriority(KEY0_EXTI_IRQn,PreemptPriority,SubPriority);          /* ��ռ���ȼ��������ȼ� */
  HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);                       /* ʹ���ж���4 */
}

void BSP_KEY::KEY1_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
	__HAL_RCC_KEY1_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY1_Pin;                        /* KEY1���� */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* ˫���ؼ�� */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* �Ȳ�����Ҳ������ */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
  HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);                 /* KEY1����ģʽ����,˫���ؼ�� */
	
	HAL_NVIC_SetPriority(KEY0_EXTI_IRQn,PreemptPriority,SubPriority);          /* ��ռ���ȼ��������ȼ� */
  HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);                       /* ʹ���ж���3 */
}

bool BSP_KEY::WK_UP_Level()
{
	return WK_UP_IN;
}

bool BSP_KEY::KEY0_Level()
{
	return KEY0_IN;
}

bool BSP_KEY::KEY1_Level()
{
	return KEY1_IN;
}


