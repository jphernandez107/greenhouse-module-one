//
// Created by juan_ on 31/10/2020.
//

#ifndef MODULEONE_BSP_H
#define MODULEONE_BSP_H

#include "bsp_actuators.h"
#include "bsp_switches.h"
#include "bsp_lcd.h"

void BSP_Init();
void BSP_Blocking_delay_ms(int ms);
void BSP_Display_Set_Cursor(uint8_t row, uint8_t col);
void BSP_Display_Print(const char* str, ...);
void BSP_Display_Print_Custom_Char(char customChar);
void BSP_Get_Lux_Meter(float *BH1750_lux);
float BSP_Get_Room_Temperature();
float BSP_Get_Room_Humidity();
uint32_t BSP_Get_Soil_Humidity();

#endif //MODULEONE_BSP_H
