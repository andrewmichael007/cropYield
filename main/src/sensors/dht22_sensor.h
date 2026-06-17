#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

class DHTSensor
{
public:
    bool begin();

    float readTemperature();

    float readHumidity();
};

#endif
