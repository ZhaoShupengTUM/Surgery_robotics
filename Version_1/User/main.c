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
/* time recording */
uint32_t g_count = 0;  /* unit:0.1s */
double g_time_s = 0.0;
double touch_time = 0.0;

/* pressure sensor params */
/* before the measure should calibration */
#define MAX_FORCE 400
#define MIN_FORCE 20
#define MAX_ADC_OUT 4050
#define MIN_ADC_OUT 3650
float pressure;
float get_pressure_value(uint16_t adcx, uint16_t max_p, \
    uint16_t min_p, uint16_t max_adc, uint16_t min_adc);

//during continue touch get the max force
uint8_t touch_flag = 0;
uint8_t touch_flag_pre = 0;
float pressure_max = 0;
void capture_max_pressure(float pressure, float * pressure_max, \
    uint8_t * touch_flag, uint8_t * touch_flag_pre);
 

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
        //printf("%d\r\n", adcx);
        
        pressure = \
        get_pressure_value(adcx, MAX_FORCE, MIN_FORCE, MAX_ADC_OUT, MIN_ADC_OUT);
        //printf("%f\r\n", pressure);
        
        capture_max_pressure(pressure, &pressure_max, &touch_flag, \
        &touch_flag_pre);
        
        delay_ms(100);
    }
    
}

float get_pressure_value(uint16_t adcx, uint16_t max_p, \
    uint16_t min_p, uint16_t max_adc, uint16_t min_adc)
{
    float pressure;
    if(adcx >= max_adc) pressure = 0;
    else if(adcx <= min_adc) pressure = 400;
    else
    {
        pressure = (float) (max_adc-adcx)/(max_adc-min_adc) * (max_p-min_p) \
        + min_p;
    }
    return pressure;
}
        
void capture_max_pressure(float pressure, float * pressure_max, \
    uint8_t * touch_flag, uint8_t * touch_flag_pre)
{
    /* touch_flag==1 -> start the comparision
    touch_flag==0 -> end the comparision and return the value */
    
    if(pressure>0)  *touch_flag = 1;
    else  *touch_flag = 0;
    //printf("touch flag:%d touch flag pre:%d \n", *touch_flag, *touch_flag_pre); 
    
    if(*touch_flag == 0 && *touch_flag_pre == 0)
    { 
        *pressure_max = 0;
    }
    else if(*touch_flag == 1 && *pressure_max < pressure) //compare model
    {
        *pressure_max = pressure;
    }    
    else if(*touch_flag == 0 && *touch_flag_pre == 1)
    {
        printf("max pressure value:%f\n", *pressure_max);
        *pressure_max = 0;
    }
    
    *touch_flag_pre = *touch_flag;
}




