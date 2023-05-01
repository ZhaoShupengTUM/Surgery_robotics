#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

#include "./BSP/EXTI/exti.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/TOUCH/touch.h"
#include "./BSP/KEY/key.h"

#include "./SYSTEM/usart/usart.h"

/* external interrupt functions */
void RIGHT_TOUCH_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(RIGHT_TOUCH_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(RIGHT_TOUCH_GPIO_PIN);
}

void  WRONG_TOUCH_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(WRONG_TOUCH_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(WRONG_TOUCH_GPIO_PIN);
}

void  KEYUP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEYUP_GPIO_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(KEYUP_GPIO_PIN);
}


/* interrupt callback functions */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);
    switch(GPIO_Pin)
    {
        case RIGHT_TOUCH_GPIO_PIN:
            if ( RIGHT_TOUCH_CHECK == 1 )
            {
                LED1(0);
                touch_time = g_time_s;
                printf("right:%lf!\r\n", touch_time);
                touch_time = 0;
                delay_ms(100);
            }
            break;
        case WRONG_TOUCH_GPIO_PIN:
            if ( WRONG_TOUCH_CHECK == 1 )
            {
                LED0(0);
                touch_time = g_time_s;
                printf("wrong:%lf!\r\n", touch_time);
                touch_time = 0;
                BEEP(1);
                delay_ms(100);
                BEEP(0);
            }
            break;
        case KEYUP_GPIO_PIN:
            if ( KEYUP == 1 )
            {
                printf("start the test! Time Reset\r\n");
                LED1(1);
                LED0(1);
                touch_time = 0;
                g_count = 0;
            }
            break;
    }
}
              
                
/* external interrupt initialisation function */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    RIGHT_TOUCH_GPIO_CLK_ENABLE();
    WRONG_TOUCH_GPIO_CLK_ENABLE();
    KEYUP_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = RIGHT_TOUCH_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    
    HAL_GPIO_Init(RIGHT_TOUCH_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = WRONG_TOUCH_GPIO_PIN;
    HAL_GPIO_Init(WRONG_TOUCH_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = KEYUP_GPIO_PIN;
    HAL_GPIO_Init(KEYUP_GPIO_PORT, &gpio_init_struct);
    
    HAL_NVIC_SetPriority(RIGHT_TOUCH_INT_IRQn, 0, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(RIGHT_TOUCH_INT_IRQn); 
    
    HAL_NVIC_SetPriority(WRONG_TOUCH_INT_IRQn, 0, 1);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(WRONG_TOUCH_INT_IRQn); 
    
    HAL_NVIC_SetPriority(KEYUP_INT_IRQn, 1, 1);               /* 抢占1，子优先级2 */
    HAL_NVIC_EnableIRQ(KEYUP_INT_IRQn); 
    
}
    
    


