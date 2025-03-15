#include "adc.h"
#include "neopixel.h"
#include "stm32l4xx_hal.h"

#define CURRENT_WARNING_THRESHOLD 3.0
#define CURRENT_CRITICAL_THRESHOLD 4.0

#define COUNTS_TO_VOLTS(COUNTS) ( (COUNTS) * 3.3 / 4095 )

extern ADC_HandleTypeDef hadc1;
extern StatusColours_e targetColour;

static uint32_t rawADCValues[VOLTAGE_CONVERSIONS + CURRENT_CONVERSIONS];
static VoltageMonitor_t moduleVoltages;
static VoltageSense_t v[] = {
  {
    // battery rail voltage
	&rawADCValues[1],
    130E3,
    10E3
  },
  {
    // 6v rail voltage
	&rawADCValues[2],
    30E3,
    10E3
  },
  {
    // 5v rail voltage
	&rawADCValues[3],
    23.2E3,
    10E3
  },
  {
    // 3v3 rail voltage
	&rawADCValues[4],
    10E3,
    3.3E3
  }
};
static CurrentMonitor_t moduleCurrents;
static CurrentSense_t c[] = {
  {
    // battery rail current
    &rawADCValues[0],
    0.22,
    100
  }
};

static void adcGetVoltage(VoltageMonitor_t *pMonitor, VoltageSense_t *pADCData)
{
  for(int i = 0; i < VOLTAGE_CONVERSIONS; ++i)
  {
    VoltageSense_t adcData = pADCData[i];
    pMonitor->data[i] =
      (adcData.rTop + adcData.rBottom) * COUNTS_TO_VOLTS(*adcData.pADCCount) / adcData.rBottom;
  }
}

static void adcGetCurrent(CurrentMonitor_t *pMonitor, CurrentSense_t *pADCData)
{
  for(int i = 0; i < CURRENT_CONVERSIONS; ++i)
  {
    CurrentSense_t adcData = pADCData[i];
    pMonitor->data[i] =
      COUNTS_TO_VOLTS(*adcData.pADCCount) / adcData.cSenseGain / adcData.rShunt;
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  adcGetVoltage(&moduleVoltages, v);
  adcGetCurrent(&moduleCurrents, c);

  if(*moduleCurrents.currentBATT < CURRENT_WARNING_THRESHOLD)
  {
    targetColour = STATUS_OK_COLOUR;
  }
  else if(*moduleCurrents.currentBATT < CURRENT_CRITICAL_THRESHOLD)
  {
    targetColour = STATUS_WARNING_COLOUR;
  }
  else
  {
    targetColour = STATUS_CRITICAL_COLOUR;
  }
}

void initADC(void)
{
  moduleVoltages.voltageBATT = moduleVoltages.data;
  moduleVoltages.voltage6V   = moduleVoltages.data + 1;
  moduleVoltages.voltage5V   = moduleVoltages.data + 2;
  moduleVoltages.voltage3V3  = moduleVoltages.data + 3;

  moduleCurrents.currentBATT = moduleCurrents.data;
}

void periodicADCTasks(void)
{
  static uint32_t nextRunTime = 0;

  if(HAL_GetTick() >= nextRunTime)
  {
    nextRunTime += 125U;

    HAL_ADC_Start_DMA(&hadc1, rawADCValues, VOLTAGE_CONVERSIONS + CURRENT_CONVERSIONS);
  }
}
