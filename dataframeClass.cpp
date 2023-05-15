// DSA 5005 - Computing Structures
// Fall 2022
// Project 3

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file

using namespace std;

// class to store one row's information
class DFrow
{
protected:
	// all the fields to store information of a row
	string name;
	char sex;
	int age;
	int height;
	int weight;
	string city;

public:
	DFrow(); // default constructor
	DFrow(string n, char c, int one, int two, int three, string ci); // non-default constructor
	// TODO: write getters for each of the fields
	string getName();
	char getSex();
	int getAge();
	int getHeight();
	int getWeight();
	string getCity();
	// TODO: write setters for each of the fields
	void setName(string n1);
	void setSex(char c1);
	void setAge(int x);
	void setHeight(int y);
	void setWeight(int z);
	void setCity(string ci1);
	// TODO: write display method to display all the fields in the same order
	// 			refer to output sample for exact format
	void display();

	// TODO: write destructor
	~DFrow();
};
DFrow::DFrow(){				//default constructor
	name = "";
	sex='z';
	age = -1;
	height = -1 ;
	weight = -1 ;
	city = "";
};
DFrow::DFrow(string n, char c, int one, int two, int three, string ci) {    //non default constructor
	name = "";
	sex = 'z';
	age = -1;
	height = -1;
	weight = -1;
	city = "";
}
void DFrow::setName(string n1) {			//Using setName method to store the Name variable.
	name = n1;
};
void DFrow::setSex(char c1) {				//Using setSex method to store the Sex variable.
	sex = c1;
}
void DFrow::setAge(int x) {					//Using setAge method to store the Age variable.
	age = x;
};
void DFrow::setHeight(int y) {				//Using setHeight method to store the Height variable.
	height = y;
};
void DFrow::setWeight(int z) {				//Using setWeight method to store the Weight variable.
	weight = z;
};
void DFrow::setCity(string ci1) {			//Using setCity method to store the City variable.
	city = ci1;
};
string DFrow::getName() {					//Using getName method to access the Name variable.
	return name;
};
char DFrow::getSex()						//Using getSex method to access the Sex variable.
{
	return sex;
};
int DFrow::getAge() {						//Using getAge method to access the Age variable.
	return age;
};
int DFrow::getHeight() {					//Using getHeight method to access the Height variable.
	return height;
};
int DFrow::getWeight() {					//Using getWeight method to access the Weight variable.
	return weight;
};
string DFrow::getCity() {					//Using getCity method to access the City variable.
	return city;
};
DFrow::~DFrow() {							//Destructor for DFrow objects.
	//cout << "DF object destroyed" << endl;
};
void DFrow::display()						//Display method to display vector if row number is specified
{
	cout << getName() << " " << getSex() << " " << getAge() << " " << getHeight() << " " << getWeight() << " " << getCity() << endl;
};
//-------------------------------------------------------------------------------------------------------------------------------------------------
// class to store the entire dataframe
class DataFrame
{
protected:
	vector<DFrow> data; // field storeing all the data
	vector<string> headers; // field to only the headers
	int nRows, nCols; // store the number of rows and cols

public:
	// Constructors
	DataFrame();
	DataFrame(int rows, int cols);

	// Overload the [] operator to access data in DF
	DFrow operator[](int i)									//Overloading the [] operators to access the data in DataFrame.
	{
		if ((i > nRows) || (i < 0))							//Checking if int i is greater than data rows or less than 0, if so will print Index Out of Bounds.
		{
			cout << "Index Out of Bounds" << endl;
		}
		else
			return data[i];									// else will return the data stored at i th row.
	};

	// File reading Method
	void readCSV(string filename, string headerPresence);

	// Output Method
	void display();

	// Search Record
	DFrow searchRecord(string name)							//searching for record based on name.
	{
		for (int i = 0; i < data.size(); i++)				//It will check for every Name in data vector and return the full details of that name.
		{
			if (data[i].getName() == name) {
				int no = i;
				return data[no];
				break;
			}
		}
		throw logic_error("Name does not exist");			//If the name is not available in the data, it will throw an error.
	};
	// Setters
	void setColName(int col, char* name); // change the name of a header/column

	// Getters
	int getNumberRows();                                              // returns the number of rows
	int getNumberCols();                                              // returns the number of columns
	//DataFrame* getColumns(int* columns, int cLen);                    // returns a dataframe with a set of cLen number of columns
	DataFrame* getRows(int* rows, int rLen);                          // returns a data frame with a set of rLen number of rows
	//DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen); // returns a data frame given a set of row numbers and column numbers
	string getHeader(int i);                                          // returns the header name given a index position

	// Find info of a given column
	double findAverage(int colNumber); // returns the average of the given column
	double findMax(int colNumber);     // returns the max of the given column
	double findMin(int colNumber);     // returns the min of the given column
	double frequency(int colNumber);   // displays the frequency of the unique values

	// Destructor
	~DataFrame();
};
DataFrame::DataFrame() {									// default constructor
	vector<DFrow> data;
	vector<string> headers;
	nRows = 0;
	nCols = 0;
};
DataFrame::DataFrame(int rows, int cols) {					// non-default constructor
	nRows = rows;
	nCols = cols;
};
void DataFrame::setColName(int col, char* name) {			//setting the Column name.
	int colnum = col;										// getting the column number and the new name and making changes into header vector
	headers[colnum - 1] = *name;
};
int DataFrame::getNumberRows() {							//getting the total number of rows of data stored in data vector
	return data.size();
};
int DataFrame::getNumberCols() {							//getting the total number of columns by accessing the header vector size.
	return headers.size();
}
DataFrame* DataFrame::getRows(int* rows, int rLen) {		//getting getRows method to get subset of data.
	int rowsN = *rows;										//creating a temp DataFrame object. storing the data using temp object from certain row number and length.
	int len = rLen;
	DataFrame* temp = new DataFrame(rowsN, len);
	for (int i = rowsN; i < len; i++)
	{
		temp->data.push_back(data[i]);						//storing the data in data vector of temp Dataframe object.
	}
	return temp;											//returning the Dataframe Object.
};
string DataFrame::getHeader(int i) {						// getHeader will return the header or column name on input of header number.
	return headers[i - 1];									//returning the header name stored in headers vector.
};
double DataFrame::findMax(int colNumber) {					//Returning max of integer data type column(Age, Height and Weight)
	double maxInt = 0;
	string nameCol = headers[colNumber];					//getting the column name from column number.
	if (nameCol == "Age")									//if column name is Age, Height and Weight then only finding the max value.
	{
		double firstNum = data[0].getAge();					//storing the first number from Age column.
		for (int j = 1; j < data.size(); j++)				//comparing that to every integer value available in that same column.
		{
			if (firstNum < data[j].getAge())				//if the firstNum is less than next numbers,
			{												//firstNum will be replaced by that number and maxInt will be firstNum.
				firstNum = data[j].getAge();				//returning maxInt.
				maxInt = firstNum;
			}
		}
		return maxInt;										//Applying same logic to Height and Weight columns.
	}
	else if (nameCol == "Height(in)")						
	{
		double firstNum = data[0].getHeight();
		for (int j = 0; j < data.size(); j++)
		{
			if (firstNum < data[j].getHeight())
			{
				firstNum = data[j].getHeight();
				maxInt = firstNum;
			}
		}
		return maxInt;
	}
	else if (nameCol == "Weight(lbs)")
	{
		double firstNum = data[0].getWeight();
		for (int j = 0; j < data.size(); j++)
		{
			if (firstNum <= data[j].getWeight())
			{
				firstNum = data[j].getWeight();
				maxInt = firstNum;
			}
		}
		return maxInt;
	}
};
double DataFrame::findMin(int colNumber) {					//Returning min of integer data type column(Age, Height and Weight)
	double minInt = 0;
	string nameCol = headers[colNumber];					//getting the column name from column number.
	if (nameCol == "Age")									//if column name is Age, Height and Weight then only finding the max value.
	{
		double firstNum = data[0].getAge();					//storing the first number from Age column.
		for (int j = 1; j < data.size(); j++)				//comparing that to every integer value available in that same column.
		{
			if (firstNum >= data[j].getAge())				//if the firstNum is greater than next numbers,
			{												//firstNum will be replaced by that number and minInt will be firstNum
				firstNum = data[j].getAge();				//returning minInt.
				minInt = firstNum;
			}
		}
		return minInt;
	}
	else if (nameCol == "Height(in)")						//Applying same logic to Height and Weight columns.
	{
		double firstNum = data[0].getHeight();
		for (int j = 0; j < data.size(); j++)
		{
			if (firstNum >= data[j].getHeight())
			{
				firstNum = data[j].getHeight();
				minInt = firstNum;
			}
		}
		return minInt;
	}
	else if (nameCol == "Weight(lbs)")
	{
		double firstNum = data[0].getWeight();
		for (int j = 0; j < data.size(); j++)
		{
			if (firstNum >= data[j].getWeight())
			{
				firstNum = data[j].getWeight();
				minInt = firstNum;
			}
		}
		return minInt;
	}
};
double DataFrame::frequency(int colNumber) {				//To get the frequency of Categorical Data (Sex Column and City Column)
	int colNo = colNumber;									//storing the colNumber
	int n = data.size();
	if (colNo == 1)											//It will check for colNo(either 1 or 5)
	{
		vector<char> temp;									//creating a temp vector of type char to store the unique values in a column.
		for (int i = 0; i < n; i++)							//comparing n th variable with all variable till (n-1) th variable by using j < i condition in 2nd for loop.
		{													
			int j;
			for (j = 0; j < i; j++)
			{
				if (data[i].getSex() == data[j].getSex())	//if the the variables are same it will break out of the loop and if i == j it will push that variable to temp vector.
				{											
					break;
				}
			}
			if (i == j)
			{
				temp.push_back(data[j].getSex());			//Storing all the unique variables in temp vector
			}
		}
		for (int i = 0; i < temp.size();i++)				//Using the temp vector and comparing each element with actual data vector and incrementing the count
		{
			int count = 0;
			for (int j = 0; j < n; j++)
			{
				if (temp[i] == data[j].getSex())
					count++;
			}
			cout << temp[i] << ": " << count << endl;		//Printing the output with unique variables and the count of that variable.
		}
	}
	if (colNo == 5)											//Applying same logic to City column.
	{
		vector<string> temp;
		for (int i = 0; i < n; i++)
		{
			int j;
			for (j = 0; j < i; j++)
			{
				if (data[i].getCity() == data[j].getCity())
				{
					break;
				}
			}
			if (i == j)
			{
				temp.push_back(data[j].getCity());
			}
		}
		for (int i = 0; i < temp.size();i++)
		{
			int count = 0;
			for (int j = 0; j < n; j++)
			{
				if (temp[i] == data[j].getCity())
					count++;
			}
			cout << temp[i] << ": " << count << endl;
		}
	}
	return 0;
};
double DataFrame::findAverage(int colNumber) {				//Returning Average of integer data type column(Age, Height and Weight)
	double sum = 0;											//Initializing the sum variable to zero
	double count = data.size();								//Storing the total number of variables.
	string nameCol = headers[colNumber];					//getting the name of the column
	if(nameCol =="Age")
		{
		for (int j = 0; j < count; j++)						//looping through every variable and adding them to sum
			{
			sum += data[j].getAge();
			}
		return sum / count;									//Dividing them by the total count of elements.
		}
	else if (nameCol == "Height(in)")						//Applying same logic for Height and Weight columns.
	{
		for (int j = 0; j < count; j++)
		{
			sum += data[j].getHeight();
		}
		return sum / count;
	}
	else if (nameCol == "Weight(lbs)")
	{
		for (int j = 0; j < count ; j++)
		{
			sum += data[j].getWeight();
		}
		return sum / count;
	}
};
void DataFrame::readCSV(string filename, string headerPresence)
{
	fstream fin;							//creating fstream object
	fin.open(filename);						//using fstream object and open method to access csv file
	if (fin.fail())							// if the file opening fails then it will print the following message.
	{
		cout << "Unable to open the file: " << filename << endl;
	}
	if (headerPresence == "true")			// if the header presence is true, it will store the all the header data in headers vector
	{
		while ((fin.peek() != EOF))			// This statement will check if read the file till the End of File character.
		{
			string headerline;				//using two string variables , headerline and headerword.
			string headerword = "";
			getline(fin, headerline, '\n');	//storing the 1st row(headers) separated by /n in the headerline variable
			headerline = headerline + ",";	//adding comma at last to the headerline string.
			for (auto x : headerline)		//looping through every character in headerline, if the character is separated with comma it will add and store previous
			{								// all characters in headerword and store in headers vector.
				if (x == ',')
				{
					headers.push_back(headerword);
					headerword = "";
				}
				else {
					headerword = headerword + x;
				}
			}
			break;							//this loop will only execute once if headerpresence = true.
		}
	}
	DFrow *tempdata = new DFrow();				//creating a tempdata DFrow object.
	while ((fin.peek() != EOF))					// This statement will check if read the file till the End of File character.
	{	
		int i = 1;
		string dataline;						//using two string variables , dataline and dataword.
		string dataword = "";
		getline(fin, dataline, '\n');			//storing the 1st row(headers) separated by /n in the dataline variable
		dataline = dataline + ",";				//adding comma at last to the dataline string.
		for (auto x : dataline)					//looping through every character in dataline, if the character is separated with comma it will add and store previous
		{										//all characters in dataword and store in data vector.
			if (x == ',')
			{	
				switch (i)						//Using switch case to separate the data and calling the setters using DFrow object.
				{
				case 1: {						//Used to set Name variable.
					tempdata->setName(dataword);
					dataword = "";
					i++;
					break;
						}
				case 2: {						//Used to set Sex variable
					tempdata->setSex(dataword[0]);
					dataword = "";
					i++;
					break;
				}
				case 3: {
					tempdata->setAge(stoi(dataword));		//Used to set Age variable
					dataword = "";
					i++;
					break;
				}
				case 4: {
					tempdata->setHeight(stoi(dataword));	//Used to set Height variable
					dataword = "";
					i++;
					break;
				}
				case 5: {
					tempdata->setWeight(stoi(dataword));	//Used to set Weight variable
					dataword = "";
					i++;
					break;
				}
				case 6: {
					tempdata->setCity(dataword);			//Used to set City variable
					dataword = "";
					i++;
					break;
				}
				}
			}
			else {
				dataword = dataword + x;
			}
		}
		data.push_back(*tempdata);					//storing the data in datavector.
	}
	fin.close();
};
void DataFrame::display() {							//Display method to display headers and data vector.
	if (headers.size() > 0) {						//checking if headers are available by checking their size
		for (int i = 0; i < headers.size(); i++)	// Looping through every element and printing it out.
		{
			cout <<" " << headers[i] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < data.size(); i++)			//looping through every data elements and printing it out.
	{
		data[i].display();
	}
};
DataFrame::~DataFrame() {							//Destructor for Dataframe class
	//cout << "DataFrame Object deleted" << endl;
};
//----------------------------------------------------------------------------------------------------------------------------------
int main()
{
	int numRows, numCols;							// declaring variables
	string fileName;
	string headerBool;
	char command;

	cin >> numRows >> numCols >> headerBool >> fileName;	//reading the inputs and storing those in respective variables.
	cout << endl;

	DataFrame* d = new DataFrame(numRows, numCols);			//creating a DataFrame object using non-default constructor.
	
	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	// TODO: read the commands from the input file (redirected input)
	cin >> command;							//Reading in F,A,R,D,X,I commands.
	while (!cin.eof())						//It will check for end of the line.
	{
		switch (command) {				
		case 'F': {							
			try {							//Using try and catch if the record does not exist the searchRecord method will throw and error
				string record;
				cin >> record;
				d->searchRecord(record);		//The 1st time it calls to check if the name exists, if it does not then it will print the exception e.
				cout << "Record found:" << endl;
				cout << '\t';
				d->searchRecord(record).display();	//displaying the record found by using DataFrame object and calling display method
				cout << endl;
			}
			catch(const std::exception& e)				//catching the exception thrown from searchRecord method if the name does not exist.
				{
				cout << e.what() << endl;
				cout << endl;
				}
			break;
		}
		case 'A': {
			string colName;
			int colNo = 0;
			cin >> colName;
			for (int i = 1; i <= d->getNumberCols();i++)	//Looping through all the available headers to get the column number.
			{
				if (d->getHeader(i) == colName)
				{
					colNo = i-1;
					break;
				}
			}
			if (colNo >= 2 && colNo <= 4)				//if the colNo is 2,3 and 4 only then it will call the findAverage method or else it will 
			{											// print out an error stating that is not an interger type column.
				cout << "Average of " << colName << " is " << int(d->findAverage(colNo))<<endl;
				break;
			}
			else cout << "Average for " << colName << " cannot be found since it is nan"<<endl;
			break;
		}
		case 'R': {
			int nRows, nLen;
			cin >> nRows >> nLen;
			cout << endl;
			d->getRows(&nRows, nLen)->display();		//calling getRows method to get the subset of data from nRows and of nLen.
			cout << endl;
			break;
		}
		case 'Q': {
			string colname;
			int colno = 0;
			cin >> colname;
			for (int i = 1; i <= d->getNumberCols();i++)	//Looping through all the available headers to get the column number.
			{
				if (d->getHeader(i) == colname)
				{
					colno = i - 1;
					break;
				}
			}
			if ((colno == 1 )|| (colno == 5))			//if the colNo is 1 and 5 only then it will call the frequency method or else it will
			{											// print out an error stating that is not an categorical data type column.
				d->frequency(colno);
			}
			else cout << "Average for " << colname << " cannot be found since it is not a Categorical data" << endl;
			break;
		}
		case 'D': {										//Using this method to display the headers and data vector of DataFrame object.
			d->display();
			cout << endl;
			break;
		}
		case 'X': {
			string colName;
			int colNo = 0;
			cin >> colName;
			for (int i = 1; i <= d->getNumberCols();i++)	//Looping through all the available headers to get the column number.
			{
				if (d->getHeader(i) == colName)
				{
					colNo = i - 1;
					break;
				}
			}
			if (colNo >= 2 && colNo <= 4)				//if the colNo is 2,3 and 4 only then it will call the findAverage method or else it will
			{											// print out an error stating that is not an interger type column.
				cout << "Max of " << colName << " is " << int(d->findMax(colNo)) << endl;
				break;
			}
			else cout << "Max for " << colName << " cannot be found since it is nan" << endl;
			break;
		}
		case 'I': {
			string colName;
			int colNo = 0;
			cin >> colName;
			for (int i = 1; i <= d->getNumberCols();i++)	//Looping through all the available headers to get the column number.
			{
				if (d->getHeader(i) == colName)
				{
					colNo = i - 1;
					break;
				}
			}
			if (colNo >= 2 && colNo <= 4)					//if the colNo is 2,3 and 4 only then it will call the findAverage method or else it will
			{												// print out an error stating that is not an interger type column.
				cout << "Min of " << colName << " is " << int(d->findMin(colNo)) << endl;
				break;
			}
			else cout << "Min for " << colName << " cannot be found since it is nan" << endl;
			break;
		}
		default:											//Default method for wrong input.
			cout << "Wrong Input" << endl;
			break;
		}
		std::cin >> command;						
	}	
	delete d;												//deleting the DataFrame object.
	return 0;
}