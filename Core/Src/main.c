#include "main.h"

void *CoolingPump, *IrrigationPump;
void *CoolingSwitch, *IrrigationSwitch;

int main(void) {

    BSP_Init();

    BSP_Actuator_On(CoolingPump);
    BSP_Actuator_Off(IrrigationPump);
    BSP_HAL_Delay(2000);

    while (1) {
        BSP_Actuator_Toggle(CoolingPump);
        BSP_Actuator_Toggle(IrrigationPump);
        BSP_HAL_Delay(500);
    }
}




