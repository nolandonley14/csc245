#include <iostream>
using namespace std;
#include "dlist.h"

char PrintMenu();
void HeadInsert(DList<int> &list);
void TailInsert(DList<int> &list);
void PrintList(const DList<int> &list);
void PrintLength(const DList<int> &list);
void AccessItem(DList<int> &list);
void Delete(DList<int> &list);
void FindAndMove(DList<int> &list, int num);
void Find(const DList<int> &list);
void SortList(DList<int> &list);
char addDuplicate();

int main() {

    DList<int> list;
    char selection;

    do
    {
        selection = PrintMenu();
        switch (toupper(selection))
        {
            case 'H' : HeadInsert(list); break;
            case 'T' : TailInsert(list); break;
            case 'F' : Find(list); break;
            case 'P' : PrintList(list); break;
            case 'A' : AccessItem(list); break;
            case 'D' : Delete(list); break;
            case 'L' : PrintLength(list); break;
            case 'S' : SortList(list); break;
            case 'Q' : cout << "\tExiting Program...\n"; break;
            default : cout << "\tError. Try again." << endl;
        }
    } while (toupper(selection) != 'Q');

}

char PrintMenu() {
    char sel;
    cout << endl;
    cout << "\tEnter 'H' for insert head, \n";
    cout << "\tEnter 'T' for insert tail, \n";
    cout << "\tEnter 'P' for print list, \n";
    cout << "\tEnter 'L' for print length, \n";
    cout << "\tEnter 'A' for access item, \n";
    cout << "\tEnter 'D' for erase list, \n";
    cout << "\tEnter 'F' to look for an item, \n";
    cout << "\tEnter 'S' to sort the list, \n";
    cout << "\tEnter 'Q' to quit the program: \t";
    cin >> sel;
    return sel;
}

void HeadInsert(DList<int> &list) {
    int variable;
    char answer;
    cout << "\nEnter value to insert: ";
    cin >> variable;
    if (list.inList(variable)) {
        do
        {
            answer = addDuplicate();
            switch (toupper(answer))
            {
                case 'Y' : list.insertHead(variable); break;
                case 'N' : cout << "\tThe item will not be inserted.\n" << endl; break;
                default : cout << "\tPlease enter Y or N." << endl;
            }
        } while (toupper(answer) != 'Y' && toupper(answer) != 'N');
    }
    else {
        list.insertHead(variable);
    }
}

char addDuplicate() {
    char ans;
    cout << ans;
    cout << "\nThis item is already in the list. Would you like to add a duplicate? (Y/N): ";
    cin >> ans;
    return ans;
}

void TailInsert(DList<int> &list) {
    int variable;
    char answer;
    cout << "\nEnter value to insert: ";
    cin >> variable;
    if (list.inList(variable)) {
        do
        {
            answer = addDuplicate();
            switch (toupper(answer))
            {
                case 'Y' : list.appendTail(variable); break;
                case 'N' : cout << "\tThe item will not be inserted.\n" << endl; break;
                default : cout << "\tPlease enter Y or N." << endl;
            }
        } while (toupper(answer) != 'Y' && toupper(answer) != 'N');
    }
    else {
        list.appendTail(variable);
    }
}

void PrintList(const DList<int> &list) {
    if (list.isEmpty()) {
        cout << "\nThe list is empty. \n";
        return;
    }
    list.print();
}

void PrintLength(const DList<int> &list) {
    cout << list.lengthIs() << endl;
}

void AccessItem(DList<int> &list) {
    int variable;
    if (list.isEmpty()) {
        cout << "\nThe list is empty. \n";
        return;
    }
    cout << "\nEnter value to access: ";
    cin >> variable;
    FindAndMove(list, variable);

}

void Delete(DList<int> &list) {
    int variable;
    if (list.isEmpty()) {
        cout << "\nThe list is empty. \n";
        return;
    }
    cout << "\nEnter value to delete: ";
    cin >> variable;
    if (list.inList(variable)){
        list.deleteItem(variable);
    }
    else {
        cout << "\nThe value you want to delete is not in the list.\n";
    }
}

void Find(const DList<int> &list) {
    int variable;
    cout << "\nEnter value to find: ";
    cin >> variable;
    if (list.inList(variable)) {
        cout << "\n" << variable << " has been found.\n" << endl;
    }
    else {
        cout << "\n" << variable << " has not been found.\n" << endl;
    }

}

void FindAndMove(DList<int> &list, int num) {
    if (list.inList(num)) {
        list.deleteItem(num);
        list.insertHead(num);
        cout << "\n" << num << " has been found, and is now the head of the list.\n" << endl;
    }
    else {
        cout << "\n" << num << " is not in the list.\n" << endl;
    }
}

void SortList(DList<int> &list) {
    for (int i=0; i < list.lengthIs(); i++)
    {
        int num = list.Least(i);
        list.deleteItem(num);
        list.insertHead(num);
    }
    list.reverseList();
    cout << "\nThe list has been sorted\n";
}
