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

#include "BSTNode.h"

BSTNode::BSTNode(int number, BSTNode* leftPtr, BSTNode* rightPtr)
{
    key = number;
    leftNode = leftPtr;
    rightNode = rightPtr;
}

BSTNode::~BSTNode()
{

}

int BSTNode::getKey()
{
    return key;
}

BSTNode* BSTNode::getLeftNode()
{
    return leftNode;
}

BSTNode* BSTNode::getRightNode()
{
    return rightNode;
}

void BSTNode::setKey(int number)
{
    key = number;
}

void BSTNode::setLeftNode(BSTNode* leftPtr)
{
    leftNode = leftPtr;
}

void BSTNode::setRightNode(BSTNode* rightPtr)
{
    rightNode = rightPtr;
}
