#include "./BSP/TIMER/btim.h"
#include "./SYSTEM/usart/usart.h"

TIM_HandleTypeDef g_timx_handle;

/* initialize TIMX 8*/
void btim_timx_init(uint16_t arr, uint16_t psc)
{
    g_timx_handle.Instance = BTIM_TIMX;
    g_timx_handle.Init.Prescaler = psc;
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_handle.Init.Period = arr;
    
    HAL_TIM_Base_Init(&g_timx_handle);
    HAL_TIM_Base_Start_IT(&g_timx_handle);
}
    

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == BTIM_TIMX)
    {
        BTIM_TIMX_CLK_ENABLE();
        HAL_NVIC_SetPriority(BTIM_TIMX_IRQn, 1, 3);
        HAL_NVIC_EnableIRQ(BTIM_TIMX_IRQn);
    }
}


/* Interrupt process public functions */
void BTIM_TIMX_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);
}

/* Interrupt callback function */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX)
    {
        g_count++;
        g_time_s = (double)g_count/10;
        //printf("%d\n\r", g_count);
        //printf("%lf\n\r", g_time_s);
    }
}
    
