#include "pid_user.h"
#include "./CAN/can_receive.h"

pid_type_def pid_v_1[8],pid_pos_1[8];
pid_type_def pid_v_2[8],pid_pos_2[8];

fp32 motor_speed_3508_pid[3] = {15, 0, 0};//3508参数
fp32 motor_position_3508_pid[3] = {0.2, 0, 1};
fp32 motor_speed_2006_pid[3] = {9, 0.1, 0};//2006参数
fp32 motor_position_2006_pid[3] = {0.2, 0, 0};


#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }


//底盘电机PID初始化
void PID_devices_Init(void)
{
	for(int i=0;i<4;i++)
	{
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 400, 300);
	}
	
	for(int i=4;i<8;i++)
	{		
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 400, 300);
	}
}



fp32 PID_velocity_realize_1(fp32 set_speed,int i)
{
	PID_calc(&pid_v_1[i-1],CAN_BUS::DJI_RM_Motor.Data_Process.can1_motor_info[i-1].speed_rpm , set_speed);
		return pid_v_1[i-1].out;
}

fp32 PID_position_realize_1(fp32 set_pos,int i)
{

		PID_calc(&pid_pos_1[i-1],CAN_BUS::DJI_RM_Motor.Data_Process.can1_motor_info[i-1].total_angle , set_pos);
		return pid_pos_1[i-1].out;

}

fp32 PID_call_1(fp32 position,int i)
{
		return PID_velocity_realize_1(PID_position_realize_1(position,i),i);
}






fp32 PID_velocity_realize_2(fp32 set_speed,int i)
{
		PID_calc(&pid_v_2[i-1],CAN_BUS::DJI_RM_Motor.Data_Process.can2_motor_info[i-1].speed_rpm , set_speed);
		return pid_v_2[i-1].out;
}

fp32 PID_position_realize_2(fp32 set_pos,int i)
{

		PID_calc(&pid_pos_2[i-1],CAN_BUS::DJI_RM_Motor.Data_Process.can2_motor_info[i-1].total_angle , set_pos);
		return pid_pos_2[i-1].out;

}

fp32 PID_call_2(fp32 position,int i)
{
		return PID_velocity_realize_2(PID_position_realize_2(position,i),i);
}
