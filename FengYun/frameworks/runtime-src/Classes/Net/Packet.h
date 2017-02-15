/**
 * @file  Packet.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_PACKET_H
#define NET_PACKET_H

#include "netbase.h"
#include <cstddef>
#include <memory>
#include <google/protobuf/message.h>

#include "buffer.h"

BEGIN_NS_NET

class Packet
{
public:
    virtual ~Packet() {}

    virtual void* ptr() const = 0;
    virtual std::size_t size() const = 0;

    inline void* offset_ptr(std::size_t offset) const
    {
        return reinterpret_cast<void*>(static_cast<char*>(ptr()) + offset);
    }

    inline mutable_buffer buffer() const
    {
        return net::buffer(ptr(), size());
    }
};

typedef std::shared_ptr<Packet> PacketPtr;

template <class T>
T* packet_ptr_cast(const PacketPtr& packet)
{
    return static_cast<T*>(packet->ptr());
}

class PacketCache
{
public:
    static PacketPtr makePacket(std::size_t size);

    static PacketPtr makeSlice(const PacketPtr& packet, std::size_t offset)
    {
        return makeSlice(packet, offset, packet->size() - offset);
    }

    static PacketPtr makeSlice(const PacketPtr& packet, std::size_t offset, std::size_t size);

    static PacketPtr resizePacket(const PacketPtr& packet, std::size_t size);
};

END_NS_NET
#endif /* NET_PACKET_H */
