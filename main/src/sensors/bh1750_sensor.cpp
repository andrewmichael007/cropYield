#include "bh1750_sensor.h"
#include <Wire.h>
#include <BH1750.h>


static BH1750 lightMeter;

bool BH1750Sensor::begin()
{
    Wire.begin();

    return lightMeter.begin();
}

float BH1750Sensor::readLux()
{
    return lightMeter.readLightLevel();
}