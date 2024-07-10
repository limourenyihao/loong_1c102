#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ls1c102.h"
#include "stdint.h"

#define pwm_gpio0 20
#define pwm_gpio1 14

void pwm_gpio_init(void);
void TIM_SetCompare(int gpio,int pwm_cmp);
void timer_irq();
void timer_interrupt(uint32_t compare,uint32_t step);

#ifdef __cplusplus
}
#endif

#endif // _TIMER_H

