/*
 * rtc_show.c
 *
 * created: 2024/5/10
 *  author: 
 */

#include "rtc_show.h"
#include "ls1c102.h"
#include <stdio.h>
#include <stdbool.h>
#include "bsp.h"
#include "console.h"
#include "ls1c102_irq.h"
#include "src/RTC/user_rtc.h"

void rtc_show(void)
{
    rtc_get_time();
    printk("ʱ�䣺");
    printk("%d/",rtc1.year+2000);
    printk("%d/",rtc1.month);
    printk("%d ",rtc1.day);
    printk("%d:",rtc0.hour);
    printk("%d:",rtc0.minute);
    printk("%d\r\n",rtc0.second);
    delay_ms(600);
}

