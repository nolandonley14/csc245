#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int maxElemLength(const vector<string> &v); //Return # of chars of largest string in v
char GetChar(string entry, int k); // Return the kth char of entry
vector< queue<string> > ItemsToQueues(const vector<string> &L, int k); // create and return intermediate array of ten queues
vector<string> QueuesToArray(vector< queue<string> > &QA); // create and return new list from values of intermediate array of queues
void RadixSort(vector<string> &L, int numDigits); // calls both functions above to sort the list
void PrintVector(const vector<string> &L); // prints contents of vector with no modification
void PadStrings(vector<string> &L, int maxLength);
void UnPadStrings(vector<string> &L);


int main()
{
    vector<string> L;
    string a[] = {"zebra", "apple", "orange", "can", "candy", "a",
                    "top", "pumpkin", "today", "parade"};

    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++)
    {
        L.push_back(a[i]);
    }
    cout << "\nUnsorted Array: ";
    PrintVector(L);
    int big = maxElemLength(L);
    PadStrings(L, big);
    RadixSort(L, big);
    UnPadStrings(L);
    cout << "\n\nSorted Array: ";
    PrintVector(L);
    cout << "\n" << endl;
    return 0;
}

int maxElemLength(const vector<string> &v)
{
    int biggest = 0;
    for (int i=0; i < v.size(); i++)
    {
        if (v.at(i).size() >= biggest)
            biggest = v.at(i).size();
    }
    return biggest;
}

void PadStrings(vector<string> &L, int maxLength)
{
    for (int i = 0; i < L.size(); i++)
    {
        L.at(i).append(maxLength - L.at(i).length(), ' ');
    }
}

void UnPadStrings(vector<string> &L)
{
    for (int i = 0; i < L.size(); i++)
    {
        while(L.at(i).back() == ' ')
        {
            L.at(i).pop_back();
        }
    }
}

char GetChar(string entry, int k)
{
    return entry[k];
}

vector< queue<string> > ItemsToQueues(const vector<string> &L, int k)
{
    vector< queue<string> > step1;
    for (int i = 0; i < 128; i++)
    {
        queue<string> QA;
        for (int j=0; j < L.size(); j++)
        {
            if(GetChar(L.at(j), k) == i)
            {
                QA.push(L.at(j));
            }
        }
        step1.push_back(QA);
    }
    return step1;
}

vector<string> QueuesToArray(vector< queue<string> > &QA)
{
    vector<string> step2;
    for (int i=0; i < QA.size(); i++)
    {
        while(!QA.at(i).empty())
        {
		step2.push_back(QA.at(i).front());
		QA.at(i).pop();
	    }
    }
    return step2;
}

void RadixSort(vector<string> &L, int numDigits)
{
    for (int i = numDigits; i >= 0; i--)
    {
        vector< queue<string> > step = ItemsToQueues(L, i);
        L = QueuesToArray(step);
    }
}

void PrintVector(const vector<string> &L)
{
    for (int i=0; i < L.size(); i++)
    {
        cout << L.at(i) << " ";
    }
}
