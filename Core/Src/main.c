#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;
float LuxMeter, RoomTemperature, RoomHumidity;
uint32_t SoilHum, Co2;

int main(void) {

    BSP_Init();

    BSP_Actuator_Off(CoolingPump);
    BSP_Actuator_On(IrrigationPump);

    while (1) {
        APP_Display_Room_Temperature(RoomTemperature);
        APP_Display_Room_Humidity(RoomHumidity);
        APP_Display_Lux_Meter(LuxMeter);
        APP_Display_Soil_Humidity(SoilHum);
        APP_Display_CO2(Co2);
    }
}


void APP_Switch_Release_Event(void *pressedSwitch) {

    if (pressedSwitch == CoolingSwitch) {
        BSP_Actuator_Toggle(CoolingPump);
    } else if (pressedSwitch == IrrigationSwitch) {
        BSP_Actuator_Toggle(IrrigationPump);
    }
}

void APP_Timer10ms() {
    BSP_Get_Lux_Meter(&LuxMeter);
}

void APP_Timer100ms() {
    RoomTemperature = BSP_Get_Room_Temperature();
    RoomHumidity = BSP_Get_Room_Humidity();
}

void APP_Timer1000ms() {
    SoilHum = BSP_Get_Soil_Humidity();
}

void APP_Timer10s() {
    Co2 = BSP_Get_Co2();
    BSP_Actuator_Toggle(IrrigationPump);
    BSP_Actuator_Toggle(CoolingPump);
}

void APP_Display_Lux_Meter(float lux) {
    BSP_Display_Set_Cursor(1, 10);
    BSP_Display_Print_Custom_Char(LIGHTBULB);
    BSP_Display_Print("%0.0fLx  ", lux);
}

void APP_Display_Room_Temperature(float RoomTemp) {
    BSP_LCD_Set_Cursor(0, 0);
    BSP_LCD_Print_Custom_Char(THERMOMETER);
    BSP_LCD_Print("%0.1f%c ", RoomTemp, (char) 223);
}

void APP_Display_Soil_Humidity(uint32_t hum) {
    BSP_LCD_Set_Cursor(0, 12);   //0,12
    BSP_LCD_Print("S%d%c", hum, '%');
    BSP_LCD_Print("  ");
}

void APP_Display_Room_Humidity(float RoomHum) {
    if (RoomHum >= 100) RoomHum = 99;
    BSP_LCD_Set_Cursor(0, 7);
    BSP_LCD_Print_Custom_Char(DROP);
    BSP_LCD_Print("%0.0f%c ", RoomHum, '%');
}

void APP_Display_CO2(uint32_t ppm) {
    if (ppm > 10000) ppm = 9999;
    BSP_LCD_Set_Cursor(1, 0);
    BSP_LCD_Print("co");
    BSP_LCD_Print_Custom_Char(CO2_3);
    BSP_LCD_Print("%0.0d", ppm);
    BSP_LCD_Print_Custom_Char(PPM_1);
    BSP_LCD_Print_Custom_Char(PPM_2);
    BSP_LCD_Print(" ");
}

