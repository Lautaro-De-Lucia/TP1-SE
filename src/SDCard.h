// SDCard.h

#ifndef SDCARD_H
#define SDCARD_H

#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"

class SDCard {
public:
    SDCard();
    ~SDCard();

    bool writeText(const char* fileName, const char* writeBuffer);
    bool writeBinary(const char* fileName, const uint16_t* data, size_t length);

    bool openTextStream(const char* fileName, bool append = false);
    bool writeTextStream(const char* text);
    void closeTextStream();

    bool openBinaryStream(const char* fileName, bool append = false);
    bool writeBinaryStream(const uint16_t* data, size_t length);
    void closeBinaryStream();

private:
    bool _mounted;
    SDBlockDevice _sd;
    FATFileSystem _fs;

    FILE* _text_fp = nullptr;
    FILE* _binary_fp = nullptr;
};

#endif /* SDCARD_H */
