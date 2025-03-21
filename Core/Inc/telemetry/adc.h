#pragma once

#include <stdint.h>

#define VOLTAGE_CONVERSIONS 4
#define CURRENT_CONVERSIONS 1

typedef struct {
  uint32_t *pADCCount;
  float rTop;
  float rBottom;
} VoltageSense_t;

typedef struct {
  uint32_t *pADCCount;
  float rShunt;
  float cSenseGain;
} CurrentSense_t;

typedef struct {
  float data[VOLTAGE_CONVERSIONS];

  float *voltageBATT;
  float *voltage6V;
  float *voltage5V;
  float *voltage3V3;
} VoltageMonitor_t;

typedef struct {
  float data[CURRENT_CONVERSIONS];

  float *currentBATT;
} CurrentMonitor_t;

/**
  * @brief  Init helper pointers in VoltageMonitor_t and CurrentMonitor_t.
  * @retval None
  */
void initADC(void);

/**
  * @brief  Execute periodic ADC maintenance tasks.
  * @retval None
  */
void periodicADCTasks(void);
