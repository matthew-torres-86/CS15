/*
 * main.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: chrisgregg
 *    
 *  Change log:
 *      2016-03-09:  [MAS] corrected comments to agree with actual tree 
 *                         structure (Correction from Jacob Ryan)
 *                   [MAS] compute size of array rather than use
 *                         hard-coded constant 
 *
 *  Main driver for testing the BinarySearchTree class
 */

#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

void print_tree_details(BinarySearchTree &bst)
{
        bst.print_tree();
        cout << "\n";
        cout << "min: "         << bst.find_min()    << "\n";
        cout << "max: "         << bst.find_max()    << "\n";
        cout << "nodes: "       << bst.node_count()  << "\n";
        cout << "count total: " << bst.count_total() << "\n";
        cout << "tree height: " << bst.tree_height() << "\n";
        cout << "\n";
}

int main()
{
        BinarySearchTree bst;
        int values[]  = {5, 5, 7, 7, 3, 3, 8, 8, 2, 2, 9, 9, 1, 1, 4, 4, 6, 6};
        int numValues = sizeof(values) / sizeof(int);
        
        //print empty tree
        print_tree_details(bst);

        for (int i = 0; i < numValues; i++) {
                bst.insert(values[i]);
        }
        cout << "Original tree "
             << "(asterisks denote a count of more than 1):\n";
        print_tree_details(bst);

        // make a copy with copy constructor
        BinarySearchTree bst_copy_constructor = bst;
        bst_copy_constructor.print_tree();
        
        // make a copy with assignment overload
        BinarySearchTree bst_copy_1;
        bst_copy_1 = bst;
        
        // remove a duplicate node at the root
        cout << "Removing 5 from original tree:\n";
        bst.remove(5);
        print_tree_details(bst);
        
        // remove the previously-unduplicated root
        cout << "Removing root of tree:\n";
        bst.remove(5);
        print_tree_details(bst);
        
        bst = bst_copy_1;
        
        // remove a node that doesnt exist
        cout << "Removing 11 from original tree:\n";
        bst.remove(11);
        print_tree_details(bst);
        
        bst = bst_copy_1;
        
        int values1[]  = {-743, 128, 1000, -7, 13, 27, 68, 2222, -9999};
        numValues = sizeof(values1) / sizeof(int);
        cout <<"Inserting variety of values to original tree \n";
        for(int i=0; i<numValues; i++)
        {
            bst.insert(values1[i]);
        }
        print_tree_details(bst);
        
        // delete tree then print details 
        // cout << "deleting tree"<<endl;
        // bst.p_o_delete();
        // print_tree_details(bst);
        
        // check if the tree contains values
        bst = bst_copy_1;
        
        BinarySearchTree linkedList;
        int values2[]  = {1, 2, 3, 4, 5};
        numValues = sizeof(values2) / sizeof(int);
        for (int i = 0; i < numValues; i++) {
                linkedList.insert(values2[i]);
        }
        print_tree_details(linkedList);
        
        cout << "Removing element from degenerate:\n";
        linkedList.remove(2);
        print_tree_details(linkedList);
        
        cout << "Removing root from degenerate:\n";
        linkedList.remove(1);
        print_tree_details(linkedList);
        
        for (int i = -10; i < 20; i++) {
                cout << "Tree "
                     << (bst.contains(i) ? "contains " : "does not contain ")
                     << "the value " << i << "\n";
        }
        cout << "\nFinished!\n";
        return 0;
}
