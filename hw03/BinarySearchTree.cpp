/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2021
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>
#include <stack>

#include "BinarySearchTree.h"

using namespace std;

//default constructor
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

//destructor
BinarySearchTree::~BinarySearchTree()
{
    // walk tree in post-order traversal and delete
    post_order_delete(root);
    root = nullptr;  // not really necessary, since the tree is going
                     // away, but might want to guard against someone
                     // using a pointer after deleting
}

void BinarySearchTree::post_order_delete(Node *node)
{
    //base case: tree is empty
    if(node == nullptr)
    {
        return;
    }
    //recursive cases, if tree is not empty, delete nodes from left and right 
    //in post order
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
    // check for self-assignment
    if(this != &source)
    {
        //delete current tree
        post_order_delete(root);
        
        //replace with tree being copied
        root = pre_order_copy(source.root);
    }
    return *this;
}

/* pre_order_copy()
 * Purpose: This function uses a pre-order traversal to iterate over each 
 * element in the BST and copy it to another BST. This function is used in 
 * both the assignment overload and the copy constructors above
 * Arguments: Takes a pointer to a node that is the root of the tree to be 
 * copied
 * Returns: A pointer to the root node of the copy of the tree
*/
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    //using a stack to store the elements of the tree
    stack<Node*> preOStack;
    preOStack.push(node);
    BinarySearchTree *copy = new BinarySearchTree();
    
    //loopily adding elements to the stack and copying the item from the 
    //top of the stack to the new tree. 
    while(not preOStack.empty())
    {
        Node *curr = preOStack.top();
        preOStack.pop();
        
        //add node to copy tree
        for(int i = 1; i <= curr->count; i++)
        {
            copy->insert(curr->data);
        }
        
        //pushing right subtree onto stack before left subtree
        if(curr->right != nullptr)
        {
            preOStack.push(curr->right);
        }
        if(curr->left != nullptr)
        {
            preOStack.push(curr->left);
        }
    }
    //return pointer to root of new tree
    return copy->root;
}

//uncomment this public shell function to use p_o_delete to test 
// void BinarySearchTree::p_o_delete()
// {
//     post_order_delete(root);
// }

/* find_min() SHELL
 * Purpose: This shell function finds the minimum value in the tree by calling
 * the recursive helper function below 
 * If the tree is empty it returns the greatest possible int
 * Arguments: none
 * Returns:  the int value representing the min value in the tree
*/
int BinarySearchTree::find_min() const
{
    //if tree is empty, return largest possible int
    if (root == nullptr)
        return numeric_limits<int>::max(); // INT_MAX
    
    //if not, call recursive helper below
    return find_min(root)->data;
}

/* find_min() HELPER
 * Purpose: This helper function finds the minimum value in the tree recursively
 * If the tree is empty it returns the greatest possible int
 * Arguments: takes a pointer to a node which it uses to recursively traverse
 * over the smallest elements of the tree
 * Returns:  the int value representing the min value in the tree
*/
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
{
    //if you are as far left as you can go, return the current node
    if(node->left == nullptr)
    {
        return node;
    }
    //else, recurse as far left on tree as possible
    return find_min(node->left);
}

/* find_max() SHELL
 * Purpose: This shell function finds the maximum value in the tree by calling
 * the recursive helper function below 
 * If the tree is empty it returns the least possible int
 * Arguments: none
 * Returns:  the int value representing the max value in the tree
*/
int BinarySearchTree::find_max() const
{
    //if tree is empty, return smallest possible int
    if (root == nullptr)
        return numeric_limits<int>::min(); 
    //else, call recursive function below
    return find_max(root)->data;
}

/* find_max() HELPER
 * Purpose: This helper function finds the maximum value in the tree recursively
 * If the tree is empty it returns the least possible int
 * Arguments: takes a pointer to a node which it uses to recursively traverse
 * over the greatest elements of the tree
 * Returns:  the int value representing the max value in the tree
*/
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
    //if you're as far right as you can be, return current node
    if(node->right == nullptr)
    {
        return node;
    }
    //else, recurse as far as you can    
    return find_max(node->right);
}

/* contains() shell
 * Purpose: This is the shell function that calls the below recursive 
 * function which determines whether or not the tree contains a given value 
 * Arguments: takes an int which it parses through the elements of the tree 
 * to try to find
 * Returns:  a bool that states whether the given value is in the tree or not
*/
bool BinarySearchTree::contains(int value) const
{
    //call recursive function starting at the root
    return contains(root, value);
}

/* contains() HELPER
 * Purpose: This helper function searches through the elements of the tree
 * recursively to determine if the given value is in the tree
 * Arguments: takes a pointer to a node which it uses to recursively traverse
 * over the smallest elements of the tree, and the value which it hopes to find
 * Returns: a bool that states whether the given value is in the tree or not  
*/
bool BinarySearchTree::contains(Node *node, int value) const
{
    //if you cannot traverse any farther, return false
    if(node == nullptr)
    {
        return false;
    }
    //base case: if you found the desired value return true
    if(node->data == value)
    {
        return true;
    }
    
    //recursive case, if value is less than the current node, go left
    if(value < node->data)
    {
        return contains(node->left, value);
    }
    //recursive case, if value is greater than the current node, go right
    else
    {
        return contains(node->right, value);
    }
}
 
/* insert() shell
 * Purpose: This is the shell function that calls the below recursive 
 * function which inserts a node into the BST at a location that maintains
 * the BST invariants
 * Arguments: takes an int which is the value of the node to be inserted into 
 * the BST
 * Returns: nothing, but modifies the BST
*/
void BinarySearchTree::insert(int value)
{
    //call recursive function below starting at root
    insert(root, nullptr, value);
}

/* insert() helper
 * Purpose: This is the helper function that recurses through the BST to find  
 * an adequate location in which to insert a new node, and inserts the node 
 * based on the value passed to it from the shell function
 * Arguments: takes a pointer to a node and a pointer to its parent which are 
 * both used to recurse through the tree, as well as the value of the node
 * to be inserted 
 * Returns: nothing, but modifies the BST
*/
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    //base case, (sub)tree is empty
    if(node==nullptr)
    {
        //create new node, set its data properly
        Node *newNode = new Node();
        newNode->data = value;
        newNode->count = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        //if this is the first node in the tree, set it to root
        if(parent==nullptr)
        {
            root=newNode;
        }
        //if parent is greater than value, it is left child
        else if(parent->data > value)
        {
            parent->left = newNode;
        }
        //if parent is less than value, it is right child
        else if(parent->data < value)
        {
            parent->right = newNode;
        }
    }
    //recursive cases, go left if the value is less than the current node,
    else if(value < node->data)
    {
        insert(node->left, node, value);
    }
    //go right if value is greater than curent node
    else if(value > node->data)
    {
        insert(node->right, node, value);
    }
    //and if value is equal to current node, mark as duplicate
    else if(value == node->data)
    {
        node->count++;
    }
}

/* remove() shell
 * Purpose: This is the shell function which calls the recursive remove 
 * function below in to recurse through the tree to find the desired element
 * to remove, remove it, and "stitch together the hole" in the tree  
 * Arguments: takes the int value of the node to be inserted 
 * Returns: a bool that determines whether the element has been removed,
 * and also modifies the BST
*/
bool BinarySearchTree::remove(int value)
{
    //call recursive function
    return remove(root, nullptr, value);
}

/* remove_w_2_children() 
 * Purpose: This is a helper function for the case of removing a node that 
 * has 2 children, where it must ensure that the children are both accounted 
 * for now that they're orphaned
 * Arguments: takes a pointer to the current node and a pointer to its parent
 * Returns: a bool that determines whether the element has been removed with 2
 * children
*/
bool BinarySearchTree::remove_w_2_children(Node *node, Node *parent)
{
    if(node->left != nullptr and node->right != nullptr)
    {
        //replace node to be deleted with smallest value in its right subtree
        Node* curr = find_min(node->right);
        //replace current nodes left and right subtrees with those of the 
        //node to be deleted
        
        Node* currParent = curr;
        currParent= find_parent(root, currParent);
        
        currParent->left=curr->right;
        
        curr->left=node->left;
        curr->right=node->right;
        //delete the node
        delete node;
        //fill in the hole left by deleting the node
        if(parent == nullptr)
        {
            root = curr;
        }
        else
        {    
            parent->right = curr;
        }

        return true;
    }
    return false;
}

/* remove_w_1_child() 
 * Purpose: This is a helper function for the case of removing a node that 
 * has 1 child, where it must ensure that the child is accounted for and 
 * that the invariant is still met due to the deletion of the parent
 * Arguments: takes a pointer to the current node and a pointer to its parent
 * Returns: a bool that determines whether the element has been removed with 1
 * child
*/
bool BinarySearchTree::remove_w_1_child(Node *node, Node *parent)
{
    //if the node has a left child
    if(node->left != nullptr)
    {
        //store left child
        Node *curr = node->left;
        //delete node
        delete node;
        //replace node with left child
        if(parent == nullptr)
        {
            root = curr;
        }
        else
        {
            parent->left=curr;
        }
        return true;
    }
    //or if the node has a right child
    else if(node->right != nullptr)
    {
        //store right child
        Node *curr = node->right;
        //delete node
        delete node;
        //replace with right child
        if(parent == nullptr)
        {
            root = curr;
        }
        else
        {
            parent->right=curr;
        }
        return true;
    }
    //no cases found with the node only having 1 child
    return false;
}

/* remove()  
 * Purpose: This function recurses over the tree until it finds the node to 
 * remove, then performs the necessary action for each of the different cases:
 * Node is a duplicate, node has no children, node has 1 child, and node has 
 * 2 children
 * Arguments: takes a pointer to the current node and a pointer to its parent 
 * as well as the int value to be removed
 * Returns: a bool that determines whether the element has been removed
*/
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    //base case: node is not found in tree 
    if(node==nullptr)
    {
        return false;
    }
    
    //base case #2, node is found in the tree
    if(node->data==value)
    {
        //case: node is duplicate
        if(node->count > 1)
        {
            node->count--;
            return true;
        }
        //case: node has no children
        else if(node->left == nullptr and node->right == nullptr)
        {
            if(parent->left == node)
            {
                delete node;
                parent->left=nullptr;
            }
            else if(parent->right == node)
            {
                delete node;
                parent->right=nullptr;
            }
            return true;
        }
        //case: node has at least 1 child;
        else
        {
            if(remove_w_2_children(node, parent))
            {
                return true;
            }
            else if(remove_w_1_child(node, parent))
            {
                return true;
            }    
        }

    }
    //recursive case: node has not yet been found
    else
    {
        //traverse left
        if(value < node->data)
        {
            return remove(node->left, node, value);
        }
        //traverse right
        else
        {
            return remove(node->right, node, value);
        }
    }
    
    //to remove may reach end of non-void function warning
    return false;
}

/* tree_height() SHELL
 * Purpose: This is the shell function which calls the recursive function below
 * to return the height of the tree
 * Arguments: none
 * Returns: the int height of the tree from its root to its farthest leaf
*/
int BinarySearchTree::tree_height() const
{
        return tree_height(root) - 1;
}

/* tree_height() HELPER
 * Purpose: This is the recursive helper function which traverses over the 
 * longest path of the tree from root to leaf to determine the tree height
 * Arguments: a pointer to a node which is used to recurse over the tree
 * Returns: the int height of the tree from its root to its farthest leaf
*/
int BinarySearchTree::tree_height(Node *node) const
{
    //if you've reached the end of the tree, do not add anything to height
    if(node == nullptr)
    {
        return 0;
    }
    //recursive case: go left and right
    else
    {
        int leftHeight = tree_height(node->left);
        int rightHeight = tree_height(node->right);
        
        //return the greater of the two
        if(leftHeight > rightHeight)
        {
            return leftHeight+1;
        }
        else
        {
            return rightHeight+1;
        }
    }
}

/* node_count() SHELL
 * Purpose: This is the shell function which calls a recursive function which 
 * traverses over the entire tree to determine the number of nodes
 * Arguments: none
 * Returns: the int total number of nodes
*/
int BinarySearchTree::node_count() const
{
    //call recursive helper starting at root
    return node_count(root);
}

/* node_count() RECURSIVE
 * Purpose: This is the recursive function which traverses over the entire tree 
 * to determine the number of nodes
 * Arguments: none
 * Returns: the int total number of nodes
*/
int BinarySearchTree::node_count(Node *node) const
{
    //if you've reached the end of the tree, don't add to count
    if(node == nullptr)
    {
        return 0;
    }
    
    //if not, add one to the count of the left subtree plus the count of the 
    //right subtree
    return 1 + node_count(node->left) + node_count(node->right);
}

/* count_total() SHELL
 * Purpose: This is the shell function which calls a recursive function which 
 * traverses over the entire tree to determine the sum of all of the nodes
 * including duplicates
 * Arguments: none
 * Returns: the int sum of all the nodes
*/
int BinarySearchTree::count_total() const
{
    //call recursive function.
    return count_total(root);
}

/* count_total() RECURSIVE
 * Purpose: This is the recursive function which traverses over the entire tree 
 * to sum all of the nodes, including duplicates
 * Arguments: a node pointer which is used to recurse over the tree's nodes
 * Returns: the int sum of all the nodes
*/
int BinarySearchTree::count_total(Node *node) const
{
    //if you've reached the end of the tree, don't add to sum
    if(node == nullptr)
    {
        return 0;
    }
    //recursive case: add value of the current node to the sums of its left and 
    //right subtrees 
    return (node->data)*(node->count) + count_total(node->left) + 
             count_total(node->right);
}

/* find_parent()
 * Purpose: This is a recursive function which finds the parent of a given node
 * In hindsight I probably could've used this function in a couple places 
 * instead of passing the parent as an argument, but alas
 * Arguments: a pointer to the child node that you want to find the parent of,
 * and a pointer to the current node used for recursion
 * Returns: the pointer to the parent of the given node
*/
BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const
{
        if (node == nullptr)
                return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

/* print_tree()
 * Purpose: This prints the tree in a diagram-style so you can see the node -
 * child relationships. It's a shell function that calls the recursive function 
 * below
 * Arguments: none
 * Returns: none, but prints the tree
*/
void BinarySearchTree::print_tree() const
{
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

/* print_tree()
 * Purpose: This prints the tree in a diagram-style so you can see the node -
 * child relationships. 
 * Arguments: pointer to a node, pointers to cstrings that allow the tree to 
 * look right
 * Returns: none, but prints the tree
*/
// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const
{
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
