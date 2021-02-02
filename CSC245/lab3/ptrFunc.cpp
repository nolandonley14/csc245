
#include <iostream>
using namespace std;

bool func1(double *ptr1, double *ptr2) {
    if (*ptr1 == *ptr2) {
        return true;
    }
    else {
        return false;
    }
}

bool func2(double *ptr1, double *ptr2) {
    if (ptr1 == ptr2) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    double *ptrOne = new double;
    double *ptrTwo;
    ptrTwo = ptrOne;
    *ptrOne = 12;
    *ptrTwo = 14;
    cout << func1(ptrOne, ptrTwo) << endl;
    cout << func2(ptrOne, ptrTwo) << endl;
    return 0;
}
