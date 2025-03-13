typedef struct {
  float currentBATT;
  float voltageBATT;
  float voltage6V;
  float voltage5V;
  float voltage3V3;
} circuit_t;

static circuit_t circuit;
static uint32_t adcValues[5];

float adcTo3V3() {
  float adcToVolt = adcValues[2] * (3.3 / 4095);
  float current = adcToVolt / 3.3E3;
  float totalVoltage = current * (10E3 + 3.3E3);

  return totalVoltage;
}

float adcTo5V() {
  float adcToVolt = adcValues[1] * (3.3 / 4095);
  float current = adcToVolt / 10E3;
  float totalVoltage = current * (23.2E3 + 10E3);

  return totalVoltage;
}

float adcTo6V() {
  float adcToVolt = adcValues[4] * (3.3 / 4095);
  float current = adcToVolt / 10E3;
  float totalVoltage = current * (30E3+10E3);

  return totalVoltage;
}

float adcToBATT() {
  float adcToVolt = adcValues[3] * (3.3 / 4095);
  float current = adcToVolt / 10E3;
  float totalVoltage = current * (130E3+10E3);

  return totalVoltage;
}

float adcToCurrent() {
  float adcToVolt = adcValues[0] * (3.3 / 4095);
  return (adcToVolt / 100.0) / 0.22;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
  circuit.voltage6V = adcTo6V();
  circuit.voltage5V = adcTo5V();
  circuit.voltage3V3 = adcTo3V3();
  circuit.voltageBATT = adcToBATT();
  circuit.currentBATT = currentSense();
}
