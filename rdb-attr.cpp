#include <bits/stdc++.h>

using namespace std;
#include "rdb.h"


//Methods of Attr base class
Attr::Attr(string s):dtype(s){};

string Attr:: getvalue()const{return dtype;}

ostream& operator<<(ostream &os,  Attr* attr) {
           if(attr->getvalue()=="int") {IntAttr* p1=dynamic_cast<IntAttr*>(attr);os<<p1->getvalue();}
    else if(attr->getvalue()=="float"){ FloatAttr* p1=dynamic_cast<FloatAttr*>(attr);os<<p1->getvalue();}
    else { StringAttr* p1=dynamic_cast <StringAttr*> (attr);os<<p1->getvalue();}
    return os;
};


//Methods of IntAttr class
 IntAttr::IntAttr(int value,string d) : value_(value), Attr(d) {};


    IntAttr::IntAttr(IntAttr &t):value_(t.value_), Attr(t.dtype){} //copy constructor

 void IntAttr::printattritube()const{
    cout<<value_;

 };

 int IntAttr::getvalue() const{
    return(value_);
 };

 bool IntAttr::operator==(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ == rightInt->value_);
}

bool IntAttr::operator!=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ != rightInt->value_);
}


bool IntAttr::operator<(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ < rightInt->value_);
}


bool IntAttr::operator<=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ <= rightInt->value_);
}


bool IntAttr::operator>(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ > rightInt->value_);
}


bool IntAttr::operator>=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ >= rightInt->value_);
}



// IntAttr* IntAttr::clone() const
// {
//     return new IntAttr(*this); // create a new object with the same value
// }

 ostream& operator<< (ostream& os,const IntAttr &a)  {
        os << a.getvalue();
        return os;
    }


//Methods of StringAttr class
StringAttr:: StringAttr(string value,string d) : value_(value),Attr(d) {};

StringAttr:: StringAttr(StringAttr &t):value_(t.value_), Attr(t.dtype){} //copy constructor

void StringAttr::printattritube()const{cout<<value_;}

string StringAttr::getvalue()const {return value_;}

bool StringAttr::operator==(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ == rightString->value_);
}

bool StringAttr::operator!=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ != rightString->value_);
}


bool StringAttr::operator<(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ < rightString->value_);
}


bool StringAttr::operator<=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ <= rightString->value_);
}

bool StringAttr::operator>(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ > rightString->value_);
}



bool StringAttr::operator>=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ >= rightString->value_);
}


// StringAttr *StringAttr::clone() const
// {
//     return new StringAttr(*this); // create a new object with the same value
// }


ostream& operator<< (ostream& os,const StringAttr &a)  {
        os <<a.getvalue();
        return os;
}


//methods for FloatAttr Class
FloatAttr:: FloatAttr(float value,string d) : value_(value),Attr(d) {}

    void FloatAttr :: printattritube() const{cout<<value_;}



    float FloatAttr :: getvalue() const{return value_;}

    bool FloatAttr :: operator==(const Attr &right) const 
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ == rightFloat->value_);
    }

    bool FloatAttr :: operator!=(const Attr &right) const
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ != rightFloat->value_);
    }

    bool FloatAttr :: operator<(const Attr &right) const{
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ < rightFloat->value_);
    }

    bool FloatAttr :: operator<=(const Attr &right) const 
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ <= rightFloat->value_);
    }

    bool FloatAttr ::operator>(const Attr &right) const 
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ > rightFloat->value_);
    }

    bool FloatAttr :: operator>=(const Attr &right) const 
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ >= rightFloat->value_);
    }

    // FloatAttr* FloatAttr :: clone() const  {
    //     return new FloatAttr(*this);  // create a new object with the same value
    // }

//    FloatAttr :: ~FloatAttr(){}





