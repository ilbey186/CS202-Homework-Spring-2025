/**
* Title       : Binary Search Tree Implementation (BST) "Header"
* Author      : Mehmet İlbey Angur
* Student ID  : 22303555
* Section     : 2
* Homework    : 1
* Description : This program implements a Binary Search Tree (BST) that supports various operations such as:
*               - Insertion and deletion of keys
*               - Inorder and postorder traversal
*               - Finding the level of a key in the tree
*               - Computing the maximum sum path from root to leaf
*               - Finding the lowest common ancestor of two nodes
*               - Determining tree properties like height, width, and completeness
*/


#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include <string>

class BST
{
    public:
        BST();
        BST(int keys[], int size);
        ~BST();
        void insertKey(int key);
        void deleteKey(int key);
        void keyLevel(int key);
        void displayInorder();
        void displayPostorder();
        void findFullBTLevel();
        void lowestCommonAncestor(int A, int B);
        void maximumSumPath();
        void maximumWidth();
        int getHeight(BSTNode* node);
        BSTNode* getRoot();
    private:
        BSTNode* root;
        bool isConstructing = false;
        void destroyTree(BSTNode* node);
        BSTNode* deleteNode(BSTNode* root, int number);
        BSTNode* findMin(BSTNode* node);
        int findKeyLevel(BSTNode* node, int key, int level);
        void inorderTraversal(BSTNode* node);
        void postorderTraversal(BSTNode* node);
        void getNodesAtLevel(BSTNode* node, int level, std::string& result);
        void findMaxSumPathHelper(BSTNode* node, int& maxSum, int currentSum, std::string currentPath, std::string& maxPath);
        int getWidthAtLevel(BSTNode* node, int level);
        bool searchKey(BSTNode* node, int number);
        bool isFullAtLevel(BSTNode* node, int level);
       
};


#endif //BST_H