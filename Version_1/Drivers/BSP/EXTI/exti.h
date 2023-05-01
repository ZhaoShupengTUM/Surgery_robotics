#ifndef __EXTI_H
#define __EXTI_H

#include "./SYSTEM/sys/sys.h"

/* pin definition */
/* clock enable */
/* Pin and clock are defined well in the touch.h */


/* interrupt number and interrupt function */

#define RIGHT_TOUCH_INT_IRQn                   EXTI2_IRQn
#define RIGHT_TOUCH_INT_IRQHandler             EXTI2_IRQHandler

#define WRONG_TOUCH_INT_IRQn                   EXTI4_IRQn
#define WRONG_TOUCH_INT_IRQHandler             EXTI4_IRQHandler

#define KEYUP_INT_IRQn                   EXTI0_IRQn
#define KEYUP_INT_IRQHandler             EXTI0_IRQHandler

void extix_init(void);

extern double g_time_s;
extern uint32_t g_count;
extern double touch_time;

#endif
