/**
* Title       : Binary Search Tree Node (BSTNode)
* Author      : Mehmet İlbey Angur
* Student ID  : 22303555
* Section     : 2
* Homework    : 1
* Description : This file implements the BSTNode class, representing a node in a Binary Search Tree (BST).
*               Each node contains:
*               - An integer key value
*               - Pointers to its left and right child nodes
*               The class provides getter and setter methods for accessing and modifying node properties.
*/

#ifndef BSTNODE_H
#define BSTNODE_H

class BSTNode
{
    public:
        BSTNode(int key, BSTNode* left, BSTNode* right);
        ~BSTNode();
        int getKey();
        BSTNode* getLeftNode();
        BSTNode* getRightNode();
        void setKey(int key);
        void setLeftNode(BSTNode* leftPtr);
        void setRightNode(BSTNode* rightPtr);
    private:
        int key;
        BSTNode* leftNode;
        BSTNode* rightNode;
};

#endif //BSTNODE_H