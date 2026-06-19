#include "irrigation_controller.h"

IrrigationDecision IrrigationController::evaluate( const SensorData& data)
{
    if(data.soilMoisture < 30 &&
       data.temperature > 30 &&
       data.humidity < 50)
    {
        return IrrigationDecision::IRRIGATE;
    }

    return IrrigationDecision::DO_NOT_IRRIGATE;
}