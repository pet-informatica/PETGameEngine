#ifndef NOTARGETEXCEPTION_H
#define NOTARGETEXCEPTION_H

#include <exception>

using std::exception;

class NoTargetException : public exception
{
    public:
        NoTargetException();

        virtual const char* what() const throw();

    protected:
    private:
};

#endif // NOTARGETEXCEPTION_H
