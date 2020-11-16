//
// Created by juan_ on 16/11/2020.
//

#include "bsp_co2_sensor.h"


/************************Hardware Related Macros************************************/
#define         MG_PIN                       0     //define which analog input channel you are going to use
#define         BOOL_PIN                     2
#define         DC_GAIN                      8.5   //define the DC gain of amplifier

/***********************Software Related Macros************************************/
#define         READ_SAMPLE_INTERVAL         50    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            5     //define the time interval(in milisecond) between each samples in
//normal operation

/**********************Application Related Macros**********************************/
//These two values differ from sensor to sensor. user should derermine this value.
#define         ZERO_POINT_VOLTAGE           0.250f //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTGAE             0.160f //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

/*****************************Globals***********************************************/
float           CO2Curve[3]  =  {2.602f,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602f-3.0f))};
///two points are taken from the curve.
///with these two points, a line is formed which is
///"approximately equivalent" to the original curve.
///data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280)
///slope = ( reaction voltage ) / (log400 –log1000)







/*****************************  MGRead *********************************************
Input:   mg_pin - analog channel
Output:  output of SEN-000007
Remarks: This function reads the output of SEN-000007
************************************************************************************/
float BSP_Co2_Get_Voltage(float adc_value)
{

#define INPUT_START 0.0f
#define INPUT_END 4095.0f
#define OUTPUT_START 0.0f
#define OUTPUT_END 3.0f

//    if (adc_value > INPUT_START) adc_value = INPUT_START;
//    if (adc_value <= INPUT_END) adc_value = INPUT_END + 1;
    return OUTPUT_START + ((OUTPUT_END - OUTPUT_START) / (INPUT_END - INPUT_START)) * (adc_value - INPUT_START);

//    for (i=0;i<READ_SAMPLE_TIMES;i++) {
//        v += analogRead(mg_pin);
//        delay(READ_SAMPLE_INTERVAL);
//    }
    adc_value = (adc_value) * 3.3f/4095.0f ;
    return adc_value;
}

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.
************************************************************************************/
int  BSP_Co2_Get_PPM(float volts)
{
    if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {
        return -1;
    } else {
        return pow(10, ((volts/DC_GAIN)-CO2Curve[1])/CO2Curve[2]+CO2Curve[0]);
    }
}