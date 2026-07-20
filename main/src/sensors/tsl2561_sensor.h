#ifndef TSL2561_SENSOR_H
#define TSL2561_SENSOR_H

class TSL2561Sensor
{
public:
    bool begin();
    float readLux();
};

#endif