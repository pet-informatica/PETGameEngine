#include "videobufferexception.h"

VideoBufferException::VideoBufferException()
{
    //ctor
}

const char* VideoBufferException::what() const throw()
{
    return "O buffer de video nao pode ser criado!";

}



