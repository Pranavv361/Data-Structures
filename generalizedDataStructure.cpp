// Project 4
// Fall 2022
// Computing Structures

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list

using namespace std;

class GL; // prototype for class GL

// node class to store char and generalized linked list called down
class node
{
protected:
    char* charVariable; // single char variable pointer (not an array)
    GL* down;           // going down to the next level

public:
    node(); // default constructor

    // setters
    void setCharVariable(char var);             //setCharVariable method to store the character
    void setDown(GL* d);                        //setDown method to point to new GL list

    // getters
    char* getChar();                            //getChar() method used to get the value
    GL* getDown();                              //getDown() method used to get the down pointer

    // display
    void displayChar();                         //displayChar() method to display characters.
};
node::node() {
    charVariable = NULL;                        //Initializing charVariable to NULL and down to NULL
    down = NULL;
};
void node::setCharVariable(char var) {
    charVariable = new char(var);               //setting the charVariable using deep-copy
    *charVariable = var;
};
void node::setDown(GL* d)
{
    down = d;                                   //setting the down node to d
};
char* node::getChar() {
    return charVariable;                        //getChar() method returning charVariable
};
GL* node::getDown() {
    return down;                                //getDown() method returning down
};
void node::displayChar()                        //displayChar() method to display the charVariable
{
    cout << *charVariable << " ";
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class Generalized List
class GL
{
protected:
    list<node> head; // head of the list - each object is of type node class

public:
    GL();                                         // default constructor
    void buildGL(string l);                       // to build the generalized list
    bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
 //   int LCAdistance(char char1, char char2);      // find the LCA distance of two char in the expression
    int heightOfGL();                             // return the height of the GL using the GL
    void searchDuplicates();                      // print all the duplicates in the GL
    void display();                               // display list
    string getString();                           // Helper method to get string of the expression
 //   string findPath(char a);                      // Helper method to find path of a character
};
GL::GL() {
    //head ;
};
void GL::buildGL(string l)
{
    string st = l;
    int stSize = st.size();
    if (st[0] == '(' && st[stSize - 1] == ')')          // removing the first and last round bracket and storing the string again.
    {                                                   //  ex: (abc) will be abc
        st = "";                                        //Intializing the string and storing the string without brackets
        for (int k = 1; k < stSize - 1; k++)
            st += l[k];
    }
    stSize = st.size();
    node store;
    GL* downTemp = new GL();
    for (int i = 0; i < stSize; i++)                    // looping through the expression without outer round brackets
    {
        if (st[i] == '(')                               // if the expression has '(' it will go inside the loop or else it will the store
        {                                               // the character in else if condition
            int j = i;                                  // storing the loop counter
            int openB = 0;                              // integer variable to count open brackets
            string substr = "";                         // Initializing new Substring
            for (int k = i; k < stSize; k++)            // counting the number of open and close brackets and incrementing openB
            {
                if (st[k] == '(') openB++;
            }
            for (int k = i; (k < stSize) && (openB != 0); k++)  //storing the substring and decrementing the openB so that complete string is stored.
            {
                if (st[k] == ')') openB--;
                substr += st[k];
                j = k;                                  //storing number of characters traversed in j
            }
            downTemp->buildGL(substr);                   // calling same funtion recursively to store the characters and down pointers
            i = j;                                       // updating the for loop counter.
            //store.setCharVariable(NULL);
            store.setDown(downTemp);                     //using Node to setDown down pointer returned by downTemp
            head.push_back(store);                       //storing the head value using pushback
        }
        else if (st[i] != '(' && st[i] != ')')             //This condition will execute only if characters are to be stored without down pointer
        {
            store.setCharVariable(st[i]);                // This will setCharVariable to the character value
            store.setDown(NULL);                         // This will store the setDown pointer to NULL so that character variable will not have down pointer.
            head.push_back(store);                       // storing the head value by using pushback
        }
    }
};
string GL::getString()                                   // Using string method to return the string from an GL expression
{
    string exp;                                         // Declaring the string
    list<node>::iterator i;                             // Declaring the iterator
    for (i = head.begin(); i != head.end(); ++i)        // the for loop will run for expression head size()
    {
        if (i->getDown() != NULL)                       // if getDown() is not null, that means the Down pointer is pointing to nextlevel.
        {                                               // Recursively call the getString() method to point where it reaches the last level.
            exp += i->getDown()->getString();           // The else condition will execute once it reaches last level and characters will be returned and stored in exp.
        }
        else                                            // The else will run to getChar() character and adding it to exp string.
        {
            exp += *(i->getChar());
        }
    }
    return exp;                                         // returning the string at the end of method call.
}

void GL::display()                                      // Using display method to display the GL expression
{
    list<node>::iterator i;                             // Declaring the iterator
    for (i = head.begin(); i != head.end(); ++i)        // the for loop will run for expression head size()
    {
        if (i->getDown() != NULL)                       // if getDown() is not null, that means the Down pointer is pointing to nextlevel.
        {
            i->getDown()->display();                     // Recursively call the display() method to point where it reaches the last level.
        }
        else
            i->displayChar();                           //else it will call the displayChar() method of node class
    }
};
bool GL::findCharInExpression(char findThisChar)        //findCharInExpression to find the character in a GL expression
{
    list<node>::iterator i;                             // Declaring the iterator
    for (i = head.begin();i != head.end(); ++i)         // the for loop will run for expression head size()
    {
        if (i->getDown() == NULL)                       // if getDown() method is null, it will check for characters in using getChar() and 
        {                                               // comparing it to the input Character variable
            if (*(i->getChar()) == findThisChar)        // if the condition is true  it will return true and the loop will break
            {
                return true;
                break;
            }
        }
        else                                            // else if getDown() is not null, It will recursively call the findCharInExpression
        {                                               // The return type will be stored in bool check
            bool check;
            check = i->getDown()->findCharInExpression(findThisChar);
            if (check == true)                          // if bool check is true then it will return true or else it will break the loop
                return true;
            break;
        }
    }
    return false;                                       // If the character is not found in all the levels it will return false
}
int GL::heightOfGL()                                    //heightOfGL() method will return the maximum height of the expression
{
    list<node>::iterator i;                             // Declaring the iterator
    for (i = head.begin();i != head.end(); ++i)         // the for loop will run for expression head size()
    {
        if (i->getDown() != NULL)                       //checking if the expression has next level by checking the getDown() is equal to NULL
        {                                               // if its not equal to null, it will initialize the height variable to zero
            int height = 0;
            height = i->getDown()->heightOfGL();        // Recursively call the heightGL() method to point where it reaches the last level.
            return height + 1;                          // returning height + 1
        }
    }
    return 1;                                           // returning 1 if the expression has only 1 level and it will return 1 for the recursive levels
};                                                      // Line 183 and 184, height will added through recursive calls
void GL::searchDuplicates()                             // searchDuplicates() method will search for duplicates in a string
{
    string exp;                                         // Declaring string exp;
    int count = 0;                                      // Initializing the count to zero
    exp = this->getString();                            // calling the getString() method and storing the string in exp
    for (int i = 0; i < exp.size(); i++)                // Using nested for loop to check for duplicates.
    {
        for (int j = i + 1; j < exp.size(); j++)
        {
            if (exp[i] == exp[j])                       // if both the characters are equal, the count will increment
            {
                count++;
                if (count > 0)                          // if count > 0, the character will be printed.
                    cout << exp[i];
            }
        }
    }
    if (count == 0)                                     // At the end of the loop if count still remains zero it will print None.
    {
        cout << "None";
    }
};

int main()
{
    int numExpressions; // number of expressions
    char option;        // command from the input file

    // read the number of expressions given
    cin >> numExpressions;
    cout << "Number of expressions: " << numExpressions << endl;

    GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects

    for (int i = 0; i < numExpressions; i++)     // read one line/expression at a time and call the buildGL method for each expression[i]
    {
        string x;
        cin >> x;
        expressions[i].buildGL(x);
    }
    cout << endl;                               //To print next line after "Number of Expressions"
    // read in and process all the options using switch case
    cin >> option;
    while (!cin.eof())						//It will check for end of the line.
    {
        switch (option)
        {
        case 'D':
        {
            cout << "Displaying all expressions:" << endl;
            for (int i = 0; i < numExpressions; i++)     // calling display function in a loop.
            {
                cout << "Expression " << i << " : ";         // displaying the expression
                expressions[i].display();                // calling the display method of GL class.
                cout << endl;
            }
            cout << endl;
            break;
        }
        case 'F':
        {
            int exp;
            char find;
            cin >> exp >> find;                         // taking in Input character and expression number
            if (expressions[exp].findCharInExpression(find) == true) //If expression is true, displaying "found" or else "not found"
            {
                cout << "Find " << find << " in " << exp << ":" << " found";
                cout << endl;
            }
            else
            {
                cout << "Find " << find << " in " << exp << ":" << " not found";
                cout << endl;
            }
            cout << endl;
            break;
        }
        case 'H':
        {
            int exp;                                    // taking in expression number
            cin >> exp;
            cout << "Height of expression " << exp << " : " << expressions[exp].heightOfGL() << endl;; // Calling the heightOfGL() method.
            cout << endl;
            break;
        }
        case 'U':
        {
            int exp;
            cin >> exp;                                // taking in Input character and expression number
            cout << "Duplicates in " << exp << " : ";  // Calling the searchDuplicates method to check for duplicates in an expression.
            expressions[exp].searchDuplicates();
            cout << endl;
            break;
        }
        default:									    //Default method for wrong input.
            cout << "Wrong Input" << endl;
            break;
        }
        std::cin >> option;
    }
    return 0;
}
