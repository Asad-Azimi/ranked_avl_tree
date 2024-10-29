#include <iostream>

#include "avl.h"


// Node constructor
Node::Node(int value)
{
    this -> value = value;
    this -> height = 1;
    this -> subtree_size = 1;
    this -> left = nullptr;
    this -> right = nullptr;
    this -> parent = nullptr;
}





// AVL tree constructor
avl::avl()
{
    root = nullptr;
}





// Helper function: getSize
int avl::getSize ()
{
    return root ? root -> subtree_size : 1;
}







// Public method: insertAtRank
bool avl::insertAtRank( int rank, int value )
{
    if (rank < 1 || rank > getSize())
    {
        // Rank out of bounds
        return false;
    }

    Node* new_node = new Node(value);

    if (root == nullptr)
    {
        // Tree is empty
        root = new_node;
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;
    bool done = false;
    int rank_so_far = 1;
    while (!done)
    {
        current -> subtree_size += 1; // increment the subtree_size as we move down the tree
        int current_rank = rank_so_far + (current -> left ? current -> left -> subtree_size : 0);

        if (rank < current_rank)
        {
            if (current -> left == nullptr)
            {
                // Move to the left
                current -> left = new_node;
                new_node -> parent = current;
                done = true;
            }
            else
            {
                current = current -> left;
            }
        }
        else if (rank == current_rank)
        {
            // Insert as the left child
            if (current -> left == nullptr)
            {
                current -> left = new_node;
                new_node -> parent = current;
                done = true;
            }
            else
            {
                current = current -> left;

                while (current -> right != nullptr)
                {
                    current -> subtree_size += 1;
                    current = current -> right;
                }
                current -> subtree_size += 1;
                current -> right = new_node;
                new_node -> parent = current;
                done = true;
            }
        }
        else
        {
            // Move to the right and update the rank_so_far
            rank_so_far = current_rank + 1;
            if (current -> right == nullptr)
            {
                current -> right = new_node;
                new_node -> parent = current;
                done = true;
            }
            else
            {
                current = current -> right;
            }
        }

    }

    // Rebalance the tree starting from the parent upwards
    rebalance(new_node -> parent);

    return true;

}







// Helper function: rebalance the tree starting from a given node
void avl::rebalance ( Node* node)
{
    while (node != nullptr)
    {
        int left_height = node -> left ? node -> left -> height : 0;
        int right_height = node -> right ? node -> right -> height : 0;

        node -> height = 1 + (left_height > right_height ? left_height : right_height);

        int balancefactor = getBalanceFactor(node);

        if (balancefactor > 1)
        {
            if (getBalanceFactor(node -> left) >= 0)
            {
                // left left case
                rightRotation(node);
            }
            else
            {
                // left right case
                leftRotation(node -> left);
                rightRotation(node);
            }
        }
        else if (balancefactor < -1)
        {
            if (getBalanceFactor(node -> right) <= 0)
            {
                // right right case
                leftRotation(node);
            }
            else
            {
                // right left case
                rightRotation(node -> right);
                leftRotation(node);
            }
        }

        node = node -> parent;
    }
}







// Public method: leftRotation
void avl::leftRotation(Node* node)
{
    cout << "\nLeft Rotation: " << node -> value << endl;
    Node* right = node -> right;
    Node* right_left = right -> left;

    // Perform the rotation
    right -> left = node;
    node -> right = right_left;

    // Update the parents
    right -> parent = node -> parent;

    if (node -> parent == nullptr)
    {
        root = right;
    }
    else if (node == node -> parent -> left)
    {
        node -> parent -> left = right;
    
    }
    else
    {
        node -> parent -> right = right;
    }
    node -> parent = right;

    if (right_left != nullptr)
    {
        right_left -> parent = node;
    }

    // Update the subtree_size
    node -> subtree_size = (node -> left ? node -> left -> subtree_size : 0) +
    (node -> right ? node -> right -> subtree_size : 0) + 1;

    right -> subtree_size = (right -> left ? right -> left -> subtree_size : 0) +
    (right -> right ? right -> right -> subtree_size : 0) + 1;

    // Update the height
    int left_height = node -> left ? node -> left -> height : 0;
    int right_height = node -> right ? node -> right -> height : 0;
    node -> height = 1 + (left_height > right_height ? left_height : right_height);

    left_height = right -> left ? right -> left -> height : 0;
    right_height = right -> right ? right -> right -> height : 0;

    right -> height = 1 + (left_height > right_height ? left_height : right_height);
}









// Public method: rightRotation
void avl::rightRotation ( Node* node)
{


    cout << "\nRight Rotation: " << node -> value << endl;
    Node* left = node -> left;
    Node* left_right = left -> right;

    // Perform the rotation
    left -> right = node;
    node -> left = left_right;

    // Update the parents
    left -> parent = node -> parent;

    if (node -> parent == nullptr)
    {
        root = left;
    }
    else if (node == node -> parent -> left)
    {
        node -> parent -> left = left;
    }
    else
    {
        node -> parent -> right = left;
    }

    node -> parent = left;

    if (left_right != nullptr)
    {
        left_right -> parent = node;
    }

    // Update the subtree_size
    node -> subtree_size = (node -> left ? node -> left -> subtree_size : 0) +
    (node -> right ? node -> right -> subtree_size : 0) + 1;

    left -> subtree_size = (left -> left ? left -> left -> subtree_size : 0) +
    (left -> right ? left -> right -> subtree_size : 0) + 1;

    // Update the height
    int left_height = node -> left ? node -> left -> height : 0;
    int right_height = node -> right ? node -> right -> height : 0;

    node -> height = 1 + (left_height > right_height ? left_height : right_height);
    
    left_height = left -> left ? left -> left -> height : 0;
    right_height = left -> right ? left -> right -> height : 0;

    left -> height = 1 + (left_height > right_height ? left_height : right_height);
}








// Helpter function: get the balance factor
int avl::getBalanceFactor ( Node* node )
{
    int left_height = node -> left ? node -> left -> height : 0;
    int right_height = node -> right ? node -> right -> height : 0;

    return left_height - right_height;
}







// Helper function: inorder traversal

void avl::inorder_traversal ( Node* node)
{
    if (node)
    {
        inorder_traversal(node -> left);
        cout << node -> value << " ";
        inorder_traversal(node -> right);
    }
}







// Public method: printAll
void avl::printAll ()
{
    inorder_traversal(root);
}




// Helper function: find by rank
Node* avl::findElementAtRank ( int rank )
{
    Node* current = root;
    int rank_so_far = 1;
    
    if (rank < 1 || rank > getSize())
    {
        return nullptr;
    }

    while (current != nullptr)
    {
        int current_rank = rank_so_far + (current -> left ? current -> left -> subtree_size : 0);

        if (rank == current_rank)
        {
            return current;
        }
        else if (rank < current_rank)
        {
            current = current -> left;
        }
        else
        {
            rank_so_far = current_rank + 1;
            current = current -> right;
        }
    }

    return nullptr;
}



// Helper function: inorder successor
Node* avl::inorder_successor ( Node* node )
{
    if (node -> right)
    {
        Node* current = node -> right;
        while (current -> left)
        {
            current = current -> left;
        }
        return current;
    }

    return nullptr;

}


// Helper function: inorder predecessor
Node* avl::inorder_predecessor ( Node* node )
{
    if (node -> left )
    {
        Node* current = node -> left;
        while (current -> right)
        {
            current = current -> right;
        }
        return current;
    }

    return nullptr;
}




// Public method: elementAtRank
int avl::elementAtRank ( int rank )
{
    Node* node = findElementAtRank (rank);
    return node ? node -> value : -1;
}




// Public method: replaceAtRank
bool avl::replaceAtRank ( int rank, int value )
{
    Node* node = findElementAtRank(rank);
    if (node)
    {
        node -> value = value;
        return true;
    }

    return false;
}


// Public method: removeAtRank
bool avl::removeAtRank ( int rank )
{
    Node* node = findElementAtRank(rank);
    if (node)
    {
        deleteNode(node);
        return true;
    }

    return false;
}


// Helper function: deleteNode
void avl::deleteNode( Node* node )
{
    if (node -> left && node -> right)
    {
        Node* successor = inorder_successor(node);
        node -> value = successor -> value;
        deleteNode(successor);
    }
    else
    {
        Node* child = node -> left ? node -> left : node -> right;
        if (child)
        {
            child -> parent = node -> parent;
            if (node == root)
            {
                root = child;
            }
            else if (node == node -> parent -> left)
            {
                node -> parent -> left = child;
            }
            else
            {
                node -> parent -> right = child;
            }
        }
    }

    rebalance (node -> parent);
    delete node;

}