#pragma once
#include "../../inc/DynamicString.h"
#include <iostream>

class Url : public DynamicString {
public:
    Url(const char* str);
    int compare(const Url& other);
private:
    char* URL;
    char* scheme;
    char* authority;
    char* path;

};