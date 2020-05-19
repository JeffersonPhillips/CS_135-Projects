/* -----------------------------------------------------------------------------
FILE:               Math_Testor.cpp
DESCRIPTION:        This program tests a user’s math skills with randomly generated arithmetic problems. 
                    The program is written for a 5th grade audience.
COMPILER:           MinGW
NOTES:              Project #2

MODIFICATION HISTORY:

Author                          Date               Version              Comments
---------------                 ----------         --------------       --------------
Jefferson Phillips Retana       2019-04-13         1.0                  First version of the program.
Jefferson Phillips Retana       2019-04-13         1.1                  First 4 functions coded. I went for a coffee.
Jefferson Phillips Retana       2019-04-14         1.2                  Continue working on the Addition function.
Jefferson Phillips Retana       2019-04-14         1.3                  With half of the addition function ready, I compiled and debug the entire code for the first time. 
Jefferson Phillips Retana       2019-04-14         1.4                  The addition function is finished. The keep_score function was added.
Jefferson Phillips Retana       2019-04-14         1.5                  The print_to_file function was added.
Jefferson Phillips Retana       2019-04-14         2.0                  All the code was modifies so everything is now printing in a file as requested.
Jefferson Phillips Retana       2019-04-14         3.0                  All the remaining functions were added.
Jefferson Phillips Retana       2019-04-14         3.1                  Small changes in Subtraction, Division and ofstream after presentation in class.
Jefferson Phillips Retana       2019-04-14         3.2                  Final changes according to teacher's instructions.
----------------------------------------------------------------------------- */
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <ios>

using namespace std;

//Global constants
const string PROGRAMMER_NAME = "Jefferson Phillips Retana";

//Prototypes
int start_up(ofstream &,int);
char main_menu();
int generate_random (int);                              //Generates random numbers according to the set range.
void Addition(ofstream &,int, int);                     //Adds
void Subtraction(ofstream &, int, int);                 //Subtracts
void Multiplication(ofstream &, int, int);              //Multiplies
void Division(ofstream &, int, int);                    //Divides
void keep_score(ofstream &, int, bool);                 //Keeps the user's score
void print_to_file(ofstream &,string,char*,int,int);    //Print initial data to a file

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       Program's mother function.
RETURNS:           Integer value.
NOTES:             
----------------------------------------------------------------------------- */
int main()
{
    
    int seed = time(0); //Generate seed for all the program
    srand(seed);        //Randomise all rand's

    time_t starting_time = time(0);   //Current date/time based on current system

    ios cout_state(nullptr);
    cout_state.copyfmt(cout);       //Storing the actual setprecision

    int difficulty;
    int range;
    bool keep_running = true;   //Do-While loop Main Menu
    ofstream results;           //Create the object
    long timestamp;

    cout << "\t\tARITHMETIC PRACTICE PROGRAM\n";
    cout << "Welcome to the Math Skills Practice Program.\n";
    cout << "This program allows you to practice your math skills.\n" << endl;

    difficulty = start_up(results, seed);

    switch(difficulty) //Set range according the the problems' difficulty.
    {
        case 1: range = 10;
            break;
        case 2: range = 100;
            break;
        case 3: range = 1000;
            break;
        case 4: range = 10000;
            break;
        case 5: range = 100000;
            break;
    }
    
    do
    {
        char operation = main_menu();

        cout.copyfmt(cout_state); //Setting the precision to the default one.
        
        switch(operation)
        {
            case 'a': Addition(results,generate_random(range),generate_random(range));
                break;
            case 'b': Subtraction(results, generate_random(range),generate_random(range));
                break;
            case 'c': Multiplication(results, generate_random(range),generate_random(range));
                break;
            case 'd': Division(results, generate_random(range),generate_random(range));
                break;
            case 'q': keep_running = false;
                break;
        }
    }
    while(keep_running);

    time_t now = time(0);   //Current date/time based on current system
    char* dt = ctime(&now); //Convert to string form

    cout << endl << endl;
    cout << "----End of the test---" << endl;
    cout << "You finished the test on: " << dt;

    results << endl << endl;
    results << "----End of the test----" << endl;
    results << "You finished the test on: " << dt;

    cout << endl;
    cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

    results.close();    //Close the file

	system("pause");

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          start_up()
DESCRIPTION:       Initialize the program: Gets the name, set the time, define the seed, and gets the level of difficulty. 
RETURNS:           Integer value wich will be the level of difficulty.
NOTES:             
----------------------------------------------------------------------------- */
int start_up(ofstream &results, int seed)
{
    bool validate = true;
    int difficulty;
    string users_name;
   
    time_t now = time(0);   //Current date/time based on current system
    char* dt = ctime(&now); //Convert to string form

    cout << "Please enter your name." << endl;
    getline(cin,users_name);
    cout << endl;

//    cin.clear();                //The string upstairs is messing up the following do loop, so let's clear this thing before hand.
//    cin.ignore(10000,'\n');     //Not necessary after using getline

    cout << "Now select the difficulty level ( 1-5 ).\n";
    cout << "This will define the quantity of numbers per operation: ";

    do //Input Validation
    {
        if ((cin >> difficulty)&&(difficulty>0)&&(difficulty<6))
        {
            cout << endl;
            cout << users_name << ", you are starting the Math Practice on " << dt << "Lets do this!" << endl << endl;
            validate = false;
        }
        else
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "That is not a valid difficulty level, please select a number from 1 to 5:" << endl; 
        }
    }
    while(validate);

    print_to_file(results, users_name, dt, seed, difficulty);

    return difficulty;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main_menu()
DESCRIPTION:       Display the main menu, validates input.
RETURNS:           Character value.
NOTES:             
----------------------------------------------------------------------------- */
char main_menu()
{
    char operation;
    bool validation = true;

    cout << "Choose what to practice in the menu shown below.\n" <<
    "---------------------------------------------------------\n" <<
    "\t\tARITHMETIC PRACTICE PROGRAM\n" <<
    "\t\t\tMAIN MENU\n" <<
    "---------------------------------------------------------\n" <<
    "a. Addition\n" <<
    "b. Subtraction\n" <<
    "c. Multiplication\n" <<
    "d. Division\n" <<
    "q. Quit the program\n" <<
    "---------------------------------------------------------\n" <<
    "Enter your choice [ a b c d q ]:";
    
    cin >> operation; 
    operation = tolower(operation);

    do
    {
        if ((operation>='a')&&(operation<='d')||(operation=='q'))
        validation = false;
        else
        {
            cin.clear();
            cin.ignore(10000,'\n');   
            cout << "That option is not available, please select one of the letters above." << endl; 
        }
    }
    while(validation);

    return operation;
}

/* -----------------------------------------------------------------------------
FUNCTION:          generate_random(int)
DESCRIPTION:       Generates random numbers according to the set range. 
RETURNS:           integer value.
NOTES:             
----------------------------------------------------------------------------- */
int generate_random (int range)
{
    return rand() % range;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Addition(ofstream &, int, int)
DESCRIPTION:       Generates random wrong answeres. Randomise the placement of the correct answer.
                   Displays the question.
                   Validate input. Checks if the anwere is correct or not. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void Addition(ofstream &results, int operand1, int operand2)
{
    int result = (operand1 + operand2); //Actual result

    int displayed_options[4];   //Incorrect anwers
    int correct_ans;        //Where the correct answere will be stored.
    char users_choice;
    bool validation = true;
    char option_letter = 'a';
    bool wrong = true;
    int counter = 0;

    for(int index=0;index<2;index++)    //Generate four of the possible incorrect answers
    {
        displayed_options[index] = result+generate_random(25);        //Set the first two incorrect answers
        displayed_options[(index+2)] = result-generate_random(25);    //Set the last two incorrect answers

        if (displayed_options[index]==result)
            displayed_options[index]+=2;
        if (displayed_options[(index+2)]==result)
            displayed_options[(index+2)]+=2;
    }
    
    correct_ans = generate_random(5); // (0 to 4) Determine the position of the correct answer.

    if(correct_ans!=4) //If it is 4, the correct answer will be Non of the above.
    {
        displayed_options[correct_ans]=result;  //Set the correct answer to one of the 4 first options.
    }

    
    cout << "Solve:" << endl;
    cout << "\t" << setw(8) << setfill(' ') << operand1 << endl;
    cout << "\t" <<"+" << setw(7) << setfill(' ') << operand2 << endl;
    cout << "\t" << "________" << endl << endl;
    
    results << "Solve:" << endl;
    results << "\t" << setw(8) << setfill(' ') << operand1 << endl;
    results << "\t" <<"+" << setw(7) << setfill(' ') << operand2 << endl;
    results << "\t" << "________" << endl << endl;

    for(int index=0;index<4;index++)    //Display all the options
    {
        cout << "(" << option_letter++ << ")\t" << displayed_options[index] << endl;
        results << "(" << option_letter << ")\t" << displayed_options[index] << endl;
    }
    
    cout << "(e)\tNone of the above" << endl << endl;
    results << "(e)\tNone of the above" << endl << endl;

    cout << "Input your choice: ";
    results << "Input your choice: ";
    

    while(counter!=3) //3 strikes
    {
        cin>>users_choice;
        users_choice = tolower(users_choice);
        results << " " << users_choice << endl;

        while(validation)   //Input validation
        {
            if ((users_choice>='a')&&(users_choice<='e'))
            validation=false;
            else
            {
                cin.clear();
                cin.ignore(10000,'\n');   
                cout << "That option is not available, please select one of the letters above." << endl;
                results << "That option is not available, please select one of the letters above."; 
                cin>>users_choice; //Again just to go out of the validation loop.
                results << " " << users_choice << endl;
            }
        }

        if((((int)users_choice)-97)==correct_ans)  //Type cast user_choise (a-e) to integers, and compare it to the correct answer.
        {
            cout << "That is correct!" << endl << endl;
            results << "That is correct!" << endl << endl;
            counter = 3; 
            keep_score(results, 0, true);
        }

        else
        {
            cout << "That is not correct.";
            results << "That is not correct.";
            counter++;

            if(counter!=3)
            {
                cout << "Try again!";
                results << "Try again!";
                keep_score(results, 1, false);
            }
            else
            {
                cout << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                results << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                keep_score(results, 1, true);
            }
        }
        
        validation=true; //Reset input validation

    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          Subtraction(ofstream &,int, int)
DESCRIPTION:       Generates random wrong answeres. Randomise the placement of the correct answer.
                   Displays the question.
                   Validate input. Checks if the anwere is correct or not. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void Subtraction(ofstream &results, int operand1, int operand2)
{
    int result = (operand1 - operand2); //Actual result
    int displayed_options[4];   //Incorrect anwers
    int correct_ans;        //Where the correct answere will be stored.
    char users_choice;
    bool validation = true;
    char option_letter = 'a';
    bool wrong = true;
    int counter = 0;

    if (result<0)   //No negatives.
    {
        result = operand2 - operand1;

        cout << "Solve:" << endl;
        cout << "\t" << setw(8) << setfill(' ') << operand2 << endl;
        cout << "\t" <<"-" << setw(7) << setfill(' ') << operand1 << endl;
        cout << "\t" << "________" << endl << endl;
    
        results << "Solve:" << endl;
        results << "\t" << setw(8) << setfill(' ') << operand2 << endl;
        results << "\t" <<"-" << setw(7) << setfill(' ') << operand1 << endl;
        results << "\t" << "________" << endl << endl;
    }
    else
    {
        cout << "Solve:" << endl;
        cout << "\t" << setw(8) << setfill(' ') << operand1 << endl;
        cout << "\t" <<"-" << setw(7) << setfill(' ') << operand2 << endl;
        cout << "\t" << "________" << endl << endl;
    
        results << "Solve:" << endl;
        results << "\t" << setw(8) << setfill(' ') << operand1 << endl;
        results << "\t" <<"-" << setw(7) << setfill(' ') << operand2 << endl;
        results << "\t" << "________" << endl << endl;
    }

    for(int index=0;index<2;index++)    //Generate four of the possible incorrect answers
    {
        displayed_options[index] = result+generate_random(25);        //Set the first two incorrect answers
        displayed_options[(index+2)] = result-generate_random(25);    //Set the last two incorrect answers

        if (displayed_options[index]==result)
            displayed_options[index]+=2;
        if (displayed_options[(index+2)]==result)
            displayed_options[(index+2)]+=2;
    }
    
    correct_ans = generate_random(5); // (0 to 4) Determine the position of the correct answer.

    if(correct_ans!=4) //If it is 4, the correct answer will be Non of the above.
    {
        displayed_options[correct_ans]=result;  //Set the correct answer to one of the 4 first options.
    }

    for(int index=0;index<4;index++)    //Display all the options
    {
        cout << "(" << option_letter++ << ")\t" << displayed_options[index] << endl;
        results << "(" << option_letter << ")\t" << displayed_options[index] << endl;
    }
    
    cout << "(e)\tNone of the above" << endl << endl;
    results << "(e)\tNone of the above" << endl << endl;

    cout << "Input your choice: ";
    results << "Input your choice: ";
    

    while(counter!=3) //3 strikes
    {
        cin>>users_choice;
        users_choice = tolower(users_choice);
        results << " " << users_choice << endl;

        while(validation)   //Input validation
        {
            if ((users_choice>='a')&&(users_choice<='e'))
            validation=false;
            else
            {
                cin.clear();
                cin.ignore(10000,'\n');   
                cout << "That option is not available, please select one of the letters above." << endl;
                results << "That option is not available, please select one of the letters above."; 
                cin>>users_choice; //Again just to go out of the validation loop.
                results << " " << users_choice << endl;
            }
        }

        if((((int)users_choice)-97)==correct_ans)  //Type cast user_choise (a-e) to integers, and compare it to the correct answer.
        {
            cout << "That is correct!" << endl << endl;
            results << "That is correct!" << endl << endl;
            counter = 3; 
            keep_score(results, 0, true);
        }

        else
        {
            cout << "That is not correct.";
            results << "That is not correct.";
            counter++;

            if(counter!=3)
            {
                cout << "Try again!";
                results << "Try again!";
                keep_score(results, 1, false);
            }
            else
            {
                cout << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                results << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                keep_score(results, 1, true);
            }
        }
        
        validation=true; //Reset input validation

    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          Multiplication(ofstream &, int, int)
DESCRIPTION:       Generates random wrong answeres. Randomise the placement of the correct answer.
                   Displays the question.
                   Validate input. Checks if the anwere is correct or not. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void Multiplication(ofstream &results, int operand1, int operand2)
{
    int result = (operand1 * operand2); //Actual result

    int displayed_options[4];   //Incorrect anwers
    int correct_ans;        //Where the correct answere will be stored.
    char users_choice;
    bool validation = true;
    char option_letter = 'a';
    bool wrong = true;
    int counter = 0;

    for(int index=0;index<2;index++)    //Generate four of the possible incorrect answers
    {
        displayed_options[index] = result+generate_random(25);        //Set the first two incorrect answers
        displayed_options[(index+2)] = result-generate_random(25);    //Set the last two incorrect answers

        if (displayed_options[index]==result)
            displayed_options[index]+=2;
        if (displayed_options[(index+2)]==result)
            displayed_options[(index+2)]+=2;
    }
    
    correct_ans = generate_random(5); // (0 to 4) Determine the position of the correct answer.

    if(correct_ans!=4) //If it is 4, the correct answer will be Non of the above.
    {
        displayed_options[correct_ans]=result;  //Set the correct answer to one of the 4 first options.
    }

    
    cout << "Solve:" << endl;
    cout << "\t" << setw(8) << setfill(' ') << operand1 << endl;
    cout << "\t" <<"*" << setw(7) << setfill(' ') << operand2 << endl;
    cout << "\t" << "________" << endl << endl;
    
    results << "Solve:" << endl;
    results << "\t" << setw(8) << setfill(' ') << operand1 << endl;
    results << "\t" <<"*" << setw(7) << setfill(' ') << operand2 << endl;
    results << "\t" << "________" << endl << endl;

    for(int index=0;index<4;index++)    //Display all the options
    {
        cout << "(" << option_letter++ << ")\t" << displayed_options[index] << endl;
        results << "(" << option_letter << ")\t" << displayed_options[index] << endl;
    }
    
    cout << "(e)\tNone of the above" << endl << endl;
    results << "(e)\tNone of the above" << endl << endl;

    cout << "Input your choice: ";
    results << "Input your choice: ";
    

    while(counter!=3) //3 strikes
    {
        cin>>users_choice;
        users_choice = tolower(users_choice);
        results << " " << users_choice << endl;

        while(validation)   //Input validation
        {
            if ((users_choice>='a')&&(users_choice<='e'))
            validation=false;
            else
            {
                cin.clear();
                cin.ignore(10000,'\n');   
                cout << "That option is not available, please select one of the letters above." << endl;
                results << "That option is not available, please select one of the letters above."; 
                cin>>users_choice; //Again just to go out of the validation loop.
                results << " " << users_choice << endl;
            }
        }

        if((((int)users_choice)-97)==correct_ans)  //Type cast user_choise (a-e) to integers, and compare it to the correct answer.
        {
            cout << "That is correct!" << endl << endl;
            results << "That is correct!" << endl << endl;
            counter = 3; 
            keep_score(results, 0, true);
        }

        else
        {
            cout << "That is not correct.";
            results << "That is not correct.";
            counter++;

            if(counter!=3)
            {
                cout << "Try again!";
                results << "Try again!";
                keep_score(results, 1, false);
            }
            else
            {
                cout << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                results << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                keep_score(results, 1, true);
            }
        }
        
        validation=true; //Reset input validation

    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          Division(ofstream &, int, int)
DESCRIPTION:       Generates random wrong answeres. Randomise the placement of the correct answer.
                   Displays the question.
                   Validate input. Checks if the anwere is correct or not. 
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void Division(ofstream &results, int operand1, int operand2)
{
    int result = (operand1 * operand2); //We want to get a integer result. /Result will be the numerator and the operand 2 will be the answer. 

    int displayed_options[4];   //Incorrect anwers
    int correct_ans;        //Where the correct answere will be stored.
    char users_choice;
    bool validation = true;
    char option_letter = 'a';
    bool wrong = true;
    int counter = 0;

    for(int index=0;index<2;index++)    //Generate four of the possible incorrect answers
    {
        displayed_options[index] = operand2+generate_random(25);        //Set the first two incorrect answers
        displayed_options[(index+2)] = operand2-generate_random(25);    //Set the last two incorrect answers
  
        if (displayed_options[index]==operand2)     //No equal answers
            displayed_options[index]+=2;
        if (displayed_options[(index+2)]==operand2)
            displayed_options[(index+2)]+=2;
    }
    
    correct_ans = generate_random(5); // (0 to 4) Determine the position of the correct answer.

    if(correct_ans!=4) //If it is 4, the correct answer will be Non of the above.
    {
        displayed_options[correct_ans]=operand2;  //Set the correct answer to one of the 4 first options.
    }

    
    cout << "Solve:" << endl;
    cout << "\t" << result << " / " << operand1 << ":" << endl << endl;
    
    results << "Solve:" << endl;
    results << "\t" << result << " / " << operand1 << ":" << endl << endl;

    for(int index=0;index<4;index++)    //Display all the options
    {
        cout << "(" << option_letter++ << ")\t" << displayed_options[index] << endl;
        results << "(" << option_letter << ")\t" << displayed_options[index] << endl;
    }
    
    cout << "(e)\tNone of the above" << endl << endl;
    results << "(e)\tNone of the above" << endl << endl;

    cout << "Input your choice: ";
    results << "Input your choice: ";
    

    while(counter!=3) //3 strikes
    {
        cin>>users_choice;
        users_choice = tolower(users_choice);
        results << " " << users_choice << endl;

        while(validation)   //Input validation
        {
            if ((users_choice>='a')&&(users_choice<='e'))
            validation=false;
            else
            {
                cin.clear();
                cin.ignore(10000,'\n');   
                cout << "That option is not available, please select one of the letters above." << endl;
                results << "That option is not available, please select one of the letters above."; 
                cin>>users_choice; //Again just to go out of the validation loop.
                results << " " << users_choice << endl;
            }
        }

        if((((int)users_choice)-97)==correct_ans)  //Type cast user_choise (a-e) to integers, and compare it to the correct answer.
        {
            cout << "That is correct!" << endl << endl;
            results << "That is correct!" << endl << endl;
            counter = 3; 
            keep_score(results, 0, true);
        }

        else
        {
            cout << "That is not correct.";
            results << "That is not correct.";
            counter++;

            if(counter!=3)
            {
                cout << "Try again!";
                results << "Try again!";
                keep_score(results, 1, false);
            }
            else
            {
                cout << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                results << "Third strike! The correct option is " << (char)(correct_ans+97) << endl << endl;
                keep_score(results, 1, true);
            }
        }
        
        validation=true; //Reset input validation

    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          keep_score(int)
DESCRIPTION:       Receives the correct, incorrect answers and keep track of them so we can have the user's score.
                   Display the score each time it is called.
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
void keep_score(ofstream &results,int right_or_wrong, bool print)
{
    static int right_answers=0;     //Initialization, just happens once.
    static int wrong_answers=0;     //Initialization, just happens once.
    double total;

    if (right_or_wrong==0)      //0 means right
        right_answers++;
    if (right_or_wrong==1)      //1 means wrong
        wrong_answers++;
    
    total = right_answers + wrong_answers;

    if(print)
    {
        cout << "Your have answered " << right_answers << " question(s) correctly out of " << total << " tries." << endl;
        cout << setprecision(1) << fixed;
        cout << "Your actual score is " << (right_answers/total)*100 << "%" << endl;
        
        results << "Your have answered " << right_answers << " question(s) correctly out of " << total << " tries." << endl;
        cout << setprecision(1) << fixed;
        results << "Your actual score is " << (right_answers/total)*100 << "%" << endl;

        time_t now = time(0);   //Current date/time based on current system
        char* dt = ctime(&now); //Convert to string form
        cout << dt << endl;
        results << dt << endl;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          print_to_file()
DESCRIPTION:       Print the initial information to a txt file
RETURNS:           Nothing
NOTES:             I just commented out the incorrect way to do it. I tried a lot of diverse ways to solve this. 
----------------------------------------------------------------------------- */
void print_to_file(ofstream &results, string users_name, char* dt, int seed, int difficulty)
{
    const int s_length = users_name.length();
//  char under_scores[s_length];
//  char back_space = 8;        //Experiment

    for(int i=0; i < s_length; i++)
    {
//        under_scores[i] = users_name[i];

        if(users_name[i]==' ')
            users_name[i] = '_';
    }
    
//    string users_name_print = string(under_scores);         //Declaring another variable because I can't and I dont want to modify users_name

//  users_name_print += back_space;

    results.open(users_name + "_results.txt");        //Open the file. It will be passed by reference.

    results << "User's Name: " << users_name << endl;
    results << dt;
    results << "Seed: " << seed << endl;
    results << "Chosen difficulty level: " << difficulty << endl << endl;
}