
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void Initialize(vector<int> &v, int num1, int num2, int num3, int num4, int num5);
void Print(vector<int> v);
void Reverse(vector<int> &v);

int main() {

    int vNum1, vNum2, vNum3, vNum4, vNum5;

    stack<string> s1, s2;
    s1.push("Hi there");
    s1.push("String 1");
    s2.push("Hi there");
    s2.push("String 2");

    if (s1 == s2) {
        cout << "equal";
    }
    else if (s1 < s2) {
        cout << "s1 < s2";
    }
    else if (s2 < s1) {
        cout << "s2 < s1";
    }
    else {
        cout << "IDK";
    }
    cout << endl;

    vector<int> v;
    //cout << v.size();
    cout << "Please enter the first number: ";
    cin >> vNum1;
    cout << "Please enter the second number: ";
    cin >> vNum2;
    cout << "Please enter the third number: ";
    cin >> vNum3;
    cout << "Please enter the fourth number: ";
    cin >> vNum4;
    cout << "Please enter the fifth number: ";
    cin >> vNum5;

    Initialize(v, vNum1, vNum2,vNum3, vNum4, vNum5);
    Print(v);
    Reverse(v);
    Print(v);
    sort(v.begin(), v.end());
    Print(v);
    return 0;
}

void Initialize(vector<int> &v, int num1, int num2, int num3, int num4, int num5)
{
    v.push_back(num1);
    v.push_back(num2);
    v.push_back(num3);
    v.push_back(num4);
    v.push_back(num5);
}

void Print(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void Reverse(vector<int> &v) {
    vector<int> v2;
    for (int i = v.size()-1; i >= 0; i--) {
        v2.push_back(v[i]);
    }
    v.clear();
    for (int i = 0; i < v2.size(); i++) {
        v.push_back(v2[i]);
    }
}
