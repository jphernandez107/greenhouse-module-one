#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;
float LuxMeter, RoomTemperature, RoomHumidity;
uint32_t SoilHum;

int main(void) {

    BSP_Init();

    BSP_Actuator_Off(CoolingPump);
    BSP_Actuator_On(IrrigationPump);

    while (1) {
        APP_Display_Room_Temperature(RoomTemperature);
        APP_Display_Room_Humidity(RoomHumidity);
        APP_Display_Lux_Meter(LuxMeter);
        APP_Display_Soil_Humidity(SoilHum);
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
    BSP_Actuator_Toggle(IrrigationPump);
    RoomTemperature = BSP_Get_Room_Temperature();
    RoomHumidity = BSP_Get_Room_Humidity();
}

void APP_Timer1000ms() {
    SoilHum = BSP_Get_Soil_Humidity();
}

void APP_Display_Lux_Meter(float lux) {
    BSP_Display_Set_Cursor(1, 10);
    BSP_Display_Print_Custom_Char(LIGHTBULB);
    BSP_Display_Print("%0.0fLx  ", lux);
}

void APP_Display_Room_Temperature(float RoomTemp) {
    lcd16x2_i2c_setCursor(0, 0);
    lcd16x2_i2c_print_custom_char(THERMOMETER);
    lcd16x2_i2c_printf("%0.1f%c ", RoomTemp, (char)223);
}

void APP_Display_Soil_Humidity(uint32_t hum) {
    lcd16x2_i2c_setCursor(0, 12);   //0,12
    lcd16x2_i2c_printf("S%d%c", hum, '%');
    lcd16x2_i2c_printf("  ");
}

void APP_Display_Room_Humidity(float RoomHum) {
    if (RoomHum >= 100) RoomHum = 99;
    lcd16x2_i2c_setCursor(0, 7);
    lcd16x2_i2c_print_custom_char(DROP);
    lcd16x2_i2c_printf("%0.0f%c ", RoomHum, '%');
}
