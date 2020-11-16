//
// Created by juan_ on 16/11/2020.
//

#ifndef MODULEONE_BSP_CO2_SENSOR_H
#define MODULEONE_BSP_CO2_SENSOR_H

#include "stm32f4xx_hal.h"
#include "math.h"

typedef struct
{
    double co2_a;
    double co2ppm;
    double inertia;
    int tries;
    double co2_v;
}MG811_DataTypeDef;

//uint32_t MG811_Read(MG811_DataTypeDef *MG811_Data, uint32_t adc_value);
//
//void MG811_Calibrate(MG811_DataTypeDef *MG811_Data, uint32_t adc_value);
//
//void MG811_Init_Default(MG811_DataTypeDef *MG811_Data);
//
//void MG811_Init(MG811_DataTypeDef *MG811_Data, int tries, double inertia);

float BSP_Co2_Get_Voltage(float adc_value);
int  BSP_Co2_Get_PPM(float volts);

#endif //MODULEONE_BSP_CO2_SENSOR_H
