#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;

int main(void) {

    BSP_Init();

    BSP_Actuator_Off(CoolingPump);
    BSP_Actuator_On(IrrigationPump);

    while (1) {
    }
}


void APP_Switch_Release_Event(void *pressedSwitch) {

    if (pressedSwitch == CoolingSwitch) {
        BSP_Actuator_Toggle(CoolingPump);
    } else if (pressedSwitch == IrrigationSwitch) {
        BSP_Actuator_Toggle(IrrigationPump);
    }
}




