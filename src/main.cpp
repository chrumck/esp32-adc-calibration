#include <Arduino.h>
#include <driver/dac.h>

#define SERIAL_BAUD_RATE 115200
#define V_IN_PIN 35
#define V_OUT_PIN DAC_CHANNEL_1 // pin 25 on ESP32

#define ANALOG_READ_COUNT 100
#define ANALOG_READ_NUM 980
#define ANALOG_READ_DEN 1000
#define ANALOG_READ_OFFSET (-20)

#define readAdcMilliVolts(_pin) \
   ((int32_t)analogReadMilliVolts(_pin) * ANALOG_READ_NUM / ANALOG_READ_DEN + ANALOG_READ_OFFSET)

// float Results[4096];
// float Res2[4095 * 5];

void testVoltage() {
  int32_t v_ADC = 0;
  for (int i = 0; i < ANALOG_READ_COUNT; i++) {
    v_ADC += readAdcMilliVolts(V_IN_PIN);
  }

  v_ADC /= ANALOG_READ_COUNT;
  Serial.printf(">v_ADC:%d\n", v_ADC);

  // for (int i = 0; i < 256; i++) {
  //   dac_output_voltage(V_OUT_PIN, (i) & 0xff);
  //   uint32_t v_REF = i * 3300 / 255;
  //   Serial.printf(">v_REF:%d\n", v_REF);

  //   delayMicroseconds(100);

  //   int32_t v_ADC = 0;
  //   for (int i = 0; i < ANALOG_READ_COUNT; i++) {
  //     v_ADC += readAdcMilliVolts(V_IN_PIN);
  //   }

  //   v_ADC /= ANALOG_READ_COUNT;
  //   Serial.printf(">v_ADC:%d\n", v_ADC);

  //   int delta = v_ADC - v_REF;
  //   Serial.printf(">delta:%d\n", delta);
  // }
}

void setup() {
  dac_output_enable(V_OUT_PIN);

  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  testVoltage();
  delayMicroseconds(500000);
  // delayMicroseconds(5000000);
}

//   float r;
//   int x, delta, deltaMin, deltaMinIndex;
//   Serial.println("Test Linearity ...");
//   for (int i = 0; i < 500; i++) {
//     if ((i % 100) == 0) Serial.println(i);
//     testVoltage(i);
//   }
//   for (int i = 0; i < 256; i++) {
//     r = Results[i * 16] + 0.5;
//     x = (int)r;
//     Serial.print(i * 16); Serial.print(" "); Serial.println(Results[i * 16]);
//   }

//   Serial.println("Calculate interpolated values ..");

//   for (int i = 0; i < 256; i++) {
//     for (int j = 1; j < 16; j++) {
//       Results[i * 16 + j] = Results[i * 16] + (Results[(i + 1) * 16] - Results[(i) * 16]) * (float)j / (float)16.0;
//     }
//   }

//   for (int i = 0; i < 4096; i++) {
//     Serial.print(i); Serial.print(" "); Serial.println(Results[i]);
//   }

//   for (int i = 0; i < 4096; i++) {
//     Results[i] = 0.5 + Results[i];
//   }

//   for (int i = 0; i < 4096; i++) {
//     Serial.print(i); Serial.print(" "); Serial.println(Results[i], 6);
//   }

//   for (int i = 0; i < 4096; i++) {
//     for (int j = 0; j < 5; j++) {
//       Res2[i * 5 + j] = Results[i] + (Results[(i + 1)] - Results[i]) * (float)j / (float)10.0;
//     }
//   }

//   for (int i = 0; i < (5 * 4096); i++) {
//     Serial.print(i); Serial.print(" "); Serial.println(Res2[i], 6);
//   }

//   for (int i = 1; i < 4096; i++) {
//     float diff, minDiff;
//     int index;
//     minDiff = 99999;
//     for (int j = 0; j < (5 * 4096); j++) {
//       diff = abs((float)(i)-Res2[j]);
//       if (diff < minDiff) {
//         minDiff = diff;
//         index = j;
//       }
//     }

//     Results[i] = index;
//   }

//   for (int i = 0; i < (4096); i++) {
//     Serial.print(i); Serial.print(" "); Serial.println(Results[i] / 5, 6);
//     Results[i] /= 5;
//   }

// #ifdef GRAPH   

//   while (1) {
//     int a1;
//     for (int i = 2; i < 256;i++) {
//       dac_output_voltage(V_OUT_PIN, (i) & 0xff);
//       delayMicroseconds(100);
//       adcStart(V_IN_PIN);
//       delayMicroseconds(100);
//       a1 = adcEnd(V_IN_PIN);
//       float r = Results[a1];
//       Serial.print(i * 16); Serial.print(" "); Serial.println(r);
//     }
//   }

// #else
//   for (int i = 0; i < 10; i++) Serial.println();
//   Serial.println(" float ADC_LUT[4096] = { 0,");
//   for (int i = 1; i < 4095; i++) {
//     Serial.print(Results[i], 4); Serial.print(",");
//     if ((i % 16) == 0) Serial.println();
//   }
//   Serial.println(Results[4095]); Serial.println("} ;");


//   for (int i = 0; i < 10; i++) Serial.println();
//   Serial.println(" int ADC_LUT[4096] = { 0,");
//   for (int i = 1; i < 4095; i++) {
//     Serial.print((int)Results[i]); Serial.print(",");
//     if ((i % 16) == 0) Serial.println();
//   }
//   Serial.println((int)Results[4095]); Serial.println("} ;");


//   while (1);

// #endif
