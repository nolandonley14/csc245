#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

struct BetNode {
        char info;
        BetNode* left;
        BetNode* right;
};

string inToPost(string expr);
bool isOperator(char ch);
bool higherPrecendence(char top, char input);
void buildTree(string s);
void preOrder(BetNode *tracker);

int main() {
    string line;
    ifstream expressionFile ("infix.dat");
    if (expressionFile.is_open())
    {
        while ( getline (expressionFile,line) )
        {
        buildTree(inToPost(line));
        cout << endl;
        }
        expressionFile.close();
    }
    return 0;
}

bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%')
        return true;
    else
        return false;
}

bool higherPrecendence(char top, char input) {
    if (top == input)
        return true;
    if ((top == '*') || (top == '/'))
        return true;
    if ((top == '+') || (top == '-'))
        if ((input == '+') || (input == '-'))
            return true;
    if (top == ')')
        return false;
    return false;
}

string inToPost(string expr) {
    string postFixExpr;
    Stack<char> st;
    for(int i = 0; i < expr.length(); i++)
    {

        if (isdigit(expr[i]))
        {
            string sub = "";
            sub += expr[i];
            while(isdigit(expr[i+1]))
            {
                sub += expr[i+1];
                i++;
            }
            postFixExpr += sub;
            postFixExpr += ' ';
        }

        else if (expr[i] == '(')
        {
            st.push(expr[i]);
        }

        else if (isOperator(expr[i]))
        {
            while(higherPrecendence(st.top(), expr[i])) {
                postFixExpr += st.topAndPop();
                postFixExpr += ' ';
            }
            st.push(expr[i]);
        }

        else if (expr[i] == ')')
        {
            while(st.top() != '(')
            {
                postFixExpr += st.topAndPop();
                postFixExpr += ' ';
            }
            st.pop();
        }

        else if (expr[i] == -1)
        {
            cout << "end of input" << endl;
            while(!st.isEmpty())
            {
                postFixExpr += st.topAndPop();
                postFixExpr += ' ';
            }
        }
    }
    return postFixExpr;
}

void buildTree(string s) {
    Stack<BetNode* > st;

    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
        {
            BetNode* node = new BetNode;
            BetNode* child1 = new BetNode;
            BetNode* child2 = new BetNode;
            node -> info = s[i];
            node -> right = NULL;
            node -> left = NULL;
            st.push(node);
        }

        else if (isOperator(s[i]))
        {
            BetNode* node = new BetNode;
            BetNode* child1 = new BetNode;
            BetNode* child2 = new BetNode;
            child1 = st.topAndPop();
            child2 = st.topAndPop();
            node -> info = s[i];
            node -> left = child2;
            node -> right = child1;
            st.push(node);
        }
    }

    preOrder(st.top());
}

void preOrder(BetNode *ptr)
{
	if(ptr != NULL)
	{
        cout<< ptr -> info << " ";
        preOrder(ptr -> left);
		preOrder(ptr -> right);
	}


}
