// this file is the irrigation profile.

// it is generated after the irrigation controller evaluates the conditions

// it contains: 
// 1. whether irrigation is required
// 2. how long irrigation should last

// the relayController then executes that profile.

#ifndef IRRIGATION_PROFILE_H
#define IRRIGATION_PROFILE_H

struct IrrigationProfile
{
    bool shouldIrrigate;

    unsigned long durationMs;
};

#endif