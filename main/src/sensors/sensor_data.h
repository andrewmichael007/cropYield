// this file defines the structure of the sensor data
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H
#include "sensor_status.h"


// defining the structure of the sensor data
struct SensorData
{
    float temperature;
    float humidity;
    float soilMoisture;
    float lightIntensity;

    unsigned long timestamp;

    bool valid;

    SensorStatus status;
};

#endif

