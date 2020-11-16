//
// Created by juan_ on 14/11/2020.
//

#include "bsp_soil_humidity_sensor.h"

#define INPUT_START 3600.0
#define INPUT_END 1830.0
#define OUTPUT_START 0.0
#define OUTPUT_END 100.0

uint8_t getSoilHumidity(uint16_t adc_value) {
    if (adc_value > INPUT_START) adc_value = INPUT_START;
    if (adc_value <= INPUT_END) adc_value = INPUT_END + 1;
    return OUTPUT_START + ((OUTPUT_END - OUTPUT_START) / (INPUT_END - INPUT_START)) * (adc_value - INPUT_START);
}