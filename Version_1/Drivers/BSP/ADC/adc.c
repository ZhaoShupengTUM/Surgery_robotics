#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"

void power_psensor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    V33_GPIO_CLK_ENABLE();
    GND_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pin = GPIO_PIN_5;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(V33_GPIO_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = GPIO_PIN_1;
    
    HAL_GPIO_Init(GND_GPIO_PORT, &gpio_init_struct);
    
    V33_ENABLE();
    GND_ENABLE();
    
}

ADC_HandleTypeDef g_adc_handle;

void adc_init(void)
{
    g_adc_handle.Instance = ADC_ADCX;
    
    g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;
    g_adc_handle.Init.ContinuousConvMode = DISABLE;
    g_adc_handle.Init.NbrOfConversion = 1;
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;
    g_adc_handle.Init.NbrOfDiscConversion = 0;
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    
    HAL_ADC_Init(&g_adc_handle);
    HAL_ADCEx_Calibration_Start(&g_adc_handle);
    
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance == ADC_ADCX)
    {
        GPIO_InitTypeDef gpio_init_struct;
        RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
        
        ADC_ADCX_CHY_CLK_ENABLE();
        ADC_ADCX_CHY_GPIO_CLK_ENABLE();
        
        adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);
        
        gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    }
}

/* rank is only used in multi channel captuer */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, \
    uint32_t rank, uint32_t stime)
{
    ADC_ChannelConfTypeDef adc_ch_conf;
    adc_ch_conf.Channel = ch;
    adc_ch_conf.Rank = rank;
    adc_ch_conf.SamplingTime = stime;
    HAL_ADC_ConfigChannel(adc_handle, &adc_ch_conf);
}

/* T_convert = T_sample + 12.5*ADC_CLK */
uint32_t adc_get_result(uint32_t ch)
{
    adc_channel_set(&g_adc_handle, ch, ADC_REGULAR_RANK_1, \
    ADC_SAMPLETIME_239CYCLES_5);
    /* ADC_SAMPLETIME_239CYCLES_5 -> 239.5 ADC_CLK sample periods */
    
    HAL_ADC_Start(&g_adc_handle);
    HAL_ADC_PollForConversion(&g_adc_handle, 10);
    /* HAL_ADC_PollForConversion() is used to avoid the reading before the conversion is done */
    
    return (uint16_t)HAL_ADC_GetValue(&g_adc_handle);
}

uint32_t adc_get_result_average(uint32_t ch, uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;
    
    for (t=0; t<times; t++)
    {
        temp_val += adc_get_result(ch);
        delay_ms(5); //
    }
    
    return temp_val / times;
}
        
    


    
    
    
    
    
        
        
