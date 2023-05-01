#include "./stm32f1xx_it.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

#include "./BSP/BEEP/beep.h"
#include "./BSP/LED/led.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/TIMER/btim.h"
#include "./BSP/ADC/adc.h"

//#include "stdio.h"
uint32_t g_count = 0;  /* unit:0.1s */
double g_time_s = 0.0;
double touch_time = 0.0;

int main(void)
{
    uint16_t adcx;
    
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    led_init();
    beep_init();
    extix_init();
    usart_init(115200);
    
    adc_init();
    power_psensor_init();
    
/* timeperiod 0.1ms -> 0.1ms=1/10000s=10kHz=72MHz/7200 -> PSC=7200 
   recording time interval(resolution) 0.1s -> 1000*0.1ms */
    btim_timx_init(1000-1, 7200-1);
    
    BEEP(0);
    LED0(1);
    LED1(1);
    
    while(1)
    {
        //printf("Hello World!\r\n");
        //delay_ms(1000);
        adcx = adc_get_result_average(ADC_ADCX_CHY, 10); 
        
        printf("%d\r\n", adcx);
        
        delay_ms(100);
    }
    
}

