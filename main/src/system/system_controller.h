#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "system_state.h"

class SystemController
{
public:
    SystemController();
    SystemState getState();
    void setState(SystemState state);

private:
    SystemState currentState;
};

#endif