#ifndef __BTIM_H
#define __BTIM_H

#include "./SYSTEM/sys/sys.h"

#define BTIM_TIMX   TIM6
#define BTIM_TIMX_IRQn   TIM6_DAC_IRQn
#define BTIM_TIMX_IRQHandler   TIM6_DAC_IRQHandler
#define BTIM_TIMX_CLK_ENABLE() \
    do{ __HAL_RCC_TIM6_CLK_ENABLE(); } while(0)
    
void btim_timx_init(uint16_t arr, uint16_t psc);
    
extern uint32_t g_count;
extern double g_time_s;

#endif

    