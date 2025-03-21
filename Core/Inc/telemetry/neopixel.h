#pragma once

#include <stdint.h>

typedef struct {
  uint8_t green;
  uint8_t red;
  uint8_t blue;
} LEDColour_t;

typedef enum {
  STATUS_OK_COLOUR = 0,
  STATUS_WARNING_COLOUR,
  STATUS_CRITICAL_COLOUR
} StatusColours_e;

/**
  * @brief  Set initial Neopixel colour, and start DMA loop.
  * @retval None
  */
void initNeopixel(void);
