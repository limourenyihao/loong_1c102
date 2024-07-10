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
    Һλ��⴫����
    ADCͨ��������������ADC0
*/
int level_sensor(void)
{
    int level = 0;
    level = adc_read(0);
    return level;
}

/*
    PT100�¶ȴ�����
    ADCͨ��������������ADC1
*/
int tem_sensor(void)
{
    int tem = 0;
    tem = adc_read(1);
    return tem;
}

/*
    PHֵ���ģ��
    ADCͨ��������������GPIO14
*/
int PH_sensor(void)
{
    int PH = 0;
    PH = adc_read(4);
    return PH;
}

/*
    ��ѹ��⴫����
    ADCͨ��������������GPIO16
*/
int pressure_sensor(void)
{
    int pressure = 0;
    pressure = adc_read(6);
    return pressure;
}

