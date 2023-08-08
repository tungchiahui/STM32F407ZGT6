#ifndef __INCLUDE_H_
#define __INCLUDE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ABS(x)	( (x>0) ? (x) : (-x) )
	
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "main.h"
#include "./data_structure/struct_typedef.h"
#include "./bit_band/bit_band.h"




#ifdef __cplusplus
}
#endif
	
#endif
