#include "user_gpio.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

/*
    gpio ���ʹ��
    gpio:���
    io = 1������� io = 0������
*/
void gpio_init(int gpio, int io)
{
    int bit;
    if(gpio < 32)
    {
        bit = gpio;
        if(io == 0) g_pmu->GPIOA_OE &= ~(0x01<<bit);
        else g_pmu->GPIOA_OE |= (0x01<<bit);
    }
    else
    {
        bit = gpio - 32;
        if(io == 0) g_pmu->GPIOB_OE &= ~(0x01<<bit);
        else g_pmu->GPIOB_OE |= (0x01<<bit);
    }
}

/*
    �趨 gpio ���ֵ
    gpio:���
    val = 1���ߵ�ƽ�� val = 0���͵�ƽ
*/
void gpio_write(int gpio, int val)
{
    int bit;
    if(gpio < 32)
    {
        bit = gpio;
        if(val == 0) g_pmu->GPIOA_O &= ~(0x01<<bit);
        else g_pmu->GPIOA_O |= (0x01<<bit);
    }
    else
    {
        bit = gpio - 32;
        if(val == 0) g_pmu->GPIOB_O &= ~(0x01<<bit);
        else g_pmu->GPIOB_O |= (0x01<<bit);
    }
}

/*
    ȡ�� gpio ���ֵ
    gpio:���
*/
void gpio_turn(int gpio)
{
    int bit;
    if(gpio <32)
    {
        bit = gpio;
        g_pmu->GPIOA_O ^= (0x01<<bit);
    }
    else
    {
        bit = gpio-32;
        g_pmu->GPIOB_O ^= (0x01<<bit);
    }
}

/*
    ��ȡ gpio ������
    gpio:���
*/
int gpio_read(int gpio)
{
    int bit;
    if(gpio < 32)
    {
        bit = gpio;
        if((g_pmu->GPIOA_I & (0x01<<bit)) == (0x01<<bit))
            return 1;
        else
            return 0;
    }
    else
    {
        bit = gpio - 32;
        if((g_pmu->GPIOB_I & (0x01<<bit)) == (0x01<<bit))
            return 1;
        else
            return 0;
    }
}

/*
    gpio ����
    gpio:���
*/
int gpio_iosel(int gpio, int iosel)
{
    int bit;
    if(gpio < 16)
    {
        bit = gpio;
        g_pmu->IOSEL0 |= iosel<<(bit * 2);
    }
    else if(gpio < 32)
    {
        bit = gpio - 16;
        g_pmu->IOSEL1 |= iosel<<(bit * 2);
    }
    else if(gpio < 48)
    {
        bit = gpio - 32;
        g_pmu->IOSEL2 |= iosel<<(bit * 2);
    }
    else if(gpio < 64)
    {
        bit = gpio - 48;
        g_pmu->IOSEL3 |= iosel<<(bit * 2);
    }
    return 0;
}


