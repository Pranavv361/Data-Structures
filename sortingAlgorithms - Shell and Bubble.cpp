//Computing Structures
//Fall 2022
//Project 6
//Author: Aditya Narasimhan

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                            // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;
    
    int *A = new int[n];        //creating an Array pointer with n pointers

    srand(s);                   // setting seed s
    int range = u - l + 1;      // calculating the range

    std::unordered_set<int> numbers;            // delcaring an unordered set of data type int

    while (numbers.size() < n)                  // Generating random variables and storing them in set
        numbers.insert(rand() % range + l);

    int tempCount = 0;                          // tempcount for Index of Array
    for (auto i : numbers)                      // Iterating through set and storing the values in Array
    {
        if(tempCount < n)     
        (A[tempCount]) = i;
        tempCount++;
    }

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;  // looping through array and printing the randomly generated numbers
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }

    cout << endl;
    cout << endl;

    int* sortA = bubbleSort(A, n, n * n);                       // calling bubbleSort method to sort the array with number of inversions = n*n

    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;   // looping through the array and printing sorted array
    for (int i = 0; i < n; i++)
    {
        cout << sortA[i] << " ";
    }
    cout << endl;
    cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int* bubResult = bubbleSort(A, n, D);                       // calling the bubbleSort method with D as constraint on number of inversions
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;           // storing the output in bubResult
    for (int i = 0; i < n; i++)                                 // looping through the bubResult and printing the Bubble sort output
    {
        cout << bubResult[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    int inversionCount = 0;                                     // Initializing the inversion count variable
    for (int i = 0; i < n; i++)                                 // For loop will compare the j th elements on the right side of i th element
    {                                                           // If they are greater the counter will increase.
        for (int j = i + 1; j < n; j++)
        {
            if(bubResult[j] < bubResult[i])
            inversionCount++;
        }
    }
    cout << "Number of inversions in bubResult: " << inversionCount << endl;

    int *posC = new int[n];                                     // Creating new array pointer to store the Chebyshev distance of the elements
    for (int i = 0; i < n;i++)                                  // For loop to check the displacement of elements in completely sorted array and bubResult
    {
        for (int j = 0; j < n;j++)                          
        {
            if(sortA[i] == bubResult[j])                        // While comparing the elements if the elements are same, storing the absolute value of
            {                                                   // difference between i th and jth value
                posC[i] = abs(i - j);
                break;
            }
        }
    }
    int maxNum = 0;                                             // Initalizing the maximum number
    for (int i = 0; i < n;i++)                                  // Looping the posC array to get the maximum number from the chebyshev distance
    {
        if (maxNum < posC[i])
            maxNum = posC[i];
    }
    cout << "Chebyshev distance in bubResult: " << maxNum << endl;
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int* copyA = new int[n];                                    // Creating a copy of the original random array
    for (int i = 0; i < n; i++)
    {
        copyA[i] = A[i];
    }

    int* shellResult = shellSort(copyA, n, D);                  // calling the shellSort method with D as constraint on number of inversions
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;            // storing the output in shellResult
    for (int i = 0; i < n; i++)                                 // looping through the bubResult and printing the Shell sort output
    {
        cout << shellResult[i] << " ";
    }
    cout << endl;
    cout << endl;

    int inversionCount1 = 0;                                    // Initializing the inversion count variable
    for (int i = 0; i < n; i++)                                 // For loop will compare the j th elements on the right side of i th element
    {                                                           // If they are greater the counter will increase.
        for (int j = i + 1; j < n; j++)
        {
            if (shellResult[j] < shellResult[i])
                inversionCount1++;
        }
    }
    cout << "Number of inversions in shellResult: " << inversionCount1 << endl;

    int* posC1 = new int[n];                                    // Creating new array pointer to store the Chebyshev distance of the elements
    for (int i = 0; i < n;i++)                                  // For loop to check the displacement of elements in completely sorted array and shellResult
    {
        for (int j = 0; j < n;j++)
        {
            if (sortA[i] == shellResult[j])                     // While comparing the elements if the elements are same, storing the absolute value of
            {                                                   // difference between i th and jth value
                posC1[i] = abs(i - j);
                break;
            }
        }
    }
    int maxNum1 = 0;                                            // Initalizing the maximum number
    for (int i = 0; i < n;i++)                                  // Looping the posC1 array to get the maximum number from the chebyshev distance
    {
        if (maxNum1 < posC1[i])
            maxNum1 = posC1[i];
    }
    cout << "Chebyshev distance in shellResult: " << maxNum1 << endl;

    delete[]A;                                              // deleting all the array pointers.
    delete[]bubResult;
    delete[]shellResult;
    delete[]sortA;
    delete[]posC;
    delete[]posC1;
    return 0;
}