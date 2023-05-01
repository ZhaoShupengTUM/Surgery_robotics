#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

/***************** power supply part *****************/
/* define a gpio to provide the 3.3v output */
#define V33_GPIO_PORT GPIOA
#define V33_GPIO_PIN  GPIO_PIN_5
#define GND_GPIO_PORT GPIOA
#define GND_GPIO_PIN  GPIO_PIN_1

/* enable clk */
#define V33_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE(); } while(0);
#define GND_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOA_CLK_ENABLE(); } while(0);

/* operation functions */
#define V33_ENABLE() \
do {HAL_GPIO_WritePin(V33_GPIO_PORT, V33_GPIO_PIN, GPIO_PIN_SET); \
} while(0)

#define GND_ENABLE() \
do{HAL_GPIO_WritePin(GND_GPIO_PORT, GND_GPIO_PIN, GPIO_PIN_RESET); \
} while(0)

/* init function */
void power_psensor_init(void);

/***************************************************/

/***************** ADC part **********************************/

#define ADC_ADCX_CHY_GPIO_PORT GPIOC
#define ADC_ADCX_CHY_GPIO_PIN  GPIO_PIN_1
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE() \
    do{ __HAL_RCC_GPIOC_CLK_ENABLE(); } while(0)
    
#define ADC_ADCX    ADC1
#define ADC_ADCX_CHY    ADC_CHANNEL_11
#define ADC_ADCX_CHY_CLK_ENABLE() \
    do{ __HAL_RCC_ADC1_CLK_ENABLE(); } while(0)

void adc_init(void);
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, \
    uint32_t rank, uint32_t stime);
uint32_t adc_get_result(uint32_t ch);
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);
    
/***************************************************/


#endif
