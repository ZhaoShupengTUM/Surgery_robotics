#ifndef __TOUCH_H
#define __TOUCH_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* pin defination */
#define RIGHT_TOUCH_PORT  GPIOE
#define RIGHT_TOUCH_GPIO_PIN   GPIO_PIN_2
#define WRONG_TOUCH_PORT  GPIOE
#define WRONG_TOUCH_GPIO_PIN   GPIO_PIN_4

/*enable clk */
#define RIGHT_TOUCH_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOE_CLK_ENABLE();} while(0)
#define WRONG_TOUCH_GPIO_CLK_ENABLE() do{__HAL_RCC_GPIOE_CLK_ENABLE();} while(0)

/* operation function */
#define  RIGHT_TOUCH_CHECK  HAL_GPIO_ReadPin(RIGHT_TOUCH_PORT, RIGHT_TOUCH_GPIO_PIN)
#define  WRONG_TOUCH_CHECK  HAL_GPIO_ReadPin(WRONG_TOUCH_PORT, WRONG_TOUCH_GPIO_PIN)

/* state defination */
#define  RIGHT_TOUCH  1
#define  WRONG_TOUCH  2

/* init function */
void touch_init(void);
uint8_t touch_scan(uint8_t mode);

#endif

