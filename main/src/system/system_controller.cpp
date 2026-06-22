//main implementation of how the control of the state system is done
#include <Arduino.h>

#include "system_controller.h"

SystemController::SystemController()
{
    currentState = SystemState::MONITORING;

    stateStartTime =+ millis();
}

SystemState SystemController::getState()
{
    return currentState;
}

void SystemController::setState(SystemState state)
{
    currentState = state;

    stateStartTime = millis();
}

unsigned long SystemController::getStateStartTime()
{
    return stateStartTime;
}