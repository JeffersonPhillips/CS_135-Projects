/* -----------------------------------------------------------------------------
FILE:              Calculator.cpp
DESCRIPTION:       Calculator practice program suitable for a seventh grade student.
COMPILER:          MinGw
NOTES:             Project #1

MODIFICATION HISTORY:

Author                          Date               Version              Comments
---------------                 ----------         --------------       --------------
Jefferson Phillips Retana       2019-03-02         1.00                 The first version of the program was built. The Int function and the main_menu were coded
Jefferson Phillips Retana       2019-03-02         1.01                 Correction in the switch. A flag was added.
Jefferson Phillips Retana       2019-03-02         2.00                 The addition option was programmed. For this, I needed to code the Addition, and the Get_Numbers functions.
Jefferson Phillips Retana       2019-03-02         2.01                 Corrections in the loos were applied. The addition functions works properly now.
Jefferson Phillips Retana       2019-03-02         2.02                 The Subtraction, Multiplication, and Division functions were added. 
Jefferson Phillips Retana       2019-03-08         2.03                 Corrections to simplify the program (according to the teacher's comments) where implemented 
Jefferson Phillips Retana       2019-03-08         2.04                 Modification to Get_Numbers so it validates the input /Setprecision
Jefferson Phillips Retana       2019-03-08         2.05                 The divison errors have been corrected
Jefferson Phillips Retana       2019-03-09         3.00                 The powers and roots menu was included
Jefferson Phillips Retana       2019-03-09         3.01                 All the Powers and Roots functions have been added.
Jefferson Phillips Retana       2019-03-09         3.02                 Setprecision's modified (Powers and Roots).
Jefferson Phillips Retana       2019-03-11         3.03                 Last couple of modifications before the submission. 
Jefferson Phillips Retana       2019-03-11         3.04                 Take any root was difficult to manage with negative bases. It works now.
----------------------------------------------------------------------------- */

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <ios>
using namespace std;

const string PROGRAMMER_NAME = "Jefferson Phillips Retana";

//Prototypes:
char main_menu();                   //Displays the main menu. Loops when incorrect input.
void Get_Numbers();                 //Gets number and validate input from the user
void Addition();                    //Adds
void Subtraction();                //Substracts
void Multiplication();              //Multiplyies
void Division();                    //Divides
int Powers_and_Roots();             //Power and Roots sub-main 
char main_menu_Powers_and_Roots();  //Powers_and_Roots Sub-menu
void Square_a_number();             //(X^2)
void Cube_a_number();               //(X^3)
void Raise_to_any_power();          //(X^Y)
void Square_root_a_number();        //(X^1/2)
void Cube_root_a_number();          //(X^1/3)
void Take_any_root();               //(X^1/Y)

//Global Variables:
long x = 0,y = 0;                   //Get_Numbers() global variables
double xf = 0.000,yf=0.000;         //Get_Numbers() global variables
char int_or_float;                  //Get_Numbers() Decides the path of the othe operations.
bool keep_looping = true;           //Main_menu and P&R maain menu. Get out from the program.
double base;                        //P&R
double exponent;                    //P&R
//---------------------------------//


/* -----------------------------------------------------------------------------
FUNCTION:          int main()
DESCRIPTION:       Main function of the program.
RETURNS:           It returns an integer value.
NOTES:              
----------------------------------------------------------------------------- */
int main()
{
    char choice;
    ios cout_state(nullptr);
    cout_state.copyfmt(cout);       //Storing the actual setprecision

    cout << "CALCULATOR PRACTICE PROGRAM" << endl;    
    cout << "Hello, and welcome to the Calculator Practice Program." << endl;
    cout << "This program allows you to practice your math skills." << endl;
    cout << "Choose what you want to practice in the menu shown below." << endl << endl;

        while(keep_looping)
        {  
            choice = main_menu();      
            switch(choice)
            {
                case 'a': 
                        cout.copyfmt(cout_state);
                        Addition();
                    break;
                case 'b': 
                        cout.copyfmt(cout_state);
                        Subtraction();
                    break;
                case 'c': 
                        cout.copyfmt(cout_state);
                        Multiplication();
                    break;
                case 'd': 
                        cout.copyfmt(cout_state);
                        Division();
                    break;
                case 'e': 
                        cout.copyfmt(cout_state);   //Setting deafault precision, in case it was modified before (floating points calculations).
                        Powers_and_Roots();
                    break;
                case 'q': keep_looping=false;
                    break;
            }

        }
    
	cout << "Goodbye Mathematician!" << endl; 
    cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;
    
    system("pause");
    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          char main_menu()
DESCRIPTION:       Displays the Main Menu and gets the value inputed by the user.
RETURNS:           It returns a character value
NOTES:             It alwas needs to display the main menu again, unless q is inputted.
----------------------------------------------------------------------------- */
char main_menu()
{
    char choice;
    bool loop=true;

    cout << "-----------------------------------------------" << endl;
    cout << "                  MAIN MENU" << endl;
    cout << "-----------------------------------------------" << endl << endl;

    cout << "a. Addition            (X+Y)" << endl;
    cout << "b. Subtraction        (X-Y)" << endl;
    cout << "c. Multiplication      (X*Y)" << endl;
    cout << "d. Division            (X/Y)" << endl;
    cout << "e. Powers & Roots" << endl;
    cout << "q. Quit the program" << endl << endl;

    cout << "-----------------------------------------------" << endl;
    cout << "Enter your choice [ a - e, q ]:" << endl;
    cout << "-----------------------------------------------" << endl;

    while (loop) 
    {
        cin >> choice;
        choice = tolower(choice);

        if ((choice >='a' && choice <='e')||choice=='q')
        {
            cout << endl << endl;
            loop=false;
        }
        else
        {
            cout << endl;
            cout << "That's is not a correct input." << endl;
            cout << "Please select one of the available options." << endl << endl;
        }
    }
    return choice;
}

/* -----------------------------------------------------------------------------
FUNCTION:          void Get_Numbers()
DESCRIPTION:       Get and store the two numbers inputted by the user.
RETURNS:           Nothing (Void function)
NOTES:             It works for almost all the other functions. It asks the user the data type that we are going to use.
----------------------------------------------------------------------------- */
void Get_Numbers()
{
    char whole_decimal;                 //Decides which variables (x&&y || xf&&yf) will be used 
    bool validation = true;             //Flag
    int decimal_test;
    double x_trunc,y_trunc;           //After the presentation in class, I needed to work on the truncation. This is easier than change the enitre function. 

    ios cout_state(nullptr);
    cout_state.copyfmt(cout);       //Storing the actual setprecision (which was set te the native one before).

    cout << "Are we using Integers (whole numbers) or Floating Points (decimals)?" << endl << endl;
    cout << "a. Integers" << endl;
    cout << "b. Floating Points" << endl;
    cout << "m. Main Menu" << endl;

    while(validation)                //I dont want the prompt upstaris to be displayed all the time.
    {
        cin >> whole_decimal;
        whole_decimal = tolower(whole_decimal);
        
        if(whole_decimal=='a')
        {
            cout << "Input two integers separated by a space." << endl;
            do                                      //This will validate that the input are just numbers.
            {

                if ((cin >> x_trunc) && (cin >> y_trunc))   //Accepting every number.
                {
                    x = static_cast<int>(x_trunc);          
                    y = static_cast<int>(y_trunc);          //Using just integers.

                    validation = false;             // This will end the first while loop, and the nested do-while loop
                    int_or_float = 'i';             //This is the global variable that will decide what kind of operation will be used next (x+y, for instance)
                }
                else
                {
                    cout << "Please enter numbers only." << endl;
                    cin.clear();
                    cin.ignore(10000,'\n');
                }
            }
            while(validation);
        }

        else if(whole_decimal=='b')
        {
            cout << "Input two numbers with decimal places separated by a space" << endl;

            do                                      //This will validate that the input are just numbers.
            {
                if ((cin >> xf) && (cin >> yf))
                {
                    validation = false;                 // This will end the fist while loop, and the nested do-while loop
                    int_or_float = 'f';                 //This is the global variable that will decide what kind of operation will be used next (xf+yf, for instance)
                    
                    if((xf != (decimal_test = static_cast<int>(xf))) || (yf != (decimal_test = static_cast<int>(yf)))) //If there are no decimals, display just one decimal point, if there are more than one decimals, display all.
                    {
                        cout.copyfmt(cout_state);       //Setting deafault precision, in case it was modified before (floating points calculations).
                    }
                    else 
                    {
                        cout << setprecision(1) << fixed;   //All the results with one decimal place (which will be cero)
                    }
                }
                else
                {
                    cout << "Please enter numbers only." << endl;
                    cin.clear();
                    cin.ignore(10000,'\n');
                }
            }
            while(validation);
        }
         
        else if(whole_decimal=='m')
        {
            validation = false;          // This will just break the loop and continue in the other functions
            int_or_float = 'm';
        }

        else
        {
            cout << "That is not a valid input, please select 'a','b', or 'm'" << endl;
        }
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          void Addition()
DESCRIPTION:       Adds two numbers inputted by the user
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Addition()
{
    char again;
    
    cout << "Welcome to addition, X and Y will be added." << endl;
    
    cout << endl;
    Get_Numbers(); 
    cout << endl;
    

    if (int_or_float=='i')          //Operation for integers
    {
        cout << "X + Y = " << x << " + " << y << " = " << x+y << endl << endl;
    }
    
    else if (int_or_float=='f')     //Operation for floating
    {
       cout << "X + Y = " << xf << " + " << yf << " = " << xf+yf << endl << endl;
    }
    
    else if (int_or_float=='m');       //Intentional! if it is M, do nothing and continue
    
    else
    {
        cout << "Something went wrong, please contact the administrator." << endl << endl; // It shouldn't, due to the int_or_float flag upstaris, but just in case.
    }
    
}

/* -----------------------------------------------------------------------------
FUNCTION:          void Subtraction()
DESCRIPTION:       Substracts two numbers inputted by the user
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Subtraction()
{
    char again;
    
    cout << "Welcome to Subtraction, X and Y will be substracted." << endl;
    
    cout << endl;
    Get_Numbers(); 
    cout << endl;
    

    if (int_or_float=='i')          //Operation for integers
    {
        cout << "X - Y = " << x << " - " << y << " = " << x-y << endl << endl;
    }
    
    else if (int_or_float=='f')     //Operation for floating
    {
       cout << "X - Y = " << xf << " - " << yf << " = " << xf-yf << endl << endl;
    }
    
    else if (int_or_float=='m');       //Intentional! if it is M, do nothing and continue
    
    else
    {
        cout << "Something went wrong, please contact the administrator." << endl << endl; // It shouldn't due to the int_or_float flag upstaris, but just in case.
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          void Multiplication()
DESCRIPTION:       Multiplies two numbers inputted by the user
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Multiplication()
{
    char again;
    
    cout << "Welcome to multiplication, X and Y will be multiply." << endl;
    
    cout << endl;
    Get_Numbers(); 
    cout << endl;
    

    if (int_or_float=='i')          //Operation for integers
    {
        cout << "X * Y = " << x << " * " << y << " = " << x*y << endl << endl;
    }
    
    else if (int_or_float=='f')     //Operation for floating
    {
       cout << "X * Y = " << xf << " * " << yf << " = " << xf*yf << endl << endl;
    }
    
    else if (int_or_float=='m');       //Intentional! if it is M, do nothing and continue
    
    else
    {
        cout << "Something went wrong, please contact the administrator." << endl << endl; // It shouldn't due to the int_or_float flag upstaris, but just in case.
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          void Division()
DESCRIPTION:       Divides two numbers inputted by the user
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Division()
{
    char again;
    
    cout << "Welcome to division, X will be divided into Y." << endl;
    
    cout << endl;
    Get_Numbers(); 
    cout << endl;
    
    if (int_or_float=='i')          //Operation for integers
    {
        if (y!=0)
        {
            cout << "X / Y = " << x << " / " << y << " = " << x/y << endl;
            cout << "Remainder value = " << x%y << endl << endl;                 //As we are working with integers, lets add the modulus.
        }
        else
        {
            cout << "There is no number which, when multiplied by 0, gives " << x << "; hence, division by zero is undefined." << endl << endl;
        }
        
    }
    
    else if (int_or_float=='f')     //Operation for floating
    {
     if (yf!=0)
        {
            cout << "X / Y = " << xf << " / " << yf << " = " << xf/yf << endl;
        }
        else
        {
            cout << "There is no number which, when multiplied by 0, gives " << xf << "; hence, division by zero is undefined." << endl << endl;
        }
    }
    
    else if (int_or_float=='m');       //Intentional! if it is M, do nothing and continue
    
    else
    {
        cout << "Something went wrong, please contact the administrator." << endl << endl; // It shouldn't due to the int_or_float flag upstaris, but just in case.
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          Powers_and_Roots()
DESCRIPTION:       Controls the powers and Roots sub-menu
RETURNS:           Integer value.
NOTES:             It is like a sub-main. 
----------------------------------------------------------------------------- */
int Powers_and_Roots()
{
    bool PR_main_menu = true;
    char pr_choice;

    cout << "Hello, and welcome to the Powers & Roots Menu." << endl;
    cout << "This menu allows you to take powers and roots of a number." << endl;

    while(PR_main_menu)
    {
        pr_choice = main_menu_Powers_and_Roots();
        switch(pr_choice)
        {
            case 'a': Square_a_number();
                break;
            case 'b': Cube_a_number();
                break;
            case 'c': Raise_to_any_power();
                break;
            case 'd': Square_root_a_number();
                break;
            case 'e': Cube_root_a_number();
                break;
            case 'f': Take_any_root();
                break;
            case 'm': PR_main_menu = false;
                break;
            case 'q':
                    PR_main_menu = false;
                    keep_looping=false;         //Global variable, It will take us out of the loop in main
                break;
        }
    }

    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main_menu_Powers_and_Roots()
DESCRIPTION:       Displays the sub-menu and validate the input
RETURNS:           Character value.
NOTES:              
----------------------------------------------------------------------------- */
char main_menu_Powers_and_Roots()
{
    char pr_choice;
    bool loop = true;

    cout << "---------------------------------------------------" << endl;
    cout << "               POWERS & ROOTS MENU"<< endl;
    cout << "---------------------------------------------------" << endl << endl;
    cout << "a. Square a number          (X^2)" << endl;
    cout << "b. Cube a number            (X^3)" << endl;
    cout << "c. Raise to any power       (X^Y)" << endl;
    cout << "d. Square root a number     (X^1/2)" << endl;
    cout << "e. Cube root a number       (X^1/3)" << endl;
    cout << "f. Take any root            (X^1/Y)" << endl;
    cout << "m. Return to Main Menu" << endl;
    cout << "q. Quit the program" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice [ a - f, m, q ]:" << endl;
    cout << "---------------------------------------------------" << endl;

    do          //Input Validation
    {
        cin >> pr_choice;
        pr_choice = tolower(pr_choice);

        if((pr_choice>='a'&&pr_choice<='f')||pr_choice=='m'||pr_choice=='q')
        {
            cout << endl << endl;
            loop=false;
        }        
        else
        {
            cout << "That is not valid input, please select from the obtoins above." << endl << endl;
        }
    }
    while(loop);

    return pr_choice;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Square_a_number()
DESCRIPTION:       (X^2)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Square_a_number()
{
    bool square = true;
    cout << "Hello there! Please input the number which will be squared." << endl;
    do
    {
        if (cin>>base)
        {
            cout << endl << endl;   
            cout << "X^2  =  " << base << "^2  =  " << pow(base,2) << endl << endl;
            square = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(square);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Cube_a_number()
DESCRIPTION:       (X^3)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Cube_a_number()
{
    bool cube = true;
    cout << "Hello there! Please input the number which will be cubed." << endl;
    do
    {
        if (cin>>base)
        {
            cout << endl << endl;
            cout << "X^3  =  " << base << "^3  =  " << pow(base,3) << endl << endl;
            cube = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(cube);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Raise_to_any_number()
DESCRIPTION:       (X^Y)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Raise_to_any_power()
{
    bool any = true;
    cout << "Hello there! Please two numbers (base and exponent) separated by a space." << endl;
    do
    {
        if ((cin>>base)&&(cin>>exponent))
        {
            cout << endl << endl;
            cout << "X^Y  =  " << base << "^" << exponent << "  =  " << pow(base,exponent) << endl << endl;
            any = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(any);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Square_root_a_number()
DESCRIPTION:       (X^1/2)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Square_root_a_number()
{
    bool square_root = true;
    cout << "Hello there! Please input a number. It's square root will be calculated." << endl;
    do
    {
        if (cin>>base)
        {
            cout << endl << endl;
            cout << "X^1/2  =  " << base << "^1/2  =  " << sqrt(base) << endl;

            if(base<0) //Displays a message if the requested root calculation is invalid.
            cout<< "There can just be positive numbers inside a square-root.";
            
            cout << endl << endl;
            square_root = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(square_root);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Cube_root_a_number()
DESCRIPTION:       (X^1/3)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Cube_root_a_number()
{
    bool cube_root = true;
    cout << "Hello there! Please input a number. It's cube root will be calculated." << endl;
    do
    {
        if (cin>>base)
        {
            cout << endl << endl;
            cout << "X^1/3  =  " << base << "^1/3  =  " << cbrt(base) << endl << endl;
            cube_root = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(cube_root);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Take_any_root()
DESCRIPTION:       (X^1/Y)
RETURNS:           Nothing (Void function)
NOTES:             This is a self-contain function, it doesn't call other functions.
----------------------------------------------------------------------------- */
void Take_any_root()
{
    bool anyr = true;
    int valid_root;

    cout << "Hello there! Please input two numbers. The first one will be rooted to the second." << endl;
    do
    {
        valid_root = fmod(exponent,2);

        if ((cin>>base)&&(cin>>exponent))
        {
            
            if (base<0&&valid_root!=0) //Is the exponent is odd, make it possitive, calculate, and display the result in negative.
            {
                base*=-1;
                cout << endl << endl;
                cout << "X^1/Y  =  -" << base << "^1/" << exponent << "  =  " << (pow(base,(1/exponent)))*-1 << endl;
            }
            else
            {
                cout << endl << endl;
                cout << "X^1/Y  =  " << base << "^1/" << exponent << "  =  " << pow(base,(1/exponent)) << endl;

                if(base<0 && valid_root==0) //Displays a message if the requested root calculation is invalid.
                cout<< "There can just be positive numbers inside an even-root.";
            }

            cout << endl << endl;
            anyr = false;
        }
        else
        {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    while(anyr);
}