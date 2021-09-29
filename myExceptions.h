#pragma once
#include <exception>
#include <iostream>

// set of my custom expressions

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
        return "Can not make triangle from points that are identical!";
    }
};

struct CouldNotOpenFileException : public std::exception
{
    const char *what() const throw()
    {
        return "Could not open desired file!";
    }
};

struct IncorrectDirectionException : public std::exception
{
    const char *what() const throw()
    {
        return "Incorrect direction!";
    }
};
