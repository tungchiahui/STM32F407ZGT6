#include "./BSP_CAN/bsp_can.h"

CAN_HandleTypeDef CAN_BUS::BSP_CAN::CAN1_Handle = {0};
CAN_HandleTypeDef CAN_BUS::BSP_CAN::CAN2_Handle = {0};


void CAN_BUS::BSP_CAN::HAL_CAN_RxFifo0MsgPendingCallback_USER(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rx_header = {0};
	uint8_t rx_data_1[8];
	uint8_t rx_data_2[8];
	
	if(hcan->Instance==CAN1)
	{
		DJI_RM_Motor.Data_Process.CAN_GetProcessRxMessage(hcan,&rx_header,rx_data_1);
	}
	else if(hcan->Instance==CAN2)
	{
		DJI_RM_Motor.Data_Process.CAN_GetProcessRxMessage(hcan,&rx_header,rx_data_2);
	}
}


void CAN_BUS::BSP_CAN::CAN1_Init(uint16_t brp,uint32_t tbs1,uint32_t tbs2,uint32_t tsjw)
{
		CAN1_Handle.Instance = CAN1;
    CAN1_Handle.Init.Prescaler = brp;                /* 分频系数(Fdiv)为brp+1 */
    CAN1_Handle.Init.Mode = CAN_MODE_NORMAL;         /* 模式设置 */
    CAN1_Handle.Init.SyncJumpWidth = tsjw;           /* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1TQ~CAN_SJW_4TQ */
    CAN1_Handle.Init.TimeSeg1 = tbs1;                /* tbs1范围CAN_BS1_1TQ~CAN_BS1_16TQ */
    CAN1_Handle.Init.TimeSeg2 = tbs2;                /* tbs2范围CAN_BS2_1TQ~CAN_BS2_8TQ */
    CAN1_Handle.Init.TimeTriggeredMode = DISABLE;    /* 非时间触发通信模式 */
    CAN1_Handle.Init.AutoBusOff = DISABLE;           /* 软件自动离线管理 */
    CAN1_Handle.Init.AutoWakeUp = DISABLE;           /* 睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位) */
    CAN1_Handle.Init.AutoRetransmission = DISABLE;   /* 不禁止报文自动传送 */
    CAN1_Handle.Init.ReceiveFifoLocked = DISABLE;    /* 报文不锁定,新的覆盖旧的 */
    CAN1_Handle.Init.TransmitFifoPriority = DISABLE; /* 优先级由报文标识符决定 */
    if (HAL_CAN_Init(&CAN1_Handle) != HAL_OK)
    {
        Error_Handler();
    }
}

void CAN_BUS::BSP_CAN::CAN2_Init(uint16_t brp,uint32_t tbs1,uint32_t tbs2,uint32_t tsjw)
{
		CAN2_Handle.Instance = CAN2;
    CAN2_Handle.Init.Prescaler = brp;                /* 分频系数(Fdiv)为brp+1 */
    CAN2_Handle.Init.Mode = CAN_MODE_NORMAL;         /* 模式设置 */
    CAN2_Handle.Init.SyncJumpWidth = tsjw;           /* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1TQ~CAN_SJW_4TQ */
    CAN2_Handle.Init.TimeSeg1 = tbs1;                /* tbs1范围CAN_BS1_1TQ~CAN_BS1_16TQ */
    CAN2_Handle.Init.TimeSeg2 = tbs2;                /* tbs2范围CAN_BS2_1TQ~CAN_BS2_8TQ */
    CAN2_Handle.Init.TimeTriggeredMode = DISABLE;    /* 非时间触发通信模式 */
    CAN2_Handle.Init.AutoBusOff = DISABLE;           /* 软件自动离线管理 */
    CAN2_Handle.Init.AutoWakeUp = DISABLE;           /* 睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位) */
    CAN2_Handle.Init.AutoRetransmission = DISABLE;   /* 不禁止报文自动传送 */
    CAN2_Handle.Init.ReceiveFifoLocked = DISABLE;    /* 报文不锁定,新的覆盖旧的 */
    CAN2_Handle.Init.TransmitFifoPriority = DISABLE; /* 优先级由报文标识符决定 */
    if (HAL_CAN_Init(&CAN2_Handle) != HAL_OK)
    {
        Error_Handler();
    }
}


static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;
/**
 * @brief       CAN底层驱动，引脚配置，时钟配置，中断配置
                此函数会被HAL_CAN_Init()调用
 * @param       hcan:CAN句柄
 * @retval      无
 */
void CAN_BUS::BSP_CAN::HAL_CAN_MspInit_USER(CAN_HandleTypeDef *canHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(canHandle->Instance == CAN1)
	{
		/*CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
		*/
		__HAL_RCC_CAN1_TX_GPIO_PORT_CLK_ENABLE();
		__HAL_RCC_CAN1_RX_GPIO_PORT_CLK_ENABLE();
		
		/* CAN1 clock enable */
		HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED == 1)
		{
      __HAL_RCC_CAN1_CLK_ENABLE();
		}
		
		GPIO_InitStruct.Pin = CAN1_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = CAN1_TX_GPIO_AF;
    HAL_GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = CAN1_RX_Pin;
		GPIO_InitStruct.Alternate = CAN1_RX_GPIO_AF;
		HAL_GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStruct);
	}
	
	else if(canHandle->Instance==CAN2)
  {
		/*CAN1 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
		*/
		__HAL_RCC_CAN2_TX_GPIO_PORT_CLK_ENABLE();
		__HAL_RCC_CAN2_RX_GPIO_PORT_CLK_ENABLE();
		
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1)
		{
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
		
		GPIO_InitStruct.Pin = CAN2_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = CAN2_TX_GPIO_AF;
    HAL_GPIO_Init(CAN2_TX_GPIO_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = CAN2_RX_Pin;
		GPIO_InitStruct.Alternate = CAN2_RX_GPIO_AF;
		HAL_GPIO_Init(CAN2_RX_GPIO_PORT, &GPIO_InitStruct);
	}
}

void CAN_BUS::BSP_CAN::CAN1_RX0_IT_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	/* CAN1 interrupt Init */
  HAL_NVIC_SetPriority(CAN1_RX0_IRQn, PreemptPriority, SubPriority);
  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
}

void CAN_BUS::BSP_CAN::CAN2_RX0_IT_ENABLE(uint32_t PreemptPriority, uint32_t SubPriority)
{
	/* CAN2 interrupt Init */
  HAL_NVIC_SetPriority(CAN2_RX0_IRQn, PreemptPriority, SubPriority);
  HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
}
void CAN_BUS::BSP_CAN::CAN1_Filter_Init()
{
	CAN_FilterTypeDef CAN_Filter_st;
  CAN_Filter_st.FilterActivation = ENABLE;
  CAN_Filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_Filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_Filter_st.FilterIdHigh = 0x0000;
  CAN_Filter_st.FilterIdLow = 0x0000;
  CAN_Filter_st.FilterMaskIdHigh = 0x0000;
  CAN_Filter_st.FilterMaskIdLow = 0x0000;
  CAN_Filter_st.FilterBank = 0;
  CAN_Filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	if(HAL_CAN_ConfigFilter(&CAN1_Handle, &CAN_Filter_st) != HAL_OK)		//滤波器初始化
	{
		Error_Handler();
	}
}

void CAN_BUS::BSP_CAN::CAN2_Filter_Init()
{
	CAN_FilterTypeDef CAN_Filter_st;
  CAN_Filter_st.FilterActivation = ENABLE;
  CAN_Filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_Filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_Filter_st.FilterIdHigh = 0x0000;
  CAN_Filter_st.FilterIdLow = 0x0000;
  CAN_Filter_st.FilterMaskIdHigh = 0x0000;
  CAN_Filter_st.FilterMaskIdLow = 0x0000;
  CAN_Filter_st.FilterBank = 14;
  CAN_Filter_st.SlaveStartFilterBank = 14;
  CAN_Filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	if(HAL_CAN_ConfigFilter(&CAN2_Handle, &CAN_Filter_st) != HAL_OK)        //滤波器初始化
	{
		Error_Handler();
	}
}

void CAN_BUS::BSP_CAN::CAN1_Start()
{
	HAL_CAN_Start(&CAN1_Handle);

	if (HAL_CAN_ActivateNotification(&CAN1_Handle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    Error_Handler();
	}
}

void CAN_BUS::BSP_CAN::CAN2_Start()
{
	HAL_CAN_Start(&CAN2_Handle);

	if (HAL_CAN_ActivateNotification(&CAN2_Handle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    Error_Handler();
	}
}

void CAN_BUS::BSP_CAN::CAN_BUS_Start_IT(CAN_HandleTypeDef *hcan , uint32_t PreemptPriority, uint32_t SubPriority)
{
	if(hcan->Instance == CAN1)
	{
		CAN1_RX0_IT_ENABLE(PreemptPriority,SubPriority);
		CAN1_Filter_Init();
		CAN1_Start();
	}
	else if(hcan->Instance == CAN1)
	{
		CAN2_RX0_IT_ENABLE(PreemptPriority,SubPriority);
		CAN2_Filter_Init();
		CAN2_Start();
	}
}
