#include "main.h"

void *CoolingPump, *IrrigationPump;


int main(void) {

    BSP_Init();

    BSP_Actuator_On(CoolingPump);
    BSP_Actuator_On(IrrigationPump);
    BSP_HAL_Delay(2000);

    while (1) {
        BSP_Actuator_Toggle(CoolingPump);
        BSP_HAL_Delay(1000);
        BSP_Actuator_Toggle(IrrigationPump);
        BSP_HAL_Delay(1000);
    }
}

