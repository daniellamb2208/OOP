#include "Vector.h"
//specializing member ‘vector<int>::count’ requires ‘template<>’ syntax
template<> int vector<int>::count = 0;
template<> int vector<float>::count = 0;
template<> int vector<char>::count = 0;
int vector<void *>::count_void = 0;