#include "standoff.h"
#include "ir_codes.h"

void StandoffController::processDistanceReading(float distance)
{
    float error = targetDistance - distance;
    float effort = piStandoffer.CalcEffort(error);

    leftEffort = effort;
    rightEffort = effort;

    // Serial.print(targetDistance);
    // Serial.print('\t');
    // Serial.print(distance);
    // Serial.print('\t');
    // Serial.print(error);
    // Serial.print('\t');
    // Serial.print(effort);
    // Serial.print('\t');
    // Serial.print(leftEffort);
    // Serial.print('\t');
    // Serial.print(rightEffort);
    // Serial.print('\t');
}
void StandoffController::processDistanceReadingUltra(float distance)
{
    piStandoffer.SetKp(0.8);
    piStandoffer.SetKd(0);
    float error = targetDistance - distance;
    float effort = piStandoffer.CalcEffort(error);
    if(error < 8 && error > -8){
        leftEffort = 10;
        rightEffort = 10;
    }
    else if(error > 0){
        rightEffort = 0;
        leftEffort = -effort;
    }
    else{
        leftEffort = 0;
        rightEffort = -effort;
    }

    // Serial.print(targetDistance);
    // Serial.print('\t');
    // Serial.print(distance);
    // Serial.print('\t');
    // Serial.print(error);
    // Serial.print('\t');
    // Serial.print(effort);
    // Serial.print('\t');
    // Serial.print(leftEffort);
    // Serial.print('\t');
    // Serial.print(rightEffort);
    // Serial.print('\t');
}

void StandoffController::handleKeyPress(int16_t key)
{
    switch(key)
    {
        case CHplus:
            targetDistance += 10;
            break;

        case CHminus:
            targetDistance -= 10;
            break;

        default:
            if(key >= NUM_0 && key <= NUM_9)
            {
                //TODO: implement standoff distance
            }
            break;
    }
}