/*
ID: duttaso2
PROG: test
LANG: C++
*/
#include <cstdio>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int stringToInt(string s)
{
    stringstream ss(s);
    int i = 0;
    ss >> i;

    return i;
}

int main() {
//    ofstream fout ("ride.out");
//    ifstream fin ("ride.in");
//    int a, b;
//    fin >> a >> b;
//    fout << a+b << endl;
//    return 0;

    char ipFileName[] = "input.txt";
    ifstream ipFile (ipFileName);
    
    string line;
    getline (ipFile,line);
    
    int m = stringToInt(line);

    vector < string > lines;
    while ( getline (ipFile,line) )
    {
        lines.push_back(line);
    }
    
    ipFile.close();
    
    m = lines.size();
    cout << m << endl;

    for (int i = 1; i <= m; i++)
    {
        char opFileName[100] = "input_";
        char mStr[20] = "txt.";
        int tempM = i;
        int j = 4;
        while (tempM > 0)
        {
            int r = tempM % 10;
            mStr[j] = r + 48;
            j++;
            tempM = tempM / 10;
        }

        for (int k = j - 1; k >= 0; k--)
        {
            opFileName[6 + j - k - 1] = mStr[k];
        }

        opFileName[6 + j] = '\0';
        
        if (i % 100 == 0)
            cout << opFileName << endl;

        ofstream opFile (opFileName);
        opFile << i << endl;
        for (int k = 0; k < lines.size(); k++)
        {
            opFile << lines[k] << endl;
        }

        opFile.close();
    }

    return 0;
}