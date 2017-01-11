/**
 * @file  ConfigReader.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 11/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef MISC_CONFIGREADER_H
#define MISC_CONFIGREADER_H

#include <cstddef>

class ConfigReader
{
public:
    virtual ~ConfigReader() {}

    // map operators
    virtual bool hasKey(const char* key) { return false; }
    virtual int readInt(const char* key) { return 0; }
    virtual float readFloat(const char* key) { return 0; }
    virtual const char* readStr(const char* key) { return nullptr; }
    virtual bool pushMap(const char* key) { return false; }
    virtual bool pushArray(const char* key) { return false; }

    // array operators
    virtual int getArraySize() { return 0; }
    virtual int readInt(int idx) { return 0; }
    virtual float readFloat(int idx) { return 0; }
    virtual const char* readStr(int idx) { return nullptr; }
    virtual bool pushMap(int idx) { return false; }
    virtual bool pushArray(int idx) { return false; }

    virtual bool pop() { return false; }
};

#endif /* MISC_CONFIGREADER_H */
