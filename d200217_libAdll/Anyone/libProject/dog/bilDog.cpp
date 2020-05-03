#include "bilDog.h"

IAnimal * CreateAnimal()
{
    return new Dog();
}
void ReleaseAnimal(IAnimal * animal)
{
    delete animal;
}
