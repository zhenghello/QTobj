#ifndef IANIMAL_H
#define IANIMAL_H

#include "ianimal_global.h"

class IANIMALSHARED_EXPORT IAnimal
{

    IAnimal();
    virtual ~IAnimal();
public:
    virtual void Eat() = 0;
    virtual void Run() = 0;
    virtual void Sleep() = 0;
};

#endif // IANIMAL_H
