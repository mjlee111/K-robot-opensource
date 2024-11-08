#include <Arduino.h>

#define ADC1_PIN A0
#define ADC2_PIN A1
#define ADC3_PIN A2
#define ADC4_PIN A7

#define POTENTIOMETER1_PIN A4
#define POTENTIOMETER2_PIN A5
#define POTENTIOMETER3_PIN A6

unsigned int ADC_v[7] = {0, 0, 0, 0, 0, 0, 0};
unsigned int POTENTIOMETER[3] = {0, 0, 0};
bool PSD_DETECTED[3] = {false, false, false};

void initializeADC()
{
  pinMode(ADC1_PIN, INPUT);
  pinMode(ADC2_PIN, INPUT);
  pinMode(ADC3_PIN, INPUT);
  pinMode(ADC4_PIN, INPUT);

  pinMode(POTENTIOMETER1_PIN, INPUT);
  pinMode(POTENTIOMETER2_PIN, INPUT);
  pinMode(POTENTIOMETER3_PIN, INPUT);
}

int readADC(int pin)
{
  return analogRead(pin);
}

int getADC(int pin)
{
  return ADC_v[pin];
}

void updateADC()
{
  ADC_v[0] = readADC(ADC1_PIN);
  ADC_v[1] = readADC(ADC2_PIN);
  ADC_v[2] = readADC(ADC3_PIN);
  ADC_v[3] = readADC(ADC4_PIN);

  ADC_v[4] = readADC(POTENTIOMETER1_PIN);
  ADC_v[5] = readADC(POTENTIOMETER2_PIN);
  ADC_v[6] = readADC(POTENTIOMETER3_PIN);

  POTENTIOMETER[0] = ADC_v[4];
  POTENTIOMETER[1] = ADC_v[5];
  POTENTIOMETER[2] = ADC_v[6];

  Serial.println();

  Serial.print("ADC1: ");
  Serial.println(ADC_v[0]);
  Serial.print("ADC2: ");
  Serial.println(ADC_v[1]);
  Serial.print("ADC3: ");
  Serial.println(ADC_v[2]);
  Serial.print("ADC4: ");
  Serial.println(ADC_v[3]);

  Serial.print("POT1: ");
  Serial.println(POTENTIOMETER[0]);
  Serial.print("POT2: ");
  Serial.println(POTENTIOMETER[1]);
  Serial.print("POT3: ");
  Serial.println(POTENTIOMETER[2]);

  Serial.println();
}

void updatePSD()
{
  PSD_DETECTED[0] = ADC_v[0] > POTENTIOMETER[0];
  PSD_DETECTED[1] = ADC_v[1] > POTENTIOMETER[1];
  PSD_DETECTED[2] = ADC_v[2] > POTENTIOMETER[2];
}

bool getPSD(int pin)
{
  return PSD_DETECTED[pin];
}
