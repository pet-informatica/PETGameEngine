#include "videoiniterrorexception.h"

VideoInitErrorException::VideoInitErrorException()
{
    //ctor
}

const char* VideoInitErrorException::what() const throw()
{
    return "Erro fatal ao iniciar o sistema de video!";
}



