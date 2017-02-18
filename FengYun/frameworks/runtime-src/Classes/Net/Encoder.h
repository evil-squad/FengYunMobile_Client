/**
 * @file  Encoder.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/


#ifndef NET_ENCODER_H
#define NET_ENCODER_H

#include "netbase.h"
#include "buffer.h"
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cstring>
#include "DebugHelper.h"

#include <google/protobuf/message_lite.h>

BEGIN_NS_NET

class Encoder
{
public:
    Encoder() : _buf(), _offset(0) {}
    virtual ~Encoder() {}

    Encoder(mutable_buffer buf) : _buf(buf), _offset(0) {}

    Encoder(const Encoder& other) = delete;
    Encoder& operator= (const Encoder& other) = delete;

    Encoder(Encoder&& other)
    {
        *this = std::move(other);
    }

    Encoder& operator= (Encoder&& other)
    {
        if (this != &other)
        {
            _buf = other._buf;
            _offset = other._offset;
            other._buf = null_buffer();
            other._offset = 0;
        }
        return *this;
    }

    std::size_t offset() const { return _offset; }

    std::size_t skip(std::size_t count)
    {
        checkRestSize(count);
        _offset += count;
        return _offset;
    }

    std::size_t restSize() const
    {
        return _buf.size() - _offset;
    }

protected:
    mutable_buffer _buf;
    std::size_t _offset;

    inline unsigned char* getPtrThenAdvance(std::size_t advance = 0)
    {
        auto ptr = static_cast<unsigned char*>(_buf.ptr()) + _offset;
        _offset += advance;
        return ptr;
    }

    inline bool hasRestSize(std::size_t size)
    {
        return restSize() >= size;
    }

    inline void checkRestSize(std::size_t size)
    {
        DBG_ASSERT(hasRestSize(size), "no more bytes!");
    }
};

class BasicEncoder : public Encoder
{
public:
    BasicEncoder() {}
    virtual ~BasicEncoder() {}

    BasicEncoder(mutable_buffer buf) : Encoder(buf) {}

    void writeByte(std::int8_t val)
    {
        checkRestSize(1);
        getPtrThenAdvance(1)[0] = val;
    }

    void writeHeadLenght(std::size_t value)
    {
        checkRestSize(2);
        unsigned char *h = static_cast<unsigned char*>(_buf.ptr());

        h[1] = value & 0xFF;
        h[0] = (value >> 8) & 0xFF;
    }

    void writeVarInt32(int value)
    {
        while(true)
        {
            if ((value & ~0x7F) == 0)
            {
                writeByte(value);
                return;
            }
            else
            {
                writeByte((value & 0x7F) | 0x80);
                value >>= 7;
            }
        }
    }

    void writeUInt8(std::uint8_t val)
    {
        checkRestSize(1);
        getPtrThenAdvance(1)[0] = val;
    }
    void writeUInt16(std::uint16_t val)
    {
        checkRestSize(2);
        auto ptr = getPtrThenAdvance(2);
        ptr[1] = val & 0xFF;
        ptr[0] = (val >> 8) & 0xFF;
    }
    void writeUInt32(std::uint32_t val)
    {
        checkRestSize(4);
        auto ptr = getPtrThenAdvance(4);
        ptr[3] = val & 0xFF;
        ptr[2] = (val >> 8) & 0xFF;
        ptr[1] = (val >> 16) & 0xFF;
        ptr[0] = (val >> 24) & 0xFF;
    }
    void writeUInt64(std::uint64_t val)
    {
        checkRestSize(8);
        auto ptr = getPtrThenAdvance(8);
        ptr[7] = val & 0xFF;
        ptr[6] = (val >> 8) & 0xFF;
        ptr[5] = (val >> 16) & 0xFF;
        ptr[4] = (val >> 24) & 0xFF;
        ptr[3] = (val >> 32) & 0xFF;
        ptr[2] = (val >> 40) & 0xFF;
        ptr[1] = (val >> 48) & 0xFF;
        ptr[0] = (val >> 56) & 0xFF;
    }

    void writeInt8(std::int8_t val)
    {
        writeUInt8(val);
    }
    void writeInt16(std::int16_t val)
    {
        writeUInt16(val);
    }
    void writeInt32(std::int32_t val)
    {
        writeUInt32(val);
    }
    void writeInt64(std::int64_t val)
    {
        writeUInt64(val);
    }

    void writeString(const std::string& str)
    {
        checkRestSize(str.size());
        auto ptr = getPtrThenAdvance(str.size());
        std::memcpy(ptr, str.c_str(), str.size());
    }

    void writeBuffer(const const_buffer& buf)
    {
        checkRestSize(buf.size());
        auto ptr = getPtrThenAdvance(buf.size());
        std::memcpy(ptr, buf.ptr(), buf.size());
    }

    void writeMessage(const google::protobuf::MessageLite& message)
    {
        checkRestSize(message.ByteSize());
        auto ptr = getPtrThenAdvance(message.ByteSize());
        std::memcpy(ptr, message.SerializeAsString().c_str(), message.ByteSize());
    }
};

END_NS_NET
#endif /* NET_ENCODER_H */
