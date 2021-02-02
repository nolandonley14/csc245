#include <fstream>
#include <iostream>
using namespace std;

#include <string>
#include "stack.h" 

struct AdviceNode
{
  string QorA;      // a question or an answer
  AdviceNode * yes;   // yes branch
  AdviceNode * no;    // no branch

  AdviceNode(const string & s);  // constructor
};

AdviceNode::AdviceNode(const string & s)
: QorA(s),
  yes(NULL),
  no(NULL)
{}

void ReadTree(istream & in, AdviceNode * & T);

bool IsQuestionNode(AdviceNode * T);
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false

void GiveAdvice(AdviceNode * T);
// precondition: T is not NULL

bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack);
// precondition:  T is not NULL

void ShowPath(const Stack<string> & pathStack);

int main()
{
  string fname;
  cout << "Enter advice tree file: ";
  cin  >> fname; cin.ignore();

  ifstream treeIn(fname.c_str());

  AdviceNode * T;
  ReadTree(treeIn, T);

  GiveAdvice(T);

  string movie;
  Stack<string> path;

  cin.ignore();

  while(movie != "q"){
    cout << "Enter movie (q to quit): ";
    getline(cin, movie);
    if(movie != "q"){
      path.makeEmpty();
      TracePath(T, movie, path);
      ShowPath(path);
    }
  }

  return 0;
}

void ReadTree(istream & in, AdviceNode * & T)
{
  string QA;

  getline(in, QA);
  T = new AdviceNode(QA);
  if(QA[QA.length()-1] != '?'){
    T->yes = NULL;
    T->no  = NULL;
  }
  else{
    ReadTree(in, T->yes);
    ReadTree(in, T->no);
  }
}

bool IsQuestionNode(AdviceNode * T)
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false
{
  return (T->QorA[(T->QorA).length()-1] == '?');
}

void GiveAdvice(AdviceNode * T)
{
  char response;
  if(IsQuestionNode(T)){
    cout << T->QorA << " ";
    cin  >> response;
    if(response == 'Y')
      GiveAdvice(T->yes);
    else
      GiveAdvice(T->no);
  }
  else{
    cout << T->QorA << endl;
  }
}


bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack)
{
  bool found;

  if(IsQuestionNode(T)){
    found = TracePath(T->yes, movie, pathStack);
    if(found){
      pathStack.push((T->QorA) + " Yes");
      return true;
    }
    found = TracePath(T->no, movie, pathStack);
    if(found){
      pathStack.push(T->QorA + " No");
      return true;
    }
    return false;
  }
  if(T->QorA == movie){
    pathStack.push(movie);
    return true;
  }
  return false;
}


void ShowPath(const Stack<string> & pathStack)
{
  Stack<string> path(pathStack);

  while(!path.isEmpty()){
    cout << path.top() << endl;
    path.pop();
  }
}
