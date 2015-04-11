#ifndef VIDEOBUFFEREXCEPTION_H
#define VIDEOBUFFEREXCEPTION_H

#include <exception>

using std::exception;

class VideoBufferException : public exception
{
    public:
        VideoBufferException();

        virtual const char* what() const throw();



};

#endif // VIDEOBUFFEREXCEPTION_H
