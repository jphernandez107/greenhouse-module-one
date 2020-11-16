#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;
float LuxMeter;
uint8_t SoilHumidity = 12;

int main(void) {

    BSP_Init();

    BSP_Actuator_Off(CoolingPump);
    BSP_Actuator_On(IrrigationPump);

    while (1) {
        APP_Display_Lux_Meter(LuxMeter);
        APP_Display_Soil_Humidity(SoilHumidity);
    }
}


void APP_Switch_Release_Event(void *pressedSwitch) {

    if (pressedSwitch == CoolingSwitch) {
        BSP_Actuator_Toggle(CoolingPump);
    } else if (pressedSwitch == IrrigationSwitch) {
        BSP_Actuator_Toggle(IrrigationPump);
    }
}

void APP_Soil_Humidity_Data_Event(uint8_t value) {
    SoilHumidity = value;
}

void APP_Timer10ms() {
    BSP_Get_Lux_Meter(&LuxMeter);
}

void APP_Timer100ms() {
    BSP_Actuator_Toggle(IrrigationPump);
//    BSP_Get_Soil_Humidity();
}

void APP_Display_Lux_Meter(float lux) {
    BSP_Display_Set_Cursor(1, 10);
    BSP_Display_Print_Custom_Char(LIGHTBULB);
    BSP_Display_Print("%0.0fLx  ", lux);
}

void APP_Display_Soil_Humidity(uint8_t soilHum) {
    BSP_Display_Set_Cursor(0, 6);   //0,12
    BSP_Display_Print("S%d%c", soilHum, '%');
}
