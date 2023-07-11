#include "Url.h"
#include <cctype>
#include <stdexcept>

using namespace std;

Url::Url(const char* str) {
    //begin validity check
    DynamicString dstr(str);
    int authStart = 0;
    int pathStart = 0;
    int authLength = 0;
    int pathLength = 0;
    int i;
    int j;

    if (dstr.find(':') == -1) {
        throw invalid_argument("Invalid URL");
    }
    else {
        i = dstr.find(':');
        while (dstr[i] != '\0') {
            if (dstr[i + 1] == '/' && dstr[i + 2] == '/') {
                authStart = (i + 3); //store value for start of authority section of URL
                if (i == 0 || dstr[i + 3] == '\0') {
                    throw invalid_argument("Invalid URL");
                }
            }
            i++;
        }//end while
        std::cout << "Valid URL" << std::endl;
    }//end validity check

    //allocate memory and assign values of full valid url address to Url variable plus 1 for the null terminator
    URL = new char[dstr.len() + 1];
    i = 0;
    while (dstr[i] != '\0') {
        URL[i] = dstr[i];
        i++;
    }
    URL[i] = '\0';

    //iterate through array storing segments into scheme, authority, path variables
    //scheme
    i = 0;
    scheme = new char[authStart - 2];
    while (i != (authStart - 3)) {
        scheme[i] = dstr[i];
        i++;
    }
    scheme[i] = '\0';

    //authority
    i = authStart;
    while (dstr[i] != '/' && dstr[i] != '\0') {
        authLength++;
        i++;
    }
    //increment once more to leave space for null terminator '\0'
    authLength++;
    authority = new char[authLength];
    i = 0;
    j = authStart;
    while (dstr[j] != '/' && dstr[j] != '\0') {
        authority[i] = dstr[j];
        i++;
        j++;
    }
    authority[i] = '\0';

    //Path
    if (dstr[j] == '\0') {
        path = new char[1];
        path[0] = '\0';
    }
    else {
        pathStart = j + 1;
        i = pathStart;
        while (dstr[i] != '\0') {
            pathLength++;
            i++;
        }
        //increment once more to leave space for null terminator '\0'
        pathLength++;
        path = new char[pathLength];
        i = 0;
        j = pathStart;
        while (dstr[j] != '\0') {
            path[i] = dstr[j];
            i++;
            j++;
        }
        path[i] = '\0';
    }

}

//iCompare ignores case, compare is case-sensitive
int Url::compare(const Url& other) {
    DynamicString sch1(scheme);
    DynamicString auth1(authority);
    DynamicString path1(path);
    DynamicString sch2(other.scheme);
    DynamicString auth2(other.authority);
    DynamicString path2(other.path);

    if (sch1.iCompare(sch2) == 0) {
        if (auth1.iCompare(auth2) == 0) {
            if (path1.compare(path2) == 0) {
                return 0;
            }
            else { return path1.compare(path2); }
        }
        else { return auth1.iCompare(auth2); }
    }
    else { return sch1.iCompare(sch2); }
}