#ifndef __BSP_CAN_H_
#define __BSP_CAN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"
#include "./CAN/can_receive.h"

#define CAN1_TX_GPIO_PORT GPIOB
#define CAN1_TX_Pin GPIO_PIN_9
#define CAN1_TX_GPIO_AF GPIO_AF9_CAN1
#define __HAL_RCC_CAN1_TX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */

#define CAN1_RX_GPIO_PORT GPIOB
#define CAN1_RX_Pin GPIO_PIN_8
#define CAN1_RX_GPIO_AF GPIO_AF9_CAN1
#define __HAL_RCC_CAN1_RX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)/* PB口时钟使能 */
	

#define CAN2_TX_GPIO_PORT GPIOB
#define CAN2_TX_Pin GPIO_PIN_6
#define CAN2_TX_GPIO_AF GPIO_AF9_CAN2
#define __HAL_RCC_CAN2_TX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */
	
#define CAN2_RX_GPIO_PORT GPIOB
#define CAN2_RX_Pin GPIO_PIN_5
#define CAN2_RX_GPIO_AF GPIO_AF9_CAN2
#define __HAL_RCC_CAN2_RX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)/* PB口时钟使能 */
	
class DJI_RM_MOTOR;


namespace CAN_BUS
{
	namespace BSP_CAN
	{
		void CAN1_Init(uint16_t brp = 3,uint32_t tbs1 = CAN_BS1_7TQ,uint32_t tbs2 = CAN_BS2_6TQ,uint32_t tsjw = CAN_SJW_1TQ);
		void CAN2_Init(uint16_t brp = 3,uint32_t tbs1 = CAN_BS1_10TQ,uint32_t tbs2 = CAN_BS2_3TQ,uint32_t tsjw = CAN_SJW_1TQ);
		void HAL_CAN_MspInit_USER(CAN_HandleTypeDef* canHandle);
		void CAN1_RX0_IT_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void CAN2_RX0_IT_ENABLE(uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void CAN1_Filter_Init(void);
		void CAN2_Filter_Init(void);
		void CAN1_Start(void);
		void CAN2_Start(void);
		void CAN_BUS_Start_IT(CAN_HandleTypeDef *hcan,uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void HAL_CAN_RxFifo0MsgPendingCallback_USER(CAN_HandleTypeDef *hcan);
	
		extern CAN_HandleTypeDef CAN1_Handle;
		extern CAN_HandleTypeDef CAN2_Handle;
	}
	
	extern DJI_RM_MOTOR DJI_RM_Motor;
}
	

#ifdef __cplusplus
}
#endif

#endif


