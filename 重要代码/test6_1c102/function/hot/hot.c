/*
 * hot.c
 *
 * created: 2024/7/3
 *  author: 
 */

#include "hot.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void hot_init(void)
{
    gpio_init(39,1);
    gpio_write(39,0);
    gpio_init(38,1);
    gpio_write(38,0);
    gpio_init(37,1);
    gpio_write(37,0);
}

void hot_going(int tem)
{
    if(tem > 80)
    {
        gpio_write(39,0);
        gpio_write(38,0);
        gpio_write(37,0);
    }
    else if(tem >= 60 && tem <= 80)
    {
        gpio_write(39,1);
        gpio_write(38,1);
        gpio_write(37,0);
    }
    else if(tem < 60)
    {
        gpio_write(39,1);
        gpio_write(38,1);
        gpio_write(37,1);
    }
}

