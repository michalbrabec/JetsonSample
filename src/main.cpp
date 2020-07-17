#include <iostream>
#include <cstdio>

#include "TracedException.h"

void myfunc()
{
    throw std::bad_exception();
}
void myfunc2()
{
    try
    {
        myfunc();
    }
    catch (const std::exception &ex)
    {
        throw TracedException(ex);
    }
}

int main()
{
    std::string test = "test";
    std::cout << test << std::endl;
    try
    {
        myfunc2();
    }
    catch (const TracedException &ex)
    {
        std::cout << ex.what() << std::endl;
        std::cout << ex.GetStackTrace() << std::endl;
        if (ex.GetEmbeddedException() != nullptr)
        {
            std::cout << ex.GetEmbeddedException()->what() << std::endl;
            std::cout << ex.GetEmbeddedException()->GetStackTrace() << std::endl;
        }
    }
}
