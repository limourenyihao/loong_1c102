/*
 * button.c
 *
 * created: 2024/5/9
 *  author: 
 */

#include "button.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

/*
    button按键初始化
    gpio:编号
*/
void button_init(int gpio)
{
    gpio_init(gpio,0);
}

/*
    button按键消抖
    gpio:编号
    voltage:设定检测高/低电压
*/
void button_get(int gpio,int voltage)
{
    if(gpio_read(gpio)==voltage)
    {
        delay_ms(50);
        if(gpio_read(gpio)==voltage)
        {
            button_work();
        }
    }
}

/*
    检测执行命令
*/
void button_work(void)
{
    printk("hello world\r\n");
}

