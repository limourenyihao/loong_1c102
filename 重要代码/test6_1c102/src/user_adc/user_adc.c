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
    使能所有adc通道
*/
void adc_init(void)
{
    g_pmu->ChipCtrl |= (0x0f<<20);
}

/*
    选择adc通道读取
    ch:adc通道号(0,1,4,6,7可用)
*/
int adc_read(int ch)
{
    g_pmu->AdcCtrl = (0x01<<8) | (ch);
    while(g_pmu->AdcCtrl & 0x80);
    return (int)g_pmu->AdcDat;
}

