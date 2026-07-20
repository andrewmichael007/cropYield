//this source file shows how the actions of the relay controller would be carried out
// this is an active low relay after unit experimentation

#include <Arduino.h>
#include "relay_controller.h"

//defining the relay pin and valve pin
#define PUMP_RELAY_PIN 26
#define VALVE_RELAY_PIN 27

// this is an active low relay after unit experimentation

bool RelayController::begin()
{
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    pinMode(VALVE_RELAY_PIN, OUTPUT);

    stopIrrigation();

    return true;
}

void RelayController::startIrrigation()
{
    digitalWrite(PUMP_RELAY_PIN, LOW);
    digitalWrite(VALVE_RELAY_PIN, LOW);
}

void RelayController::stopIrrigation()
{
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    digitalWrite(VALVE_RELAY_PIN, HIGH);
}

//note: check the relays

// 1. can be active = low;
// meaning : high = off & low = on

// 2. can be active = high
// meaning : high = on & low = off
