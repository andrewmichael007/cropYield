// original main.cpp
#include <Arduino.h>
#include "sensors/sensor_manager.h"

#include "control/irrigation_controller.h"
#include "control/irrigation_profile.h"

#include "control/relay_controller.h"

#include "system/system_controller.h"

#include "../include/config.h"


//creating objects
//... later these methods would be called on these objects
SensorManager sensorManager;

IrrigationController irrigationController;

RelayController relayController;

SystemController systemController;

IrrigationProfile currentProfile;


void setup()
{
    Serial.begin(115200);

    //call the begin function on sensorManager object
    sensorManager.begin();

    //call the begin function on relayController object
    relayController.begin();
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
                //raise a critical error message
                Serial.println("[CRITICAL] Sensor Failure" );

                //... and set the system state to fault
                systemController.setState( SystemState::FAULT);

                break;
            }
            
            // .. else if data is valid: 
            //we set currentProfile to irrigationController
            currentProfile = irrigationController.evaluate(data);

            if(currentProfile.shouldIrrigate)
            {
                relayController.startIrrigation();

                systemController.setState( SystemState::IRRIGATING );
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


// temporal main.cpp for testing

// #include <Arduino.h>

// #include "sensors/dht22_sensor.h"
// #include "sensors/soil_moisture_sensor.h"

// DHTSensor dhtSensor;
// SoilMoistureSensor SoilMoistureSensor;

// void setup()
// {
//     Serial.begin(115200);

//     dhtSensor.begin();
//     SoilmoistureSensor.begin();
// }

// void loop()
// {
//     Serial.println("==========");

//     Serial.print("Temperature: ");
//     Serial.println(dhtSensor.readTemperature());

//     Serial.print("Humidity: ");
//     Serial.println(dhtSensor.readHumidity());

//     Serial.print("Raw Moisture: ");
//     Serial.println(SoilMoistureSensor.readRaw());

//     Serial.print("Moisture (%): ");
//     Serial.println(SoilMoistureSensor.readPercentage());

//     delay(2000);
// }


// void loop()
// {   
//     // we create an object, data on SensorData class of which we run the getSensorData() method
//     SensorData data = sensorManager.getSensorData();

//     IrrigationDecision decision = irrigationController.evaluate(data);

//     //checking the validity of the data 
//     //...if data validity is false
//     if (!data.valid)
//     {
//         Serial.println("[CRITICAL] Sensor Failure");

//         //while data is still invalid, continue continue loggin error message after every second
//         while(true)
//         {
//             delay(1000);
//         }
//     }

//     //else print output to serial monitor...

//     Serial.println("==========");

//     Serial.print("Temperature: ");
//     Serial.println(data.temperature);

//     Serial.print("Humidity: ");
//     Serial.println(data.humidity);

//     Serial.print("Moisture: ");
//     Serial.println(data.soilMoisture);

//     Serial.print("Light: ");
//     Serial.println(data.lightIntensity);

//     // print outputs at every 2s
//     delay(2000);

// }



