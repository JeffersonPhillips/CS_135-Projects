/* -----------------------------------------------------------------------------
FILE:               Array_Processor.cpp
DESCRIPTION:        This program computes statistical values based on data stored in .txt files. 
COMPILER:           MS Visual Studio 2017  C++ compiler
NOTES:              This semester I learned a lot, thank you :)

MODIFICATION HISTORY:

Author                          Date               Version              Comments
---------------                 ----------         --------------       --------------
Jefferson Phillips Retana       2019-05-07         1.0                  0% Complited at this point.
Jefferson Phillips Retana       2019-05-07         1.1                  Array is reading infromation from the input files properly.
Jefferson Phillips Retana       2019-05-07         1.2                  First 4 functions were added and tested. 
Jefferson Phillips Retana       2019-05-07         1.3                  Standard deviation and Sorting functions were added. 
Jefferson Phillips Retana       2019-05-07         2.0                  Modifications after in-class presentation.
Jefferson Phillips Retana       2019-05-08         2.1                  Separate function for getting the data ready.
Jefferson Phillips Retana       2019-05-08         2.2                  Print to file was added.
----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

//Global Constants
const string PROGRAMMER_NAME = "Jefferson Phillips Retana";
const int array_size = 1000;

//Prototypes
string read_file(int[], int &);
int get_min(int[], int);
int get_max(int[], int);
int get_total(int[], int);
double get_average(int, int);
double get_sdev(int[], int, double);
void sort_array(int[], int);
void swap(int &, int &);
double get_median(int[], int);
void mode(ostream&, int[], int);        //Print from its own function.
void histogram(ostream&, int[],int);    //Print from its own function. 

/* -----------------------------------------------------------------------------
FUNCTION:          main ()
DESCRIPTION:       main function of the program
RETURNS:           Integer number
NOTES:             
----------------------------------------------------------------------------- */
int main()
{
    int data[array_size];
    int number_of_elements = 0;
    
    string input_file_name = read_file(data, number_of_elements);    //Getting everything ready
    
    int min = get_min(data, number_of_elements);
    int max = get_max(data, number_of_elements);
    int sum_total = get_total(data, number_of_elements);
    double average = get_average(sum_total, number_of_elements);
    double sdev = get_sdev(data, number_of_elements, average);
    sort_array(data, number_of_elements);
    double median = get_median(data, number_of_elements);

    cout << endl;
    cout << "No. points: " << number_of_elements << endl;
    cout << "The Min is: " << min << endl;
    cout << "The Max is: " << max << endl;
    cout << "Sum  Total: " << sum_total << endl;
    cout << "The Avg is: " << average << endl;
    cout << "Std Dev is: " << sdev << endl;
    cout << "Median  is: " << median << endl;

    mode(cout, data, number_of_elements); //This is printed from its own function
    histogram(cout , data, number_of_elements);//This is printed from its own function

    cout << endl << endl;
    
    //Printing out to file.

    string output_filename;     //Create the object
    ofstream output_file;
    cout << "Output filename: ";
    cin >> output_filename; 
    output_file.open(output_filename);
    
    output_file << "\nInput file name: " << input_file_name << endl << endl;
    output_file << "No. points: " << number_of_elements << endl;
    output_file << "The Min is: " << min << endl;
    output_file << "The Max is: " << max << endl;
    output_file << "Sum  Total: " << sum_total << endl;
    output_file << "The Avg is: " << average << endl;
    output_file << "Std Dev is: " << sdev << endl;
    output_file << "Median  is: " << median << endl;

    mode(output_file, data, number_of_elements);        //This is printed from its own function
    histogram(output_file, data, number_of_elements);   //This is printed from its own function

    output_file.close();

	cout << "\nProgrammed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

	system("pause");
	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          read_file()
DESCRIPTION:       reads the first elements on the files
RETURNS:           Integer array
NOTES:             
----------------------------------------------------------------------------- */
string read_file(int* data, int &number_of_elements)
{
    string file_name;
    ifstream input_file;            //Create the file object
    bool file_validation;

    do
    {
        file_validation = false;
        cout << "\nInput file name: ";  //Get the file to use.
        cin >> file_name;
        input_file.open(file_name);     //Open the file

        if (!input_file)            //Check if it opened correctly, loop if it didnt.
        {
            file_validation = true;
            cout << "The file didn't open correctly, please try again." << endl;
        }
    }
    while(file_validation);

    while(input_file >> data[number_of_elements])        //Returns a boolean expresion checking if the file doesn't have more elemets.
    {
        number_of_elements++;                    //At the end, number_of_elements will have the pseudo-total number of elements.
    }
    input_file.close();

    return file_name;
}


/* -----------------------------------------------------------------------------
FUNCTION:          get_min()
DESCRIPTION:       Finds the minimun value in the array.
RETURNS:           Integer number
NOTES:             
----------------------------------------------------------------------------- */
int get_min(int data[], int elements)
{
    int index = 0; 
    int min = data[index];

    for(; index != elements; index++)
    {
        if(min > data[index])
            min = data[index];
    }

    return min;
}

/* -----------------------------------------------------------------------------
FUNCTION:          get_max()
DESCRIPTION:       Finds the maximun value in the array.
RETURNS:           Integer number
NOTES:             
----------------------------------------------------------------------------- */
int get_max(int data[], int elements)
{
    int index = 0; 
    int max = data[index];

    for(; index != elements; index++)
    {
        if(max < data[index])
            max = data[index];
    }

    return max;
}

/* -----------------------------------------------------------------------------
FUNCTION:          get_total()
DESCRIPTION:       Adds all the values in the array (not the garbage)
RETURNS:           Integer number
NOTES:             
----------------------------------------------------------------------------- */
int get_total(int data[], int elements)
{
    int index = 0; 
    int total = 0;

    for(; index != elements; index++)
    {
        total += data[index];
    }

    return total;
}

/* -----------------------------------------------------------------------------
FUNCTION:          get_average()
DESCRIPTION:       Calculates the average (without using the array)
RETURNS:           Floating point
NOTES:             
----------------------------------------------------------------------------- */
double get_average(int sum, int elements)
{   
    double average = double(sum)/double(elements);

    return average; 
}

/* -----------------------------------------------------------------------------
FUNCTION:          sdev()
DESCRIPTION:       Calculates the global standar deviation 
RETURNS:           Floating point
NOTES:             
----------------------------------------------------------------------------- */
double get_sdev(int data[], int elements, double mean)
{
    double sdev; // = The square root of the variance
    double variance; // = (x-mean)/n-1. The sum of the differences of the elements - the mean divided by the quantity of elements -1.
    double numerator = 0;
 
    for(int index=0; index < elements; index++)
    {
        numerator += pow((double(data[index]) - mean),2);
    }

    variance = numerator/elements;
    sdev = sqrt(variance);

    return sdev;
}


/* -----------------------------------------------------------------------------
FUNCTION:          sort_array()
DESCRIPTION:       Sorts the elements of an array from smales to largest 
RETURNS:           Nothing
NOTES:             This one uses the selection sort algorithm found in Chapter 8, Starting Out with C++. Author: Tonny Gaddis.
----------------------------------------------------------------------------- */
void sort_array(int data[], int elements)
{
    int minindex, minvalue;

    for(int start = 0; start < (elements-1); start++)
    {
        minindex = start;
        minvalue = data[start];
        for(int index = start+1; index < elements; index++)
        {
            if (data[index]<minvalue)
            {
                minvalue = data[index];
                minindex = index;
            }
        }
        swap(data[minindex], data[start]);

    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          swap()
DESCRIPTION:       Exchange the memory addresses of two variables. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void swap(int &helloo, int &goodbye)
{
    int z;

    z = helloo;
    helloo = y;
    goodbye = z;
}

/* -----------------------------------------------------------------------------
FUNCTION:          median()
DESCRIPTION:       Calculates the value in the middle of the data set. 
RETURNS:           Floating point
NOTES:             
----------------------------------------------------------------------------- */
double get_median(int data[], int elements)
{
    double median_location = elements/2 -1;
    double median;

    if(median_location-int(median_location) == 0.00)
    {
        median = (data[int(median_location)]+data[int(median_location+1)])/2.0;
    }
    else
    {
        median = data[int(median_location+0.5)];
    }

    return median;
}

/* -----------------------------------------------------------------------------
FUNCTION:          mode()
DESCRIPTION:       Calculates and displays the mode(s). 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void mode(ostream& print_to, int array[], int elements)
{
    vector<int> mode_vector;
    int counter = 0;
    int greates_rep = 0;

    for(int index = 0; index < elements; index++)
    {

        for(int subindex = 0; subindex < elements; subindex++)
        {
            if (array[index]==array[subindex])
                counter++;
        }

        if (counter > greates_rep)
        {            
            greates_rep = counter;
            mode_vector.clear();
            mode_vector.push_back(array[index]);
        }
        else if(counter == greates_rep)
        {
            mode_vector.push_back(array[index]);
        }
        counter = 0;
    }

    print_to << "Modes  are: ";

    for(int index = 0; index < mode_vector.size(); index += greates_rep)
        print_to << mode_vector[index] << "  ";

    print_to << endl << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          histogram()
DESCRIPTION:       Displays a histogram of the data. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void histogram(ostream& print_to, int data[], int elements)
{
    int start = 1;
    int finish = 100;

    print_to << "Histogram:" << endl << endl;

    while(finish<1001)
    {   
        print_to << setw(4) << start << " - " << setw(4) << finish << ": ";
        
        for (int index = 0; index < elements; index++)
        {
            if ((data[index] > start) && (data[index] < finish))
                print_to << "*";
        }
        
        print_to << endl;
        start += 100;
        finish += 100;
    }
}