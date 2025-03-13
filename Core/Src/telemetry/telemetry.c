#include "stm32l4xx_hal.h"
#include "telemetry.h"

#define R2_SHUNT 0.22
#define R4_BATT 130E3
#define R9_BATT 10E3
#define R18_6V 30E3
#define R19_3V3 10E3
#define R20_5V 23.2E3
#define R21_6V 10E3
#define R22_3V3 3.3E3
#define R23_5V 10E3

#define countToVolts 3.3 / 4095.0
#define ADC_GAIN 100

typedef struct {
  float currentBATT;
  float voltageBATT;
  float voltage6V;
  float voltage5V;
  float voltage3V3;
} circuit_t;

extern ADC_HandleTypeDef hadc1;

static uint32_t adcValues[5];

static voltageDivider_t PWR_3V3 = {&adcValues[2], R19_3V3, R22_3V3};
static voltageDivider_t VIN_5V = {&adcValues[1], R20_5V, R23_5V};
static voltageDivider_t PWR_6V = {&adcValues[4], R18_6V, R21_6V};
static voltageDivider_t PWR_BATT = {&adcValues[3], R4_BATT, R9_BATT};

static circuit_t circuit;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
  circuit.voltage6V = adcToVoltage(&PWR_6V);
  circuit.voltage5V = adcToVoltage(&VIN_5V);
  circuit.voltage3V3 = adcToVoltage(&PWR_3V3);
  circuit.voltageBATT = adcToVoltage(&PWR_BATT);
  circuit.currentBATT = adcToCurrent();
}

void readADC() {
  HAL_ADC_Start_DMA(&hadc1, adcValues, 5);
}

float adcToVoltage(voltageDivider_t *voltageDivider) {
  float adcToVolt = *(voltageDivider->adcValue) * countToVolts;
  float current = adcToVolt / voltageDivider->resistor2;
  float totalVoltage = current * (voltageDivider->resistor1 + voltageDivider->resistor2);

  return totalVoltage;
}

float adcToCurrent() {
  float adcToVolt = adcValues[0] * countToVolts;

  return (adcToVolt / ADC_GAIN) / R2_SHUNT;
}
