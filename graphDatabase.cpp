#include <iostream>
#include <string>
using namespace std;

class Node {				//Node class to store Node's details
protected:
	int nodeNumber; // field to store node's number
	string nodeInfo; // field to store node's information
public:
	Node(); // default constructor
	
	string getNodeInfo();	// getters
	int getNodeNumber();
	
	void setNodeInfo(string newInfo);	// setters
	void setNodeNumber(int newNum);

	void display(); // display node details 
};
Node::Node()			//default constructor for Node
{	nodeNumber = -1;
	nodeInfo = "";
};
string Node::getNodeInfo()			//get nodeInfo method
{	return nodeInfo;
};
int Node::getNodeNumber()			//get nodeNumber method
{	return nodeNumber;
}
void Node::setNodeInfo(string newInfo)		//set nodeInfo method
{	nodeInfo = newInfo;
};
void Node::setNodeNumber(int newNum)		//set nodeNumber method
{	nodeNumber = newNum;
};
void Node::display()
{	cout << nodeNumber << ": " << nodeInfo<<endl;		//displaying nodes.
};
//-----------------------------------------------------------------------------------------------
class Edge {				//Edge class to store edge's details
protected:
	Node* u; // field to store source node pointer
	Node* v; // field to store destination node pointer
	string edgeInfo; // field to store edge information
public:
	Edge();			// default constructor
	
	Node& getu();	// getters 
	Node& getv();
	string getEdgeInfo();
	
	void setu(Node* newu);		// setters
	void setv(Node* newv);
	void setEdgeInfo(string newInfo);

	void display();		// display edge details
};
Edge::Edge()			//default constructor Edge
{	u = NULL;			//Initializing the variables to NULL and string to empty string.
	v = NULL;
	string edgeInfo = "";
};
void Edge::setu(Node* newu)			//set u for Edges
{	u = newu;
};
void Edge::setv(Node* newv)			//set v for Edges
{	v = newv;
};
void Edge::setEdgeInfo(string newInfo)		//setting edge Info of a node.
{	edgeInfo = newInfo;
};
Node &Edge:: getu()						//returning pointer value stored in u.
{	return *u;
};
Node &Edge::getv()						//returning pointer value stored in v.
{	return *v;
};
string Edge::getEdgeInfo()				//returning string Edge info between two nodes.
{	return edgeInfo;
};
void Edge::display()					//displaying both the nodes with edgeInfo.
{	
	if ((u != NULL)&&(v != NULL)) 
	{
		cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << getEdgeInfo() << endl;
	}
};
//-----------------------------------------------------------------------------------------------
class GraphDB {
protected:
	Node* myNodes;					// array of nodes 
	Edge* myEdges;					// array of edges
	int numNodes;					// number of nodes
	int numEdges;					// current number of edges
	int maxEdges;					// store the max number of edges (array size)
public:
	GraphDB(int nNodes, int mEdges);	// non-default constructor
	//setters
	void setNode(Node& newNode);
	void setEdge(Edge& newEdge);
	void setNodeInfo(int u, string newInfo);
	void setEdgeInfo(int u, int v, string newInfo);
	
	// getters
	Node* getNode(int nodeNum);
	string getNodeInfo(int nodeNum);
	Edge* getEdgeInfo(int u, int v);

	// operations
	bool isAnEdge(int u, int v);				// is this edge existent
	void addEdge(Edge& newEdge);				// add an edge
	void deleteEdge(int u, int v);				// delete/remove the edge
	void display();

	//int numN1 = 0;
};
GraphDB::GraphDB(int nNodes, int mEdges) {
	numNodes = 0;
	maxEdges = mEdges;
	numEdges = 0;
	myNodes = new Node[nNodes]; //gives the address of the first node object
	myEdges = new Edge[mEdges]; //declaring the edge object.
};
void GraphDB::setNode(Node& newNode) {				// taking node object and Info stored in it using setNode.
	
	myNodes[numNodes] =  newNode;
	numNodes = numNodes + 1;
};
void GraphDB::setEdge(Edge& newEdge) {				// taking edge object and Info stored in it using setEdge.
		myEdges[numEdges] = newEdge;
		numEdges = numEdges + 1;
};
void GraphDB::setNodeInfo(int u, string newInfo) {			//to set node info by passing the interger and string
	for (int k = 0; k < numNodes; k++) 
		{
		myNodes[u].setNodeNumber(u);
		myNodes[u].setNodeInfo(newInfo);
		}
};
void GraphDB::setEdgeInfo(int u, int v, string newInfo) {			//to pass u, v and string about edges.
	for(int m=0;m < numEdges ; m++)
	myEdges->setu(&myNodes[u]);
	myEdges->setv(&myNodes[v]);
	myEdges->setEdgeInfo(newInfo);
};
Node* GraphDB::getNode(int nodeNum) {				//to get nodeNumber stored in Node Number.
	return &myNodes[nodeNum];
};
string GraphDB::getNodeInfo(int nodeNum) {			//to get nodeInfo stored in Node Object.
	return myNodes[nodeNum].getNodeInfo();
};
Edge* GraphDB::getEdgeInfo(int u, int v) {			//to get Edge Info.
	for (int i = 0; i < numEdges; i++) 
	{
		if (this -> myEdges[i].getu().getNodeNumber() == u && this->myEdges[i].getv().getNodeNumber() == v)		//using this to pass same instance of object to other method.
		{
			return &myEdges[i];
		}
	}
};
bool GraphDB::isAnEdge(int u, int v) {
	for (int i = 0; i < numEdges; i++)				//To check if the edge exist between two nodes.
	{
		if (this->myEdges[i].getu().getNodeNumber() == u && this->myEdges[i].getv().getNodeNumber() == v)		//using this to pass same instance of object to other method.
		{
			return true;
		}
	}
	return false;									// If edge exists return true or else return false.
};
void GraphDB::addEdge(Edge& newedge) {				//To increase myEdges pointer if Input function exists maximum numbers of Edges.
	maxEdges += 1;
	Edge* temp = new Edge[maxEdges];
	for(int i = 0; i< numEdges; i++)			// Copying previous array pointer to temp array pointer
		{										// deleting Edges from memory and increasing the size and storing them in temp and reassigning values to MyEdges.
		temp[i] = myEdges[i];
		}
	delete[] myEdges;
	myEdges = temp;
	maxEdges++;
	this->setEdge(newedge);						//set Edge function to pass Edge object.
};
void GraphDB::deleteEdge(int u, int v) {		//copying (i + 1)th array pointer to i th position so, Edge at i th position gets deleted.
	int find;									//using two varialble. find:-i for which the edge is to be deleted and flag:- to decrement the numedges after Left shift is done.
	int flag = 0;
	for (int i = 0; i < numEdges; i++) {
		if (this->myEdges[i].getu().getNodeNumber() == u && this->myEdges[i].getv().getNodeNumber() == v) {
			find = i;
			flag = 1;
		}
	}
	for (int i = find; i < numEdges-1; i++) {
		myEdges[i] = myEdges[i + 1];
	}
	if (flag==1) {
		numEdges--;
	}
};
void GraphDB::display() {
	cout << "Displaying myNodes:" << endl;
	for (int i = 0;i < numNodes;i++) {		//Displaying all the nodes
		myNodes[i].display();
	}
	cout << "Displaying myEdges:" << endl;	//Displaying all the edges
	for (int i = 0;i < numEdges; i++) {
		myEdges[i].display();
	}
};
//-----------------------------------------------------------------------------------------------
int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store maxEdges from input
	int nodeNum;	//variable to send number of nodes to node class
	string nodeLabel;  //variable to assign label to nodes

	char command;	//variable to send command such as Insert, display, remove and edge checking.
	int u, v;		// to store connections between edges
	string edgeLabel;  //variable to store edge info

	GraphDB* masterGraph; // pointer object of GraphDB class
	
	cin >> numNodes >> maxEdges;							// read the numNodes and maxEdges from redirected input
	masterGraph = new GraphDB(numNodes, maxEdges);			//creating new Graph Object.
	cout << "numNodes: " << numNodes << endl;				// display the values read in
	cout << "maxEdges: " << maxEdges << endl;
	cout << endl;
	Node tempNodes = Node();
	for (int i = 0;i < numNodes; i++)
	{
		
		cin >> nodeNum >> nodeLabel;		//Inputs for Node Num and Node Label
		tempNodes.setNodeNumber(nodeNum);
		tempNodes.setNodeInfo(nodeLabel);
		masterGraph->setNode(tempNodes);	//setting the nodes to the Graph Object
	}
	int i = 0;								//counter to check if Insert exceeds maxEdges.
	cin >> command;							//Reading in I,E,R,D commands with edge label.
	while (!cin.eof())						//It will check for end of the line.
	{
		switch (command) {
		case 'I': {
			Edge* newEdge = new Edge();				//declaring Edge object.
			cin >> u >> v >> edgeLabel;
			cout << "Inserting " << u << " " << v << ": " << edgeLabel << endl;
			cout << endl;
			if (i < maxEdges) {							//Inserting edges upto max edges count, If i > maxEdges it will run addEdge function i.e. else condition.
				newEdge -> setu(masterGraph->getNode(u));	//calling get node method using Graph object which is then passed by setu method which is called by Edge object newEdge.
				newEdge -> setv(masterGraph->getNode(v));
				newEdge -> setEdgeInfo(edgeLabel);
				masterGraph->setEdge(*newEdge);
				i++;									//Incrementing the counter.
			}
			else
			{	newEdge->setu(masterGraph->getNode(u));
				newEdge->setv(masterGraph->getNode(v));
				newEdge->setEdgeInfo(edgeLabel);
				masterGraph->addEdge(*newEdge);
			}
			break;
		}
		case 'E': {
			cin >> u >> v;
			if(masterGraph->isAnEdge(u,v) == true)		//Checking if edge exists or not
				{										//This if condition will run only if edge exists between two nodes.
				cout << "Edge exists between " << masterGraph->getNodeInfo(u) << " and " << masterGraph->getNodeInfo(v) << endl;
				cout << endl;
				}
			else
				{										//else condition will run if edge does not exists between two nodes.
				cout << "No edge exists between " << masterGraph->getNodeInfo(u) << " and " << masterGraph->getNodeInfo(v) << endl;
				cout << endl;
				}
			break;
		}
		case 'R': {
			cin >> u >> v;
			if (masterGraph->isAnEdge(u, v) == true)	//Removing an edge.
			{
				masterGraph->deleteEdge(u, v);			//deleting the edge by calling deleteEdge function.
				cout << "Removing " << u << " " << v << endl;
				cout << endl;
				i--;
			}
			else
			{							//This loop will only for dummy input i.e. deleting an edge even if it does not exists.
				cout << "No edge exists between " << u << " " << v << endl;
				cout << endl;
			}
			break;
		}
		case 'D': {						//Displaying both the edges using display function()
			masterGraph->display();
			cout<<endl;
			break;
		}
		default:					//Default method for wrong input.
			cout << "Wrong Input" << endl;
			break;
		}
		cin >> command;
	}
	return 0;
}
