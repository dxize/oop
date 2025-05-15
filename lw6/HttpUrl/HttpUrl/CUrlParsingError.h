#pragma once
#include <stdexcept>
#include <string>

class CUrlParsingError : public std::invalid_argument
{
public:
    explicit CUrlParsingError(const std::string& what_arg)
        : std::invalid_argument(what_arg)
    {}
};