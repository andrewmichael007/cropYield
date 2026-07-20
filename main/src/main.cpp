// original main.cpp
//including headers
#include <Arduino.h>

#include "sensors/sensor_manager.h"

//including the control files+
#include "control/irrigation_controller.h"
#include "control/irrigation_profile.h"
#include "control/relay_controller.h"

#include "system/system_controller.h"

//including logger  the files
#include "logger/logger.h"
#include "logger/log_record.h"
#include "logger/data_logger.h"

//including storage files
#include "storage/sd_storage.h"

//including config file
#include "../include/config.h"

//creating global objects
//... later these methods would be called on these objects
SensorManager sensorManager;

IrrigationController irrigationController;

RelayController relayController;

SystemController systemController;

SDStorage sdStorage;

IrrigationProfile currentProfile;

void setup()
{
    Serial.begin(115200);

    Logger::info("System Startup");

    //call the begin function on sensorManager object
    sensorManager.begin();

    //call the begin function on relayController object
    relayController.begin();

    //initializing SD card

    //check if sdStorage.begin is false
    if(sdStorage.begin())

    //log info
    {
        Logger::info(
            "SD Card Ready"
        );
    }

    //else, log error
    else
    {
        Logger::error(
            "SD Card Initialization Failed"
        );
    }   

    //expected outpt
    // [INFO] System Startup

    // [INFO] SD Card Ready
}

void loop()
{
    //switch : main state, we use .getState() function to get state
    switch
    (
        systemController.getState()
    )

    {
        //case 1: if the system is in monitoring state
        case SystemState::MONITORING:
        {
            //we get sensor data and store in data
            SensorData data = sensorManager.getSensorData();

            // is data valid ? if no ...
            if(!data.valid)
            {
                Logger::error(
                    "Sensor Failure"
                );

                systemController.setState(
                    SystemState::FAULT
                );

                break;
            }
            
            // .. else if data is valid: 
            //we set currentProfile to irrigationController
            currentProfile = irrigationController.evaluate(data);

            if(currentProfile.shouldIrrigate)
            {
                relayController.startIrrigation();

                Logger::info(
                    "Irrigation Started"
                );

                systemController.setState( SystemState::IRRIGATING );

                Logger::state(
                    "IRRIGATING"
                );
            }

        
            //creating a log record after evaluating
            LogRecord record;

            record.timestamp = millis();

            record.sensorData = data;

            record.decision = currentProfile.decision;

            record.state = systemController.getState();
        
            //building csv file
            String csv = DataLogger::buildCSV(record);

            //saving the dataset file
            if(
                !sdStorage.append(
                    csv.c_str()
                )
            )
            {
                Logger::error(
                    "Dataset Write Failed"
                );
            }

            break;
        }

        //case 2:
        case SystemState::IRRIGATING:
        {
            if( millis() - systemController.getStateStartTime() >= currentProfile.durationMs )
            
            {
                relayController.stopIrrigation();

                systemController.setState(SystemState::SETTLING);
            }

            break;
        }

        //case 3: 
        case SystemState::SETTLING:
        {
            if( millis() - systemController.getStateStartTime() >= SETTLING_PERIOD_MS )

            {
                systemController.setState( SystemState::MONITORING );

                Logger::state(
                    "MONITORING"
                );
            }

            break;
        }

        //case 4
        case SystemState::FAULT:
        {
            relayController.stopIrrigation();

            break;
        }
    }
}


// temporal main.cpp for testing DHT22 sensor
// #include <Arduino.h>
// #include "sensors/dht22_sensor.h"

// DHT22Sensor dhtSensor;

// void setup()
// {
//     Serial.begin(115200);
//     dhtSensor.begin();
// }

// void loop()
// {
//     Serial.println("==========");

//     Serial.print("Temperature: ");
//     Serial.println(dhtSensor.readTemperature());

//     Serial.print("Humidity: ");
//     Serial.println(dhtSensor.readHumidity());

//     delay(2000);
// }


// // temporal main.cpp for testing BH1750

// #include <Arduino.h>
// #include <Wire.h>
// #include <BH1750.h>

// BH1750 lightMeter;

// void setup()
// {
//     Serial.begin(115200);

//     Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22

//     if (lightMeter.begin())
//     {
//         Serial.println("BH1750 initialized successfully");
//     }
//     else
//     {
//         Serial.println("Error initializing BH1750");
//     }
// }

// void loop()
// {
//     float lux = lightMeter.readLightLevel();

//     Serial.println("==========");
//     Serial.print("Light: ");
//     Serial.print(lux);
//     Serial.println(" lx");

//     delay(2000);
// }


//new test code for TSL2561 light intensity sensor 

// Note: there was a bug in this code, another version is written below

// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_TSL2561_U.h>

// Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// void setup()
// {
//     Serial.begin(115200);
//     Wire.begin(21, 22);

//     if (tsl.begin())
//     {
//         Serial.println("TSL2561 initialized successfully");
//     }
//     else
//     {
//         Serial.println("Error initializing TSL2561");
//     }
// }

// void loop()
// {
//     sensors_event_t event;
//     tsl.getEvent(&event);

//     Serial.println("==========");
//     if (event.light)
//     {
//         Serial.print("Light: ");
//         Serial.print(event.light);
//         Serial.println(" lx");
//     }
//     else
//     {
//         Serial.println("Sensor overload or no reading");
//     }

//     delay(2000);
// }


// second version of light intensity sensor test code

// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_TSL2561_U.h>

// Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// void setup()
// {
//     Serial.begin(115200);
//     Wire.begin(21, 22);
//     Wire.setTimeOut(1000); // extend I2C timeout to 1000ms

//     if (tsl.begin())
//     {
//         Serial.println("TSL2561 initialized successfully");

//         tsl.enableAutoRange(true);
//         tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS); // longer, more stable read
//     }
//     else
//     {
//         Serial.println("Error initializing TSL2561");
//     }
// }

// void loop()
// {
//     sensors_event_t event;
//     tsl.getEvent(&event);

//     Serial.println("==========");
//     if (event.light)
//     {
//         Serial.print("Light: ");
//         Serial.print(event.light);
//         Serial.println(" lux");
//     }
//     else
//     {
//         Serial.println("Sensor overload or no reading");
//     }

//     delay(2000);
// }

// I2C Scanner - temporal main.cpp

// #include <Arduino.h>
// #include <Wire.h>

// void setup()
// {
//     Serial.begin(115200);
//     Wire.begin(21, 22);
//     delay(1000);
//     Serial.println("I2C Scanner starting...");
// }

// void loop()
// {
//     byte count = 0;
//     Serial.println("Scanning...");

//     for (byte address = 1; address < 127; address++)
//     {
//         Wire.beginTransmission(address);
//         byte error = Wire.endTransmission();

//         if (error == 0)
//         {
//             Serial.print("Device found at address 0x");
//             if (address < 16) Serial.print("0");
//             Serial.println(address, HEX);
//             count++;
//         }
//     }

//     if (count == 0) Serial.println("No I2C devices found");
//     else { Serial.print(count); Serial.println(" device(s) found"); }

//     delay(3000);
// }


// temporal main.cpp for testing Soil Moisture Sensor

// #include <Arduino.h>
// #include "sensors/soil_moisture_sensor.h"

// SoilMoistureSensor soilMoistureSensor;

// void setup()
// {
//     Serial.begin(115200);
//     soilMoistureSensor.begin();
// }

// void loop()
// {
//     int raw = soilMoistureSensor.readRaw();
//     float percentage = soilMoistureSensor.readPercentage();

//     Serial.println("==========");
//     Serial.print("Raw Value: ");
//     Serial.println(raw);
//     Serial.print("Moisture (%): ");
//     Serial.println(percentage);

//     delay(2000);
// }




// temporal main.cpp for testing Relay

// #include <Arduino.h>
// #include "control/relay_controller.h"

// RelayController relayController;

// void setup()
// {
//     Serial.begin(115200);
//     relayController.begin();
//     Serial.println("Relay Controller initialized");
// }

// void loop()
// {
//     Serial.println("==========");
//     Serial.println("Starting irrigation (relay ON and valve should OPEN)");
//     relayController.startIrrigation();
//     delay(5000);

//     Serial.println("Stopping irrigation (relay OFF and valve should CLOSE)");
//     relayController.stopIrrigation();
//     delay(5000);
// }