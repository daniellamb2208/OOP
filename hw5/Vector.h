#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include "Trace.h"
#include <iostream>
using namespace std;

template <class T>
class vector
{
private:
    int size;
    T *space;
    static int count;

public:
    vector() : size(0), space(nullptr) {}
    vector(int s) : size(s), space(new T[size])
    {
        TRACE(x, "vector<T>::vector(int)");
        cout << "count = " << ++count << endl;
    }
    ~vector()
    {
        size = 0;
        delete[] space;
        space = nullptr;
        TRACE(y, "vector<T>::~vector");
        cout << "count = " << count-- << endl;
    }
    //    T &elem(int i) { return space[i]; }
    T &operator[](int i) { return space[i]; }
};

template <>
class vector<void *>
{
protected:
    int size;
    void **space;
    static int count_void;

public:
    vector() = default;
    vector(int s) : size(s), space(new void *[size])
    {
        TRACE(z, "vector<void*>::vector(int)");
        cout << "count = " << ++count_void << endl;
    }
    ~vector()
    {
        TRACE(a, "vector<void*>::~vector");
        cout << "count = " << count_void-- << endl;
        delete[] space;
        space = nullptr;
    }

    void *&elem(int i) { return space[i]; }
    void *&operator[](int i) { return space[i]; }
};

template <class T>
class vector<T *> : public vector<void *>
{

public:
    vector(int s) : vector<void *>(s)
    {
        TRACE(b, "vector<T*>::vector(int)");
    }
    ~vector()
    {
        TRACE(c, "vector<T*>::~vector");
    }
    T *&elem(int i) { return (T *&)(vector<void *>::elem(i)); }
    T *&operator[](int i) { return (T *&)(vector<void *>::operator[](i)); }
};
#endif