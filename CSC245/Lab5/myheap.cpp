#include <iostream>
#include "BinaryHeap.h"

using namespace std;

int main() {

    BinaryHeap<char> PQ(50);
    for(int i=65; i<=74; i++)
        PQ.insert(i);
    PQ.printLeaves();
    PQ.deleteMin();
    cout << "Printing Left Subtree of the Root of the Heap: ";

    cout << "\nThe height of the Heap is: " << PQ.Height() << endl;
    cout << "The Maximum Value of the Heap is: " << PQ.findMax() << endl;

    return 0;
}
