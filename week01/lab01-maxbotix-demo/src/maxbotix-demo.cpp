// /*
//  * Code for interfacing with the MCP3002 ADC using the SPI bus on the ESP32.
//  * This code is written to use specific pins:
//  * 
//  * MISO = 19
//  * MOSI = 23
//  * SCLK = 18
//  * SS   = 5
//  * 
//  * RX   = 16 (inverted for MaxBotix!)
//  * (best not to use TX-17 for anything else, since the uart will likely conflict with pin operation)
//  * 
//  * pulse width is read on: 35
//  * ultrasonic control pin: 2
//  */

// #include <Arduino.h>
// #include <SPI.h>

// #include <MaxBotix.h>

// void setup()
// {
//   delay(1000);
  
//   Serial.begin(115200);
//   Serial.println("Velkommen til");

//   mb_ez1.init();
// }

// int counter = 0;

// void loop() 
// {
//   /**
//    * For this demo, we key everything on the ascii output, since
//    * that is the last thing that the sensor prepares for output.
//    * Everything else should be ready at that point.
//    */
//   uint16_t asciiResponse = mb_ez1.readASCII();
  
//   if(asciiResponse) 
//   {
  
//   if (counter > 200) {
//     return;
//   }

//   uint32_t pulseLen = mb_ez1.checkEcho();
//   if (pulseLen <= 0){
//     return;
//   }

//     Serial.print(asciiResponse);
//     Serial.print('\t');
//     float asciiResponceCM = (asciiResponse + 1.5)/0.368;
//     Serial.print(asciiResponceCM); //TODO: change this line to output distance in cm
//     Serial.print('\t');

//     Serial.print(pulseLen);
//     Serial.print('\t');
//     float pulseLenCm = (pulseLen - 351) / 44.067;
//     Serial.print(pulseLenCm); //TODO: change this line to output distance in cm
//     Serial.print('\t');

//     //passing true ignores the timer and forces a reading
//     //from the datasheet, if the serial output is ready, the voltage is ready
//     uint16_t adcReading = mb_ez1.readMCP3002(true);
//     Serial.print(adcReading); 
//     Serial.print('\t');
//     float adcReadingCm = (adcReading + 4.53) / 0.806;
//     Serial.print(adcReadingCm); //TODO: change this line to output distance in cm
//     Serial.print('\n');
//     counter ++;
//   }
// }




// #include <Arduino.h>
// #include <SPI.h>

// #include <hc-sr04.h>

// void setup()
// {
//   delay(1000);
  
//   Serial.begin(115200);
//   Serial.println("Velkommen til");

//   irSensor.init();
// }

// int counter = 0;
// unsigned long prevMicro = micros();

// void loop() 
// {
//   /**
//    * For this demo, we key everything on the ascii output, since
//    * that is the last thing that the sensor prepares for output.
//    * Everything else should be ready at that point.
//    */
//   //uint16_t asciiResponse = irSensor.readASCII();
  
//   //if(asciiResponse) 
//   // {
  
//   if (counter > 200) {
//     return;
//   }
//   unsigned long current = micros();
//   if(current > prevMicro + 8000){
//       irSensor.checkPingTimer();
//       prevMicro = current;
//   }

//   uint32_t pulseLen = irSensor.checkEcho();

//     //Serial.print(asciiResponse);
//     //Serial.print('\t');
//     //float asciiResponceCM = (asciiResponse + 1.5)/0.368;
//     //Serial.print(asciiResponceCM); //TODO: change this line to output distance in cm

//     Serial.print(pulseLen);
  

//     //passing true ignores the timer and forces a reading
//     //from the datasheet, if the serial output is ready, the voltage is ready
//     //uint16_t adcReading = mb_ez1.readMCP3002(true);
//     //Serial.print(adcReading); 
//     //Serial.print('\t');
//     //float adcReadingCm = (adcReading + 4.53) / 0.806;
//     //Serial.print(adcReadingCm); //TODO: change this line to output distance in cm
//     Serial.print('\n');
//     counter ++;
//   //}
// }

#include <Arduino.h>
#include <SPI.h>

#include <IRSensor.h>
#include <Filter.h>

AveragingFilter averagingFilter(30);

void setup()
{
  delay(1000);
  
  Serial.begin(115200);
  Serial.println("Velkommen til");

  irSensor.init();
}

int counter = 0;
unsigned long prevMicro = micros();

void loop() 
{
  /**
   * For this demo, we key everything on the ascii output, since
   * that is the last thing that the sensor prepares for output.
   * Everything else should be ready at that point.
   */
  //uint16_t asciiResponse = irSensor.readASCII();
  
  //if(asciiResponse) 
  // {
  
  // if (counter > 2000) {
  //   return;
  // }
  unsigned long current = micros();
  if(current > prevMicro + 8000){
      irSensor.checkPingTimer();
      prevMicro = current;
  }

  //uint32_t pulseLen = irSensor.checkEcho();
  //  if(pulseLen <=  0){
  //    return;
  //  }

    //Serial.print(asciiResponse);
    //Serial.print('\t');
    //float asciiResponceCM = (asciiResponse + 1.5)/0.368;
    //Serial.print(asciiResponceCM); //TODO: change this line to output distance in cm

    //Serial.print(pulseLen);
  

    //passing true ignores the timer and forces a reading
    //from the datasheet, if the serial output is ready, the voltage is ready
    uint16_t adcReading = irSensor.readMCP3002(true);
    Serial.print(adcReading); 
    Serial.print('\t');
    float adcReadingCm = 4452.0/(adcReading-167.0);
    Serial.print(adcReadingCm); //TODO: change this line to output distance in cm
    Serial.print('\t');
    Serial.print(averagingFilter.addAndReturnAverage(adcReading));
    Serial.print('\t');
    Serial.print(averagingFilter.addAndReturnMedian(adcReading));
    Serial.print('\n');

    counter ++;
  //}
}
