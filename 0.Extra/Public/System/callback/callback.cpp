#include "./callback/callback.h"


#ifdef __cplusplus
extern "C"
{
#endif

/***********************��ͨ�ص�������ʼ************************/

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


/***********************��ͨ�ص���������************************/



/***********************MSP�ص�������ʼ************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

}


/***********************MSP�ص���������************************/


#ifdef __cplusplus
}
#endif
