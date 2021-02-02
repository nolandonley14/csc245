
#include "tree.h"
#include <iostream> 

Tree::Tree()
{
	root = NULL;
}

Tree::~Tree()
{
	Destroy (root);
}

void Tree::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}

void Tree::Destroy (TreePtr& root)
{
	if (root != NULL)
	{
		Destroy (root -> LeftChild);
		Destroy (root -> RightChild);
		delete root;
	}
}

bool Tree::IsEmpty () const
{
	return (root == NULL);
}

bool Tree::IsFull () const
{
	return (CountNodes() == TREE_SIZE);
}	

Tree::Tree (const Tree& otherTree)
{
	CopyTree (root, otherTree.root);
}

void Tree::CopyTree (TreePtr& toPtr, TreePtr fromPtr) 
{
	if (fromPtr == NULL)
		toPtr = NULL;
	else
	{
		toPtr = new TreeNode;
		toPtr -> Component = fromPtr -> Component;
		toPtr -> LineNums = fromPtr -> LineNums;
		CopyTree (toPtr -> LeftChild, fromPtr -> LeftChild);
		CopyTree (toPtr -> RightChild, fromPtr -> RightChild);
	}
}
		
void Tree::Inorder(TreePtr t) const
{
	if (t != NULL)
	{
		Inorder(t -> LeftChild);
	 	cout << "\t" << t -> Component << ", ";
		PrintLines(t -> LineNums);
		Inorder(t -> RightChild);
	}
}

void Tree::PrintLines(queue<int>& lineQ) const
{
	queue<int> copy = lineQ;
	for (; ! copy.empty();  copy.pop())
	{
		cout << copy.front();

		if (copy.size() != 1)
			cout << ", ";
	}
	cout << endl;
}
	
void Tree::Inorder() const
{
	Inorder(root);
        cout << endl;
}
	
void Tree::Insert(TreePtr& t, ComponentType item, int lineNum)
{
	if (t == NULL)
	{
	  t = new TreeNode;
	  t -> LeftChild = NULL;
	  t -> RightChild = NULL;
	  t -> Component = item;		
	  t -> LineNums.push(lineNum);
	}
        else if (item == t -> Component)
        {
           if (lineNum != t->LineNums.back())
             t -> LineNums.push(lineNum);
        }
	else if (item < t -> Component)
	   Insert(t->LeftChild, item, lineNum);
	else
	   Insert(t->RightChild, item, lineNum);
}

void Tree::Insert (ComponentType item, int lineNum)
{
	Insert(root, item, lineNum);
}

int Tree::CountNodes () const
{
	return (CountNodes(root));	
}

int Tree::CountNodes(TreePtr t) const
{
	if (t == NULL)
		return 0;
	else
		return (CountNodes(t->LeftChild) +
		        CountNodes(t->RightChild) + 1 );
}

bool Tree::Find(ComponentType item) const
{
	return Find(root, item);
}

bool Tree::Find(TreePtr t, ComponentType item) const
{
	if (t == NULL)
		return false;
	else if (t->Component == item)
		return true;
	else if (item < t->Component)
		return Find(t->LeftChild, item);
	else
		return Find(t->RightChild, item);
}

void Tree::Delete(ComponentType item)
{
	Delete(root, item);
}

void Tree::Delete(TreePtr& t, ComponentType item)
{
	if (item < t->Component)
	 	Delete (t-> LeftChild, item);  //Look in Left Subtree
	else if (item > t-> Component)
		Delete (t-> RightChild, item); //Look in Right Subtree 
	else
		DeleteNode (t);        //  Node found;  call DeleteNode
}

void Tree::DeleteNode (TreePtr& t)
{
	ComponentType data;
	TreePtr	tempPtr = t;

	if ( (t -> LeftChild) == NULL ) 
	{
		t = t -> RightChild;
		delete tempPtr;
	}
	else if ( (t -> RightChild) == NULL ) 
	{
		t = t -> LeftChild;
		delete tempPtr;
	}
	else
	{
		data = GetSuccessor (t->RightChild);
		t->Component = data;
		Delete (t -> RightChild, data);
	}

}

ComponentType Tree::GetSuccessor (TreePtr t)
{
	while (t -> LeftChild != NULL)
		t = t -> LeftChild;
	
	return t -> Component;
}

bool Tree::operator == (const Tree& otherTree) const
{
	return (Duplicate(root, otherTree.root));
}

bool Tree::Duplicate(TreePtr t1,  TreePtr t2)  const
{
       if ( (t1 == NULL) && (t2 == NULL) )
                return true;
       else if (CountNodes(t1) != CountNodes(t2))
                return false;
       else if ( t1->Component != t2->Component )
                return false;
       else
        return (true &&
        Duplicate(t1->LeftChild,t2->LeftChild) &&
        Duplicate(t1->RightChild,t2->RightChild) );
}
