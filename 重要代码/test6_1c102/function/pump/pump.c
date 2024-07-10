/*
 * pump.c
 *
 * created: 2024/7/7
 *  author: 
 */

#include "pump.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void pump_init(void)
{
    gpio_init(22,1);
    gpio_write(22,0);
}

void pump_run(void)
{
    int cmp = 0;
    cmp = level_sensor();
    if(cmp < 100)
    {
        gpio_write(22,1);
    }
    if(cmp > 250)
    {
        gpio_write(22,0);
    }
}

