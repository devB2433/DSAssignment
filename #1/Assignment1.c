/* Assignment #1 
 *
 * Students Names:  Songtao Bei
 * Date last revised:    2025-05-13
 * 
 * Description: This program will perform experimental analysis of two different algorithms 
 * that do the exact same thing.  Using the execution times obtained, the growth rates can be  
 * determined and compared. 
 *  
 * What is given here is just to help you perform the experiment.  Make sure you understand it.   
 * It includes the following: 
 *     - it prompts the user for which algorithm to run
 *     - it prompts the user for the initial size of the input 
 *     - it creates an array of that size and populates it with random integers from 1 to 100 
 *     - it executes and times how long the algorithm takes on size x, 2x, 3x, 4x, and 5x, 
 *            where "x" is the initial size the user enters. 
 *     		- for each size, it executes the algorithm 3 times 
 *  
 * What you will need to add (minimally): 
 *  - code to implement the prefix averages algorithms; see block comments below
 *  
 * 
 * Note: Starter Code is copyright (c) 2025 Hoda Fahmy
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Function declarataions:
int getAlgorithmChoice();
int* generateArray(int n);
void printIntArray(int *array, int size);
void printFloatArray(float *array, int size);
void display(int *input, float *output, int size);

//Functions to be implemented:
float* prefixAverages1(int X[],  int n);   
float* prefixAverages2(int X[],  int n);


int main() { 
    int initialSize=0;
    int size = 0;
    int numOfRuns = 3;      //Change this if you want more runs
    bool testing = False;    //Set this to False once code is verified and you are ready to perform experimental growth rate analysis
    int *inputArray=NULL;
    float *outputArray=NULL;
    clock_t start;
    double executionTime=0.0;

    int algo = getAlgorithmChoice();
    if (algo==1) 
        printf("Enter the initial size of the array for PrefixAverages1:  ");
    else 
        printf("Enter the initial size of the array for PrefixAverages2:  ");

    scanf("%d", &initialSize);
    size=initialSize;

    for (int i = 0; i < 5; i++) {
        printf("Running with input size of %d\n", size);
        printf("=====================================\n\n");
        //generate  input array
        inputArray = generateArray(size);
        
        //Run algorithm numOfRuns times 
        for(int j=1; j<=numOfRuns; j++) {
            start = clock();

            //You will need to implement prefixAverages1 and prefixAverages2 
            if (algo==1) 
                outputArray = prefixAverages1(inputArray, size);
            else
                outputArray = prefixAverages2(inputArray, size);

            executionTime = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
            printf("Run #%d on an input size of %d took %f ms\n", j, size, executionTime);       
        }

        if (testing)
            display(inputArray, outputArray, size);
       
        printf("\n\n");

        size += initialSize;  //Increase input size for next iteration.
        
        //free memory
        free(inputArray);
        free(outputArray);
    }
} 

/*******************************************************************
*  Method Name: getAlgorithmChoice
*  Returns: an int representing user's choice
*  Parameters: none
*  Description: Prompts the user for a choice of algorithm
*******************************************************************/

int getAlgorithmChoice() {
    int choice = -1;
    while (choice < 1 || choice > 2) {
        printf("1: prefix_averages1\n");
        printf("2: prefix_averages2\n");
        printf("Which algorithm do you want to run? ");
        scanf("%d", &choice);
    }
    return choice;
}

/*******************************************************************
*  Method Name: generateArray
*  Returns: a pointer to an int array
*  Parameters: int representing length of an array
*  Description: generates an array of size length of random integers
*******************************************************************/

int* generateArray(int n) {
    srand(time(NULL)); // Generate Random Number Seed
    //create new array
    int *input = malloc(n*sizeof(int)); // Array of Values
    //Populate the array with random values from 1 to 100 
    for (int r = 0; r < n; r++) {
        input[r] = rand()%100 + 1;
    }
    return input;
  }

/*******************************************************************
*  Method Name: printIntArray
*  Returns: nothing
*  Parameters: an int array and the size
*  Description: prints the contents to screen
*******************************************************************/

void printIntArray(int *array, int size) {
    printf("[ ");
    for (int r = 0; r < size-1; r++) {
        printf("%d, ", array[r]);
    }
    printf("%d]\n\n", array[size-1]);
}

/*******************************************************************
*  Method Name: printFloatArray
*  Returns: nothing
*  Parameters: a float array and the size
*  Description: prints the contents to screen
*******************************************************************/

void printFloatArray(float *array, int size) {
    printf("[ ");
    for (int r = 0; r < size-1; r++) {
        printf("%.3f, ", array[r]);
    }
    printf("%.3f]\n", array[size-1]);
}

/*******************************************************************
*  Method Name: display
*  Returns: nothing
*  Parameters: an int array (input), a float array (output) and the size
*  Description: prints the contents of the input and output arrays 
*               to the screen when testing with small input sizes
*******************************************************************/
void display(int* input, float* output, int size) {
    printf("\nInput Array with size %d\n", size);
    printf("==============================\n");
    printIntArray(input, size); 
    printf("Output Array with size %d\n", size);
    printf("==============================\n");  
    printFloatArray(output, size);  
}

/*******************************************************************
*  Method Name: prefixAverages1
*  Returns: a pointer to a float array
*  Parameters: an int array and the size of the array
*  Description: implements the prefixAverages1 algorithm given in 
*  the assignment description
*******************************************************************/

float* prefixAverages1(int X[],  int n){
     float* A = (float*) malloc(n * sizeof(float));
     //Add your code for prefixAverages2 here:
    for (int i = 0; i < n; i++) {
            int a = 0;
            for (int j = 0; j <= i; j++) {
                a += X[j];//sum the values
            }
            A[i] = (float)a / (i + 1); // calculate the average
        }
     return A;

}



/*******************************************************************
*  Method Name: prefixAverages2
*  Returns: a pointer to a float array
*  Parameters: an int array and the size of the array
*  Description: implements the prefixAverages2 algorithm given in 
*  the assignment description
*******************************************************************/

float* prefixAverages2(int X[],  int n){
    float* B = (float*) malloc(n * sizeof(float));
    //Add your code for prefixAverages2 here:
    int b = 0; 
    for (int i = 0; i < n; i++) {
        b += X[i];
        B[i] = (float)b / (i + 1); // calculate the average
    }
    return B;

}