/* Operations for BTree */

#include <cmath>

#include <iostream>
#include <string>

#include "BTreeTypeDefinitions.h"

using namespace std;

/* Initialize BTree */
BTree* initializeBTree(int m)
{
    BTree* bt = new BTree;
    bt->m = m;
    bt->root = NULL;
    return bt;
}

/* Initialize a BTree node */
Node* initializeNode()
{
    Node* n = new Node;
    // by default the type of node is set to internal type which is 0
    n->type = 0;
    return n;
};

/* Initialize a BTree leaf node */
LeafNode* initializeLeafNode()
{
    LeafNode* ln = new LeafNode;
    // lead node has type set to 1
    ln->type = 1;
    ln->leftNode = NULL;
    ln->rightNode = NULL;
    return ln;
}

/* Initializes the search result object */
SearchResult* initializeSearchResult(LeafNode* ln, int pos)
{
    SearchResult* sr = new SearchResult;
    sr->n = ln;
    sr->pos = pos;
    return sr;
}

/* Inserts key, value into BTree */
int insertBTree(BTree* bt, double key, string data)
{
    // Check for valid BTree
    if (bt == NULL)
    {
        printf("Error: BTree not initialized.");
        return 1;
    }

    // if root node is NULL then just intiliatize a leaf node and make it root
    if (bt->root == NULL)
    {
        bt->root = initializeLeafNode();
    }

    // call insert object at node function
    Node* newRoot = insertIntoBTreeNode(bt->root, bt->m, key, data);

    // update root it root is updated due to split operation
    if (newRoot != NULL)
    {
        bt->root = newRoot;
    }

    return 0;
}

/* Inserts into BTree node and handles overflows and splits */
Node* insertIntoBTreeNode(Node* n, int m, double key, string value)
{
    if (n->type == 1)
    {
        // insert in leaf node
        LeafNode* ln = (LeafNode*)n;
        int pos = 0;
        bool iskeyPresent = false;

        // check if a key is present in the leaf node and find its position
        for (; pos < ln->keys.size(); pos++)
        {
            if (ln->keys[pos] > key)
            {
                break;
            }
            else if (ln->keys[pos] == key)
            {
                iskeyPresent = true;
                break;
            }
        }

        if (iskeyPresent)
        {
            // if key is present then just add the value to the existing key
            ln->values[pos].push_back(value);
        }
        else
        {
            // append new key, value to the node
            vector < string > tempValue;
            tempValue.push_back(value);
            
            ln->keys.push_back(key);
            ln->values.push_back(tempValue);

            ln->children.push_back(NULL);
            
            // if only one key is present after insertion of key then add two null children 
            if (ln->keys.size() == 1)
            {
                ln->children.push_back(NULL);
            }

            // shift the new key, value to the correct position in the sorted array
            for (int i = n->keys.size() - 1; i > pos; i--)
            {
                double tempKey = ln->keys[i];
                ln->keys[i] = ln->keys[i - 1];
                ln->keys[i - 1] = tempKey;

                vector<string> tempValues = ln->values[i];
                ln->values[i] = ln->values[i - 1];
                ln->values[i - 1] = tempValues; 

                Node* tempChild = ln->children[i + 1];
                ln->children[i + 1] = ln->children[i];
                ln->children[i] = tempChild;
            }

            // check if the size of the node has reached limit
            if (ln->keys.size() == m)
            {
                // split the node, find the pos for which the key is moved up
                int splitPos = (int)((m - 1) / 2);

                // create a new lead node and copy elements after the splitPos
                LeafNode* newLeafNode = initializeLeafNode();
                newLeafNode->rightNode = ln->rightNode;
                ln->rightNode = newLeafNode;
                newLeafNode->leftNode = ln;
                
                newLeafNode->children.push_back(NULL);
                for (int i = splitPos; i < m; i++)
                {
                    newLeafNode->keys.push_back(ln->keys[i]);
                    newLeafNode->children.push_back(ln->children[i + 1]);
                    newLeafNode->values.push_back(ln->values[i]);
                }

                // Create a new node which will be added to the parent node of the node which is split
                Node* newParentNode = initializeNode();
                newParentNode->children.push_back(ln);
                newParentNode->children.push_back(newLeafNode);
                newParentNode->keys.push_back(ln->keys[splitPos]);

                while (ln->keys.size() != splitPos)
                {
                    ln->keys.pop_back();
                    ln->children.pop_back();
                    ln->values.pop_back();
                }
                
                // return new parent node which is used to add it to the existing parent node
                return newParentNode;
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
        // insert into a non leaf node
        int pos = 0;
        bool iskeyPresent = false;
        for (; pos < n->keys.size(); pos++)
        {
            if (n->keys[pos] > key)
            {
                break;
            }
            else if (n->keys[pos] == key)
            {
                iskeyPresent = true;
                break;
            }
        }

        if (iskeyPresent)
        {
            // if key is present, recurse the child node
            return insertIntoBTreeNode(n->children[pos + 1], m, key, value);
        }
        else
        {
            // if key not present recurse into appropriate child node and take care of overflow
            Node* newChildRoot = insertIntoBTreeNode(n->children[pos], m, key, value);
            
            // check for new node which can be formed when child node is split
            if (newChildRoot == NULL)
            {
                return NULL;
            }
            else
            {
                if (newChildRoot->keys.size() != 1)
                {
                    cout << "Error: New node has more than 1 keys" << endl;
                }
                else
                {
                    n->children.push_back(newChildRoot->children[1]);
                    n->keys.push_back(newChildRoot->keys[0]);
                    for (int i = n->keys.size() - 1; i > pos; i--)
                    {
                        double tempKey = n->keys[i];
                        n->keys[i] = n->keys[i - 1];
                        n->keys[i - 1] = tempKey;

                        Node* tempChild = n->children[i + 1];
                        n->children[i + 1] = n->children[i];
                        n->children[i] = tempChild;
                    }

                    if (n->keys.size() == m)
                    {
                        int splitPos = (int)((m - 1) / 2);
                        Node* newSplitNode = initializeNode();
                        newSplitNode->children.push_back(n->children[splitPos + 1]);
                        for (int i = splitPos + 1; i < m; i++)
                        {
                            newSplitNode->keys.push_back(n->keys[i]);
                            newSplitNode->children.push_back(n->children[i + 1]);
                        }
        
                        Node* newParentNode = initializeNode();
                        newParentNode->children.push_back(n);
                        newParentNode->children.push_back(newSplitNode);
                        newParentNode->keys.push_back(n->keys[splitPos]);
        
                        while (n->keys.size() != splitPos)
                        {
                            n->keys.pop_back();
                            n->children.pop_back();
                        }
        
                        return newParentNode;
                    }
                    else
                    {
                        return NULL;
                    }
                }
            }
        }
    }

    return NULL;
}

/* print BTree */
void printBTree(BTree* bt)
{
    printBTreeNode(bt->root);
}

/* Search for a key in BTree */
SearchResult* searchKeyBTree(BTree* bt, double key)
{
    if (bt->root == NULL)
    {
        return NULL;
    }

    return searchKeyBTreeNode(bt->root, key, false, false);
}

/* Search for a range in a BTree */
vector < SearchResult* > searchKeyRangeBTree(BTree* bt, double key1, double key2)
{
    vector < SearchResult* > result;

    if (bt->root == NULL)
    {
        return result;
    }

    // swap keys if second is less than the first in the search range
    if (key1 > key2)
    {
        double tempKey = key1;
        key1 = key2;
        key2 = tempKey;
    }

    // search for both the keys
    SearchResult* sr1 = searchKeyBTreeNode(bt->root, key1, true, false);
    SearchResult* sr2 = searchKeyBTreeNode(bt->root, key2, true, true);

    // return empty result if any one key is out of the tree boundaries
    if (sr1 == NULL || sr2 == NULL)
    {
        return result;
    }

    // if the pos of the second key is found before the first key then return empty
    if (sr1->n == sr2->n && sr1->pos < sr2->pos)
    {
        return result;
    }

    // if the first key is found just after the end of the keys in that node
    // shift the starting position to the next node
    if (sr1->pos >= sr1->n->values.size())
    {
        sr1->n = sr1->n->rightNode;
        sr1->pos = 0;
    }

    result.push_back(sr1);
    result.push_back(sr2);

    return result;
}

/* Search a BTree Node */
SearchResult* searchKeyBTreeNode(Node* n, double key, bool isRange, bool isLess)
{
    int pos = 0;
    bool iskeyPresent = false;
    for (; pos < n->keys.size(); pos++)
    {
        if (n->keys[pos] > key)
        {
            break;
        }
        else if (n->keys[pos] == key)
        {
            iskeyPresent = true;
            break;
        }
    }

    if (n->type == 1)
    {
        // if leaf node then create search result and return
        if (iskeyPresent)
        {
            return initializeSearchResult((LeafNode*)n, pos);
        }
        else
        {
            if (isRange)
            {
                return initializeSearchResult((LeafNode*)n, pos + (isLess ? (-1) : 0));
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
        // if internal node then recurse appropriate child node
        if (iskeyPresent)
        {
            return searchKeyBTreeNode(n->children[pos + 1], key, isRange, isLess);
        }
        else
        {
            return searchKeyBTreeNode(n->children[pos], key, isRange, isLess);
        }
    }
}

void printBTreeNode(Node* n)
{
    if (n == NULL || n->keys.size() == 0)
    {
        return;
    }

    if (n->type == 1)
    {
        LeafNode* ln = (LeafNode*)n;
        cout << "(";
        for (int i = 0; i < ln->keys.size(); i++)
        {            
            cout << ln->keys[i] << "# ";
            cout << "$";
            for (int j = 0; j < ln->values[i].size(); j++)
            {
                cout << ln->values[i][j] << ((j != (ln->values[i].size() - 1)) ? ", " : "");
            }
            cout << "$ ";
        }
        cout << ((n->children[n->keys.size()] != NULL) ? "| " : "* ");
        cout << ")" << endl;
    }
    else
    {
        cout << "(";
        for (int i = 0; i < n->keys.size(); i++)
        {
            cout << ((n->children[i] != NULL) ? "| " : "* ");            
            cout << n->keys[i] << "# ";
        }
        cout << ((n->children[n->keys.size()] != NULL) ? "| " : "* ");
        cout << ")" << endl;
        for (int i = 0; i < n->children.size(); i++)
        {
            printBTreeNode(n->children[i]);
        }
    }

    return;
}