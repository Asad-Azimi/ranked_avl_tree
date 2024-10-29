#include "avl.h"

int main()
{
    avl tree;
    tree.insertAtRank(1, 10);
    tree.insertAtRank(1, 20);
    tree.insertAtRank(1, 30); // (2, 30)
    tree.insertAtRank(3, 40);//
    // tree.insertAtRank(2, 50);//
    // tree.insertAtRank(2, 60);
    // tree.insertAtRank(1, 70);
    // tree.insertAtRank(1, 80);
    // tree.insertAtRank(8, 90);//
    // tree.insertAtRank(1, 100);
    // tree.insertAtRank(1, 0);
    // tree.insertAtRank(1, 110);
    // tree.insertAtRank(1, 120);
    // tree.insertAtRank(1, 130);
    // tree.insertAtRank(2, 140);
    // tree.insertAtRank(3, 145);
    // tree.insertAtRank(4, 150);
    // tree.insertAtRank(5, 160);
    // tree.insertAtRank(3, 145);
    // tree.insertAtRank(4, 150);
    tree.printAll();
    cout << endl;
    tree.removeAtRank(3);
    tree.printAll();
    

    return 0;
}