#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "bsp.h"

#ifdef __cplusplus
}
#endif

void APP_Timer100ms();

void APP_Display_Lux_Meter(float lux);
void APP_Display_Room_Temperature(float RoomTemp);
void APP_Display_Room_Humidity(float RoomHum);

#endif /* __MAIN_H */
