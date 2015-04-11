#ifndef VIDEOINITERROREXCEPTION_H
#define VIDEOINITERROREXCEPTION_H

#include <exception>

using std::exception;

class VideoInitErrorException : public exception
{
    public:
        VideoInitErrorException();

        virtual const char* what() const throw();
};

#endif // VIDEOINITERROREXCEPTION_H
