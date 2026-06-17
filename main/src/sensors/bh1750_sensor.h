#ifndef BH1750_SENSOR_H
#define BH1750_SENSOR_H

class BH1750Sensor
{
public:
    bool begin();
    float readLux();
};

#endif
