// Computing Structures Fall 2022
// Project 5

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
protected:
	// Instance Variables
	DT* _info;
	int _left;
	int _right;

public:
	// Constructors and Destructor
	ArrayBTNode();								//Default constructor
	ArrayBTNode(DT& info);						//Non - Default constructor
	~ArrayBTNode();								//Destructor

	// getter Methods
	DT* getInfo();								// It will return the Info of the node
	int getLeft();								// It will return the Left index value of the node
	int getRight();								// It will return the Left index value of the node

	// setter Methods
	void setInfo(DT& info);						// This will set the Info of the node
	void setInfoNull(); // Sets _info to Null	// This method will set Info of the node to NULL
	void setLeft(int left);						// This method will set left index value
	void setRight(int right);					// This method will set right index value

	// Display Method
	// Outputs data in _info, _left, _right
	void display();								// The display method of the Array BT node will display the Node details

	// Overloaded Comparison Operators
	// Used for comparing _info field with other ArrayBTNodes
	bool operator<(const ArrayBTNode<DT>& x);	// operator overloading to compare two Node Infos of DT data type
	bool operator>(const ArrayBTNode<DT>& x);
	bool operator==(const ArrayBTNode<DT>& x);
	bool operator>=(const ArrayBTNode<DT>& x);
	bool operator<=(const ArrayBTNode<DT>& x);
	bool operator!=(const ArrayBTNode<DT>& x);

	// TODO: Overloaded Ostream Operator - Uses display method to output ArrayBTNode contents
	friend ostream& operator << (ostream& s, ArrayBTNode<DT>& g)	// ostream operator for ArrayBTNode
	{
		g.display(s);										//using ostream object g to call the display method.
		return s;
	};
};
template <class DT>
ArrayBTNode<DT>::ArrayBTNode() {				// Initializing the info value to NULL and left and right indexes to -1
	_info = NULL;
	_left = -1;
	_right = -1;
};

template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT& info)			// Non - default constructor
{
	_info = new DT(info);						// creating a pointer by using new and setting left and right indexes to -1
	_left = -1;
	_right = -1;
};

template <class DT>
void ArrayBTNode<DT>::setInfo(DT& info)
{
	delete _info;								// deleting the previous _info
	_info = new DT(info);						// creating a new pointer.
};

template <class DT>
void ArrayBTNode<DT>::setInfoNull()				// setting the _info to NULL
{
	_info = NULL;
};

template <class DT>
void ArrayBTNode<DT>::setLeft(int left)			// Setting the _left value to left index
{
	_left = left;
};

template <class DT>
void ArrayBTNode<DT>::setRight(int right)		// Setting the _right value to right index
{
	_right = right;
};

template <class DT>
DT* ArrayBTNode<DT>::getInfo() {				// Getter method to get the _info
	return _info;
};

template <class DT>
int ArrayBTNode<DT>::getLeft() {				// Getter method to get the left index
	return _left;
};

template <class DT>
int ArrayBTNode<DT>::getRight() {				// Getter method to get the right index
	return _right;
};

template <class DT>
bool ArrayBTNode<DT>::operator < (const ArrayBTNode<DT>& x) {
	return ((*_info)) < *(x._info);				// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
bool ArrayBTNode<DT>::operator > (const ArrayBTNode<DT>& x) {
	return ((*_info)) > *(x._info);				// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
bool ArrayBTNode<DT>::operator == (const ArrayBTNode<DT>& x) {
	return ((*_info)) == *(x._info);			// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
bool ArrayBTNode<DT>::operator >= (const ArrayBTNode<DT>& x) {
	return ((*_info)) >= *(x._info);			// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
bool ArrayBTNode<DT>::operator <= (const ArrayBTNode<DT>& x) {
	return ((*_info)) <= *(x._info);			// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
bool ArrayBTNode<DT>::operator != (const ArrayBTNode<DT>& x) {
	return ((*_info)) != *(x._info);			// Comparing the two DT type variables and returning boolean value ( Operator overloading )
};

template <class DT>
void ArrayBTNode<DT>::display()					// Display method to display Node details( _info, _left and _right)
{												// printraw() will call this method to display Raw Tree data.
	cout << ": Info: " << *(this->getInfo()) << ", Left: " << this->getLeft() << ", Right: " << this->getRight() << endl;
};

template <class DT>
ArrayBTNode<DT>::~ArrayBTNode()					// ArrayBT Node destructor, deleting the _info and setting indexes back to -1
{
	delete _info;
	_left = -1;
	_right = -1;
};
////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT> > _tree;			// Vector of ArrayBTNodes used to create a tree
	int _rootIndex;							// Index of the root node in _tree
	int _numNodes;							// Number of nodes in the tree
	int _size;								// Maximum size of the _tree array
	stack<int> _freeLocations;				// Stack containing indexes of freeLocations in the _tree array

public:
	// Constructors and Destructor
	ArrayBST();							// Default constructor
	ArrayBST(int k);					// initialize the vector with NULL nodes and fill the stack
	~ArrayBST();						// Destructor

	// Accessor Methods
	bool isEmpty() const;				// This method will check if the tree is empty or not.
	int Height();						// This method will check the height of the tree.
	int _height(int h);					// helper method for height of the tree
	int Size();							// The method will check size of the tree.
	int rootIndex();					// The method will return the rootIndex of the tree
	int maxSize();						// the method will return the max available nodes in the tree.

	// Mutator Methods
	void setData(int index, DT& value);		// setting the _info data
	void setLeft(int index, int value);		// setting the left index
	void setRight(int index, int value);	// setting the right index

	// Display methods and traversals
	void display(ostream& os) ;				// display method to call the Preorder and Inorder
	void displayPreOrder(ostream& os) ;		// to display nodes in Preorder
	void displayInOrder(ostream& os) ;		// to display nodes in Ineorder
	void printRaw();						// Display the array and all of its contents

	// BST Specific Methods
	void insert(DT& object);				// To insert elements in Node _info
	bool find(DT& object);					// To find a node element by traversing through tree and returning the boolean
	int findIndex(DT& object);				// To find the Index of the given node element by traversing throught the tree.
	int _findIndex(DT& object, int pos);				//helper method to find index
	//void remove(DT& object); // extra credit
	bool _find(DT& object, int pos);					//helper method to find the object position
	void _preOrder(int p);								//helper method to display preorder method
	void _inOrder(int i);								//helper method to display inorder method

	// TODO: Overridden ostream operator for ArrayBST - this will call the pre order and in order methods
	friend ostream& operator << (ostream& s, ArrayBST<DT>& g)	// ostream operator for ArrayBST
	{
		g.display(s);											//using ostream object g to call the display method.
		return s;
	};
};

template <class DT>
ArrayBST<DT>::ArrayBST() {					// Default constructor
	_rootIndex = -1;						// setting all the variables to -1
	_numNodes = -1;
	_size = -1;
	_freeLocations = -1;
};

template <class DT>
ArrayBST<DT>::ArrayBST(int k)				// Non - default constructor
{
	_tree.reserve(k);						// Allocating the memory location as per number of input
	_size = k;								// Assigning the max size to _size.
	_rootIndex = k - 1;						// Root index will be k - 1 (0 to k -1)
	_numNodes = 0;							// Counter to check the number of nodes positions filled in tree _vector
	for (int i = 0; i < k;i++)				// Storing the k values in stack ( ex: 0 will be stored at 0th position )
		_freeLocations.push(i);
	for (int i = 0; i < k;i++)				// Initializing all the Nodes values to NULL
		_tree.push_back(ArrayBTNode<DT>());
};

template <class DT>
bool ArrayBST<DT>::isEmpty() const {		// checking the Empty positions in _tree
	if ((maxSize() - Size()) == 0)			// If there are empty positions it will return true or else false
		return false;						// Subtracting maxSize() and available size
	else return true;
};

template <class DT>
int ArrayBST<DT>::Height()					// This method will give the height of the tree
{
	return (this->_height(_rootIndex));		// calling the helper Height method
};

template <class DT>
int ArrayBST<DT>::_height(int h)			// helper method for height
{
	int heightLeft = 0, heightRight = 0;	// Initializing the variables for left and right height 
	if(_tree[h].getLeft() != -1)			// checking for left index if its not -1 
		heightLeft = heightLeft + _height((_tree[h].getLeft()));	// If yes, It will recursively call the method
	if(_tree[h].getRight() != -1)			// checking for right index if its not -1
		heightRight = heightRight + _height((_tree[h].getRight()));	// If yes, It will recursively call the method
	if (heightLeft > heightRight)			// It will return the largest of the counters
		return heightLeft + 1;				
	else
		return heightRight + 1;
};

template <class DT>
int ArrayBST<DT>::Size() {
	return maxSize() - _numNodes;			// This method will return available size by calling maxSize() and numNodes
};

template <class DT>
int ArrayBST<DT>::rootIndex() {				// This method will return _rootIndex which is the (max number of nodes - 1)
	return _rootIndex;
};

template <class DT>
int ArrayBST<DT>::maxSize() {				// This method will return the max number of nodes a tree can store
	return _size;
};

template <class DT>
void ArrayBST<DT>::setData(int index, DT& value)	// This method will set the _info value to insert element value
{
	_tree[index].setInfo(value);
};

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value)	// This method will set the _left to Left Index value of the node
{
	_tree[index].setLeft(value);
};

template <class DT>
void ArrayBST<DT>::setRight(int index, int value)	// This method will set the _right to Right Index value of the node
{
	_tree[index].setRight(value);
};

template <class DT>
void ArrayBST<DT>::insert(DT& object)				// Insert method used to insert node values in the tree.
{
	if (_freeLocations.size() == 0 && _numNodes == _size)  // Checking if the tree is full by checking the stack size and numNodes size.
	{
		cout << "Cannot insert data, BST Full."<<endl;     // Displaying the if the tree is full
		return;
	}
	int freeInd = _freeLocations.top();				// storing the top of the stack in freeInd variable
	_freeLocations.pop();							// popping that stack value
	_numNodes++;									// Incrementing numNodes as a counter to check the number of nodes used in tree
	_tree[freeInd].setInfo(object);					// setting the root Info value
	int curIndex = _rootIndex;						// setting the current Index as _root Index
	if (_rootIndex != freeInd)						// checking if rootIndex! = free Ind
	{
		while (true)								// using while loop ( condition true)
		{	
			if (_tree[curIndex] > _tree[freeInd])	//checking if value stored at Current Index is greater than free Index
			{
				if (_tree[curIndex].getLeft() == -1)  // checking if current index has left index == -1 i.e. empty left index
				{										// If yes, then set that left index to freeInd
					_tree[curIndex].setLeft(freeInd);	// else it will traverse to left index which is not -1
					break;
				}
				else
				{
					curIndex = _tree[curIndex].getLeft();
				}
			}
			else									//else the value stored at Current Index is less than free Index
			{
				if (_tree[curIndex].getRight() == -1) // checking if current index has right index == -1 i.e. empty right index
				{										// If yes, then set that right index to freeInd
					_tree[curIndex].setRight(freeInd);	// else it will traverse to right index which is not -1
					break;
				}
				else
				{
					curIndex = _tree[curIndex].getRight();
				}
			}
		}
	}
};

template <class DT>
int ArrayBST<DT>::findIndex(DT& object)			// method to get the Index of the node element
{
	return _findIndex(object, rootIndex());		// calling a helper method to get the node element by traversing through the root Index
};

template <class DT>
int ArrayBST<DT>::_findIndex(DT& object, int pos)		// To get the index of the node element and returning the index value
{
	if (*(_tree[pos].getInfo()) == object)				// if that object is equal to node Info value return the position
		return pos;
	if (*(_tree[pos].getInfo()) < object)				// if the object is greater than the node Info value 
	{
		if ((_tree[pos]).getRight() != -1)				// checking if the right index value is not -1
		{												// if yes, call the same method recursively
			return _findIndex(object, _tree[pos].getRight());	
		}
	}
	else												// else the object is less than the node Info value
	{
		if ((_tree[pos]).getLeft() != -1)				// checking if the left index value is not -1
		{												// if yes, call the same method recursively
			return _findIndex(object, _tree[pos].getLeft());
		}
	}
};

template <class DT>
bool ArrayBST<DT>::find(DT& object)				// method to check if the node value exist in nodes in tree
{
	return _find(object, rootIndex());			// calling helper method
};

template <class DT>
bool ArrayBST<DT>::_find(DT& object, int pos) {
	if (*(_tree[pos].getInfo()) == object)		// if that object is equal to node Info value return true
		return true;
	if (*(_tree[pos].getInfo()) < object) {		// if the object is greater than the node Info value
		if ((_tree[pos]).getRight() != -1)		// checking if the right index value is not -1
		{										// if yes, call the same method recursively
			return _find(object, _tree[pos].getRight());
		}
		return false;							// or else return false
	}
	else {										// else the object is less than the node Info value
		if ((_tree[pos]).getLeft() != -1) {		// checking if the left index value is not -1
			return _find(object, _tree[pos].getLeft());	//  if yes, call the same method recursively
		}
		return false;							// or else return false
	}
};

template <class DT>
void ArrayBST<DT>::display(ostream& os)			//display method
{	
	cout << "Information in Tree:" << endl;		
	this->displayPreOrder(os);					// calling Preorder and Inorder method
	cout << endl;
	this->displayInOrder(os);
	cout << endl;
};

template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream& os)		//Preorder method to display node Info in PreOrder form
{
	cout << "Pre Order Traversal:" << endl;		// Calling helper method
	this->_preOrder(_rootIndex);
};

template <class DT>
void ArrayBST<DT>::_preOrder( int p)
{
	cout << *(_tree[p].getInfo())<<" ";			// Printing out the Node Info
	if(_tree[p].getLeft() != -1 )				// checking if there is Left Index
		this->_preOrder(_tree[p].getLeft());	// If there is Left Index, call the same method recursively.
	if(_tree[p].getRight() !=  -1 )				// checking if there is Right Index
		this->_preOrder(_tree[p].getRight());	// If there is Right Index, call the same method recursively.
};

template <class DT>
void ArrayBST<DT>::displayInOrder(ostream& os)	// Inorder method to display node Info in InOrder form
{
	cout << "In Order Traversal:" << endl;		// Calling helper method
	this->_inOrder(_rootIndex);
};

template <class DT>
void ArrayBST<DT>::_inOrder(int i)
{
	if(_tree[i].getLeft() != -1)				// checking if there is Left Index
		this->_inOrder(_tree[i].getLeft());		// If there is Left Index, call the same method recursively.
	cout << *(_tree[i].getInfo())<< " ";		// Printing out the Node Info
	if(_tree[i].getRight() != -1)				// checking if there is Right Index
		this->_inOrder(_tree[i].getRight());	// If there is Right Index, call the same method recursively.
};

template <class DT>
void ArrayBST<DT>::printRaw()					// To display the tree vector data
{
	for(int i = 0; i < _size; i++)				// Using for loop
	{ 
		if(_tree[i].getInfo() != NULL)			// if the Info value is not NULL, print the following statement
		{
			cout << "Index " << i;
			_tree[i].display();					// calling ArrayBTNode display() method
		}
	}
	cout << "Free Indexes:" << endl;			// Printing out the Free Indexes
	if (_numNodes == _size)						// checking if the tree is full
		cout << "None";							// if yes, it will print None
	else										// or else it will loop through the available numNodes counter
	{
		for (int i = _size - _numNodes - 1; i >= 0; i--)	// Using for loop and decrementing it, Initializing i at (max size of tree - used node values - 1)
		{
			if (i == 0)										// Using this condition to display the last free Index with out ,
				cout << i;
			else											// Using this condition to display index with comma
				cout << i << ", ";
		}
	}
	cout << endl;
	cout << endl;
};

template <class DT>
ArrayBST<DT>::~ArrayBST() 
{
	// Destructor for Array BST and this will call the destructor for ArrayBT node class
};
////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	cin >> inputSize;
	char option;

	// Create a BST of the size inputSize
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);
	cout << "Number of maximum nodes: " << inputSize << endl;
	// TODO: input loop for commands
	cout << endl;
	cin >> option;
	while (!cin.eof())					// It will check for end of the line.
	{
		switch (option)					// using switch function
		{
			case 'I':
			{
				int input;				// storing the input
				cin >> input;
				cout << "Inserting " << input <<endl;
				myBST.insert(input);	// calling the insert method for the input value
				cout << endl;
				break;
			}
			case 'O':
			{
				cout << myBST << endl;;		// calling myBST object using friend ostream operator
				break;
			}
			case 'A':
			{
				cout << "Raw Data:"<<endl;
				myBST.printRaw();			// calling the printRaw() method
				break;
			}
			case 'F':
			{
				int input;					// storing the input
				cin >> input;
				bool find = myBST.find(input);	// calling the find method
				cout << "Finding " << input << endl;	// if the number is not found, print the following statement.
				if (find == false)
				{
					cout << "Number not found." << endl;
				}
				else								// if the number is found, calling the findIndex method to get the position
					cout << "Number found at index "<< myBST.findIndex(input)<<"."<<endl;
				cout << endl;
				break;
			}
			//case 'H':							// getting the height of the tree
			//{
			//	cout << myBST.Height()<<endl;	// calling the height() method
			//	break;
			//}
			default:								//Default method for wrong input.
			{
				cout << "Wrong Input" << endl;
				break;
			}
		}
		cin >> option;
	}
	return 0;
}
