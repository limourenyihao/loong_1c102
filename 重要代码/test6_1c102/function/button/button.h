/*
 * button.h
 *
 * created: 2024/5/9
 *  author: 
 */

#ifndef _BUTTON_H
#define _BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

void button_init(int gpio);
void button_get(int gpio,int voltage);
void button_work(void);

#ifdef __cplusplus
}
#endif

#endif // _BUTTON_H

