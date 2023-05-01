#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"

/* not used */
void key_init()
{
    GPIO_InitTypeDef gpio_init_struct;
    KEYUP_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    gpio_init_struct.Pin = KEYUP_GPIO_PIN;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(KEYUP_GPIO_PORT, &gpio_init_struct);
    
}