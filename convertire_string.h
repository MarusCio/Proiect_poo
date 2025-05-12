#ifndef CONVERSIE_STRING_H
#define CONVERSIE_STRING_H

#include <sstream>
#include <string>


template<typename T>
std::string To_String_Custom(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif