/**
 * @file  Decoder.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/
#ifndef NET_DECODER_H
#define NET_DECODER_H

#include "netbase.h"
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cstring>
#include "buffer.h"
#include "DebugHelper.h"

#include <google/protobuf/message_lite.h>

BEGIN_NS_NET

class Decoder
{
public:
    Decoder() : _buf(), _offset(0) {}
    virtual ~Decoder() {}

    Decoder(const_buffer buf) : _buf(buf), _offset(0) {}

    Decoder(const Decoder& other) = delete;
    Decoder& operator= (const Decoder& other) = delete;

    Decoder(Decoder&& other)
    {
        *this = std::move(other);
    }

    Decoder& operator= (Decoder&& other)
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
    const_buffer _buf;
    std::size_t _offset;

    inline const unsigned char* getPtrThenAdvance(std::size_t advance = 0)
    {
        auto ptr = static_cast<const unsigned char*>(_buf.ptr()) + _offset;
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

class BasicDecoder : public Decoder
{
public:
    BasicDecoder() {}
    virtual ~BasicDecoder() {}

    BasicDecoder(const_buffer buf) : Decoder(buf) {}

    char readByte()
    {
        checkRestSize(1);
        return getPtrThenAdvance(1)[0];
    }

    int readVarInt32()
    {
        char tmp = readByte();
        if (tmp >= 0)
            return tmp;

        int result = tmp & 0x7f;
        tmp = readByte();
        if (tmp >= 0)
        {
            result |= tmp << 7;
        }
        else
        {
            result |= (tmp & 0x7f) << 7;
            tmp = readByte();
            if (tmp >= 0)
            {
                result |= tmp << 14;
            }
            else
            {
                result |= (tmp & 0x7f) << 14;
                tmp = readByte();
                if (tmp >= 0)
                {
                    result |= tmp << 21;
                }
                else
                {
                    result |= (tmp & 0x7f) << 21;
                    tmp = readByte();
                    result |= tmp << 28;
                    if (tmp < 0)
                    {
                        for (int i = 0; i < 5; ++i)
                        {
                            if (readByte() >= 0)
                                return result;
                        }
                    }
                }
            }
        }
        return result;
    }

    std::int64_t readVarInt64()
    {
        int shift = 0;
        std::int64_t result = 0;
        while(shift < 64)
        {
            char b = readByte();
            result |= (std::int64_t)(b & 0x7F) << shift;
            if ((b & 0x80) == 0)
            {
                return result;
            }
            shift += 7;
        }
        return result;
    }

    std::uint8_t readUInt8()
    {
        checkRestSize(1);
        return getPtrThenAdvance(1)[0];
    }
    std::uint16_t readUInt16()
    {
        checkRestSize(2);
        auto ptr = getPtrThenAdvance(2);
        return ptr[0] << 8 | ptr[1];
    }
    std::uint32_t readUInt32()
    {
        checkRestSize(4);
        auto ptr = getPtrThenAdvance(4);
        return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
    }
    std::uint64_t readUInt64()
    {
        checkRestSize(8);
        auto ptr = getPtrThenAdvance(8);
        return (std::uint64_t)ptr[0] << 56 | (std::uint64_t)ptr[1] << 48 | (std::uint64_t)ptr[2] << 40 | (std::uint64_t)ptr[3] << 32 | (std::uint64_t)ptr[4] << 24 | (std::uint64_t)ptr[5] << 16 | (std::uint64_t)ptr[6] << 8 | (std::uint64_t)ptr[7];
    }

    std::int8_t readInt8()
    {
        return readUInt8();
    }
    std::int16_t readInt16()
    {
        return readUInt16();
    }
    std::int32_t readInt32()
    {
        return readUInt32();
    }
    std::int64_t readInt64()
    {
        return readUInt64();
    }

    std::string readString(std::size_t len)
    {
        checkRestSize(len);
        auto ptr = getPtrThenAdvance(len);
        return std::string(reinterpret_cast<const char*>(ptr), len);
    }

    void readBuffer(const mutable_buffer& buf)
    {
        checkRestSize(buf.size());
        auto ptr = getPtrThenAdvance(buf.size());
        std::memcpy(buf.ptr(), ptr, buf.size());
    }

    void readMessage(google::protobuf::MessageLite& message)
    {
        checkRestSize(_buf.size());
        auto ptr = getPtrThenAdvance(_buf.size());
        message.ParseFromArray(ptr, _buf.size());
    }
};

END_NS_NET
#endif /* NET_DECODER_H */
