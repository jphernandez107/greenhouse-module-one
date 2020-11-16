//
// Created by juan_ on 31/10/2020.
//

#ifndef MODULEONE_BSP_H
#define MODULEONE_BSP_H

#include "stdint.h"

void BSP_Init();
void BSP_Blocking_delay_ms(int ms);
void BSP_Display_Set_Cursor(uint8_t row, uint8_t col);
void BSP_Display_Print(const char* str, ...);
void BSP_Display_Print_Custom_Char(char customChar);
void BSP_Get_Lux_Meter(float *BH1750_lux);
float BSP_Get_Room_Temperature();
float BSP_Get_Room_Humidity();
uint32_t BSP_Get_Soil_Humidity();
uint16_t BSP_Get_Co2();

/**
 * @brief Set cursor position
 * @param[in] row - 0 or 1 for line1 or line2
 * @param[in] col - 0 - 15 (16 columns LCD)
 */
inline void BSP_LCD_Set_Cursor(uint8_t row, uint8_t col);

/**
 * @brief Print to display
 */
void BSP_LCD_Print(const char* str, ...);

void BSP_LCD_Print_Custom_Char(char customChar);

enum BSP_LCD_Custom_Char {LIGHTBULB, THERMOMETER, DROP, CO2_1, CO2_2, CO2_3, PPM_1, PPM_2};


void BSP_Actuator_On(void *actuator);
void BSP_Actuator_Off(void *actuator);
void BSP_Actuator_Toggle(void *actuator);




#endif //MODULEONE_BSP_H
