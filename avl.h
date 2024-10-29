#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

class Node
{
    public:
        int value;
        int height;
        //int left_size;
        int subtree_size;
        Node* left;
        Node* right;
        Node* parent;
    Node(int value);
};





class avl
{
    private:
    Node* root;


    // Helper functinos for AVL tree operations
    void updateNode ( Node* node );
    void leftRotation ( Node* node );
    void rightRotation ( Node* node );
    void rebalance ( Node* node );
    void deleteNode ( Node* node );
    void inorder_traversal ( Node* node );
    int getBalanceFactor ( Node* node );
    Node* inorder_successor ( Node* node ); // Minimum node in the right subtree
    Node* inorder_predecessor ( Node* node ); // Maximum node in the left subtree
    Node* findElementAtRank ( int rank );




    public:
    // Member functions
    avl();
    int elementAtRank ( int rank );
    int rankOfElement ( int value );
    int getSize ();
    bool replaceAtRank ( int rank, int value );
    bool insertAtRank ( int rank, int value );
    bool removeAtRank ( int rank );
    void printAll ();
    

};



#endif // avl_H