#include "timer.h"
#include <stdio.h>
#include "ls1c102.h"
#include "ls1c102_irq.h"

#include "src/GPIO/user_gpio.h"

HW_TIMER_t *g_timer = (HW_TIMER_t *)LS1C102_TIMER_BASE;// ��ȡ��ʱ���Ĵ���
HW_INTC_t *intc = (HW_INTC_t *)LS1C102_INTC_BASE;      // ��ȡ�жϼĴ���

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

    g_timer->cfg = g_timer->cfg;// ִ�к�����жϱ�־λ
}

void timer_interrupt(uint32_t compare,uint32_t step)
{
    // ��ʱ�����á��ж���������
    g_timer->cfg = 0;                    // ��ʱ�����ø�λ
    g_timer->cnt = 0;                    // ��ʱ������ֵ���

    g_timer->cmp = compare;             // �״ν��붨ʱ���жϵļ�������Ϊ16M�����ʱ��Ϊ8M����ô��Լ��2s��ʱ��û���⡣
    //g_timer->step = 32000000;            // ��ʱ���жϲ���������32M����һ���жϣ���Լ��4s��ʱ��û���⡣
    // һ�㶼�����ڴ���ģʽ�����Ե�һ�δ����ж���Ҫ������ cmp ��֮��ÿ�μ��� step �ͻᴥ��һ���жϡ�
    g_timer->step = step;

    g_timer->cfg = 0x07;                 // �������ڴ������ж�ʹ�ܣ���ʼ����
    intc->en |= 0x01;                    // ������ʱ��ȫ���ж�
    
    ls1c102_install_isr(LS1C102_IRQ_TIMER, &timer_irq, NULL);// װ�ض�ʱ�жϺ���
    // ��ʱ���жϱ�� LS1C102_IRQ_TIMER = 11�����жϺ��� timer_irq �ĵ�ַ��Ϊ��������
    // ��ʱ�����á��ж���������
}
    
    
        

    




