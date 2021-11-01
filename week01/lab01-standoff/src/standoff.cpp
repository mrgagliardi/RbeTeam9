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
    piStandoffer.SetKp(0.3);
    piStandoffer.SetKd(0.01);
    float error = targetDistance - distance;
    float effort = piStandoffer.ComputeEffort(error);
    if(error < 2 && error > -2){
        rightEffort = 10;
        leftEffort = 10;
        return;
    }
    rightEffort = 30-effort;
    leftEffort = 30+effort;
    // if(10 - effort < -30){
    //     rightEffort = -30;
    // }
    // else if(10 - effort > 30){
    //     rightEffort = 30;
    // }
    // else{
    // rightEffort = 10-effort;
    // }
    // if(10 + effort > 30){
    //     leftEffort = 30;
    // }
    // else if(10 + effort < -30){
    //     leftEffort = -30;
    // }
    // else{
    //     leftEffort = 10+effort;
    // }
    Serial.print("Right Effort:");
    Serial.print(rightEffort);
    Serial.print(" Left Effort:");
    Serial.print(leftEffort);
    Serial.print("\n");

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