#include <sstream>
#include <string>

#include "Helper.h"

using namespace std;

/* Converts string to int */
int stringToInt(string s)
{
    stringstream ss(s);
    int i = 0;
    ss >> i;

    return i;
}

/* Converts string to double */
double stringToDouble(string s)
{
    stringstream ss(s);
    double d = 0;
    ss >> d;

    return d;
}