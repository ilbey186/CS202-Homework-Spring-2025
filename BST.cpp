/**
* Title       : Binary Search Tree Implementation (BST)
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

#include "BST.h"
#include <iostream>

BST::BST()
{
    root = nullptr;
}

BST::BST(int keys[], int size)
{
    root = nullptr;
    isConstructing = true; 

    for (int i = 0; i < size; ++i)
    {
        insertKey(keys[i]);  
    }

    isConstructing = false; 
    std::cout << "BST with size " << size << " created." << std::endl;
}

BST::~BST()
{
    destroyTree(root);
}

void BST::insertKey(int number)
{
    BSTNode* newNode = new BSTNode(number, nullptr, nullptr);

    if (root == nullptr)  
    {
        root = newNode;
        if (!isConstructing)
            std::cout << "Key " << number << " is added!"<< std::endl;
        return;
    }

    BSTNode* currentNode = root;
    BSTNode* parentNode = nullptr;

    while (currentNode)
    {
        if (number == currentNode->getKey())  
        {
            if (!isConstructing)
                std::cout << "Key " << number << " is not added! It already exists in the BST." << std::endl;
            delete newNode;  
            return;
        }

        parentNode = currentNode;  

        if (number < currentNode->getKey())
            currentNode = currentNode->getLeftNode(); 
        else
            currentNode = currentNode->getRightNode(); 
    }

    if (number < parentNode->getKey())
        parentNode->setLeftNode(newNode);
    else
        parentNode->setRightNode(newNode); 

    if (!isConstructing)
        std::cout << "Key " << number << " is added!" << std::endl;
}

void BST::deleteKey(int number)
{
    if (!searchKey(root, number)) 
    {
        std::cout << "Key " << number << " is not deleted. It does not exist in the BST." << std::endl;
        return;
    }

    root = deleteNode(root, number);
    std::cout << "Key " << number << " is deleted." << std::endl;
}

void BST::keyLevel(int key) 
{
    
    int level = findKeyLevel(root, key, 1);
    if (level == -1) 
    {
        std::cout << "Key " << key << " not found in the tree." << std::endl;
    } 
    else 
    {
        std::cout << "The level of key " << key << " is: " << level << std::endl;
    }
}

void BST::displayInorder()
{
    std::cout << "Inorder display is: ";
    inorderTraversal(root);
    std::cout << std::endl;
}

void BST::displayPostorder()
{
    std::cout << "Postorder display is: ";
    postorderTraversal(root);
    std::cout << std::endl;
}

void BST::findFullBTLevel() 
{
    int height = getHeight(root);  
    int completeBTLevel = -1;
    for (int level = 1; level <= height; ++level) 
    {  
        int nodesAtLevel = getWidthAtLevel(root, level);  
        
        if (nodesAtLevel == (1 << (level - 1))) 
        {  
            completeBTLevel = level;  
        } 
        else 
        {
            break;  
        }
    }

    if (completeBTLevel != -1)
        std::cout << "Maximum complete binary tree level is: " << completeBTLevel << std::endl;
    else
        std::cout << "No complete binary tree level found." << std::endl;
}
void BST::lowestCommonAncestor(int A, int B)
{
    BSTNode* lca = root;

    while (lca != nullptr)
    {
        
        if (A < lca->getKey() && B < lca->getKey())
            lca = lca->getLeftNode();
       
        else if (A > lca->getKey() && B > lca->getKey())
            lca = lca->getRightNode();
        else
            break; 

    }

    if (lca != nullptr)
        std::cout << "Lowest common ancestor of " << A << " and " << B << " is: " << lca->getKey() << std::endl;
    else
        std::cout << "Lowest common ancestor not found for " << A << " and " << B << " is: " << std::endl;

    
}

void BST::maximumSumPath()
{
    int maxSum = 0;
    std::string maxPath = "";
    
    findMaxSumPathHelper(root, maxSum, 0, "", maxPath);
    
    std::cout << "Maximum sum path is: " << maxPath << std::endl;
}

void BST::maximumWidth()
{
    int height = getHeight(root);
    int maxWidth = 0;
    int maxWidthLevel = 1;

    for (int i = 1; i <= height; i++)
    {
        int width = getWidthAtLevel(root, i);
        if (width > maxWidth)
        {
            maxWidth = width;
            maxWidthLevel = i;
        }
    }

   
    std::string maxWidthNodes = "";
    getNodesAtLevel(root, maxWidthLevel, maxWidthNodes);

   
    std::cout << "Maximum width level is: " << maxWidthNodes << std::endl;
}

void BST::destroyTree(BSTNode* node)
{
    if (node)
    {
        destroyTree(node->getLeftNode());  
        destroyTree(node->getRightNode());  
        delete node;               
    }
}

BSTNode* BST::deleteNode(BSTNode* root, int number)
{
    if (root == nullptr)
        return root;  


    if (number < root->getKey())
        root->setLeftNode(deleteNode(root->getLeftNode(), number));
    else if (number > root->getKey())
        root->setRightNode(deleteNode(root->getRightNode(), number));
    else 
    {
       
        if (root->getLeftNode() == nullptr && root->getRightNode() == nullptr)
        {
            delete root;
            return nullptr;
        }
        
      
        if (root->getLeftNode() == nullptr)
        {
            BSTNode* temp = root->getRightNode();
            delete root;
            return temp;
        }
        else if (root->getRightNode() == nullptr)
        {
            BSTNode* temp = root->getLeftNode();
            delete root;
            return temp;
        }

       
        BSTNode* successor = findMin(root->getRightNode());
        root->setKey(successor->getKey()); 
        root->setRightNode(deleteNode(root->getRightNode(), successor->getKey())); 
    }
    return root;
}

BSTNode* BST::findMin(BSTNode* node)
{
    while (node->getLeftNode() != nullptr)
        node = node->getLeftNode();
    return node;
}


int BST::findKeyLevel(BSTNode* node, int key, int level) {
   
    if (node == nullptr)
    {
        return -1;
    }
    if (node->getKey() == key) 
    {
        return level;
    }
    int leftLevel = findKeyLevel(node->getLeftNode(), key, level + 1);
    if (leftLevel != -1) 
    {
        return leftLevel;  
    }

    return findKeyLevel(node->getRightNode(), key, level + 1);
}

void BST::inorderTraversal(BSTNode* node)
{
    if (node == nullptr) return;

    inorderTraversal(node->getLeftNode());

    static bool first = true;  
    if (!first) {
        std::cout << ", ";  
    }
    std::cout << node->getKey();
    first = false; 

    inorderTraversal(node->getRightNode());
}


void BST::postorderTraversal(BSTNode* node)
{
    if (node == nullptr) return;

    postorderTraversal(node->getLeftNode());
    postorderTraversal(node->getRightNode());

    static bool first = true; 
    if (!first) {
        std::cout << ", ";  
    }
    std::cout << node->getKey();
    first = false;  
}


void BST::findMaxSumPathHelper(BSTNode* node, int& maxSum, int currentSum, std::string currentPath, std::string& maxPath) {
    if (node == nullptr) 
    {
        return;
    }

    currentSum += node->getKey();
    bool isLeaf = (node->getLeftNode() == nullptr && node->getRightNode() == nullptr);
    
    currentPath += std::to_string(node->getKey());
    if (!isLeaf) 
    {
        currentPath += ", ";
    }

    if (isLeaf) 
    {
        if (currentSum > maxSum) 
        {
            maxSum = currentSum;
            maxPath = currentPath;
        }
    }

    findMaxSumPathHelper(node->getLeftNode(), maxSum, currentSum, currentPath, maxPath);
    findMaxSumPathHelper(node->getRightNode(), maxSum, currentSum, currentPath, maxPath);
}


void BST::getNodesAtLevel(BSTNode* node, int level, std::string& result)
{
    if (node == nullptr) return;
    if (level == 1)
    {
        if (!result.empty()) result += ", ";
        result += std::to_string(node->getKey());
    }
    else
    {
        getNodesAtLevel(node->getLeftNode(), level - 1, result);
        getNodesAtLevel(node->getRightNode(), level - 1, result);
    }
}

int BST::getWidthAtLevel(BSTNode* node, int level)
{
    if (node == nullptr) return 0;
    if (level == 1) return 1;  
    return getWidthAtLevel(node->getLeftNode(), level - 1) + getWidthAtLevel(node->getRightNode(), level - 1);
}

int BST::getHeight(BSTNode* node) 
{
    if (node == nullptr) return 0;

    int leftHeight = getHeight(node->getLeftNode());  
    int rightHeight = getHeight(node->getRightNode()); 

    if (leftHeight > rightHeight) 
    {
        return leftHeight + 1; 
    } 
    else 
    {
        return rightHeight + 1; 
    }
}
bool BST::searchKey(BSTNode* node, int number)
{
    if (node == nullptr) return false;
    if (node->getKey() == number) return true;
    if (number < node->getKey()) return searchKey(node->getLeftNode(), number);
    return searchKey(node->getRightNode(), number);
}


bool BST::isFullAtLevel(BSTNode* node, int level) {
    if (node == nullptr) return true;

    if (level == 1) 
    {
        return (node->getLeftNode() && node->getRightNode()) ||
               (node->getLeftNode() == nullptr && node->getRightNode() == nullptr);
    }

    return isFullAtLevel(node->getLeftNode(), level - 1) &&
           isFullAtLevel(node->getRightNode(), level - 1);
}

BSTNode* BST::getRoot()
{
    return root;
}