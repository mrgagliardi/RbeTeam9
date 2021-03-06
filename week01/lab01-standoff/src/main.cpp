#include <Arduino.h>
#include <RBE-200n-Lib.h>

#include "robot.h"
#include "hc-sr04.h"

Robot robot;

void setup() 
{
  Serial.begin(115200);

  delay(500);

  robot.init();
}

void loop()
{
  robot.loop();
}