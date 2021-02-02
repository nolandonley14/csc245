#include <iostream>
#include <cstdlib>
#include "bst.h"

using namespace std;

int main() {

    BinarySearchTree<int> T(0);

    T.insert(6);
    T.insert(2);
    T.insert(8);
    T.insert(1);
    T.insert(4);
    T.insert(3);
    T.postOrder();
    cout << "Height is: " << T.height() << endl;
    cout << "Number of leaves is: " << T.numLeaves() << endl;
    if (T.isBalanced())
    {
        cout << "Tree is Balanced" << endl;
    }
    else {
        cout << "Tree is not Balanced" << endl;
    }
    T.insert(9);
    cout << " inserted the 9" << endl;
    T.postOrder();
    cout << "Height is: " << T.height() << endl;
    cout << "Number of leaves is: " << T.numLeaves() << endl;
    if (T.isBalanced())
    {
        cout << "Tree is Balanced" << endl;
    }
    else {
        cout << "Tree is not Balanced" << endl;
    }

    return 0;
}
