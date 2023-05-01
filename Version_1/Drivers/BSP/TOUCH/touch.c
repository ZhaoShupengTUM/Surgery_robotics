#include "./BSP/TOUCH/touch.h"

/* not used */
void touch_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    RIGHT_TOUCH_GPIO_CLK_ENABLE();
    WRONG_TOUCH_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = RIGHT_TOUCH_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(RIGHT_TOUCH_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = WRONG_TOUCH_GPIO_PIN;
    
    HAL_GPIO_Init(WRONG_TOUCH_PORT, &gpio_init_struct);
}

/* not used */
uint8_t touch_scan(uint8_t mode)
{
    static uint8_t key_up = 1; /* button releases sign */
    uint8_t keyval = 0;
    
    if (mode) key_up = 1;
    
    if(key_up && (RIGHT_TOUCH_CHECK == 1 || WRONG_TOUCH_CHECK == 1) )
    {
        delay_ms(10);
        key_up = 0;
        if(RIGHT_TOUCH_CHECK == 1)  keyval = RIGHT_TOUCH;
        if(WRONG_TOUCH_CHECK == 1)  keyval = WRONG_TOUCH;
    }
    else if(RIGHT_TOUCH_CHECK == 0 && WRONG_TOUCH_CHECK == 0)
    {
        key_up = 1;
    }
    
    
    return keyval;
}





