#include "system_controller.h"

SystemController::SystemController()
{
    currentState = SystemState::MONITORING;
}

SystemState SystemController::getState()
{
    return currentState;
}

void SystemController::setState(
    SystemState state)
{
    currentState = state;
}