#include "servo.h"

#define SERVO_COUNT 4

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim15;

static Servo_t servos[SERVO_COUNT] = {
  {
    1U,
    &htim1,
    TIM_CHANNEL_1,
    0.05,
    0.10
  },
  {
    2U,
    &htim1,
    TIM_CHANNEL_2,
    0.05,
    0.10
  },
  {
    4U,
    &htim1,
    TIM_CHANNEL_3,
    0.05,
    0.10
  },
  {
    5U,
    &htim15,
    TIM_CHANNEL_1,
    0.05,
    0.10
  }
};

void initServos(void)
{
  for(int i = 0; i < SERVO_COUNT; ++i)
  {
    uint32_t prescaler = servos[i].timer->Instance->PSC + 1;
    uint32_t period = servos[i].timer->Instance->ARR + 1;

    servos[i].minCCR = servos[i].minDutyCycle * period;
    servos[i].maxCCR = servos[i].maxDutyCycle * period;
    servos[i].period = HAL_RCC_GetPCLK1Freq() / (prescaler * period) * 1e6;

    uint32_t halfDutyCycle = (servos[i].minCCR + servos[i].maxCCR) / 2.0;
    __HAL_TIM_SET_COMPARE(servos[i].timer, servos[i].channel, halfDutyCycle);
    HAL_TIM_PWM_Start (servos[i].timer, servos[i].channel);
  }
}

void dutyCycleActuation(float dutyCycle, uint8_t actuatorID)
{
  for(int i = 0; i < SERVO_COUNT; ++i)
  {
    if (servos[i].actuatorID != actuatorID)
    {
      continue;
    }

    uint32_t ccrValue = servos[i].timer->Instance->ARR * dutyCycle / servos[i].period;
    __HAL_TIM_SET_COMPARE(servos[i].timer, servos[i].channel, ccrValue);
    return;
  }
}

void percentageActuation(float percentage, uint8_t actuatorID)
{
  for(int i = 0; i < SERVO_COUNT; ++i)
  {
    if (servos[i].actuatorID != actuatorID)
    {
      continue;
    }

    percentage = (percentage + 1) / 2;
    uint32_t ccrValue = servos[i].minCCR + percentage * (servos[i].maxCCR - servos[i].minCCR);
    __HAL_TIM_SET_COMPARE(servos[i].timer, servos[i].channel, ccrValue);
    return;
  }
}
