/**
 * @file  MinHeap.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

// T must satisfy CopyConstructible, CopyAssignable, EqualityComparable, EqualLessThanComparable concept
template <class T>
class MinHeap
{
public:
    MinHeap();
    MinHeap(int capacity);
    ~MinHeap();

    T top();
    T pop();
    void push(T v);

    bool contains(T v);

    template <class K>
    bool containsByKey(K key);

    int find(T v);

    template <class K>
    int findByKey(K key);


    T& at(int idx);

    void resort(int idx);
    void resort();

    bool empty() const { return size() == 0; }
    std::size_t size() const { return _heap.size(); }
    std::size_t capacity() const { return _heap.capacity(); }

    void clear() { _heap.clear(); }

private:
    std::vector<T> _heap;

    void filterdown(int start, int end);
    void filterup(int start);
};

template <class T>
MinHeap<T>::MinHeap()
{
    _heap.reserve(30);
}

template <class T>
MinHeap<T>::MinHeap(int capacity)
{
    _heap.reserve(capacity);
}

template <class T>
MinHeap<T>::~MinHeap()
{
}

template <class T>
T MinHeap<T>::top()
{
    return _heap[0];
}

template <class T>
T MinHeap<T>::pop()
{
    T v = _heap[0];

    if (_heap.size() > 1)
        _heap[0] = *(_heap.rbegin());

    _heap.pop_back();

    if (_heap.size() > 1)
        filterdown(0, _heap.size()-1);

    return v;
}

template <class T>
void MinHeap<T>::push(T v)
{
    _heap.push_back(v);
    filterup(_heap.size()-1);
}

template <class T>
bool MinHeap<T>::contains(T v)
{
    return find(v) != -1;
}

template <class T>
template <class K>
bool MinHeap<T>::containsByKey(K key)
{
    return findByKey(key) != -1;
}

template <class T>
int MinHeap<T>::find(T v)
{
    for (int i=0; i<_heap.size(); ++i)
        if (_heap[i] == v) return i;
    return -1;
}

template <class T>
template <class K>
int MinHeap<T>::findByKey(K key)
{
    int c = (int)_heap.size();
    for (int i=0; i<c; ++i)
        if (_heap[i].key() == key) return i;
    return -1;
}

template <class T>
T& MinHeap<T>::at(int idx)
{
    return _heap[idx];
}

template <class T>
void MinHeap<T>::resort(int idx)
{
    if (idx == -1) return;

    int p = (idx-1)/2;

    if (p != idx && _heap[idx] < _heap[p])
        filterup(idx);
    else
        filterdown(idx, _heap.size()-1);
}

template <class T>
void MinHeap<T>::resort()
{
    for (int i=0; i<_heap.size(); ++i)
        filterup(i);
}

template <class T>
void MinHeap<T>::filterdown(int start, int end)
{
    int c = start;
    int ch = 2*c + 1; // child, left first
    T tmp = _heap[c];

    while(ch <= end)
    {
        if(ch < end && _heap[ch+1] < _heap[ch]) // choose minimal child
            ch++;
        if (_heap[ch] < tmp)
        {
            _heap[c] = _heap[ch];
            c = ch;
            ch = 2*c + 1;
        }
        else
            break;
    }

    if (c != start)
        _heap[c] = tmp;
}

template <class T>
void MinHeap<T>::filterup(int start)
{
    int c = start;
    int p = (c-1)/2; // parent
    T tmp = _heap[c];

    while(c > 0)
    {
        if (tmp < _heap[p])
        {
            _heap[c] = _heap[p];
            c = p;
            p = (p-1)/2;
        }
        else
            break;
    }
    
    if (c != start)
        _heap[c] = tmp;
}

#endif /* MINHEAP_H */
