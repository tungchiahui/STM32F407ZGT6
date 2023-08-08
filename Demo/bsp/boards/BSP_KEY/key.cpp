#include "./BSP_KEY/key.h"


/**
 * @brief       中断服务程序中需要做的事情
 *              在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
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
 * @brief       WK_UP 外部中断服务程序
 * @param       无
 * @retval      无
 */
extern "C"
void WK_UP_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KW_UP_Pin);        /* 调用中断处理公用函数 清除WK_UP所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(KW_UP_Pin);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY0 外部中断服务程序
 * @param       无
 * @retval      无
 */
extern "C"
void KEY0_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);        /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_Pin);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY1 外部中断服务程序
 * @param       无
 * @retval      无
 */
extern "C"
void KEY1_EXTI_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);        /* 调用中断处理公用函数 清除KEY1所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_Pin);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}


void BSP_KEY::KEY_Init()
{
	WK_UP_Init();
	KEY0_Init();
	KEY1_Init();
}

void BSP_KEY::WK_UP_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_WK_UP_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KW_UP_Pin;                        /* WKUP引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* 输入 */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                    /* 下拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(WK_UP_GPIO_PORT, &GPIO_InitStruct);                 /* WKUP引脚模式设置,下拉输入 */
}

void BSP_KEY::KEY0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_KEY0_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY0_Pin;                        /* KEY0引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* 输入 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                     /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);                 /* KEY0引脚模式设置,上拉输入 */
}

void BSP_KEY::KEY1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_KEY1_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY1_Pin;                        /* KEY1引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                  /* 输入 */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                     /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);                 /* KEY1引脚模式设置,上拉输入 */
}

void BSP_KEY::WK_UP_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_WK_UP_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KW_UP_Pin;                        /* WKUP引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* 双边沿检测 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* 既不上拉也不下拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(WK_UP_GPIO_PORT, &GPIO_InitStruct);                 /* WKUP引脚模式设置,双边沿检测 */
	
	HAL_NVIC_SetPriority(WK_UP_EXTI_IRQn,PreemptPriority,SubPriority);          /* 抢占优先级，子优先级 */
  HAL_NVIC_EnableIRQ(WK_UP_EXTI_IRQn);                       /* 使能中断线0 */
}

void BSP_KEY::KEY0_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_KEY0_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY0_Pin;                        /* KEY0引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* 双边沿检测 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* 既不上拉也不下拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);                 /* KEY0引脚模式设置,双边沿检测 */
	
	HAL_NVIC_SetPriority(KEY0_EXTI_IRQn,PreemptPriority,SubPriority);          /* 抢占优先级，子优先级 */
  HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);                       /* 使能中断线4 */
}

void BSP_KEY::KEY1_EXTI_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
	__HAL_RCC_KEY1_GPIO_PORT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = KEY1_Pin;                        /* KEY1引脚 */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;      /* 双边沿检测 */
  GPIO_InitStruct.Pull = GPIO_NOPULL;                     /* 既不上拉也不下拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
  HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);                 /* KEY1引脚模式设置,双边沿检测 */
	
	HAL_NVIC_SetPriority(KEY0_EXTI_IRQn,PreemptPriority,SubPriority);          /* 抢占优先级，子优先级 */
  HAL_NVIC_EnableIRQ(KEY0_EXTI_IRQn);                       /* 使能中断线3 */
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


