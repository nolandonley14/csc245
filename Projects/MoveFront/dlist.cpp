#include <cstddef>
#include <iostream>

using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList()
{
	// Post: List is empty; All items have been deallocated.
	makeEmpty();
}

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
	NodeType<ItemType> *temp = head;
	while(temp != NULL)
	{
		deleteItem(temp -> info);
		temp = temp -> next;
	}
	length = 0;
}

template <class ItemType>
void DList<ItemType>::reverseList()
{
    // Post: List is empty; all items have been deallocated.
	NodeType<ItemType> *temp = head;
	NodeType<ItemType> *temp2 = NULL;

    while(temp != NULL) {
		temp2 = temp -> back;
		temp -> back = temp -> next;
		temp -> next = temp2;
		temp = temp -> back;
	}
	if (temp2 != NULL)
	{
		temp2 = temp2 -> back;
		head = temp2;
	}
}

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)
{
	//  Pre :  item to be deleted is passed in via parameter
	NodeType<ItemType> *temp = head;
	// Pre  : List is not
	while(temp != NULL)
	{
		if (temp -> info == item) {
			if (temp == head) {
				head = temp -> next;
			}
			if (temp -> next != NULL) {
				temp -> next -> back = temp -> back;
			}
			if (temp -> back != NULL) {
				temp -> back -> next = temp -> next;
			}
			if (temp -> next == NULL && temp -> back == NULL)
			{
				head = NULL;
			}
			delete temp;
			length--;
			break;
		}
		else
		{
			temp = temp -> next;
		}
	}
        // Post :  item is deleted if it exists in list
}

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter
	NodeType<ItemType> *temp = head;
	// Pre  : List is not
	while(temp != NULL)
	{
		if (temp -> info == item) {
			return true;
		}
		else
		{
			temp = temp -> next;
		}
	}
	return false;
        // Post :  function returns bool value if item is found
}

template <class ItemType>
bool DList<ItemType>::isEmpty() const
{
	// Post : function returns true if list is empty, false otherwise
	return head == NULL;
}

template <class ItemType>
void DList<ItemType>::print() const
{
	NodeType<ItemType> *temp = head;
	// Pre  : List is not
	if (temp == NULL) {
		return;
	}
	else {
		while(temp != NULL)
		{
			cout << temp -> info << endl;
			temp = temp -> next;
		}
	}
	// Post : Items in List have been printed to screen
}

template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)
{
	//  Pre : item to be inserted is passed in via parameter
	NodeType<ItemType> *newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> back = NULL;
	if (head == NULL) {
		newNode -> next = NULL;
	}
	else {
		head -> back = newNode;
		newNode -> next = head;
	}
	head = newNode;
	length++;
        // Post : item is inserted at head of list;  Former first node is
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty
}

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
	NodeType<ItemType> *newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> next = NULL;
	newNode -> back = NULL;
	if (head == NULL) {
		head = newNode;
	}
	else {
		NodeType<ItemType> *temp = last();
		newNode -> back = temp;
		temp -> next = newNode;
	}
	length++;
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link
}

template <class ItemType>
int DList<ItemType>::Least(int start)
{
	//  Pre :  list is to be sorted
	int least;
	NodeType<ItemType> *temp = head;
	for (int i=0; i<start; i++)
	{
		temp = temp -> next;
	}
	least = temp -> info;
	while(temp != NULL)
	{
		if (temp -> info < least)
		{
			least = temp -> info;
		}
		else
		{
			temp = temp -> next;
		}
	}
	return least;
        // Post :  list is sorted
}

template <class ItemType>
int DList<ItemType>::lengthIs() const
{
	// Post : Function returns current length of list
	return length;
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const
{
	//  Pre : item to be located is passed in via parameter
	NodeType<ItemType> *temp = head;
	// Pre  : List is not
	while(temp != NULL)
	{
		if (temp -> info == item) {
			return temp;
		}
		else
		{
			temp = temp -> next;
		}
	}
	return NULL;
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned

}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const
{
	// Post : Function returns location of current last item in list
	NodeType<ItemType> *temp = head;
	while(temp -> next != NULL)
	{
		temp = temp -> next;
	}
	return temp;
}

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)
{
	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
	if (inList(delPtr -> info)) {
		deleteItem(delPtr -> info);
		length--;
	}

	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
}
