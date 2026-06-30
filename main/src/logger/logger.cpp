//this is the implementation of the  logger interface
#include <Arduino.h>
#include "logger.h"

//implementation of the info log
void Logger::info(
    const char* message
)

{
    Serial.print("[INFO] ");

    Serial.println(message);
}

//implementation of warning log
void Logger::warning(
    const char* message
)

{
    Serial.print("[WARNING] ");

    Serial.println(message);
}

//implementation of error log
void Logger::error(
    const char* message
)
{
    Serial.print("[ERROR] ");

    Serial.println(message);
}

//implementation of state log
void Logger::state(
    const char* message
)
{
    Serial.print("[STATE] ");

    Serial.println(message);
}