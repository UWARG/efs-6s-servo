#include "adc.h"
#include "stm32l4xx_hal.h"

#define LED_BUFFER_SIZE 500

#define BIT1_CCR_VALUE 56
#define BIT0_CCR_VALUE 24

#define CURRENT_THRESHOLD1 2.5
#define CURRENT_THRESHOLD2 5.0

typedef struct {
  uint8_t green;
  uint8_t red;
  uint8_t blue;
} LEDColour_t;

extern TIM_HandleTypeDef htim2;
extern Circuit_t circuit;

static uint32_t ledBuffer[LED_BUFFER_SIZE];
static LEDColour_t curColour;
static uint8_t curColourMutex;

static void setColour(float current)
{
  curColourMutex = 1;
  if(current < CURRENT_THRESHOLD1)
  {
    curColour.green = 2;
    curColour.red   = 0;
    curColour.blue  = 0;
  }
  else if(current < CURRENT_THRESHOLD2)
  {
    curColour.green = 1;
    curColour.red   = 1;
    curColour.blue  = 0;
  }
  else
  {
    curColour.green = 0;
    curColour.red   = 0;
    curColour.blue  = 2;
  }
  curColourMutex = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if(!curColourMutex)
  {
    for(int i = 0; i < 8; ++i)
    {
      *(ledBuffer + i) = (curColour.green & (1U << i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
    }

    for(int i = 0; i < 8; ++i)
    {
      *(ledBuffer + 8 + i) = (curColour.red & (1U << i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
    }

    for(int i = 0; i < 8; ++i)
    {
      *(ledBuffer + 16 + i) = (curColour.blue & (1U << i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
    }
  }

  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, ledBuffer, LED_BUFFER_SIZE);
}

void initNeopixel(void)
{
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, ledBuffer, LED_BUFFER_SIZE);
}

void periodicNeopixelTasks(void)
{
  static uint32_t nextRunTime = 0;

  if(HAL_GetTick() >= nextRunTime)
  {
    nextRunTime += 250U;

    setColour(circuit.currentBATT);
  }
}
