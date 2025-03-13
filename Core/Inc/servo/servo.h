#pragma once

#include <stdint.h>
#include "stm32l4xx_hal.h"

/**
  * @brief  Configure and start servo PWM generation.
  * @retval None
  */
void initServos(void);

/**
  * @brief  Drive servos with UAVCAN_EQUIPMENT_ACTUATOR_COMMAND_COMMAND_TYPE_PWM.
  * @param  dutyCycle for PWM given in microseconds
  * @retval None
  */
void dutyCycleActuation(float dutyCycle, uint8_t actuatorID);

/**
  * @brief  Drive servos with UAVCAN_EQUIPMENT_ACTUATOR_COMMAND_COMMAND_TYPE_UNITLESS.
  * @param  percentage of ROM with bounds [-1, 1]
  * @retval None
  */
void percentageActuation(float percentage, uint8_t actuatorID);
