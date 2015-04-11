#include "screenexception.h"

ScreenException::ScreenException()
{
    //ctor
}

const char* ScreenException::what() const throw()
{
            return "Deve have apenas uma screen!";
}



