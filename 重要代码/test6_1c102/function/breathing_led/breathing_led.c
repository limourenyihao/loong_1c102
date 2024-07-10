/*
 * breathing_led.c
 *
 * created: 2024/5/13
 *  author: 
 */

#include "breathing_led.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void breathing_init(int gpio)
{
    for(int x=0;x<20;x++)
        {
            gpio_write(gpio,1);
            delay_us(x);
            gpio_write(gpio,0);
            delay_us(20-x);
        }
        for(int y=20;y>0;y--)
        {
            gpio_write(gpio,1);
            delay_us(y);
            gpio_write(gpio,0);
            delay_us(20-y);
        }
}



