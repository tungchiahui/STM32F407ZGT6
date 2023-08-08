#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"


namespace TIMER
{
  void TIM_Init(uint16_t psc,uint16_t arr);
	void HAL_TIM_PeriodElapsedCallback_USER(TIM_HandleTypeDef *htim);
  void TIM_UP_IT_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
  extern TIM_HandleTypeDef TIM_Handle;
}



#ifdef __cplusplus
}
#endif

#endif
