// Computing Structures Fall 2022
// DSA 5005
// Project 2

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
template <class DT>
class Node
{
protected:
    int nodeNumber;  // field to store node's number
    string nodeInfo; // field to store node's information
    DT yearCreated;  // field to store the year of the node created
    string location; // field to store the location

public:
    Node(); // default constructor

    // getters
    string getNodeInfo();
    int getNodeNumber();
    DT getYearCreated();
    string getLocation();

    // setters
    void setNodeInfo(string newInfo, DT newYearCreated, string newLoc);
    void setNodeNumber(int newNum);
    void setYearCreated(DT newYearCreated);
    void setLocation(string newLocation);

    void display(); // display node details

    ~Node(); // destructor
};
template <class DT>
Node<DT>::Node()			//default constructor for Node
{
    nodeNumber = -1;
    nodeInfo = "";
	yearCreated = -1;
	location = "";
};
template <class DT>
string Node<DT>::getNodeInfo()			//get nodeInfo method
{
    return nodeInfo;
};
template <class DT>
int Node<DT>::getNodeNumber()			//get nodeNumber method
{
    return nodeNumber;
};
template <class DT>
DT Node<DT>::getYearCreated()			//get Year created.
{
    return yearCreated;
};
template <class DT>
string Node<DT>::getLocation()			//get Location created.
{
    return location;
};
template <class DT>
void Node<DT>::setNodeInfo(string newInfo,DT newYearCreated, string newLoc)		//set nodeInfo method
{
    nodeInfo = newInfo;
    yearCreated = newYearCreated;
    location = newLoc;
};
template <class DT>
void Node<DT>::setNodeNumber(int newNum)		//set nodeNumber method
{
    nodeNumber = newNum;
};
template <class DT>
void Node<DT>::setYearCreated(DT newYearCreated)		//set Year Created
{
    yearCreated = newYearCreated;
};
template <class DT>
void Node<DT>::setLocation(string newLocation)			// Setting the location
{
    location = newLocation;
};
template <class DT>
void Node<DT>::display()
{
    cout << nodeNumber << ": " << nodeInfo << ", "<<getYearCreated()<<", "<<location<<endl;		//displaying nodes.
};
template <class DT>
Node<DT>::~Node()										//Destructor method.
{
    //cout << "Node Object was destroyed" << endl;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class to store one edge's details
template <class DT>
class Edge
{
protected:
    Node<DT>* u;     // field to store source node pointer
    Node<DT>* v;     // field to store destination node pointer
    string edgeInfo; // field to store edge information
    DT yearsKnown;   // u and v - years known

public:
    Edge(); // default constructor
    // getters
    Node<DT>* getu();
    Node<DT>* getv();
    string getEdgeInfo();
    DT getYearsKnown();

    // setters
    void setu(Node<DT>* newu);
    void setv(Node<DT>* newv);
    void setEdgeInfo(string newInfo, DT newYearsKnown);
    void setYearsKnown(DT newYear);                     

    void display(); // display edge details

    ~Edge(); // destructor
};
template <class DT>
Edge<DT>::Edge()			//default constructor Edge
{
    u = NULL;			//Initializing the variables to NULL and string to empty string.
    v = NULL;
    edgeInfo = "";
	int yearsKnown = 0;
};
template <class DT>
void Edge<DT>::setu(Node<DT>* newu)			//set u for Edges
{
    u = newu;
};
template <class DT>
void Edge<DT>::setv(Node<DT>* newv)			//set v for Edges
{
    v = newv;
};
template <class DT>
void Edge<DT>::setEdgeInfo(string newInfo, DT newYearsKnown)		//setting edge Info of a node.
{
    edgeInfo = newInfo;
    yearsKnown = newYearsKnown;
};
template <class DT>
void Edge<DT>::setYearsKnown(DT newYear)		//setting Years Known.
{
    yearsKnown = newYear;
};
template <class DT>
Node<DT>* Edge<DT>::getu()						//returning pointer value stored in u.
{
    return u;
};
template <class DT>
Node<DT>* Edge<DT>::getv()						//returning pointer value stored in v.
{
    return v;
};
template <class DT>
string Edge<DT>::getEdgeInfo()				//returning string Edge info between two nodes.
{
    return edgeInfo;
};
template <class DT>
DT Edge<DT>::getYearsKnown()			//returning yearsKnown on calling this method.
{
    return yearsKnown;
};
template <class DT>
void Edge<DT>::display()					//displaying both the nodes with edgeInfo.
{
    if ((u != NULL) && (v != NULL))
    {
        cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << getEdgeInfo() <<", "<<getYearsKnown()<< endl;
    }
};
template <class DT>
Edge<DT>::~Edge()						//Destructor for Edge
{
    //cout << "Edge Object was destroyed" << endl;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class to store the graph
template <class DT>
class GraphDB
{
	friend ostream & operator << (ostream& s,GraphDB& g)	// ostream operator for displaying mynodes and myedges
	{
		g.display();										//using ostream object g to call the display method.
		return s;
	};
protected:
    Node<DT>* myNodes; // array of nodes
    Edge<DT>* myEdges; // array of edges
    int numNodes;      // number of nodes
    int numEdges;      // number of edges
    int maxEdges;      // store the max number of edges (array size)

public:
    GraphDB(int nNodes, int nEdges); // non-default constructor
    // setters
    void setNode(Node<DT>& newNode);
    void setEdge(Edge<DT>& newEdge);
    void setNodeInfo(int u, string newInfo);
    void setEdgeInfo(int u, int v, string newInfo);

    // getters
    Node<DT>* getNode(int nodeNum);
    string getNodeInfo(int nodeNum);
    Edge<DT>* getEdgeInfo(int u, int v);

    // operations
    bool isAnEdge(int u, int v);     // is this edge existent
    void addEdge(Edge<DT>& newEdge); // add an edge
    void deleteEdge(int u, int v);   // delete the edge
    void display();                  // display the contents of the two arrays
    int* findNeighbours(int u);      // returns an integer array of neighbours' nodeNum

    ~GraphDB(); // destructor
};
template <class DT>
GraphDB<DT>::GraphDB(int nNodes, int mEdges) {				//non - default constructor and variables assignment.
	numNodes = 0;
	maxEdges = mEdges;
	numEdges = 0;
	myNodes = new Node<DT>[nNodes]; //gives the address of the first node object
	myEdges = new Edge<DT>[mEdges]; //declaring the edge object.
};
template <class DT>
void GraphDB<DT>::setNode(Node<DT>& newNode) {				// taking node object and Info stored in it using setNode.

	myNodes[numNodes] = newNode;
	numNodes = numNodes + 1;
};
template <class DT>
void GraphDB<DT>::setEdge(Edge<DT>& newEdge) {				// taking edge object and Info stored in it using setEdge.
	myEdges[numEdges] = newEdge;
	numEdges = numEdges + 1;
};
template <class DT>
void GraphDB<DT>::setNodeInfo(int u, string newInfo) {			//to set node info by passing the interger and string
	for (int k = 0; k < numNodes; k++)
	{
		myNodes[u].setNodeNumber(u);
		myNodes[u].setNodeInfo(newInfo);
	}
};
template <class DT>
void GraphDB<DT>::setEdgeInfo(int u, int v, string newInfo) {			//to pass u, v and string about edges.
	for (int m = 0;m < numEdges; m++)
		myEdges->setu(&myNodes[u]);
	myEdges->setv(&myNodes[v]);
	myEdges->setEdgeInfo(newInfo);
};
template <class DT>
Node<DT>* GraphDB<DT>::getNode(int nodeNum) {				//to get nodeNumber stored in Node Number.
	int flag = 0;											//flag to check if node number exists or not.
	for (int i = 0;i < numNodes;i++)						//Looping through all the Nodes to get Node Number. if the nodeNum des not exist it will throw and exception.
	{
		if (myNodes[i].getNodeNumber() == nodeNum) {
				flag++;
				return &myNodes[nodeNum];
		}
	}
		if (flag == 0) {						// Throwing exception if the nodes entered are out of bounds. i.e. flag = 0.
			throw logic_error("Node not a part of the graph");
		}
};
template <class DT>
string GraphDB<DT>::getNodeInfo(int nodeNum) {			//to get nodeInfo stored in Node Object.
	return myNodes[nodeNum].getNodeInfo();
};
template <class DT>
Edge<DT>* GraphDB<DT>::getEdgeInfo(int u, int v) {			//to get Edge Info.
	for (int i = 0; i < numEdges; i++)
	{
		if (this->myEdges[i].getu().getNodeNumber() == u && this->myEdges[i].getv().getNodeNumber() == v)		//using this to pass same instance of object to other method.
		{
			return &myEdges[i];
		}
	}
};
template <class DT>
bool GraphDB<DT>::isAnEdge(int u, int v) {
	for (int i = 0; i < numEdges; i++)				//To check if the edge exist between two nodes.
	{
		if (this->myEdges[i].getu()->getNodeNumber() == u && this->myEdges[i].getv()->getNodeNumber() == v)		//using this to pass same instance of object to other method.
		{
			return true;
		}
	}
	return false;									// If edge exists return true or else return false.
};
template <class DT>
void GraphDB<DT>::addEdge(Edge<DT>& newedge) {				//To increase myEdges pointer if Input function exists maximum numbers of Edges.
	maxEdges += 1;
	Edge<DT>* temp = new Edge<DT>[maxEdges];
	for (int i = 0; i < numEdges; i++)			// Copying previous array pointer to temp array pointer
	{										// deleting Edges from memory and increasing the size and storing them in temp and reassigning values to MyEdges.
		temp[i] = myEdges[i];
	}
	delete[] myEdges;
	myEdges = temp;
	//maxEdges++;
	this->setEdge(newedge);						//set Edge function to pass Edge object.
};
template <class DT>
void GraphDB<DT>::deleteEdge(int u, int v) {				// Memory Reallocation if (numEdges = maxEdges/2)
	int z = maxEdges/2;
	if (numEdges == (z))									//checking for the numEdges with half of maxEdges.
	{	
		myEdges[numEdges];								// If condition is true, myEdges is reallocated to myEdges[numEdges].

		int find;									//using two varialble. find:-i for which the edge is to be deleted and flag:- to decrement the numedges after Left shift is done.
		int flag = 0;								//copying (i + 1)th array pointer to i th position so, Edge at i th position gets deleted.
		for (int i = 0; i < numEdges; i++) {
			if (this->myEdges[i].getu()->getNodeNumber() == u && this->myEdges[i].getv()->getNodeNumber() == v) {
				find = i;
				flag = 1;
				break;
			}
		}
		for (int i = find; i < numEdges - 1; i++) {
			myEdges[i] = myEdges[i + 1];
		}
		if (flag == 1) {
			numEdges--;
		}
	}
	else {											//If condition is false, myEdges remains same.
		int find;									//using two varialble. find:-i for which the edge is to be deleted and flag:- to decrement the numedges after Left shift is done.
		int flag = 0;				//copying (i + 1)th array pointer to i th position so, Edge at i th position gets deleted.
		for (int i = 0; i < numEdges; i++) {
			if (this->myEdges[i].getu()->getNodeNumber() == u && this->myEdges[i].getv()->getNodeNumber() == v) {
				find = i;
				flag = 1;
			}
		}
		for (int i = find; i < numEdges - 1; i++) {
			myEdges[i] = myEdges[i + 1];
		}
		if (flag == 1) {
			numEdges--;
		}
	}
};
template <class DT>
void GraphDB<DT>::display() {
	cout << "Displaying myNodes:" << endl;
	for (int i = 0;i < numNodes;i++) {		//Displaying all the nodes
		myNodes[i].display();
	}
	cout << "Displaying myEdges:" << endl;	//Displaying all the edges
	for (int i = 0;i < numEdges; i++) {
		myEdges[i].display();
	}
	cout << endl;
};
template <class DT>	
int* GraphDB<DT>::findNeighbours(int u)			// to find neighbours of a node.
{
	int countN=0;								//Initializing the countN to get Number of neighbours for a node.
	for (int j = 0; j < numEdges; j++)			
	{
		if ((myEdges[j].getu()->getNodeNumber() == u) || (myEdges[j].getv()->getNodeNumber() == u))
			countN++;							//checking all values of u and v, If it matches, increment the countN.
	}
	int* arr = new int[countN+1];
	arr[0] = countN;							//storing countN at 0th place of an array, to use this counter to print all the values in main function for loop.
	int intial_value = 1;
	for (int i = 0; i < numEdges;i++)
	{
		if (myEdges[i].getu()->getNodeNumber() == u) {	//checking all values of u and v, If it matches, store the value in an array pointer.
			arr[intial_value++] = myEdges[i].getv()->getNodeNumber();
		}
		if (myEdges[i].getv()->getNodeNumber() == u) {
			arr[intial_value++] = myEdges[i].getu()->getNodeNumber();
		}
	}
	return arr;										//returning array pointer with all address of stored values.
};
template <class DT>
GraphDB<DT>::~GraphDB()								// Destructor for GraphDB		
{
	//cout << "GraphDB Object was destroyed" << endl;
	delete[] myEdges;
	delete[] myNodes;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store maxEdges from input
	int nodeNum;	//variable to send number of nodes to node class
	string nodeLabel;  //variable to assign label to nodes
	string location;	//variable to assign location value to node
	int date;		//variable to assign date to node.

	char command;	//variable to send command such as Insert, display, remove and edge checking.
	int u, v;		// to store connections between edges
	string edgeLabel;  //variable to store edge info
	int year;      //variable to store no of years knowns by the nodes.

	GraphDB<int> *masterGraphI ; // pointer object of GraphDB class
	
	cin >> numNodes >> maxEdges;							// read the numNodes and maxEdges from redirected input
	masterGraphI = new GraphDB<int> (numNodes, maxEdges);	//creating new Graph Object.

	cout << "numNodes: " << numNodes << endl;				// display the values read in
	cout << "maxEdges: " << maxEdges << endl;
	cout << endl;
	Node<int> tempNodesI =  Node <int>();					//Creating a node Object of type int.
	
	for (int i = 0;i < numNodes; i++)
	{

		cin >> nodeNum >> nodeLabel >> date >>location;		
		tempNodesI.setNodeNumber(nodeNum);					//calling setters to store the Node Info
		tempNodesI.setNodeInfo(nodeLabel,date, location);
		tempNodesI.setYearCreated(date);
		tempNodesI.setLocation(location);
		masterGraphI->setNode(tempNodesI);	//setting the nodes to the Graph Object
		
	}
	int i = 0;								//counter to check if Insert exceeds maxEdges.
	cin >> command;							//Reading in I,E,R,D,N commands with edge label.
	while (!cin.eof())						//It will check for end of the line.
	{
		switch (command) {
		case 'I': {
			try							//If the node number does not exist after calling the getNode
			{
				Edge<int> newEdge = Edge<int>();				//declaring Edge object.
				cin >> u >> v >> edgeLabel >> year;
				cout << "Inserting " << u << " " << v << ": " << edgeLabel << ", " << year << endl;
				if (i < maxEdges) {							//Inserting edges upto max edges count, If i > maxEdges it will run addEdge function i.e. else condition.
					newEdge.setu(masterGraphI->getNode(u));	//calling get node method using Graph object which is then passed by setu method which is called by Edge object newEdge.
					newEdge.setv(masterGraphI->getNode(v));
					newEdge.setEdgeInfo(edgeLabel, year);
					masterGraphI->setEdge(newEdge);
					i++;									//Incrementing the counter.
					cout << endl;
				}
				else
				{
					newEdge.setu(masterGraphI->getNode(u));
					newEdge.setv(masterGraphI->getNode(v));
					newEdge.setEdgeInfo(edgeLabel, year);
					masterGraphI->addEdge(newEdge);
					cout << endl;
				}
			}
				catch (const std::exception& e)				//catching the exception thrown from getNode method.
				{
					cout << e.what()<<endl;
					cout << endl;
				}
			break;
		}
		case 'E': {
			cin >> u >> v;
			if (masterGraphI->isAnEdge(u, v) == true)		//Checking if edge exists or not
			{										//This if condition will execute only if edge exists between two nodes.
				cout << "Edge exists between " << masterGraphI->getNodeInfo(u) << " and " << masterGraphI->getNodeInfo(v) << endl;
				cout << endl;
			}
			else
			{										//else condition will run if edge does not exists between two nodes.
				cout << "No edge exists between " << masterGraphI->getNodeInfo(u) << " and " << masterGraphI->getNodeInfo(v) << endl;
				cout << endl;
			}
			break;
		}
		case 'R': {
			cin >> u >> v;
			if (masterGraphI->isAnEdge(u, v) == true)	//Removing an edge.
			{
				masterGraphI->deleteEdge(u, v);			//deleting the edge by calling deleteEdge function.
				cout << "Removing the item " << u << " " << v << endl;
				cout << endl;
				i--;
			}
			else
			{							//This loop will be only for dummy input i.e. deleting an edge even if it does not exist.
				cout << "Removing the item " << u << " " << v << endl;
				cout << "Edge does not exist to be deleted"<< endl;
				cout << endl;
			}
			break;
		}
		case 'D': {						//Displaying both nodes and edges using ostream operator overloading.
			//masterGraphI->display();
			cout << *masterGraphI;
			break;
		}
		case 'N': {						//checking the Neighbours of the node.
			cin >> u;
			cout << "Neighbours of " << u << ": ";
			int* loopCounter = masterGraphI->findNeighbours(u);
			int counter = loopCounter[0];		//storing the 0th value of the array returned and using that value as counter for loop.
			for (int k = 1;k <= counter; k++)
			{
				cout << loopCounter[k] << " ";	// printing the array.
			}
			cout << endl;
			cout << endl;
			break;
		}
		default:					//Default method for wrong input.
			cout << "Wrong Input" << endl;
			break;
		}
		cin >> command;
	}
	delete masterGraphI;
	return 0;
}