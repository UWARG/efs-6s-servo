#include "adc.h"
#include "stm32l4xx_hal.h"

#define R2_SHUNT 0.22
#define R4_BATT  130E3
#define R9_BATT  10E3
#define R18_6V   30E3
#define R21_6V   10E3
#define R20_5V   23.2E3
#define R23_5V   10E3
#define R19_3V3  10E3
#define R22_3V3  3.3E3

#define CSENSE_GAIN 100.0

#define COUNTS_TO_VOLTS(COUNTS) ( (COUNTS) * 3.3 / 4095 )

extern ADC_HandleTypeDef hadc1;
extern Circuit_t circuit;

static uint32_t adcValues[5];

static float adcGetCurrent(void)
{
  return COUNTS_TO_VOLTS(adcValues[0]) / CSENSE_GAIN / R2_SHUNT;
}

static float adcGetVoltage(uint32_t adcCount, float rTop, float rBottom)
{
  return COUNTS_TO_VOLTS(adcCount) * (rTop + rBottom) / rBottom;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  circuit.currentBATT = adcGetCurrent();
  circuit.voltageBATT = adcGetVoltage(adcValues[3], R4_BATT, R9_BATT);
  circuit.voltage6V   = adcGetVoltage(adcValues[4], R18_6V, R21_6V);
  circuit.voltage5V   = adcGetVoltage(adcValues[1], R20_5V, R23_5V);
  circuit.voltage3V3  = adcGetVoltage(adcValues[2], R19_3V3, R22_3V3);
}

void periodicADCTasks(void)
{
  static uint32_t nextRunTime = 0;

  if(HAL_GetTick() >= nextRunTime)
  {
    nextRunTime += 250U;

    HAL_ADC_Start_DMA(&hadc1, adcValues, 5);
  }
}
