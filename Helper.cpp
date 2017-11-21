#include <cmath>
#include <cstdio>

#include <fstream>
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

void toPrecisionOneForInt(ofstream& file, double d)
{
    double intpart;
    if (modf (d , &intpart) == 0)
    {
        char buffer[50];
        sprintf(buffer, "%.1f", d);
        file << buffer;
    }
    else
    {
        file << d;
    }
}
