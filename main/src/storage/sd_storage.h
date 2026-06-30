//creating  a secure digital card (sd card) layer for storage
#ifndef SD_STORAGE_H
#define SD_STORAGE_H

//this class only ...
//1. initializs class and...
//2. write text
// no sensors, no decisions, no irrigations, SINGLE RESPONSIBILITY

class SDStorage
{
public:
    bool begin();

    bool append(
        const char* data
    );

    //adding one more functionality
    private:
        bool createDatasetFile();
};

#endif


