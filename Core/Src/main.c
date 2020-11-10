#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;
float LuxMeter;

int main(void) {

    BSP_Init();

    BSP_Actuator_Off(CoolingPump);
    BSP_Actuator_On(IrrigationPump);

    while (1) {
        APP_Display_Lux_Meter(LuxMeter);
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
}

void APP_Display_Lux_Meter(float lux) {
    BSP_Display_Set_Cursor(1, 10);
    BSP_Display_Print_Custom_Char(LIGHTBULB);
    BSP_Display_Print("%0.0fLx  ", lux);
}


