/*
 * valve.c
 *
 * created: 2024/5/26
 *  author: 
 */

#include "valve.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void valve_init(void)
{
    gpio_init(36,1);
    gpio_init(35,1);
    gpio_write(36,0);
    gpio_write(35,0);

    gpio_init(32,0);
    gpio_init(33,0);
}

void valve_run(void)
{
    if(gpio_read(33) == 0)
    {
        gpio_write(36,1);
        //printk("冷水：");
        printk("ON\r\n");
    }
    if(gpio_read(33) == 1)
    {
        gpio_write(36,0);
       // printk("冷水：");
        printk("OFF\r\n");
    }
    if(gpio_read(32) == 0)
    {
        gpio_write(35,1);
      //  printk("热水：");
        printk("ON\r\n");
    }
    if(gpio_read(32) == 1)
    {
        gpio_write(35,0);
      //  printk("热水：");
        printk("OFF\r\n");
    }
}


