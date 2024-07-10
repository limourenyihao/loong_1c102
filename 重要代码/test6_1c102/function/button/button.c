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
    button������ʼ��
    gpio:���
*/
void button_init(int gpio)
{
    gpio_init(gpio,0);
}

/*
    button��������
    gpio:���
    voltage:�趨����/�͵�ѹ
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
    ���ִ������
*/
void button_work(void)
{
    printk("hello world\r\n");
}

