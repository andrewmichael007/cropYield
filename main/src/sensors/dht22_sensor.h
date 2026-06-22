#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

class DHT22Sensor
{
public:
    bool begin();
    float readTemperature();
    float readHumidity();
};

#endif
