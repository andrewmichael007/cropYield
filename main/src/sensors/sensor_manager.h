// this is the sensor manager, it manages all sensors
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

// we include these files in other to manage the sensors
#include "sensor_data.h"
#include "dht22_sensor.h"
#include "soil_moisture_sensor.h"
// #include "bh1750_sensor.h"
#include "tsl2561_sensor.h"

class SensorManager
{
public: 
    bool begin();
    SensorData getSensorData();

private:
    DHT22Sensor dht22Sensor;
    SoilMoistureSensor soilMoistureSensor;
    // BH1750Sensor bh1750Sensor;
    TSL2561Sensor tsl2561Sensor;
};

#endif

