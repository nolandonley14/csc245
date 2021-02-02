Nolan Donley
Project 1 Questions
*********************
1. The attributes of the DList class and why templates are being used.

DList consists of the NodeType struct, a constructer, destructor, various
public functions, and some private functions and variables. Templates are
being used so that we can use this same DList class with different data types.

2. A description of each of the operations of the DList class.

- isEmpty – returns a bool indicating whether or not list is empty.
- inList – returns a bool indicating whether or not a given item sent
            in as a parameter is in the list.
- makeEmpty – deallocates all memory used by list, and sets head pointer
                of list to NULL.
- insertHead - inserts an item sent in as a parameter onto the head
                of the list.
 - appendTail – inserts an item sent in as a parameter onto the tail
                of the list.
 - print – prints the info stored in each node of the list.
 - lengthIs - returns the current length of the list.
 - deleteItem – deletes the item from the list sent in as a parameter
                from the list after finding it via inList and then
                deleting the location of that item via deleteLocation
- reverseList - reverses the order of the list.
- least - starting at the node of the int passed as a parameter, this
            function returns the node whos info is the lowest number.

- last – returns a pointer to the current last node in the list.
- location – returns a pointer to a node containing the item sent
            in as a parameter. If the item is not found, it returns NULL.
- deleteLocation – deletes the location sent in as a parameter from the
                list, and resets preceding and succeeding nodes.

3. The role of the move to front algorithm.

The role of the move to front algorithm is to make searching for
an item more efficient. After looking for an item in the list, it is
moved to the font of the list, and therefore, if it needs to be accessed
again, it is closer to the front.

4. A description of the main algorithm followed by the client program.

The main algorithm creates a DList object that hold integers. Then
creates a variable to hold a character named selection. Then until the
user enters 'q' or 'Q' on the keyboard the program prints out the list of
operations that the user can perform on their DList. Based on the users input,
the main function calls the apropriate function to carry out the desired
operation. When the user enters 'q' or 'Q', the program ends.
