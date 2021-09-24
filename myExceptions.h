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

struct SamePointsException : public std::exception
{
    const char *what() const throw()
    {
        return "Can not make triangle from points that are the same!";
    }
};