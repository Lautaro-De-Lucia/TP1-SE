// SDCard.cpp

#include "SDCard.h"
#include <cstdio>

SDCard::SDCard()
    : _mounted(false),
      _sd(PB_15, PB_14, PB_13, PB_12),
      _fs("sd")
{
    if (_fs.mount(&_sd) != 0) {
        FATFileSystem::format(&_sd);
        _fs.mount(&_sd);
    }
    _mounted = true;
}

SDCard::~SDCard()
{
    closeTextStream();
    closeBinaryStream();
    if (_mounted) {
        _fs.unmount();
    }
}

bool SDCard::writeText(const char* fileName, const char* writeBuffer)
{
    char path[64];
    snprintf(path, sizeof(path), "/sd/%s", fileName);
    FILE* fp = fopen(path, "w");
    if (!fp) return false;
    bool ok = fputs(writeBuffer, fp) >= 0;
    fclose(fp);
    return ok;
}

bool SDCard::writeBinary(const char* fileName, const uint16_t* data, size_t length)
{
    char path[64];
    snprintf(path, sizeof(path), "/sd/%s", fileName);
    FILE* fp = fopen(path, "wb");
    if (!fp) return false;
    size_t written = fwrite(data, sizeof(uint16_t), length, fp);
    fclose(fp);
    return written == length;
}

// Text stream methods
bool SDCard::openTextStream(const char* fileName, bool append)
{
    if (_text_fp) closeTextStream(); // Close if already open
    char path[64];
    snprintf(path, sizeof(path), "/sd/%s", fileName);
    _text_fp = fopen(path, append ? "a" : "w");
    return _text_fp != nullptr;
}

bool SDCard::writeTextStream(const char* text)
{
    if (!_text_fp) return false;
    return fputs(text, _text_fp) >= 0;
}

void SDCard::closeTextStream()
{
    if (_text_fp) {
        fclose(_text_fp);
        _text_fp = nullptr;
    }
}

bool SDCard::openBinaryStream(const char* fileName, bool append)
{
    if (_binary_fp) closeBinaryStream();
    char path[64];
    snprintf(path, sizeof(path), "/sd/%s", fileName);
    _binary_fp = fopen(path, append ? "ab" : "wb");
    return _binary_fp != nullptr;
}

bool SDCard::writeBinaryStream(const uint16_t* data, size_t length)
{
    if (!_binary_fp) return false;
    size_t written = fwrite(data, sizeof(uint16_t), length, _binary_fp);
    return written == length;
}

void SDCard::closeBinaryStream()
{
    if (_binary_fp) {
        fclose(_binary_fp);
        _binary_fp = nullptr;
    }
}
