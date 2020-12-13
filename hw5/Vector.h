#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include "Trace.h"

template <class T>
class vector
{
private:
    int size;
    T *space;

public:
    vector() : size(0), space(nullptr) {}
    vector(int s) : size(s), space(new T[size])
    {
        TRACE(x, "vector<T>::vector(int)");
    }
    ~vector()
    {
        size = 0;
        delete[] space;
        space = nullptr;
        TRACE(y, "vector<T>::~vector");
    }
    T &elem(int i) { return space[i]; }
    T &operator[](int i) { return space[i]; }
};

template <>
class vector<void *>
{
protected:
    int size;
    void *space;

public:
    vector()
    {
        TRACE(z, "vector<void*>::vector(int)");
    }
    ~vector()
    {
        TRACE(a, "vector<void*>::~vector");
    }
};

template <class T>
class vector<T *> : public vector<void *>
{
private:
    T **real;

public:
    vector(int s) : vector<void *>()
    {
        size = s;
        space = (void *)(new char[sizeof(T *) * size]);
        TRACE(b, "vector<T*>::vector(int)");

        real = (T **)space;
    }
    ~vector()
    {
        TRACE(c, "vector<T*>::~vector");
        delete[] real;
        operator delete(space);
        real = nullptr;
        space = nullptr;
        size = 0;
    }
    T *elem(int i) { return (reinterpret_cast<T **>(space))[i]; }
    T *operator[](int i) { return (reinterpret_cast<T **>(space))[i]; }
};
#endif