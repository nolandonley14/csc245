#include <iostream>
#include "stack.h"

using namespace std;

void getToken(Stack<int> st, string expr);
int add(int num1, int num2);
int subtract(int num1, int num2);
int multiply(int num1, int num2);
int divide(int num1, int num2);
int mod(int num1, int num2);

int main() {

    char again = 'Y';
    string expression;
    do {
        Stack<int> s;
        cout << "Please enter the string: ";
        getline (cin, expression);
        getToken(s, expression);
        cout << "Go Again? (Y/N) ";
        cin >> again;
    } while (toupper(again) != 'N');
    return 0;
}


void getToken(Stack<int> st, string expr) {

    for(int i = 0; i < expr.length(); i++)
    {
        if (expr[i] == ';')
        {
            cout << st.topAndPop() << endl;
        }
        else if (expr[i] == ' ')
        {
            continue;
        }
        else if (expr[i] == '_')
        {
            string sub = "";
            while(isdigit(expr[i+1]))
            {
                sub += expr[i+1];
                i++;
            }
            int num = stoi(sub);
            cout << "Token is: " << 0 - num << "\tpush " << 0-num << endl;
            st.push(0-num);
        }
        else if (isdigit(expr[i]))
        {
            string sub = "";
            sub += expr[i];
            while(isdigit(expr[i+1]))
            {
                sub += expr[i+1];
                i++;
            }
            int num = stoi(sub);
            cout << "Token is: " << num << "\tpush " << num << endl;
            st.push(num);
        }
        else if (expr[i] == '*')
        {
            int num1 = st.topAndPop();
            int num2 = st.topAndPop();
            int result = multiply(num1, num2);
            cout << num1 << " * " << num2 << "\tpush " << result << endl;
            st.push(result);
        }

        else if (expr[i] == '/')
        {
            int num1 = st.topAndPop();
            int num2 = st.topAndPop();
            int result = divide(num1, num2);
            cout << num2 << " / " << num1 << "\tpush " << result << endl;
            st.push(result);
        }

        else if (expr[i] == '+')
        {
            int num1 = st.topAndPop();
            int num2 = st.topAndPop();
            int result = add(num1, num2);
            cout << num1 << " + " << num2 << "\tpush " << result << endl;
            st.push(result);
        }

        else if (expr[i] == '-')
        {
            int num1 = st.topAndPop();
            int num2 = st.topAndPop();
            int result = subtract(num1, num2);
            cout << num2 << " - " << num1 << "\tpush " << result << endl;
            st.push(result);
        }
    }
    //
    // while(!st.isEmpty())
    // {
        cout << st.topAndPop() << endl;
    // }
}

int add(int num1, int num2) {
    return num1 + num2;
}

int subtract(int num1, int num2) {
    return num2 - num1;
}

int multiply(int num1, int num2) {
    return num1 * num2;
}

int divide(int num1, int num2) {
    return num2 / num1;
}

int mod(int num1, int num2) {
    return num2 % num1;
}
