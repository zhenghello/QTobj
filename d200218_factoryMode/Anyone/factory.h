#ifndef FACTORY_H
#define FACTORY_H
#include "Product.h"


class Factory
{
public:
    virtual ~Factory();
    virtual AbstractProduct *CreateProduct()=0;
protected:
    Factory();
private:

};

class ConcreteFactory:public Factory
{
public:
    ConcreteFactory();
    ~ConcreteFactory();
    AbstractProduct *CreateProduct();
protected:
private:
};


#endif // FACTORY_H
