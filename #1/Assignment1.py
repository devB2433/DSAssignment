# Assignment #1 
# Students Names: Songtao Bei 
# Date last revised: 2025-05-13

# Description: This program will perform experimental analysis of two different algorithms 
# that do the exact same thing.  Using the execution times obtained, the growth rates can be  
# determined and compared. 

# What is given here is just to help you perform the experiment.  Make sure you understand it.   
# It includes the following: 
#     - it prompts the user for which algorithm to run
#     - it prompts the user for the initial size of the input 
#     - it creates an array of that size and populates it with random integers from 1 to 100 
#     - it executes and times how long an algorithm takes on size x, 2x, 3x, 4x, and 5x, 
#            where "x" is the initial size the user enters. 
#     		- for each size, it executes the algorithm 3 times 
#  
# What you will need to add (minimally): 
# - code to implement the prefix averages algorithms; see block comments below
 
#  Note: Starter Code is copyright (c) 2025 Hoda Fahmy

from statistics import mean
import random 
import time
import csv
from datetime import datetime
from statistics import mean #for algorithm 3


def create_random_array(n):
    """ 
    Returns an array of size n containing random integers from [1..100]

    Parameters:
    n (int): the size of the array to be created

    Returns:
    list: the created int array 
    """

    random_array = [0]*n
    for x in range(n):
        random_array[x] = random.randint(1,101)
    #print (random_array)
    return random_array

def get_algorithm_choice():
    """
    Prompts the user for a choice of algorithm.

    Returns:
    int: The user's choice of algorithm (1, 2, or 3).
    """

    choice = -1
    while choice < 1 or choice > 3:  # 修改为允许1到3的输入
        print("1: prefix_averages1")
        print("2: prefix_averages2")
        print("3: prefix_averages3")
        choice = int (input("Which algorithm do you want to run? "))
    return choice

def display(input_array, output_array):
    """
    Displays the contents of the input and output lists

    Parameters:
    input_array (list): The input array for which to compute the prefix averages.
    output_array (list): The output array containing the prefix averages.

    """
    print("Input Array with size ", size)
    print("=" * 40)
    print(input_array)
    print()
    print("Output Array with size ", size)
    print("=" * 40)
    if output_array != None:
        formatted_output_array = ', '.join(['{:.3f}'.format(value) for value in output_array])
        print(formatted_output_array) 
    else:
        print(output_array)
    print()


def prefix_averages1(input_array):
    """
    Computes the prefix averages of an input array using the prefix_averages1 
    algorithm 

    Parameters:
    input_array (list): The input array for which to compute the prefix averages.

    Returns:
    list: The list of prefix averages.
    """
    # Add code to implement this function
    
    """
    explanation of the pseudocode:
    This pseudocode describes the prefix_averages1 algorithm, which computes the prefix averages of an array.
    The Algorithm:
    The Algorithm
    1,Create an array A of size n to store the results.
    2,For each index i from 0 to n-1:
        3,Initialize a variable a to 0. This will be used to accumulate the sum.
        4,For each index j from 0 to i:
        5,Add X[j] to a.
        6,After the inner loop, a contains the sum of X[0] to X[i].
        7,Set A[i] to a / (i+1), which is the average of the first i+1 elements.
    8,Return the array A.
    """

    A = [] ## create an array to store the results
    for i in range(len(input_array)):
        a = 0
        for j in range(i+1):
            a += input_array[j] ## add all the numbers
        A.append(a/(i+1)) ## calculate the average
    return A

def prefix_averages2(input_array):
    """
    Computes the prefix averages of an input array using the prefix_averages2 
    algorithm 

    Parameters:
    input_array (list): The input array for which to compute the prefix averages.

    Returns:
    list: The list of prefix averages.
    """
    # Add code to implement this function

    """
    explanation of the pseudocode:
    the difference between this algorithm and the first one is that use one loop instead of two.
    """

    A = [] ## create an array to store the results
    a = 0
    for i in range(len(input_array)):
        a += input_array[i] ## add all the numbers
        A.append(a/(i+1)) ## calculate the average
    return A

def prefix_averages3(input_array):
    """
    Computes the prefix averages of an input array using the python built-in function mean()
    """
    A = []
    for i in range(len(input_array)):
        A.append(mean(input_array[:i+1]))
    return A


if __name__ == '__main__':
    testing = False   #Set this to False once code is verified and you are ready to begin experimental growth rate analysis
    alg = get_algorithm_choice()
    initial_size = int (input("What is the initial size of the array? "))
    size = initial_size
    num_of_runs = 3    #change this if you want more runs
    
    # Create CSV filename (using timestamp and algorithm choice)
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"results_alg{alg}_{timestamp}.csv"
    
    # Prepare CSV data
    csv_data = []
    headers = ["Input Size", "#1", "#2", "#3", "Average"]
    csv_data.append(headers)
    
    for x in range(5):
        input_array = create_random_array(size) 
        print("Running with input size of ", size)
        print("=" * 40)
        
        run_times = []
        for run in range(1,num_of_runs+1):
            start = time.time()
            if alg == 1:
                output_array = prefix_averages1(input_array)
            elif alg == 2:
                output_array = prefix_averages2(input_array)
            elif alg == 3:
                output_array = prefix_averages3(input_array)
            exec_time = 1000 * (time.time() - start)
            run_times.append(exec_time)
            print(f"Run #{run} on input size {size} took {exec_time:.2f} ms.")
        
        # Calculate average and add to CSV data
        avg_time = mean(run_times)
        row_data = [size] + [f"{t:.2f}" for t in run_times] + [f"{avg_time:.2f}"]
        csv_data.append(row_data)
        
        print()

        if testing:
            display(input_array, output_array)
        
        size += initial_size  # Increase input size for next iteration.
    
    # Write data to CSV file
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(csv_data)
    
    print(f"\nResults have been saved to file: {filename}")