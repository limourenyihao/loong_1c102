/*
 * Copyright (C) 2020-2023 Suzhou Tiancheng Software Ltd. All Rights Reserved.
 */

#include <string.h>
#include <larchintrin.h>

#include "bsp.h"
#include "cpu.h"
#include "ls1c102.h"
#include "clock.h"

//-----------------------------------------------------------------------------

extern void exception_common_entry(void);
extern void console_init(unsigned int baudrate);
extern int main(void);

//-----------------------------------------------------------------------------
// global Variable
//-----------------------------------------------------------------------------

unsigned int cpu_frequency = 8000000;     // CPU ����Ƶ��
unsigned int bus_frequency = 8000000;     // BUS ����Ƶ��

//-----------------------------------------------------------------------------
// ȫ�ֿ�����
//-----------------------------------------------------------------------------

HW_PMU_t  *g_pmu  = (HW_PMU_t  *)LS1C102_PMU_BASE;
HW_INTC_t *g_intc = (HW_INTC_t *)LS1C102_INTC_BASE;

//-----------------------------------------------------------------------------
// ʹ���ⲿ 8M ʱ������
//-----------------------------------------------------------------------------

#define USER_OUTER_OSC8M    1

#if USER_OUTER_OSC8M

static void OSC_init_outer(void)
{
    int i = 2*8000;  // 2ms
    
    g_pmu->ChipCtrl &= ~CHIPCTRL_8M_SEL;
    g_pmu->ChipCtrl |= CHIPCTRL_8M_EN;

    /*
     * ������ʱ��˯���������ʱ��ʧЧ? ��loop ����ѭ��
     */
    while (i-- > 0);

    while (g_pmu->CmdSts & CMDSR_8M_FAIL)
    {
        g_pmu->ChipCtrl &= ~CHIPCTRL_8M_SEL;
    }

    g_pmu->ChipCtrl |= CHIPCTRL_8M_SEL;
}

#endif

//-----------------------------------------------------------------------------

static void get_frequency(void)
{
    unsigned int val = g_pmu->CmdSts;

    if (!(val & CMDSR_8M_SEL))      /* û��ʹ���ⲿ 8M ����*/
    {
        /*
         * ������þ���Ƶ����FLASH 0xBF0201B0 ��?
         */
        val = (*(volatile unsigned int *)0xBF0201B0) * 1000;
        if (val > 0)
        {
            cpu_frequency = val;
            bus_frequency = val;
        }

#if !USER_OUTER_OSC8M
        /*
         * �ڲ� 32MHZ ����
         */
        val = g_pmu->ChipCtrl;
        
        if (val & CHIPCTRL_FASTEN)      // 3 ��Ƶ
        {
            cpu_frequency = cpu_frequency * 4 / 3;
            bus_frequency = bus_frequency * 4 / 3;
        }
#endif
    }
}

//-----------------------------------------------------------------------------
// ls1c102 bsp start
//-----------------------------------------------------------------------------

extern void ls1c102_init_isr_table(void);

void bsp_start(void)
{
    unsigned int eentry;

    loongarch_interrupt_disable();

    /**
     * ���жϴ��븴�Ƶ�0x80000000
     */
    eentry = __csrrd_w(LA_CSR_EBASE);
    memcpy((void *)eentry, (void *)exception_common_entry, 32);

    g_pmu->CommandW = 0;            // CMDSR_SLEEP_EN;

#if USER_OUTER_OSC8M
    OSC_init_outer();               // ����Ϊ�ⲿʱ�� TODO delay_ms() ������
#else

#endif

    get_frequency();                /* ��ȡƵ������ */

    ls1c102_init_isr_table();       /* ��ʼ���ж������� */

    console_init(115200);           /* initialize Console */

    Clock_initialize();             /* initialize system ticker */

    loongarch_interrupt_enable();   /* Enable all interrupts */

    main();                         /* goto main function */
    
    while (1);                      /* XXX never goto HERE! */
    
    return;
}

//-----------------------------------------------------------------------------

/*
 * @@ END
 */
