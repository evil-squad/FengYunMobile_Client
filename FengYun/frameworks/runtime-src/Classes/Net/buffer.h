/**
 * @file  buffer.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/13.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_BUFFER_H
#define NET_BUFFER_H

BEGIN_NS_NET

class mutable_buffer
{
public:
    mutable_buffer() : _buf(nullptr), _size(0) {}
    mutable_buffer(void* buf, std::size_t size) : _buf(buf), _size(size) {}

    void* ptr() const { return _buf; }
    std::size_t size() const { return _size; }

private:
    void* _buf;
    std::size_t _size;
};

class const_buffer
{
public:
    const_buffer() : _buf(nullptr), _size(0) {}
    const_buffer(const void* buf, std::size_t size) : _buf(buf), _size(size) {}
    const_buffer(const mutable_buffer& buf) : _buf(buf.ptr()), _size(buf.size()) {}

    const void* ptr() const { return _buf; }
    std::size_t size() const { return _size; }

private:
    const void* _buf;
    std::size_t _size;
};

inline std::size_t buffer_size(const mutable_buffer& buf)
{
    return buf.size();
}

inline std::size_t buffer_size(const const_buffer& buf)
{
    return buf.size();
}

template <class T>
inline T* buffer_ptr(const mutable_buffer& buf, std::size_t offset = 0)
{
    return reinterpret_cast<T*>(static_cast<char*>(buf.ptr()) + offset);
}

inline void* buffer_ptr(const mutable_buffer& buf, std::size_t offset = 0)
{
    return buffer_ptr<char>(buf, offset);
}

template <class T>
inline const T* buffer_ptr(const const_buffer& buf, std::size_t offset = 0)
{
    return reinterpret_cast<const T*>(static_cast<const char*>(buf.ptr()) + offset);
}

inline const void* buffer_ptr(const const_buffer& buf, std::size_t offset = 0)
{
    return buffer_ptr<void>(buf, offset);
}

inline mutable_buffer buffer(void* data, std::size_t size)
{
    return mutable_buffer(data, size);
}

inline const_buffer buffer(const void* data, std::size_t size)
{
    return const_buffer(data, size);
}

inline mutable_buffer buffer(mutable_buffer buf, std::size_t offset, std::size_t size = 0)
{
    size = size == 0 ? buf.size() - offset : size;
    return mutable_buffer(buffer_ptr(buf, offset), size);
}

inline const_buffer buffer(const_buffer buf, std::size_t offset, std::size_t size = 0)
{
    size = size == 0 ? buf.size() - offset : size;
    return const_buffer(buffer_ptr(buf, offset), size);
}

inline mutable_buffer null_buffer()
{
    return mutable_buffer(nullptr, 0);
}

inline bool is_null_buffer(const mutable_buffer& buf)
{
    return buf.ptr() == nullptr;
}

inline bool is_null_buffer(const const_buffer& buf)
{
    return buf.ptr() == nullptr;
}

END_NS_NET
#endif /* NET_BUFFER_H */
