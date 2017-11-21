/* main file for BTree */

#include <cstdio>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "BTreeTypeDefinitions.h"
#include "Helper.h"

using namespace std;

int main(int argc, char *argv[])
{
    BTree* bt;
    int m;
    string line;
    char opFileName[] = "output_file.txt";

    ifstream ipFile (argv[1]);
    ofstream opFile (opFileName);
    
    if (ipFile.is_open())
    {
        if (getline(ipFile, line))
        {
            m = stringToInt(line);;
        }

        bt = initializeBTree(m);

        string command, value;
        double key1, key2;
        string insertCommand = "Insert", searchCommand = "Search";
        while ( getline (ipFile,line) )
        {
            size_t pos1 = line.find(insertCommand), pos2;
            if (pos1 != string::npos)
            {
                pos1 = line.find("(");
                command = line.substr(0, pos1);

                pos2 = line.find(",", pos1 + 1);
                key1 = stringToDouble(line.substr(pos1 + 1, pos2 - pos1 - 1));
                
                pos1 = line.find(")", pos2 + 1);
                value = line.substr(pos2 + 1, pos1 - pos2 - 1);

                // cout << command << "# " << key1 << " " << value << endl;
                insertBTree(bt, key1, value);
                // printBTree(bt);
            }
            else
            {
                pos1 = line.find("(");
                command = line.substr(0, pos1);

                pos2 = line.find(",", pos1 + 1);
                if (pos2 == string::npos)
                {
                    // search key command
                    pos2 = line.find(")", pos1 + 1);
                    key1 = stringToDouble(line.substr(pos1 + 1, pos2 - pos1 - 1));

                    // cout << command << "# " << key1 << endl;
                    SearchResult* sr = searchKeyBTree(bt, key1);
                    if (sr != NULL)
                    {
                        for (int i = 0; i < (int)sr->n->values[sr->pos].size(); i++)
                        {
                            // cout << ((i == 0) ? (sr->n->values[sr->pos][i]) : ("," + sr->n->values[sr->pos][i]));
                            opFile << ((i == 0) ? (sr->n->values[sr->pos][i]) : (", " + sr->n->values[sr->pos][i]));
                        }
                    }
                    else
                    {
                        // cout << "Null";
                        opFile << "Null";
                    }

                    // cout << endl;
                    opFile << endl;
                }
                else
                {
                    // search range command
                    key1 = stringToDouble(line.substr(pos1 + 1, pos2 - pos1 - 1));
                    pos1 = line.find(")", pos2 + 1);
                    key2 = stringToDouble(line.substr(pos2 + 1, pos1 - pos2 - 1));

                    // cout << command << "# " << key1 << " " << key2 << endl;
                    vector < SearchResult* > result = searchKeyRangeBTree(bt, key1, key2);
                    if ((int)result.size() == 2 && result[0] != NULL && result[1] != NULL)
                    {
                        int offset = result[0]->pos;
                        LeafNode* startNode = result[0]->n;
                        while (startNode != result[1]->n)
                        {
                            for (int i = offset; i < (int)startNode->keys.size(); i++)
                            {
                                for (int j = 0; j < (int)startNode->values[i].size(); j++)
                                {
                                    // cout << "(";
                                    // cout << startNode->keys[i];
                                    // cout << ",";
                                    // cout << startNode->values[i][j];
                                    // cout << "),";
                                    opFile << "(";
                                    toPrecisionOneForInt(opFile, startNode->keys[i]);
                                    opFile << ",";
                                    opFile << startNode->values[i][j];
                                    opFile << "), ";
                                }
                            }

                            offset = 0;
                            startNode = startNode->rightNode;
                        }

                        int end = result[1]->pos;
                        {
                            for (int i = 0; i < (int)result[1]->n->keys.size() && i <= end; i++)
                            {
                                for (int j = 0; j < (int)result[1]->n->values[i].size(); j++)
                                {    
                                    // cout << "(";
                                    // cout << result[1]->n->keys[i];
                                    // cout << ",";
                                    // cout << result[1]->n->values[i][j];
                                    // cout << ")" << ((i < (result[1]->n->keys.size() - 1) && i < end) ? "," : "");                                    
                                    opFile << "(";
                                    toPrecisionOneForInt(opFile, result[1]->n->keys[i]);
                                    opFile << ",";
                                    opFile << result[1]->n->values[i][j];
                                    opFile << ")" << ((i < ((int)result[1]->n->keys.size() - 1) && i < end) ? ", " : "");                                    
                                }
                            }               
                        }
                    }
                    else
                    {
                        // cout << "Null";
                        opFile << "Null";
                    }

                    // cout << endl;
                    opFile << endl;
                }
            }
        }

        ipFile.close();
        opFile.close();
    }
    else
    {
        printf("Error: Count not open file.\n");
        return 0;
    }
    
    // cout << "Printing BTree" << endl;
    // printBTree(bt);
    // cout << "End" << endl;
    return 0;
}
