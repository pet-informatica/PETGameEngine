#ifndef ASCREENALREADYEXISTSEXCEPTION_H
#define ASCREENALREADYEXISTSEXCEPTION_H

#include <exception>

using std::exception;

class ScreenException : public exception
{


    public:

        ScreenException();

        virtual const char* what() const throw();




};

#endif // ASCREENALREADYEXISTSEXCEPTION_H
