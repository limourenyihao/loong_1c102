/*
 * user_adc.h
 *
 * created: 2024/5/9
 *  author: 
 */

#ifndef _USER_ADC_H
#define _USER_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

void adc_init(void);
int adc_read(int ch);

#ifdef __cplusplus
}
#endif

#endif // _USER_ADC_H

