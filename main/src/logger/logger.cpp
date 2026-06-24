//this is the implementation of the  logger interface
#include <Arduino.h>
#include "logger.h"

void Logger::info(
    const char* message
)

{
    Serial.print("[INFO] ");

    Serial.println(message);
}

void Logger::warning(
    const char* message
)

{
    Serial.print("[WARNING] ");

    Serial.println(message);
}

void Logger::error(
    const char* message
)
{
    Serial.print("[ERROR] ");

    Serial.println(message);
}

void Logger::state(
    const char* message
)
{
    Serial.print("[STATE] ");

    Serial.println(message);
}