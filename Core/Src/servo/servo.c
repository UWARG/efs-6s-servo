#include "servo.h"

#define SERVO_COUNT 4

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

typedef struct {
  uint8_t actuatorID;

  TIM_HandleTypeDef *timer;
  uint32_t channel;

  float minDutyCycle;
  float maxDutyCycle;

  // internal variables to be auto-initialized
  uint32_t minCCR;
  uint32_t maxCCR;
  uint64_t period;
} Servo_t;

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
    &htim2,
    TIM_CHANNEL_3,
    0.05,
    0.10
  }
};

void initServos(void)
{
  for(int i = 0; i < SERVO_COUNT; ++i)
  {
    TIM_TypeDef *timInstance = servos[i].timer->Instance;
    servos[i].minCCR = servos[i].minDutyCycle * timInstance->ARR;
    servos[i].maxCCR = servos[i].maxDutyCycle * timInstance->ARR;
    servos[i].period = HAL_RCC_GetPCLK1Freq() / (timInstance->PSC * timInstance->ARR) * 1e6;

    __HAL_TIM_SET_COMPARE(servos[i].timer, servos[i].channel, servos[i].minCCR);
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
