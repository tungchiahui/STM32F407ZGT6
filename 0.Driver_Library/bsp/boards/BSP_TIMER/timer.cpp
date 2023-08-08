#include "./BSP_TIMER/timer.h"
#include "./BSP_LED/led.h"

TIM_HandleTypeDef TIMER::TIM_Handle = {0};

void TIMER::HAL_TIM_PeriodElapsedCallback_USER(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
      BSP_LED::LED1_Toggle();
    }
}

extern "C"
void TIM1_UP_TIM10_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIMER::TIM_Handle);
}


void TIMER::TIM_Init(uint16_t psc,uint16_t arr)
{
    __HAL_RCC_TIM1_CLK_ENABLE();

     TIMER::TIM_Handle.Instance = TIM1;                 /* 通用定时器x */
     TIMER::TIM_Handle.Init.Prescaler = psc;                     /* 预分频系数 */
     TIMER::TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;    /* 递增计数模式 */
     TIMER::TIM_Handle.Init.Period = arr;                        /* 自动装载值 */

    HAL_TIM_Base_Init(&TIM_Handle);
}

void TIMER::TIM_UP_IT_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, PreemptPriority, SubPriority);         /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);                 /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&TIM_Handle);                  /* 使能定时器x和定时器x更新中断 */
}
