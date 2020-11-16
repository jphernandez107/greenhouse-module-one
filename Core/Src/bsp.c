//
// Created by juan_ on 29/10/2020.
//


#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "bsp_actuators.h"
#include "bsp_switches.h"
#include "bsp_lcd.h"
#include "bsp_lux_sensor.h"
#include "bsp_soil_humidity_sensor.h"

extern void APP_Timer100ms();
extern void APP_Timer10ms();
extern void APP_Soil_Humidity_Data_Event(uint8_t value);

#define TIMER  TIM2
volatile static uint32_t gu32_ticks = 0;

TIM_HandleTypeDef htim2;
I2C_HandleTypeDef hi2c1;
ADC_HandleTypeDef hadc1;

void SystemClock_Config(void);
void Error_Handler(void);
void HAL_TIM_Init(void);
static void I2C1_Init(void);
static void ADC1_Init(void);

void BSP_Init() {
    HAL_Init();

    SystemClock_Config();

    HAL_TIM_Init();
    I2C1_Init();
    ADC1_Init();
    BSP_Actuators_Init();
    BSP_Switches_Init();
    lcd16x2_i2c_init(&hi2c1);
    BSP_LCD_Initialize();
    BH1750_Init(&hi2c1);
    BH1750_SetMode(CONTINUOUS_HIGH_RES_MODE_2);
//    HAL_ADC_Start_IT(&hadc1);
}

void HAL_TIM_Init() {
    gu32_ticks = (HAL_RCC_GetHCLKFreq() / 1000000);
    htim2.Instance = TIMER;

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Init.Prescaler = gu32_ticks; // deberia ser 100 pero HAL_RCC_GetHCLKFreq() devuelve 64MHz -> gu32_ticks = 64
    htim2.Init.Period = 1000;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) Error_Handler();
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) Error_Handler();

    HAL_TIM_Base_Start_IT(&htim2);
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    static uint16_t App_100msTimeOut = 100;
    static uint16_t App_10msTimeOut = 10;
    // Period TIM2 = 1ms
    if(htim->Instance == TIMER){
        if (App_100msTimeOut){
            App_100msTimeOut--;
            if (App_100msTimeOut == 0){
                App_100msTimeOut = 100;
                APP_Timer100ms();
            }
        }
        if (App_10msTimeOut){
            App_10msTimeOut--;
            if (App_10msTimeOut == 0){
                App_10msTimeOut = 10;
                APP_Timer10ms();
            }
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    BSP_Switches_Pin_Interrupt_Callback(GPIO_Pin);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
//    adc_values[0] = HAL_ADC_GetValue(hadc);
//    adc_values[1] = HAL_ADC_GetValue(hadc);


    APP_Soil_Humidity_Data_Event(getSoilHumidity(HAL_ADC_GetValue(hadc)));
    HAL_ADC_Start_IT(hadc);
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) Error_Handler();
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};

    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)*/
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 2;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK) Error_Handler();
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) Error_Handler();

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) Error_Handler();

}

void BSP_HAL_Delay(int ms) {
    HAL_Delay(ms);
}


void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 100;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
}



void Error_Handler(void) {}


//**************************************************************************************//

void BSP_Display_Set_Cursor(uint8_t row, uint8_t col) {
    lcd16x2_i2c_setCursor(row, col);
}

void BSP_Display_Print(const char* str, ...) {
    lcd16x2_i2c_printf(str);
}

void BSP_Display_Print_Custom_Char(char customChar) {
    lcd16x2_i2c_print_custom_char(customChar);
}

void BSP_Get_Lux_Meter(float *BH1750_lux) {
    BH1750_ReadLight(BH1750_lux);
}

void BSP_Get_Soil_Humidity() {
    HAL_ADC_Start_IT(&hadc1);
}

