#include "./BSP_UDB/udb.h"

UART_HandleTypeDef UDB::UART_Handle = {0};    /* UART句柄 */
uint8_t UDB::tx_buffer[1];
uint8_t UDB::rx_buffer[1];



/**
 * @brief       Rx传输回调函数
 * @param       huart: UART句柄类型指针
 * @retval      无
 */ 
void UDB::HAL_UART_RxCpltCallback_USER(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UDB_UART)             /* 如果是串口1 */
    {
			
		}
}


extern "C"
void UDB_USART_IRQHandler(void)
{ 
  uint32_t timeout = 0;
  uint32_t maxDelay = 0x1FFFF;
	
	HAL_UART_IRQHandler(&UDB::UART_Handle);       /* 调用HAL库中断处理公用函数 */
	
//	UDB::HAL_UART_RxCpltCallback_USER(&UDB::UART_Handle);   //去中断回调函数里被调用
	
	timeout=0;
    /* 一次处理完成之后，重新开启中断并设置RxXferCount为1 */
   while (HAL_UART_Receive_IT(&UDB::UART_Handle,UDB::rx_buffer, sizeof(UDB::rx_buffer)) != HAL_OK)
   {
       timeout++;                              /* 超时处理 */
       if (timeout > maxDelay)
       {
            break;
       }
   }
}



void UDB::UART_Init(uint32_t baudrate)
{
	 UART_Handle.Instance = UDB_UART;                        /* USART1 */
   UART_Handle.Init.BaudRate = baudrate;                    /* 波特率 */
   UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
   UART_Handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
   UART_Handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
   UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
   UART_Handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
   HAL_UART_Init(&UART_Handle);                             /* HAL_UART_Init()会使能UART1 */
	
//	 HAL_UART_MspInit_USER(&UDB::UART_Handle);   //去回调函数里调用
}


/**
 * @brief       UART底层初始化回调函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置
 * @retval      无
 */
void UDB::HAL_UART_MspInit_USER(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};       /* GPIO配置参数存储变量 */
    if(huart->Instance == UDB_UART)                             /* 如果是串口1，进行串口1 MSP初始化 */
    {
        __HAL_RCC_UDB_UART_CLK_ENABLE();                                  /* USART1 时钟使能 */
        __HAL_RCC_UDB_TX_GPIO_PORT_CLK_ENABLE();                             /* 发送引脚时钟使能 */
        __HAL_RCC_UDB_RX_GPIO_PORT_CLK_ENABLE();                             /* 接收引脚时钟使能 */

        GPIO_InitStruct.Pin = UDB_TX_Pin;               /* TX引脚 */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;          /* 高速 */
        GPIO_InitStruct.Alternate = UDB_TX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(UDB_TX_GPIO_PORT, &GPIO_InitStruct);   /* 初始化发送引脚 */

        GPIO_InitStruct.Pin = UDB_RX_Pin;               			/* RX引脚 */
			  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;          /* 高速 */
        GPIO_InitStruct.Alternate = UDB_RX_GPIO_AF;          /* 复用为USART1 */
        HAL_GPIO_Init(UDB_RX_GPIO_PORT, &GPIO_InitStruct);   /* 初始化接收引脚 */
    }
}



void UDB::UART_TX_IT_ENABLE(uint8_t * pData ,uint16_t Size , uint32_t PreemptPriority, uint32_t SubPriority)
{
	HAL_NVIC_EnableIRQ(UDB_UART_IRQn);                      /* 使能USART1中断通道 */
  HAL_NVIC_SetPriority(UDB_UART_IRQn, PreemptPriority, SubPriority);              /* 抢占优先级，子优先级 */
	/* 该函数会开启发送中断 */
  HAL_UART_Transmit_IT(&UART_Handle,pData, Size);
}



void UDB::UART_RX_IT_ENABLE(uint8_t * pData ,uint16_t Size , uint32_t PreemptPriority, uint32_t SubPriority)
{
	HAL_NVIC_EnableIRQ(UDB_UART_IRQn);                      /* 使能USART1中断通道 */
  HAL_NVIC_SetPriority(UDB_UART_IRQn, PreemptPriority, SubPriority);              /* 抢占优先级，子优先级 */
	/* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
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



#ifndef __cplusplus   //如果在C++使用，则不启用
#include <stdio.h>
/******************************************************************************************/
/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");          /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((UDB_UART->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

    UDB_UART->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif
/***********************************************END*******************************************/
#endif
