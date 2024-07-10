/*
 * valve.h
 *
 * created: 2024/5/26
 *  author: 
 */

#ifndef _VALVE_H
#define _VALVE_H

#ifdef __cplusplus
extern "C" {
#endif

void valve_init(void);
int valve_coldrun(void);
int valve_hotrun(void);

#ifdef __cplusplus
}
#endif

#endif // _VALVE_H

