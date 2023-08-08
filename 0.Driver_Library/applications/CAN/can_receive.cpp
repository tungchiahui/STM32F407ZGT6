#include "./CAN/can_receive.h"

class DJI_RM_MOTOR CAN_BUS::DJI_RM_Motor;

void DJI_RM_MOTOR::DATA_PROCESS::CAN_GetProcessRxMessage(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef *pHeader, uint8_t aData[])
{
	if(hcan->Instance==CAN1)
	{
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, pHeader, aData);

		switch (pHeader->StdId)
		{
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
			case CAN_3508_M5_ID:
			case CAN_3508_M6_ID:
			case CAN_3508_M7_ID:
//			case CAN_3508_ALL_ID:
			{
				static uint8_t i = 0;
				//get motor id
				i = pHeader->StdId - CAN_3508_M1_ID;
				can1_motor_info[i].msg_cnt++ <= 50	?	get_moto_offset(&can1_motor_info[i], aData) : get_motor_measure(&can1_motor_info[i], aData);
				get_motor_measure(&can1_motor_info[i], aData);
				break;
			}
			default:
			{
			break;
			}	
		}
	}
	else if(hcan->Instance==CAN2)
	{
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, pHeader, aData);

		switch (pHeader->StdId)
		{
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
			case CAN_3508_M5_ID:
			case CAN_3508_M6_ID:
			case CAN_3508_M7_ID:
//			case CAN_3508_ALL_ID:
			{
				static uint8_t i = 0;
				//get motor id
				i = pHeader->StdId - CAN_3508_M1_ID;
				can2_motor_info[i].msg_cnt++ <= 50	?	get_moto_offset(&can2_motor_info[i], aData) : get_motor_measure(&can2_motor_info[i], aData);
				get_motor_measure(&can2_motor_info[i], aData);
				break;
			}
			default:
			{
			break;
			}	
		}
	}
}

void DJI_RM_MOTOR::DATA_PROCESS::get_motor_measure(motor_measure_t *ptr,uint8_t data[])
{
	        (ptr)->last_angle = (ptr)->angle;                                                          
        (ptr)->angle = data[0] << 8 | data[1];           
        (ptr)->speed_rpm = data[2] << 8 | data[3];     
        (ptr)->given_current = data[4] << 8 | data[5]; 
        (ptr)->temperate = data[6];                                              
//				((ptr)->angle) = (int32_t)(((ptr)->ecd) - ((ptr)->last_ecd));

					if(ptr->angle - ptr->last_angle > 4096)
						ptr->round_cnt --;
					else if (ptr->angle - ptr->last_angle < -4096)
						ptr->round_cnt ++;
					ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

void DJI_RM_MOTOR::DATA_PROCESS::get_moto_offset(motor_measure_t *ptr, uint8_t data[])
{
	ptr->angle = data[0]<<8 |data[1] ;
	ptr->offset_angle = ptr->angle;
}

void DJI_RM_MOTOR::DATA_PROCESS::get_total_angle(motor_measure_t *p)
{
	int res1, res2, delta;
	if(p->angle < p->last_angle){			//可能的情况
		res1 = p->angle + 8192 - p->last_angle;	//正转，delta=+
		res2 = p->angle - p->last_angle;				//反转	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
		res2 = p->angle - p->last_angle;				//正转	delta +
	}
	//不管正反转，肯定是转的角度小的那个是真的
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}


void DJI_RM_MOTOR::CMD::CAN_1::Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
	CAN_TxHeaderTypeDef can_tx_message = {0};
	uint8_t	can_send_data[8] = {0};
	uint32_t send_mail_box = 0;
	
	can_tx_message.StdId = 0x200;
	can_tx_message.IDE = CAN_ID_STD;
	can_tx_message.RTR = CAN_RTR_DATA;
	can_tx_message.DLC = 0x08;
	can_send_data[0] = motor1 >> 8;
	can_send_data[1] = motor1;
	can_send_data[2] = motor2 >> 8;
	can_send_data[3] = motor2;
	can_send_data[4] = motor3 >> 8;
	can_send_data[5] = motor3;
	can_send_data[6] = motor4 >> 8;
	can_send_data[7] = motor4;
	HAL_CAN_AddTxMessage(&CAN_BUS::BSP_CAN::CAN1_Handle, &can_tx_message, can_send_data, &send_mail_box);
}

void DJI_RM_MOTOR::CMD::CAN_1::Back(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
	CAN_TxHeaderTypeDef can_tx_message = {0};
	uint8_t	can_send_data[8] = {0};
	uint32_t send_mail_box = 0;
	
  can_tx_message.StdId = 0x1FF;
  can_tx_message.IDE = CAN_ID_STD;
  can_tx_message.RTR = CAN_RTR_DATA;
  can_tx_message.DLC = 0x08;
  can_send_data[0] = motor5 >> 8;
  can_send_data[1] = motor5;
  can_send_data[2] = motor6 >> 8;
  can_send_data[3] = motor6;
  can_send_data[4] = motor7 >> 8;
  can_send_data[5] = motor7;
  can_send_data[6] = motor8 >> 8;
  can_send_data[7] = motor8;
  HAL_CAN_AddTxMessage(&CAN_BUS::BSP_CAN::CAN1_Handle, &can_tx_message, can_send_data, &send_mail_box);
}

void DJI_RM_MOTOR::CMD::CAN_2::Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
	CAN_TxHeaderTypeDef can_tx_message = {0};
	uint8_t	can_send_data[8] = {0};
	uint32_t send_mail_box = 0;
	
	can_tx_message.StdId = 0x200;
	can_tx_message.IDE = CAN_ID_STD;
	can_tx_message.RTR = CAN_RTR_DATA;
	can_tx_message.DLC = 0x08;
	can_send_data[0] = motor1 >> 8;
	can_send_data[1] = motor1;
	can_send_data[2] = motor2 >> 8;
	can_send_data[3] = motor2;
	can_send_data[4] = motor3 >> 8;
	can_send_data[5] = motor3;
	can_send_data[6] = motor4 >> 8;
	can_send_data[7] = motor4;
	HAL_CAN_AddTxMessage(&CAN_BUS::BSP_CAN::CAN2_Handle, &can_tx_message, can_send_data, &send_mail_box);
}

void DJI_RM_MOTOR::CMD::CAN_2::Back(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
	CAN_TxHeaderTypeDef can_tx_message = {0};
	uint8_t	can_send_data[8] = {0};
	uint32_t send_mail_box = 0;
	
  can_tx_message.StdId = 0x1FF;
  can_tx_message.IDE = CAN_ID_STD;
  can_tx_message.RTR = CAN_RTR_DATA;
  can_tx_message.DLC = 0x08;
  can_send_data[0] = motor5 >> 8;
  can_send_data[1] = motor5;
  can_send_data[2] = motor6 >> 8;
  can_send_data[3] = motor6;
  can_send_data[4] = motor7 >> 8;
  can_send_data[5] = motor7;
  can_send_data[6] = motor8 >> 8;
  can_send_data[7] = motor8;
  HAL_CAN_AddTxMessage(&CAN_BUS::BSP_CAN::CAN2_Handle, &can_tx_message, can_send_data, &send_mail_box);
}

