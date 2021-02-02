#include <queue>
#include <iostream>
#include <string>

using namespace std;

void insert(priority_queue<string> &pq);
void print(priority_queue<string> &pq);

int main() {

    priority_queue<string> pq;
    insert(pq);
    print(pq);
    return 0;
}

void insert(priority_queue<string> &pq) {
    pq.push("Nolan");
    pq.push("Andy");
    pq.push("Trevor");
    pq.push("Steven");
    pq.push("Usman");
    pq.push("Mikae");
    pq.push("Colton");
    pq.push("Morrice");
    pq.push("Grant");
    pq.push("Michael");
}

void print(priority_queue<string> &pq) {
    priority_queue<string> local = pq;
    while (!local.empty())
    {
        cout << local.top() << " ";
        local.pop();
    }
    cout << "\n";
}
