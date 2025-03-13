#pragma once

typedef struct {
  uint32_t *adcValue;
  float resistor1;
  float resistor2;
} voltageDivider_t;

/**
  * @brief Start ADC data transfer with DMA
  * @retval None
  */
void readADC();

/**
  * @brief Convert ADC value to voltage
  * @retval Calculated voltage
  */
float adcToVoltage(voltageDivider_t *voltageDivider);

/**
  * @brief Convert ADC value to battery current
  * @retval Calculated current
  */
float adcToCurrent();
