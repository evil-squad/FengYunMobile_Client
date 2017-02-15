
/**
 * @file  PacketCache.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include <algorithm>
#include <cstring>

#include "Packet.h"

BEGIN_NS_NET

namespace
{
    class PacketData final : public Packet
    {
    public:
        PacketData(void* ptr, std::size_t size) : _buf(ptr), _size(size) {}
        virtual ~PacketData() { if (_buf) delete static_cast<char*>(_buf); }

        virtual void* ptr() const override { return _buf; }
        virtual std::size_t size() const override { return _size; }

    private:
        PacketData() = delete;

    private:
        void* _buf;
        std::size_t _size;

    };

    class PacketSlice final : public Packet
    {
    public:
        PacketSlice(const PacketPtr& packet, void* buf, std::size_t size)
            : _parent(packet)
            , _buf(buf)
            , _size(size)
        {
        }

        virtual ~PacketSlice() {}

        virtual void* ptr() const override { return _buf; }
        virtual std::size_t size() const override { return _size; }

    private:
        PacketSlice() = delete;

    private:
        PacketPtr _parent;
        void* _buf;
        std::size_t _size;
    };
}

inline static PacketPtr getEmpty()
{
    static PacketPtr empty(new PacketData(nullptr, 0));
    return empty;
}

PacketPtr PacketCache::makePacket(std::size_t size)
{
    if (size == 0) return getEmpty();
    return PacketPtr(new PacketData(new char[size], size));
}

PacketPtr PacketCache::makeSlice(const PacketPtr &packet, std::size_t offset, std::size_t size)
{
    std::size_t packetSize = packet->size();
    if (offset >= packetSize) return getEmpty();
    if (offset + size > packetSize) size = packetSize - offset;

    void* buf = packet_ptr_cast<char>(packet) + offset;

    return PacketPtr(new PacketSlice(packet, buf, size));
}

PacketPtr PacketCache::resizePacket(const PacketPtr &packet, std::size_t size)
{
    auto p = new PacketData(new char[size], size);
    std::memcmp(p->ptr(), packet->ptr(), std::min(size, packet->size()));
    return PacketPtr(p);
}

END_NS_NET
