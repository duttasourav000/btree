#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Helper.h"

#define EPSILON 0.00000001

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

int compareValues(double d1, double d2)
{
    double diff = d1 - d2;
    if (abs(diff) < EPSILON)
    {
        return 0;
    }

    if (diff < 0)
    {
        return -1;
    }

    return 1;
}

int searchArrayRange(vector < double > array, double d, int start, int end)
{
    if (end < start)
    {
        return start;
    }

    int m = (start + end) / 2;
    int res = compareValues(d, array[m]);
    if (res == 0)
    {
        return m;
    }

    if (res < 0)
    {
        return searchArrayRange(array, d, start, m - 1);
    }

    return searchArrayRange(array, d, m + 1, end);
}

int searchArray(vector < double > array, double d)
{
    if (array.size() == 0)
    {
        return 0;
    }

    return searchArrayRange(array, d, 0, array.size() - 1);
}
