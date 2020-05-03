#ifndef DOG_H
#define DOG_H

#include "ianimal.h"

class Dog:public IAnimal
{
public:
    Dog();
    virtual ~Dog();
public:
    virtual void Eat()  ;
    virtual void Run()  ;
    virtual void Sleep();
};

#endif // DOG_H
