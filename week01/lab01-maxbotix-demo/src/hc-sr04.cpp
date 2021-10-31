#include "hc-sr04.h"

#define ECHO_PIN 18       //for pinging -- not a great choice since this can hamper uploading
#define TRIG_PIN 5    //for reading pulse

#define MB_WINDOW_DUR 50    //ms
unsigned long prev;
uint16_t echoLength = 0;

// Here is the mb_ez1 object that we declared as in extern in the .h file
HRUltrasonic hrUltrasonic;

//ISR for reading the echoes. Or is it echos?
void ISR_HRUltrasonic(void)
{
    hrUltrasonic.MB_ISR();
}

// Constructor. Nothing to see here. Move along.
HRUltrasonic::HRUltrasonic(void) {}

// Default init engages all interfaces
void HRUltrasonic::init(void)
{
    init(USE_ADC | USE_UART | USE_ECHO | USE_CTRL_PIN);
    prev = millis();

}

// Allows the user to select the interface
void HRUltrasonic::init(uint8_t interfaces)
{
        // assert ECHO pin is an input
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    attachInterrupt(ECHO_PIN, ISR_HRUltrasonic, CHANGE);

}


/**
 * checkPingTimer check to see if it's time to send a new ping.
 * You must select USE_CTRL_PIN in init() for this to work.
 */
uint8_t HRUltrasonic::checkPingTimer(void)
{
    //check if we're ready to ping
    if(millis() - lastPing >= pingInterval)
    {
        pulseEnd = pulseStart = 0;

        //clear out any leftover states
        state = 0;

        Serial.print("in if");

        lastPing = millis();    //not perfectly on schedule, but safer and close enough
        lastADCread = lastPing; //this will make sure the proper interval is past before we read the ADC

        digitalWrite(TRIG_PIN, HIGH); //commands a ping; leave high for the duration
        delayMicroseconds(10); //datasheet says hold HIGH for >20us; we'll use 30 to be 'safe'
        digitalWrite(TRIG_PIN, LOW); //unclear if pin has to stay HIGH
    }

    return state;
}

uint16_t HRUltrasonic::checkEcho(void)
{
    echoLength = pulseEnd - pulseStart;
    return echoLength;
}



void HRUltrasonic::checkPin(uint8_t checkPingTimer){ 
    unsigned long current = millis();
    if (current > prev + 10) {
        digitalWrite(TRIG_PIN, LOW);
        prev = current;
    }
    else{
        digitalWrite(TRIG_PIN, HIGH);
    }
}

//ISR for echo pin
void HRUltrasonic::MB_ISR(void)
{
    if(digitalRead(ECHO_PIN))  //transitioned to HIGH
    {
        pulseStart = micros();
    }

    else                        //transitioned to LOW
    {
        pulseEnd = micros();
        state |= ECHO_RECD;
    } 
}

/**
 * EXERCISE: Write a getDistance() function for the distance method of your choice.
 * 
 * getDistance should return true whenever there is a new reading, and put the result
 * in distance, which is _passed by reference_ so that you can "return" a value
 */
bool HRUltrasonic::getDistance(float& distance)
{
    distance = -99;
    return false;
}