#include "./callback/callback.h"
#include "./BSP_UDB/udb.h"
#include "./BSP_TIMER/timer.h"
#include "./BSP_KEY/key.h"
#include "./BSP_CAN/bsp_can.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***********************普通回调函数开始************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BSP_KEY::HAL_GPIO_EXTI_Callback_USER(GPIO_Pin);
}
	
	
	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	if(huart->Instance == UDB_UART)
//	{
		UDB::HAL_UART_RxCpltCallback_USER(huart);
//	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_BUS::BSP_CAN::HAL_CAN_RxFifo0MsgPendingCallback_USER(hcan);
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	if(htim->Instance == TIM1)
//	{
		TIMER::HAL_TIM_PeriodElapsedCallback_USER(htim);
//	}
}


/***********************普通回调函数结束************************/



/***********************MSP回调函数开始************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
//	if(huart->Instance == UDB_UART)
//	{
		UDB::HAL_UART_MspInit_USER(huart);
//	}
}


/***********************MSP回调函数结束************************/


#ifdef __cplusplus
}
#endif
