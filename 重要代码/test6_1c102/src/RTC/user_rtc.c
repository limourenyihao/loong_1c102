/*
 * rtc.c
 *
 * created: 2024/5/10
 *  author: 
 */

#include <stdio.h>
#include <stdbool.h>
#include "bsp.h"
#include "console.h"
#include "ls1c102_irq.h"
#include "user_rtc.h"
#include "ls1c102.h"

HW_RTC_t *g_rtc = (HW_RTC_t *)LS1C102_RTC_BASE;

RTC1 rtc1;
RTC0 rtc0;

/*
    ʱ�ӷ�Ƶ��
    ѡ���ⲿ32Mʱ�ӣ�
    ����freq=32768 / 16 = 2048 .
*/
void rtc_init(int freq)
{
    g_rtc->freq = freq<<16;
}

/*
    ��дrtc0��дrtc1
    ����ʱ��
*/
void rtc_set_time(uint32_t year,uint32_t month,uint32_t day,uint32_t hour,uint32_t minute,uint32_t second)
{
    g_rtc->cfg = 0;
    
    rtc0.reg = 0;
    rtc0.hour = hour;
    rtc0.minute = minute;
    rtc0.second = second;
    rtc0.sixteenth = 0;
    g_rtc->rtc0 = rtc0.reg;//��ʼ��rtc0�ж�Ӧ��ʱ��
    
    rtc1.reg = 0;
    rtc1.year = year - 2000;
    rtc1.month = month;
    rtc1.day = day;
    g_rtc->rtc0 = rtc1.reg;//��ʼ��rtc1�ж�Ӧ��ʱ��
}

/*
    ��ȡrtc��ʱ��ֵ
*/
void rtc_get_time()
{
    rtc1.reg = g_rtc->rtc1;
    rtc0.reg = g_rtc->rtc0;
}

