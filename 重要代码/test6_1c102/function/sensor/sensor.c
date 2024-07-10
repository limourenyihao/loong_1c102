/*
 * sensor.c
 *
 * created: 2024/5/24
 *  author: 
 */

#include "sensor.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;
/*
    液位检测传感器
    ADC通道——————ADC0
*/
int level_sensor(void)
{
    int level = 0;
    level = adc_read(0);
    return level;
}

/*
    PT100温度传感器
    ADC通道——————ADC1
*/
int tem_sensor(void)
{
    int tem = 0;
    tem = adc_read(1);
    return tem;
}

/*
    PH值检测模块
    ADC通道——————GPIO14
*/
int PH_sensor(void)
{
    int PH = 0;
    PH = adc_read(4);
    return PH;
}

/*
    气压检测传感器
    ADC通道——————GPIO16
*/
int pressure_sensor(void)
{
    int pressure = 0;
    pressure = adc_read(6);
    return pressure;
}

