#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <random>
#include <iostream>
#include <string>   
#include <conio.h>
using namespace std;

typedef unsigned int u_int;

namespace Tools
{
    static int RandomInt(const u_int& _max, const u_int& _min)
    {
        random_device _rSeed;
        mt19937 _gen(_rSeed());
        uniform_int_distribution<> distr(_min, _max);

        return distr(_gen);
    }

    template<typename Type>
    Type RandomInt(const Type& _max, const Type& _min)
    {
        random_device _rSeed;
        mt19937 _gen(_rSeed());
        uniform_real_distribution<Type> distr(_min, _max);

        return distr(_gen);
    }

    template<typename Type>
    Type GetRandomObjectInArray(Type* _array, const u_int& _arraySize)
    {
        int _randomIndex = RandomInt(_arraySize, 0);
        return _array[_randomIndex];
    }
}