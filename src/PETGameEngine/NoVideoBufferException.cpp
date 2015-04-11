#include "NoVideoBufferException.h"

NoVideoBufferException::NoVideoBufferException()
{
    //ctor
}

const char* NoVideoBufferException::what() const throw()
{
    return " Acao Proibida! Nao existe nenhum videoBuffer, um videoBuffer eh nescessario!";
}

