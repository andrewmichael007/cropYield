#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

// creating a blueprint for soil moisture sensor basically what the soil moisture can do
class SoilMoistureSensor
{
public: 
    bool begin();
    int readRaw();
    float readPercentage();

// these are real calculated  readings of the capacitive soil moisture sensor
private:
    const int dryValue = 2560;
    const int wetValue = 1140;
};

#endif