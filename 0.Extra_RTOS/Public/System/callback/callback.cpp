#include "./callback/callback.h"


#ifdef __cplusplus
extern "C"
{
#endif

/***********************普通回调函数开始************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}
	
	
	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}


/***********************普通回调函数结束************************/



/***********************MSP回调函数开始************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

}


/***********************MSP回调函数结束************************/


#ifdef __cplusplus
}
#endif
