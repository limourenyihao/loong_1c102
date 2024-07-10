/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd. All Rights Reserved.
 *
 */

/*
 * Loongson 1c102 Bare Program, Sample main file
 */

#include <stdio.h>
#include <stdbool.h>

#include "bsp.h"
#include "console.h"
#include "ls1c102.h"

#include "src/GPIO/user_gpio.h"
#include "src/RTC/user_rtc.h"
#include "src/WDG/ls1x_wdg.h"
#include "src/user_adc/user_adc.h"
#include "src/TIMER/timer.h"
#include "function/breathing_led/breathing_led.h"

extern HW_PMU_t *g_pmu;
extern int printk(const char* format,...);
extern int usart0_print(const char* format,...);

int main(void)
{
    WdgInit();
    rtc_init(2048);
    gpio_init(20,1);
    gpio_write(20,1);
    adc_init();
    hot_init();
    valve_init();
    pump_init();
    
    char string0[100] = "A";
    char *string1 = "abc";
    
    for (;;)
    {
        pump_run();
        hot_going(tem_sensor());
        printk("饮水机运行状态：");
        printk("WORKING");
        printk("\r\n");
        printk("PH：");
        printk("%d\r\n",PH_sensor());
        printk("水位：");
        printk("%d\r\n",level_sensor());
        printk("水温：");
        printk("%d\r\n",tem_sensor());
        valve_run();
        printk("\r\n");

        delay_ms(1000);
    }

    /*
     * Never goto here!
     */
    return 0;
}

/*
 * @@ End
 */
