#include "LoadImageException.h"

LoadImageException::LoadImageException(const char* filename)
{
    this->filename = filename;
}

const char* LoadImageException::what() const throw()
{
    stringstream message;
    message << filename << " nao pode ser carregado. Erro ao carregar imagem!";

    return message.str().c_str();
}

