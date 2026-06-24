//this data logger file generates the csv file (dataset) for machine learning implementation
#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include "../sensors/sensor_data.h"
#include "../control/irrigation_decision.h"
#include "../system/system_state.h"

class DataLogger
{
public:
    static void log(
        const SensorData& data,
        IrrigationDecision decision,
        SystemState state
    );
};

#endif



