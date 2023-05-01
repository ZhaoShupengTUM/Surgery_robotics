#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"

#define KEYUP_GPIO_PORT  GPIOA
#define KEYUP_GPIO_PIN   GPIO_PIN_0
#define KEYUP_GPIO_CLK_ENABLE() \
    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  
    
#define KEYUP  HAL_GPIO_ReadPin(KEYUP_GPIO_PORT, \
    KEYUP_GPIO_PIN)
    
void key_init(void);

#endif
