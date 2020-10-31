//
// Created by juan_ on 29/10/2020.
//


#include <stm32f4xx_hal_tim.h>
#include "stm32f4xx_hal.h"
#include "bsp_actuators.h"



void BSP_Init() {
    BSP_Actuators_Init();
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    static uint8_t App_100msTimeOut = 100;
    // Period TIM2 = 1ms
    if(htim->Instance == TIM2){
        if (App_100msTimeOut){
            App_100msTimeOut--;
            if (App_100msTimeOut == 0){
//                APP_Timer100ms();
                App_100msTimeOut = 100;
            }
        }
    }
}

void BSP_HAL_Delay(int ms) {
    HAL_Delay(ms);
}
