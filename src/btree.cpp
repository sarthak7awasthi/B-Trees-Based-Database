#include "btree.h"
#include <iostream>
#include <functional>


BTreeNode::BTreeNode(bool leaf) : isLeaf(leaf) {}


BTreeNode::~BTreeNode() {
    for (auto child : children) {
        delete child;
    }
}


BTree::BTree(int degree) : degree(degree) {
    root = new BTreeNode(true);
}

BTree::~BTree() {
    freeNode(root);
}

void BTree::freeNode(BTreeNode* node) {
    if (!node->isLeaf) {
        for (auto child : node->children) {
            freeNode(child);
        }
    }
    delete node;
}


int BTree::search(int key) {
    return searchNode(root, key);
}

int BTree::searchNode(BTreeNode* node, int key) {
    int i = 0;


    while (i < node->keys.size() && key > node->keys[i]) {
        i++;
    }


    if (i < node->keys.size() && key == node->keys[i]) {
        return node->dataOffsets[i];
    }

 
    if (node->isLeaf) {
        return -1;
    }


    return searchNode(node->children[i], key);
}


void BTree::insert(int key, int offset) {
    BTreeNode* rootNode = root;


    if (rootNode->keys.size() == 2 * degree - 1) {
        BTreeNode* newRoot = new BTreeNode(false);
        newRoot->children.push_back(rootNode);
        splitChild(newRoot, 0);


        root = newRoot;
        insertNonFull(newRoot, key, offset);
    } else {
        insertNonFull(rootNode, key, offset);
    }
}

void BTree::splitChild(BTreeNode* parent, int index) {
    BTreeNode* fullChild = parent->children[index];
    BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);

  
    for (int i = 0; i < degree - 1; i++) {
        newChild->keys.push_back(fullChild->keys[degree + i]);
        newChild->dataOffsets.push_back(fullChild->dataOffsets[degree + i]);
    }


    if (!fullChild->isLeaf) {
        for (int i = 0; i < degree; i++) {
            newChild->children.push_back(fullChild->children[degree + i]);
        }
    }

    fullChild->keys.resize(degree - 1);
    fullChild->dataOffsets.resize(degree - 1);
    if (!fullChild->isLeaf) {
        fullChild->children.resize(degree);
    }

  
    parent->keys.insert(parent->keys.begin() + index, fullChild->keys[degree - 1]);
    parent->dataOffsets.insert(parent->dataOffsets.begin() + index, fullChild->dataOffsets[degree - 1]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}


void BTree::insertNonFull(BTreeNode* node, int key, int offset) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
     
        node->keys.push_back(0);
        node->dataOffsets.push_back(0);

        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->dataOffsets[i + 1] = node->dataOffsets[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->dataOffsets[i + 1] = offset;
    } else {
   
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;


        if (node->children[i]->keys.size() == 2 * degree - 1) {
            splitChild(node, i);

            if (key > node->keys[i]) {
                i++;
            }
        }

        insertNonFull(node->children[i], key, offset);
    }
}


void BTree::display() {
    std::function<void(BTreeNode*, int)> printNode = [&](BTreeNode* node, int level) {
        std::cout << std::string(level * 2, ' ') << "[ ";
        for (int key : node->keys) {
            std::cout << key << " ";
        }
        std::cout << "]\n";

        for (auto child : node->children) {
            printNode(child, level + 1);
        }
    };

    printNode(root, 0);
}


void BTree::saveToDisk(const std::string& filePath) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to open index file for saving.");
    }

    outFile.write(reinterpret_cast<const char*>(&degree), sizeof(degree));
    saveNode(root, outFile);
    outFile.close();
}


void BTree::loadFromDisk(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        return;
    }

    inFile.read(reinterpret_cast<char*>(&degree), sizeof(degree));
    root = loadNode(inFile);
    inFile.close();
}


void BTree::saveNode(BTreeNode* node, std::ofstream& outFile) {
    bool isLeaf = node->isLeaf;
    outFile.write(reinterpret_cast<const char*>(&isLeaf), sizeof(isLeaf));

    size_t keyCount = node->keys.size();
    outFile.write(reinterpret_cast<const char*>(&keyCount), sizeof(keyCount));
    outFile.write(reinterpret_cast<const char*>(node->keys.data()), keyCount * sizeof(int));
    outFile.write(reinterpret_cast<const char*>(node->dataOffsets.data()), keyCount * sizeof(int));

    if (!node->isLeaf) {
        size_t childCount = node->children.size();
        outFile.write(reinterpret_cast<const char*>(&childCount), sizeof(childCount));
        for (auto child : node->children) {
            saveNode(child, outFile);
        }
    }
}


BTreeNode* BTree::loadNode(std::ifstream& inFile) {
    bool isLeaf;
    inFile.read(reinterpret_cast<char*>(&isLeaf), sizeof(isLeaf));

    BTreeNode* node = new BTreeNode(isLeaf);

    size_t keyCount;
    inFile.read(reinterpret_cast<char*>(&keyCount), sizeof(keyCount));
    node->keys.resize(keyCount);
    node->dataOffsets.resize(keyCount);

    inFile.read(reinterpret_cast<char*>(node->keys.data()), keyCount * sizeof(int));
    inFile.read(reinterpret_cast<char*>(node->dataOffsets.data()), keyCount * sizeof(int));

    if (!node->isLeaf) {
        size_t childCount;
        inFile.read(reinterpret_cast<char*>(&childCount), sizeof(childCount));
        for (size_t i = 0; i < childCount; ++i) {
            node->children.push_back(loadNode(inFile));
        }
    }

    return node;
}
