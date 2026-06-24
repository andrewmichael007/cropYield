#include <Arduino.h>
#include "data_logger.h"

void DataLogger::log(
    const SensorData& data,
    IrrigationDecision decision,
    SystemState state
)
{
    Serial.print(millis());

    Serial.print(",");
    Serial.print(data.temperature);

    Serial.print(",");
    Serial.print(data.humidity);

    Serial.print(",");
    Serial.print(data.soilMoisture);

    Serial.print(",");
    Serial.print(data.lightIntensity);

    Serial.println();
}