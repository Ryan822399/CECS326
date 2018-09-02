#include <array>
#include <iostream>
#include<limits>

using namespace std;

//Struct required by the instructions
struct data
{
	char *charPointer[20];
	int intArray[20];

}obj;

int fillArray(int i)
{
	cout << (obj.intArray[i] -1) << endl;
	for (int j = 0; j < (obj.intArray[i] -1); j++)
	{
		//cout << j << endl;
		*(obj.charPointer[j]) = 'h';
	}
	return 0;
}

void initCharArray()
{
	for (int i = 0; i < 19; i++)
	{
		obj.charPointer[i] = new char[obj.intArray[i]]();
		fillArray(i);
	}
}

//Fills the array using the function specified by the instructions
//n will always start at 1
int initArray(int n)
{
	obj.intArray[0] = 2700;
	if (n < 20)
	{
		//Setting the current index of the array to double the previous index
		obj.intArray[n] = (obj.intArray[n - 1] * 2);
		initArray(n + 1);
	}

	initCharArray();
	return 0;
}

//Helper function to print out either the main menu or the sub menu
int printMenu(int a)
{
	//Main menu
	if (a == 1)
	{
		cout << "(1) Access a pointer" << endl;
		cout << "(2) List deallocated memory (index)" << endl;
		cout << "(3) Deallocate all memory" << endl;
		cout << "(4) Exit program" << endl;
	}

	//Sub Menu
	if (a == 2)
	{
		cout << "(1) Print the first 10 char's in the chosen array" << endl;
		cout << "(2) Delete all the char's associated with this pointer" << endl;
		cout << "(3) Return to main menu" << endl;
	}

	return 0;
}

//Prompts the user for the index of the array to manipulate then displays a sub menu of options for that index
int accessPointer()
{
	//collecting user input for the index
	int index = 0;
	cout << "What index of the array would you like to access? " << endl;
	cin >> index;

	//Validating the input to prevent crashing
	while (index < 0 || index > 19 || cin.fail())
	{
		cout << "That is not a valid input, please enter a number again: " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> index;
	}

	//Collecting user input for the sub menu
	int subMenuInput = 0;
	printMenu(2);
	cin >> subMenuInput;

	//validating the input to prevent crashing
	while (subMenuInput < 1 || subMenuInput > 3 || cin.fail())
	{
		cout << "That is not a valid input, please enter a number again: " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> subMenuInput;
	}

	//These are the three options when manipulating the data at the index specified
	switch (subMenuInput)
	{
	case 1: cout << "Print the first 10 char's in the chosen array" << endl; break;
	case 2: cout << "Delete all the char's associated with this pointer" << endl; break;
	case 3: cout << " Return to main menu" << endl; break;
	}

	return 0;
}

//Lists out all of the memory that has been deallocated
int listDeallocatedMemory()
{
	cout << "Running function 2" << endl;
	return 0;
}

//physically deallocates memory from the system
int deallocateMemory()
{
	cout << "Running function 3" << endl;
	return 0;
}

//deallocates all memory and exits the program
int exitProgram()
{
	//exit function here
	exit(0);
}

int main()
{
	//Initializing the integer array
	initArray(1);

	//debugging
	for (int i = 0; i < 19; i++)
	{
		cout << obj.intArray[i] << endl;
	}

	//the main is in a loop so that the main menu can be accessed multiple times
	int userInput = 0;
	while (true)
	{
		//printing the main menu and collecting input
		printMenu(1);
		cin >> userInput;

		//validating user input
		while (userInput < 1 || userInput > 4 || cin.fail())
		{
			cout << "That is not a valid input, please enter a number again: " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userInput;
		}

		switch (userInput)
		{
		case 1: accessPointer(); break;
		case 2: listDeallocatedMemory(); break;
		case 3: deallocateMemory(); break;
		case 4: exitProgram();
		}
	}

	return 0;
}
