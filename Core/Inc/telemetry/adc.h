#pragma once

typedef struct {
  float currentBATT;
  float voltageBATT;
  float voltage6V;
  float voltage5V;
  float voltage3V3;
} Circuit_t;

/**
  * @brief  Execute periodic ADC maintenance tasks.
  * @retval None
  */
void periodicADCTasks(void);
