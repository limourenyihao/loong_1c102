/*
 * sensor.h
 *
 * created: 2024/5/24
 *  author: 
 */

#ifndef _SENSOR_H
#define _SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

int level_sensor(void);
int tem_sensor(void);
int PH_sensor(void);
int pressure_sensor(void);

#ifdef __cplusplus
}
#endif

#endif // _SENSOR_H

