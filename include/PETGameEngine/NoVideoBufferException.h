#ifndef NOVIDEOBUFFEREXCEPTION_H
#define NOVIDEOBUFFEREXCEPTION_H

#include <exception>

using std::exception;

class NoVideoBufferException : public exception
{
    public:
        NoVideoBufferException();

        const char* what() const throw();

};

#endif // NOVIDEOBUFFEREXCEPTION_H
