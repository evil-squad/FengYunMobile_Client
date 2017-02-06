/**
 * @file  BitArray.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstddef>
#include <algorithm>

class BitArray
{
public:
    typedef unsigned int word_t;
    enum { WORD_SIZE = sizeof(word_t) * 8 };

    BitArray() : _buf(nullptr), _size(0), _capacity(0) { reserve(WORD_SIZE); }
    BitArray(size_t size) : _buf(nullptr), _size(0), _capacity(0) { reserve(size); }
    ~BitArray()
    {
        delete[] _buf;
    }

    inline bool at(int idx) const
    {
        return _buf[windex(idx)] & (1 << woffset(idx));
    }

    inline void set(int idx, bool value)
    {
        if (value)
            _buf[windex(idx)] |= 1 << woffset(idx);
        else
            _buf[windex(idx)] &= ~(1 << woffset(idx));
    }

    inline void reserve(int size)
    {
        _size = size;

        if (size > _capacity)
        {
            if (_buf) delete[] _buf;
            int n = size / WORD_SIZE + 1;
            _buf = new word_t[n];
            _capacity = n * WORD_SIZE;
        }
    }

    inline size_t size() const { return _size; }

    inline void reset (bool value = false)
    {
        if (value)
            std::fill_n(_buf, _capacity / WORD_SIZE, ~0);
        else
            std::fill_n(_buf, _capacity / WORD_SIZE, 0);
    }

    inline void clear() { _size = 0; }

private:
    BitArray(const BitArray& other);
    BitArray& operator= (const BitArray& other);

    word_t* _buf;
    int _size, _capacity;

    inline int windex(int idx) const
    {
        return idx / WORD_SIZE;
    }

    inline int woffset(int idx) const
    {
        return idx % WORD_SIZE;
    }
};

#endif /* BITARRAY_H */
