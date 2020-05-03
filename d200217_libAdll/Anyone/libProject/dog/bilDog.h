#ifndef BILDOG_H
#define BILDOG_H
#include "dog.h"

extern "C"
{
 Q_DECL_EXPORT IAnimal * CreateAnimal();
 Q_DECL_EXPORT void ReleaseAnimal(IAnimal * animal);
}

#endif // DOG_H
