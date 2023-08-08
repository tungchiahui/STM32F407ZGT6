#ifndef __CAN_RECEIVE_H_
#define __CAN_RECEIVE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "./startup/include.h"
#include "./BSP_CAN/bsp_can.h"

/* CAN send and receive ID */
typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,
    CAN_3508_M5_ID = 0x205,
    CAN_3508_M6_ID = 0x206,
    CAN_3508_M7_ID = 0x207,
    CAN_3508_ALL_ID = 0x1FF,
} can_msg_id_e;

typedef struct
{
	uint16_t angle;
	int16_t speed_rpm;
	int16_t given_current;
	uint8_t temperate;
	int16_t last_angle;
	int32_t total_angle;
	int32_t	round_cnt;
	uint16_t offset_angle;
	uint32_t msg_cnt;
}motor_measure_t;


class DJI_RM_MOTOR
{
	public:
		class DATA_PROCESS   //数据处理
		{
			public:
				motor_measure_t can1_motor_info[8];
				motor_measure_t can2_motor_info[8];
				void CAN_GetProcessRxMessage(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef *pHeader, uint8_t aData[]);
			
			private:
				void get_motor_measure(motor_measure_t *ptr,uint8_t data[]);
				void get_moto_offset(motor_measure_t *ptr, uint8_t data[]);
				void get_total_angle(motor_measure_t *ptr);
		}Data_Process;

		class CMD
		{
			public:
				class CAN_1
				{
					public:
						void Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
						void Back(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8);
				}Can_1;
				
				class CAN_2
				{
					public:
						void Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
						void Back(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8);
				}Can_2;
		}Cmd;
};




#ifdef __cplusplus
}
#endif

#endif
