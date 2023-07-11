#include "..\inc\DynamicString.h"
#include <cctype>
#include <stdexcept>

using std::out_of_range;
using std::tolower;
using std::toupper;
using std::ostream;

DynamicString::DynamicString(){
    cstr = new char[1];
    cstr[0] = '\0';
}

DynamicString::DynamicString(const char* str){
    if (str[0] == '\0') { 
        cstr = new char[1];
        cstr[0] = '\0';
    }
    else {
        int length = 0;
        //while loop to ascertain the size of the array
        while (str[length] != '\0') {
            length++;
        }
        
        cstr = new char[length+1];
        for (int i = 0; i < length; i++) {
            cstr[i] = str[i];

        }
        cstr[length] = '\0';
    }
    
}

int DynamicString::len() const{
    int length = 0;
    while (this->cstr[length] != '\0') {
        length++;
    }
   return length;
}

const char* DynamicString::c_str() const{
   /*Delete this garbage and just return cstr
    * once you have your constructors implemented
    */
   return cstr;
}

char DynamicString::char_at(int position) const{
    if (position > len() || position < 0) { throw out_of_range("Error: index is out of range"); }
   return cstr[position];
}

char& DynamicString::operator[](int position){
    if (position > len() || position < 0) { throw out_of_range("Error: index is out of range"); }
   return cstr[position];
}

bool DynamicString::startsWith(const DynamicString& other) const{
    int otherLen = other.len();
    if (otherLen > len()) { return false; }

    int i = 0;
    while (other.cstr[i] != '\0') {
        if (other.cstr[i] != this->cstr[i]) { return false; }
        i++;
    }

   return true;
}

bool DynamicString::endsWith(const DynamicString& other) const{
    if (other.len() > len()) { return false; }

    int i = (len() - other.len());
    int j = 0;
    while (other.char_at(j) != '\0') {
        if (other.cstr[j] != this->cstr[i]) { return false; }
        i++;
        j++;
    }


   return true;
}

int DynamicString::compare(const DynamicString& other) const {

    int i = 0;
    while (other.cstr[i] != '\0') {
        if (other.cstr[i] < this->cstr[i]) { return 1; }
        if (other.cstr[i] > this->cstr[i]) { return -1; }
        i++;
    }
    //if all of other.cstr char are equal to corresponding this->cstr char values then check which one is longer, returning 0 if they're the same.
    if (other.len() > len()) { return -1; }
    else if (other.len() < len()){ return 1; }
    return 0;
}

int DynamicString::iCompare(const DynamicString& other) const{
    int i = 0;
    while (other.cstr[i] != '\0') {
        //other is upper case and this is lowercase
        if ((other.cstr[i] >= 65 && other.cstr[i] <= 90) && (this->cstr[i] >= 97 && this->cstr[i] <= 122)) {
            if ((other.cstr[i] + 32) < this->cstr[i]) { return 1; }
            if ((other.cstr[i] + 32) > this->cstr[i]) { return -1; }
        }
        //other is lower case and this is uppercase
        else if ((this->cstr[i] >= 65 && this->cstr[i] <= 90) && (other.cstr[i] >= 97 && other.cstr[i] <= 122)) {
            if (other.cstr[i] < (this->cstr[i]+ 32)) { return 1; }
            if (other.cstr[i] > (this->cstr[i]+ 32)) { return -1; }
        }
        //both arrays are the same case in position i
        else {
            if (other.cstr[i] < this->cstr[i]) { return 1; }
            if (other.cstr[i] > this->cstr[i]) { return -1; }
        }
        i++;
    }
    //if all of other.cstr char are equal to corresponding this->cstr char values then check which one is longer, returning 0 if they're the same.
    if (other.len() > len()) { return -1; }
    else if (other.len() < len()) { return 1; }
    return 0;
}

DynamicString& DynamicString::toLower(){
    int i = 0;
    while (cstr[i] != '\0') {
        if (cstr[i] >= 65 && cstr[i] <= 90) {
            cstr[i] = cstr[i] + 32;
        }
        i++;

    }
    
   return *this;
}

DynamicString& DynamicString::toUpper(){
    int i = 0;
    while (cstr[i] != '\0') {
        if (cstr[i] >= 97 && cstr[i] <= 122) {
            cstr[i] = cstr[i] - 32;
        }
        i++;

    }
   return *this;
}

DynamicString& DynamicString::replace(char old, char newCh){
    int i = 0;
    while (cstr[i] != '\0') {
        if (cstr[i] == old) {
            cstr[i] = newCh;
        }
        i++;
    }
   return *this;
}

int DynamicString::find(char c, int start) const{
    while (cstr[start] != '\0') {
        if (cstr[start] == c) { return start; }
        start++;
    }
   return -1;
}

int DynamicString::reverseFind(char c, int start) const{
    while (start >= 0) {
        if (cstr[start] == c) { return start; }
        start--;
    }
   return -1;
}

int DynamicString::reverseFind(char c) const{
    int i = len() - 1;
    while (i >= 0) {
        if (cstr[i] == c) { return i; }
        i--;
    }
   return -1;
}

ostream& operator<<(ostream& out, const DynamicString& str){
    int i = 0;
    while (str.cstr[i] != '\0') {
        out << str.cstr[i];
        i++;
    }

   return out;
}

//additional methods for Try it Out 2: Dynamic Strings

DynamicString::DynamicString(const DynamicString& other) {
    int length = other.len();
    this->cstr = new char[length + 1];
    int i = 0;
    while (other.cstr[i] != '\0') {
        this->cstr[i] = other.cstr[i];
        i++;
    }
    this->cstr[len()] = '\0';
}

DynamicString& DynamicString::operator=(const DynamicString& other) {
    if (this != &other) {
        delete cstr;
        this->cstr = new char[other.len() + 1];
         
        int i = 0;
        while (other.cstr[i] != '\0') {
            this->cstr[i] = other.cstr[i];
            i++;
        }
        this->cstr[len()] = '\0';
    }
    return *this;
}

DynamicString::~DynamicString() {
    delete[] cstr;
}


