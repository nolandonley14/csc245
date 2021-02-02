
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;

struct RecType {
    int age;
    float weight;
    char gender;
};

int main() {

    int num = 5;
    int *intPtr = NULL;
    intPtr = &num;
    *intPtr *= 10;
    cout << *intPtr << endl;

    RecType *recPtr;
    recPtr = new RecType;
    recPtr -> age = 25;
    recPtr -> weight = 190;
    recPtr -> gender = 'M';
    recPtr -> age+=5;
    cout << (*recPtr).age << " " << (*recPtr).weight << " " << (*recPtr).gender << endl;

    delete recPtr;
    recPtr = NULL;

    char *strPtr;
    strPtr = new char[50];
    char temp[] = "Operating Systems";
    strcpy(strPtr, temp);
    while (*strPtr != '\0') {
        cout << *strPtr;
        strPtr++;
    }
    cout << endl;
    int lowerCase = 0;
    strcpy(strPtr, temp);
    for (int i = 0; i < strlen(temp); i++) {
        if (islower(*strPtr)) {
            lowerCase++;
        }
        strPtr++;
    }
    cout << lowerCase << endl;

    strcpy(strPtr, temp);
    strPtr+=10;
    while (*strPtr != '\0') {
        cout << *strPtr;
        strPtr++;
    }
    cout << endl;

    strPtr-=10;
    delete strPtr;
    
    return 0;
}
