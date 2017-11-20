#include <string>
#include <vector>

using namespace std;

struct Node
{
    int type;
    vector < double > keys;
    vector < Node* > children;    
};

struct LeafNode : Node
{
    vector < vector < string > > values;
    LeafNode* leftNode;
    LeafNode* rightNode;
};

struct BTree
{
    int m;
    Node * root;
};

struct SearchResult
{
    LeafNode* n;
    int pos;
};

BTree* initializeBTree(int m);
int insertBTree(BTree* bt, double key, string data);
Node* insertIntoBTreeNode(Node* n, int m, double key, string value);
void printBTree(BTree* bt);
void printBTreeNode(Node* n);
SearchResult* searchKeyBTree(BTree* bt, double key);
SearchResult* searchKeyBTreeNode(Node* bt, double key, bool isRange, bool isLess);
vector < SearchResult* > searchKeyRangeBTree(BTree* bt, double key1, double key2);