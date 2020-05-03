#include "Product.h"
#include <QDebug>
AbstractProduct::AbstractProduct()
{

}

AbstractProduct::~AbstractProduct()
{

}


ConcreteProduct::ConcreteProduct()
{
    qDebug()<<"ConcreteProduct....";
}
ConcreteProduct::~ConcreteProduct()
{

}
