#include "./BSP_UDB/udb.h"

UART_HandleTypeDef UDB::UART_Handle = {0};    /* UART��� */
uint8_t UDB::tx_buffer[1];
uint8_t UDB::rx_buffer[1];



/**
 * @brief       Rx����ص�����
 * @param       huart: UART�������ָ��
 * @retval      ��
 */ 
void UDB::HAL_UART_RxCpltCallback_USER(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UDB_UART)             /* ����Ǵ���1 */
    {
			
		}
}


extern "C"
void UDB_USART_IRQHandler(void)
{ 
  uint32_t timeout = 0;
  uint32_t maxDelay = 0x1FFFF;
	
	HAL_UART_IRQHandler(&UDB::UART_Handle);       /* ����HAL���жϴ����ú��� */
	
//	UDB::HAL_UART_RxCpltCallback_USER(&UDB::UART_Handle);   //ȥ�жϻص������ﱻ����
	
	timeout=0;
    /* һ�δ������֮�����¿����жϲ�����RxXferCountΪ1 */
   while (HAL_UART_Receive_IT(&UDB::UART_Handle,UDB::rx_buffer, sizeof(UDB::rx_buffer)) != HAL_OK)
   {
       timeout++;                              /* ��ʱ���� */
       if (timeout > maxDelay)
       {
            break;
       }
   }
}



void UDB::UART_Init(uint32_t baudrate)
{
	 UART_Handle.Instance = UDB_UART;                        /* USART1 */
   UART_Handle.Init.BaudRate = baudrate;                    /* ������ */
   UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
   UART_Handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
   UART_Handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
   UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
   UART_Handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
   HAL_UART_Init(&UART_Handle);                             /* HAL_UART_Init()��ʹ��UART1 */
	
//	 HAL_UART_MspInit_USER(&UDB::UART_Handle);   //ȥ�ص����������
}


/**
 * @brief       UART�ײ��ʼ���ص�����
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ���������
 * @retval      ��
 */
void UDB::HAL_UART_MspInit_USER(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO���ò����洢���� */
    if(huart->Instance == UDB_UART)                             /* ����Ǵ���1�����д���1 MSP��ʼ�� */
    {
        __HAL_RCC_UDB_UART_CLK_ENABLE();                                  /* USART1 ʱ��ʹ�� */
        __HAL_RCC_UDB_TX_GPIO_PORT_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */
        __HAL_RCC_UDB_RX_GPIO_PORT_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = UDB_TX_Pin;               /* TX���� */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;          /* ���� */
        GPIO_InitStruct.Alternate = UDB_TX_GPIO_AF;          /* ����ΪUSART1 */
        HAL_GPIO_Init(UDB_TX_GPIO_PORT, &GPIO_InitStruct);   /* ��ʼ���������� */

        GPIO_InitStruct.Pin = UDB_RX_Pin;               			/* RX���� */
			  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;          /* ���� */
        GPIO_InitStruct.Alternate = UDB_RX_GPIO_AF;          /* ����ΪUSART1 */
        HAL_GPIO_Init(UDB_RX_GPIO_PORT, &GPIO_InitStruct);   /* ��ʼ���������� */
    }
}



void UDB::UART_TX_IT_ENABLE(uint8_t * pData ,uint16_t Size , uint32_t PreemptPriority, uint32_t SubPriority)
{
	HAL_NVIC_EnableIRQ(UDB_UART_IRQn);                      /* ʹ��USART1�ж�ͨ�� */
  HAL_NVIC_SetPriority(UDB_UART_IRQn, PreemptPriority, SubPriority);              /* ��ռ���ȼ��������ȼ� */
	/* �ú����Ὺ�������ж� */
  HAL_UART_Transmit_IT(&UART_Handle,pData, Size);
}



void UDB::UART_RX_IT_ENABLE(uint8_t * pData ,uint16_t Size , uint32_t PreemptPriority, uint32_t SubPriority)
{
	HAL_NVIC_EnableIRQ(UDB_UART_IRQn);                      /* ʹ��USART1�ж�ͨ�� */
  HAL_NVIC_SetPriority(UDB_UART_IRQn, PreemptPriority, SubPriority);              /* ��ռ���ȼ��������ȼ� */
	/* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
  HAL_UART_Receive_IT(&UART_Handle,pData, Size);
}

void UDB::UART_Transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	HAL_UART_Transmit(&UART_Handle,pData,Size,Timeout);
}

void UDB::UART_Receive(uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	HAL_UART_Receive(&UART_Handle,pData,Size,Timeout);
}



#ifndef __cplusplus   //�����C++ʹ�ã�������
#include <stdio.h>
/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");          /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((UDB_UART->SR & 0X40) == 0);               /* �ȴ���һ���ַ�������� */

    UDB_UART->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/***********************************************END*******************************************/
#endif
