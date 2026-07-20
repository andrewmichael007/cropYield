#include "soil_moisture_sensor.h"
#include <Arduino.h>

#define MOISTURE_PIN 32

bool SoilMoistureSensor::begin()
{
    pinMode(MOISTURE_PIN, INPUT);
    return true;
}

int SoilMoistureSensor::readRaw()
{
    return analogRead(MOISTURE_PIN);
}

//calculation of the soil moisture percentage

// current position in range / total range * 100

//reading the percentage
float SoilMoistureSensor::readPercentage()
{
    // 1. we store the value of the readRaw function in raw container
    int raw = readRaw();

    float percentage =
        ((float)(dryValue - raw) / (dryValue - wetValue)) * 100.0;

    percentage = constrain(percentage, 0, 100);

    return percentage;                                                                                                                                                                                                                                                                                              
}
