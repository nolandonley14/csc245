
#include <queue>
#include <string>

const int TREE_SIZE = 300;

typedef string ComponentType;

struct TreeNode;  // Forward Declaration 
typedef TreeNode *TreePtr;
struct TreeNode
{
        ComponentType Component;
        TreePtr LeftChild;
        TreePtr RightChild;
	queue<int> LineNums;
};

class Tree
{
public:
	Tree();
	~Tree();
	Tree (const Tree& otherTree);
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int CountNodes() const;
  	bool Find(ComponentType item) const;
	void Insert(ComponentType item, int lineNum);
  	void Delete(ComponentType item);
	void Inorder() const;
        bool operator == (const Tree& otherTree) const;
private:
	TreePtr root;

	bool Find(TreePtr t, ComponentType item) const; 
	int CountNodes (TreePtr t) const; 
	void Inorder (TreePtr t) const;
	void Insert (TreePtr& t, ComponentType item, int lineNum);
	void Delete (TreePtr& t, ComponentType item); 
	void DeleteNode (TreePtr& t); 
	ComponentType GetSuccessor (TreePtr t); 
	void CopyTree (TreePtr& toPtr, TreePtr fromPtr);
	void Destroy (TreePtr& root); 
        bool Duplicate (TreePtr t1, TreePtr t2) const;
	void PrintLines(queue<int>& lineQ) const;
};
