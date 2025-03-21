#include "neopixel.h"
#include "stm32l4xx_hal.h"

#define LED_BUFFER_SIZE 300
#define BIT0_CCR_VALUE 24
#define BIT1_CCR_VALUE 64

extern TIM_HandleTypeDef htim2;

StatusColours_e targetColour = STATUS_OK_COLOUR;

static StatusColours_e currentColour = STATUS_OK_COLOUR;
static LEDColour_t green  = {10, 0, 0};
static LEDColour_t yellow = {8, 12, 0};
static LEDColour_t red    = {0, 10, 0};
static uint32_t ledBuffer[LED_BUFFER_SIZE];

static void updateLEDBuffer(LEDColour_t *colour)
{
  for(int i = 0; i < 8; ++i)
  {
    *(ledBuffer + i) = colour->green & (1U << (7 - i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
  }

  for(int i = 0; i < 8; ++i)
  {
    *(ledBuffer + 8 + i) = colour->red & (1U << (7 - i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
  }

  for(int i = 0; i < 8; ++i)
  {
    *(ledBuffer + 16 + i) = colour->blue & (1U << (7 - i)) ? BIT1_CCR_VALUE : BIT0_CCR_VALUE;
  }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if(targetColour != currentColour)
  {
    currentColour = targetColour;

    switch(currentColour)
    {
      case STATUS_OK_COLOUR:
        updateLEDBuffer(&green);
        break;
      case STATUS_WARNING_COLOUR:
        updateLEDBuffer(&yellow);
        break;
      default:
        updateLEDBuffer(&red);
    }
  }

  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, ledBuffer, LED_BUFFER_SIZE);
}

void initNeopixel(void)
{
  updateLEDBuffer(&green);
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, ledBuffer, LED_BUFFER_SIZE);
}

