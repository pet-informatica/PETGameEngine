#ifndef LOADIMAGEEXCEPTION_H
#define LOADIMAGEEXCEPTION_H

#include <exception>
#include <sstream>

using std::exception;
using std::stringstream;
using std::string;

class LoadImageException : public exception
{
    private:

        const char* filename;


    public:
        LoadImageException(const char* filename);
        //virtual ~LoadImageException(){filename.clear();}


        const char* what() const throw();


};

#endif // LOADIMAGEEXCEPTION_H
