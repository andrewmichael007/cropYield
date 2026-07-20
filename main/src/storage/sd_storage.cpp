#include "sd_storage.h"

#include <Arduino.h>

// #include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5

bool SDStorage::begin()
{
    if (!SD.begin(SD_CS_PIN, SPI, 1000000))
    {
        return false;
    }

    return createDatasetFile();
}

//creating the dataset file

bool SDStorage::createDatasetFile()
{
    //first check if dataset already exists
    if (SD.exists("/dataset.csv"))
    {
        return true;
    }

    //if dataset doesn't exist, open file
    File file = SD.open("/dataset.csv", FILE_WRITE);

    //if opening the dataset file doesn't exist
    if (!file)
    {
        return false;
    }

    //if the dataset file exists, write the below parameters to the file
    file.println(
        "timestamp,"
        "temperature,"
        "humidity,"
        "soil_moisture,"
        "light,"
        "decision,"
        "state"
    );

    //close the file
    file.close();

    return true;
}

//appending new records
bool SDStorage::append(
    const char* data)
{
    //creating a file object
    File file = SD.open("/dataset.csv", FILE_APPEND);

    //file check
    if (!file)
    {
        return false;
    }

    //if file exists, print the data
    file.println(data);

    //close file
    file.close();

    return true;
}


//NOTES

//the SPI is a synchronous
// serial communication protocol
// used to connect microcontrollers
// to peripherals like sensors,
// displays, memory chips, etc.

//the SD.h is part of the Arduino SD library.
// It provides functions to:
// Initialize an SD card via SPI.
// Create, read, write, and delete files.
// Navigate directories.
// It supports FAT16 and FAT32 file systems.
// Internally, it uses the SPI protocol to 
// communicate with the SD card.