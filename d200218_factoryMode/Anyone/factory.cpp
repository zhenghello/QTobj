#include "Factory.h"
#include <QDebug>
Factory::Factory()
{

}
Factory::~Factory()
{

}


ConcreteFactory::ConcreteFactory()
{
    qDebug()<<"ConcreteFactory";
}
ConcreteFactory::~ConcreteFactory()
{

}

AbstractProduct *ConcreteFactory::CreateProduct()
{
    return new ConcreteProduct();
}
