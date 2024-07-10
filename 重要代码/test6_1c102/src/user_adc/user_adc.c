/*
 * user_adc.c
 *
 * created: 2024/5/9
 *  author: 
 */

#include "user_adc.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

/*
    ʹ������adcͨ��
*/
void adc_init(void)
{
    g_pmu->ChipCtrl |= (0x0f<<20);
}

/*
    ѡ��adcͨ����ȡ
    ch:adcͨ����(0,1,4,6,7����)
*/
int adc_read(int ch)
{
    g_pmu->AdcCtrl = (0x01<<8) | (ch);
    while(g_pmu->AdcCtrl & 0x80);
    return (int)g_pmu->AdcDat;
}

