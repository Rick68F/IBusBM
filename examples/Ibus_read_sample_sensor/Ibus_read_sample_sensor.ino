#include <IBusBM.h>

/* Simple read of the 10 channel and sending an arbitrary voltage value */

/* tested with STM32 F411CEU */

#ifdef ARDUINO_ARCH_STM32

#ifdef ARDUINO_GENERIC_F411CEUX  // Serial2
HardwareSerial Serial1(USART1);  // or HardWareSerial Serial1 (PA3, PA2);
#endif

#ifndef ARDUINO_GENERIC_F411CEUX  // Serial2
HardwareSerial Serial2(USART2);   // or HardWareSerial Serial2 (PA9, PA10);
#endif

#endif

IBusBM IBusData;
IBusBM IBusSensor;

#define NB_CANNAUX 10

void setup() {

  Serial.begin(115200);
  delay(3000);
  Serial.println("Starting");

  IBusSensor.begin(Serial1);
  IBusData.begin(Serial2);
  IBusSensor.addSensor(IBUSS_INTV);  // add voltage sensor

  Serial.println("Wait for receiver");
  while (IBusData.cnt_rec == 0) delay(100);
  Serial.println("Init done");
}

void loop() {
  //  static int j = 0;
  for (int i = 0; i < NB_CANNAUX; i++) {
    uint16_t value = IBusData.readChannel(i);
    Serial.print("c");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println("");
  IBusSensor.setSensorMeasurement(1, 1000+random(1,100));  // 10.00 V
}
