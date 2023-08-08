#ifndef __UDB_H_
#define __UDB_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"

/*******************************************************************************************************/
/* ���� �� ���� ���� 
 * Ĭ�������USART1��.
 * ע��: ͨ���޸���12���궨��,����֧��USART1~UART7����һ������.
 */
	
#define UDB_TX_GPIO_PORT GPIOA
#define UDB_TX_Pin GPIO_PIN_9
#define UDB_TX_GPIO_AF GPIO_AF7_USART1
#define __HAL_RCC_UDB_TX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PF��ʱ��ʹ�� */
	
	
#define UDB_RX_GPIO_PORT GPIOA
#define UDB_RX_Pin GPIO_PIN_10
#define UDB_RX_GPIO_AF GPIO_AF7_USART1
#define __HAL_RCC_UDB_RX_GPIO_PORT_CLK_ENABLE()         do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)/* PF��ʱ��ʹ�� */


#define UDB_UART          			 USART1
#define UDB_UART_IRQn            USART1_IRQn
#define UDB_UART_IRQHandler      USART1_IRQHandler
#define __HAL_RCC_UDB_UART_CLK_ENABLE()      do{ __HAL_RCC_USART1_CLK_ENABLE(); }while(0)             /* USART1 ʱ��ʹ�� */

/*******************************************************************************************************/

namespace UDB
{
		void UART_Init(uint32_t baudrate = 115200);
		void HAL_UART_MspInit_USER(UART_HandleTypeDef *huart);
		void UART_TX_IT_ENABLE(uint8_t * pData ,uint16_t Size ,uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void UART_RX_IT_ENABLE(uint8_t * pData ,uint16_t Size ,uint32_t PreemptPriority = 5, uint32_t SubPriority = 0);
		void HAL_UART_RxCpltCallback_USER(UART_HandleTypeDef *huart);
		void UART_Transmit(const uint8_t *pData, uint16_t Size = sizeof(pData), uint32_t Timeout = HAL_MAX_DELAY);
		void UART_Receive(uint8_t *pData, uint16_t Size = sizeof(pData), uint32_t Timeout = HAL_MAX_DELAY);
	
		extern UART_HandleTypeDef UART_Handle;    /* UART��� */
		extern uint8_t tx_buffer[1];
		extern uint8_t rx_buffer[1];
}
	

#ifdef __cplusplus
}
#endif

#endif
