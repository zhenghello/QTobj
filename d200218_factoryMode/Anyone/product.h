#ifndef Product_H
#define Product_H


class AbstractProduct
{
public:
    virtual ~AbstractProduct();
protected:
    AbstractProduct();
private:

};
class ConcreteProduct:public AbstractProduct
{
public:
    ConcreteProduct ();
    ~ConcreteProduct();
protected:

private:

};
#endif // Product_H
