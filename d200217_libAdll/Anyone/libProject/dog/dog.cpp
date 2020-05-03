#include "dog.h"
#include <QDebug>

Dog::Dog()
{

}
Dog::~Dog()
{

}
void Dog::Eat()
{
    QString str = "Hello + Dog eating ...";
}
void Dog::Run()
{
    qDebug()<<"Hello "<< "Dog running ...";
}
void Dog::Sleep()
{
    qDebug()<<"Hello "<< "Dog sleeping ...";
}
