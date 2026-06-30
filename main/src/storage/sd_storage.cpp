#include "sd_storage.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5

bool SDStorage::begin()
{
    if (!SD.begin(SD_CS_PIN))
    {
        return false;
    }

    return createDatasetFile();
}













//main implementation of the sd card storage
#include "sd_storage.h"

#include <Arduino.h>
#include <SPI.h>  //required for sd card communication
#include <SD.h> //sd card library

#define SD_CS_PIN 5

//initializing SD card storage
bool SDStorage::begin()
{
    if(!SD.begin(SD_CS_PIN))
    {
        return false;
    }

    return true;
}

bool SDStorage::append(
    const char* data)
{
    //create an object called file from the file class
    //sd.open(filename, mode)
    File file = SD.open("/dataset.csv", O_APPEND);

    //if no file exists return false
    if(!file)
    {
        return false;
    }

    //if file exists, print data and close file
    file.println(data);

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