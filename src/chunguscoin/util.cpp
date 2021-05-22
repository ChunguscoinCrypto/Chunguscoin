#include <stdarg.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "util.h"

#define _CRT_NO_VA_START_VALIDATION

std::string std_format(const std::string& format, ...)
{
    va_list args;
    va_start(args, format);
    size_t len = std::vsnprintf(NULL, 0, format.c_str(), args);
    va_end(args);
    std::vector<char> vec(len + 1);
    va_start(args, format);
    std::vsnprintf(&vec[0], len + 1, format.c_str(), args);
    va_end(args);
    return &vec[0];
}