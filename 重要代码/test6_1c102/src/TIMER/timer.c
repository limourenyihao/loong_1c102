#include "timer.h"
#include <stdio.h>
#include "ls1c102.h"
#include "ls1c102_irq.h"

#include "src/GPIO/user_gpio.h"

HW_TIMER_t *g_timer = (HW_TIMER_t *)LS1C102_TIMER_BASE;// 获取定时器寄存器
HW_INTC_t *intc = (HW_INTC_t *)LS1C102_INTC_BASE;      // 获取中断寄存器

int gpio_state0 = 0;
int gpio_state1 = 0;
int count_timer_irq = 0;
int pwm_max_count = 100;
int pwm_cmp0 = 10;
int pwm_cmp1 = 10;

void pwm_gpio_init(void)
{
    gpio_init(pwm_gpio0,1);
    gpio_init(pwm_gpio1,1);
}

void TIM_SetCompare(int gpio,int pwm_cmp)
{
    if(gpio == pwm_gpio0)
    {
        if(pwm_cmp > pwm_max_count)
            pwm_cmp0 = pwm_max_count;
        else if(pwm_cmp < 0)
            pwm_cmp0 = 0;
        else
            pwm_cmp0 = pwm_cmp;
    }
    if(gpio == pwm_gpio1)
    {
        if(pwm_cmp > pwm_max_count)
            pwm_cmp1 = pwm_max_count;
        else if(pwm_cmp < 0)
            pwm_cmp1 = 0;
        else
            pwm_cmp1 = pwm_cmp;
    }
}

void timer_irq(int vector, void *arg)
{
    if(count_timer_irq <= pwm_cmp0 && gpio_state0 == 0)
    {
        gpio_write(pwm_gpio0,1);
        gpio_state0 = 1;
    }
    else if(count_timer_irq > pwm_cmp0 && gpio_state0 == 1)
    {
        gpio_write(pwm_gpio0,0);
        gpio_state0 = 0;
    }
    
    if(count_timer_irq <= pwm_cmp1 && gpio_state1 == 0)
    {
        gpio_write(pwm_gpio1,1);
        gpio_state1 = 1;
    }
    else if(count_timer_irq >pwm_cmp1 && gpio_state1 == 1)
    {
        gpio_write(pwm_gpio1,0);
        gpio_state1 = 0;
    }
    
    count_timer_irq++;
    if(count_timer_irq > pwm_max_count)
    {
        count_timer_irq = 0;
    }

    g_timer->cfg = g_timer->cfg;// 执行后清除中断标志位
}

void timer_interrupt(uint32_t compare,uint32_t step)
{
    // 定时器配置、中断配置如下
    g_timer->cfg = 0;                    // 定时器配置复位
    g_timer->cnt = 0;                    // 定时器计数值清空

    g_timer->cmp = compare;             // 首次进入定时器中断的计数次数为16M，如果时钟为8M，那么大约是2s，时间没问题。
    //g_timer->step = 32000000;            // 定时器中断步进，计数32M触发一次中断，大约是4s，时间没问题。
    // 一般都是周期触发模式，所以第一次触发中断需要计数到 cmp ，之后每次计数 step 就会触发一次中断。
    g_timer->step = step;

    g_timer->cfg = 0x07;                 // 开启周期触发，中断使能，开始计数
    intc->en |= 0x01;                    // 开启定时器全局中断
    
    ls1c102_install_isr(LS1C102_IRQ_TIMER, &timer_irq, NULL);// 装载定时中断函数
    // 定时器中断编号 LS1C102_IRQ_TIMER = 11。把中断函数 timer_irq 的地址作为参数传入
    // 定时器配置、中断配置如上
}
    
    
        

    




