/*
 * rtc.h
 *
 * created: 2024/5/10
 *  author: 
 */

#ifndef _USER_RTC_H
#define _USER_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef union{
    struct{
        uint32_t day:5;
        uint32_t month:4;
        uint32_t year:7;
        uint32_t reserve:15;
        uint32_t bad_time:1;
    };
    uint32_t reg;
}RTC1;

typedef union{
    struct{
        uint32_t sixteenth:4;
        uint32_t second:6;
        uint32_t minute:6;
        uint32_t hour:5;
        uint32_t reserve:10;
        uint32_t bad_time:1;
    };
    uint32_t reg;
}RTC0;

extern RTC1 rtc1;
extern RTC0 rtc0;

void rtc_init(int freq);
void rtc_set_time(uint32_t year,uint32_t month,uint32_t day,uint32_t hour,uint32_t minute,uint32_t second);
void rtc_get_time();

#ifdef __cplusplus
}
#endif

#endif // _USER_RTC_H

