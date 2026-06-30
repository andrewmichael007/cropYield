//this contains one experimental observation
//one record, exactly one row of the dataset
#ifndef LOG_RECORD_H
#define LOG_RECORD_H

//including the sensor data, irrigation decision , 
// and system state files in order to be able to log data
#include "../sensors/sensor_data.h"
#include "../control/irrigation_decision.h"
#include "../system/system_state.h"


struct LogRecord
{
    unsigned long timestamp;

    SensorData sensorData;

    IrrigationDecision decision;

    SystemState state;
};

#endif
