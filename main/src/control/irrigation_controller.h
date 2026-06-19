#ifndef IRRIGATION_CONTROLLER_H
#define IRRIGATION_CONTROLLER_H

#include "../sensors/sensor_data.h"
#include "irrigation_decision.h"

class IrrigationController
{
public:
    IrrigationDecision evaluate(const SensorData& data);
};

#endif


