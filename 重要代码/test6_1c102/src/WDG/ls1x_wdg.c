#include "ls1x_wdg.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void WdgInit(void)
{
    WDG_SetWatchDog(0x80007fff);// ���Ź����ʱ
    // time = 0x80007fff = 0b10000000000000000111111111111111
    // time = 0x80007fff = 0b1000000000000000 0111111111111111
    // ~time =             0b1000000000000000 0000000000000000
    // PMU->WDT_CFG =      0b1000000000000000 0111111111111111
    WDG_DogFeed();
}

/*
time = 0x8000_7fff
~time = 0x7fff_8000
~time<<16 = 0x8000_0000
(~time<<16) | time = 0x8000_7fff
*/

/*
    ���ÿ��Ź���λʱ��
    time:32λ���ݣ���16λ�����ǵ�16λ����ȡ��
*/
void WDG_SetWatchDog(uint32_t time)
{
    WDG_DogFeed();
    g_pmu->WdtCfg = (((~time)<<16) | time);// WdtCfg ���ñ�����ȷ������ֱ�Ӹ�λ��
}

void WDG_DogFeed(void)
{
    g_pmu->WdtFeed = WDTFEED_FOOD;
}

void my_delay(volatile int i)
{
    while(i--);
}



