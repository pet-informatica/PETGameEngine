#include "NoTargetException.h"

NoTargetException::NoTargetException()
{

}



const char* NoTargetException::what() const throw()
{
    return "Can't create a monster without a target!";

}
