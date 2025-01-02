#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <string>
#include <fstream>

struct BTreeNode {
    bool isLeaf;                          
    std::vector<int> keys;               
    std::vector<int> dataOffsets;         
    std::vector<BTreeNode*> children;    

    BTreeNode(bool leaf);                 // Constructor for a B-Tree node
    ~BTreeNode();                         // Destructor to free child nodes
};

class BTree {
public:
    BTree(int degree);
    ~BTree();

    void insert(int key, int offset);    
    int search(int key);                

    void loadFromDisk(const std::string& filePath); // Load B-Tree from disk
    void saveToDisk(const std::string& filePath);   // Save B-Tree to disk

    void display();                     

private:
    BTreeNode* root;                    
    int degree;                       

    void splitChild(BTreeNode* parent, int index);      
    void insertNonFull(BTreeNode* node, int key, int offset); 
    int searchNode(BTreeNode* node, int key);          

    void freeNode(BTreeNode* node);                      // Recursively free memory for a node and its children
    void saveNode(BTreeNode* node, std::ofstream& outFile); 
    BTreeNode* loadNode(std::ifstream& inFile);          // Load a node and its children from a file
};

#endif // BTREE_H
