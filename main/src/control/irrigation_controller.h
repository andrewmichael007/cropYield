#ifndef IRRIGATION_CONTROLLER_H
#define IRRIGATION_CONTROLLER_H

#include "../sensors/sensor_data.h"
#include "irrigation_profile.h"

class IrrigationController
{
public:
    IrrigationProfile evaluate(const SensorData& data);
};

#endif


