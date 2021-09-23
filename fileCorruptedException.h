#pragma once
#include <exception>
#include <iostream>

struct FileCorruptedException : public std::exception
{
    const char *what() const throw()
    {
        return "File corrupted!";
    }
};