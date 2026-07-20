#include "tsl2561_sensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

static Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

bool TSL2561Sensor::begin()
{
    Wire.setTimeOut(1000);

    if (!tsl.begin())
    {
        return false;
    }

    tsl.enableAutoRange(true);
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);

    return true;
}

float TSL2561Sensor::readLux()
{
    sensors_event_t event;
    tsl.getEvent(&event);

    if (event.light)
    {
        return event.light;
    }

    return NAN;
}