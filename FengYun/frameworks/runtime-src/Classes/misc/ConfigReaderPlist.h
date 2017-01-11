/**
 * @file  ConfigReaderPlist.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 11/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef MISC_CONFIGREADERPLIST_H
#define MISC_CONFIGREADERPLIST_H

#include <stack>
#include "cocos2d.h"
#include "ConfigReader.h"
#include "external/xxtea/xxtea.h"

class ConfigReaderPlist : public ConfigReader
{
public:
    ConfigReaderPlist(const char* filename, bool isMap = true)
    {
        cocos2d::Data plistData = cocos2d::FileUtils::getInstance()->getDataFromFile(filename);

        std::string markXXTEA("FengYunWuShuang");
        const unsigned char* ret = nullptr;
        unsigned char* releaseRet = nullptr;
        unsigned int len = 0;

        if (plistData.getSize() > markXXTEA.length()
            && std::string((const char*)plistData.getBytes(), (const char*)plistData.getBytes() + markXXTEA.length()) == markXXTEA)
        {
            char key[] = "Lock0906";
            releaseRet = xxtea_decrypt(plistData.getBytes() + markXXTEA.length(), plistData.getSize() - markXXTEA.length(), (unsigned char*)key, 8, &len);
            ret = releaseRet;
        }
        else
        {
            ret = plistData.getBytes();
            len = plistData.getSize();
        }

        if (isMap)
            _root = cocos2d::FileUtils::getInstance()->getValueMapFromData((const char*)ret, len);
        else
            _root = cocos2d::FileUtils::getInstance()->getValueVectorFromData((const char*)ret, len);

        if (releaseRet)
            free(releaseRet);

        releaseRet = nullptr;
        ret = nullptr;

        _cur = &_root;
    }

    virtual ~ConfigReaderPlist() {}

    virtual bool hasKey(const char* key)
    {
        auto& map = _cur->asValueMap();
        auto iter = map.find(key);

        return iter != map.end();
    }

    //map operators

    virtual int readInt(const char* key)
    {
        return _cur->asValueMap()[key].asInt();
    }

    virtual float readFloat(const char* key)
    {
        return _cur->asValueMap()[key].asFloat();
    }

    virtual const char* readStr(const char* key)
    {
        _str = _cur->asValueMap()[key].asString();
        return _str.c_str();
    }

    virtual bool pushMap(const char* key)
    {
        cocos2d::Value& val = _cur->asValueMap()[key];
        if (val.getType() != cocos2d::Value::Type::MAP) return false;

        _stack.push(_cur);
        _cur = &val;
        return true;
    }

    virtual bool pushArray(const char* key)
    {
        cocos2d::Value& val = _cur->asValueMap()[key];
        if (val.getType() != cocos2d::Value::Type::VECTOR) return false;

        _stack.push(_cur);
        _cur = &val;
        return true;
    }

    //array operators

    virtual int getArraySize()
    {
        return _cur->asValueVector().size();
    }

    virtual int readInt(int idx)
    {
        return _cur->asValueVector()[idx].asInt();
    }

    virtual float readFloat(int idx)
    {
        return _cur->asValueVector()[idx].asFloat();
    }

    virtual const char* readStr(int idx)
    {
        _str = _cur->asValueVector()[idx].asString();
        return _str.c_str();
    }

    virtual bool pushMap(int idx)
    {
        cocos2d::Value& val = _cur->asValueVector()[idx];
        if (val.getType() != cocos2d::Value::Type::MAP) return false;

        _stack.push(_cur);
        _cur = &val;
        return true;
    }

    virtual bool pushArray(int idx)
    {
        cocos2d::Value& val = _cur->asValueVector()[idx];
        if (val.getType() != cocos2d::Value::Type::VECTOR) return false;

        _stack.push(_cur);
        _cur = &val;
        return true;
    }

    virtual bool pop()
    {
        if (_stack.empty()) return false;
        _cur = _stack.top();
        _stack.pop();
        return true;
    }

    const cocos2d::Value& getCurValue() const
    {
        return *_cur;
    }

    cocos2d::Value& getCurValue()
    {
        return *_cur;
    }

private:
    cocos2d::Value _root;
    std::stack<cocos2d::Value*> _stack;
    cocos2d::Value* _cur;
    std::string _str;
};

#endif /* MISC_CONFIGREADERPLIST_H */
