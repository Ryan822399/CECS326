// parent process and child processes

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <string> 
using namespace std;

int main() {
	
	int stringsReplaced;
	long childPID;
	bool forever = true;
	string inputTarget;
	string inputReplacement;
	string textDocument = "In recent years, JavaScript has become the de-facto language of choice when building websites, and one of the most popular ones to build web applications. There are many reasons behind this, including it’s treatment of objects and the ability to build applications quickly. There are some people who feel that it’s unjustly popular, due to a lot of JavaScript’s perceived shortcomings when compared with more traditional programming languages. JavaScript has some strange quirks and behavior that bothers some engineers. One thing everyone can agree on is that JavaScript is one of the most used languages today, and for all intents and purposes it seems to be staying that way. Knowing JavaScript is essential for any web developer. To remedy JavaScript’s shortcomings, developers have created a vast amount of libraries, each trying to solve their own problem, or plenty trying to solve the same problem in marginally different ways. Being familiar these libraries has become essential, even if it is merely to be aware that you can use them to ease your development process. Some of the most widely used libraries are as follows: Lodash, Ramda, and TypeScript. The maintainers of JavaScript language are of course aware of these needs and are adding these sought after features into the core JavaScript standard as time passes. There is one distinction that needs to be addressed, however, the differences between ECMAScript and JavaScript.";
	
	while (forever)
	{
		sleep(1);
		cout << "Enter a target string that will be replaced within the text document or :wq to exit the program" << endl;
		cin >> inputTarget;
		if(inputTarget == ":wq")
		{
			exit(0);
		}

cout << "Enter a replacement string that will replaced the target string in the text document or :wq to exit the program" << endl;
		cin >> inputReplacement;
		if(inputReplacement != ":wq")
		{
			childPID = fork();	
			if (childPID == 0)
			{
				int stringPosition = 0;
				int stringsReplaced = 0;
				bool firstRun = true;
				
				while ((stringPosition = textDocument.find(inputTarget, stringPosition)) != std::string::npos || firstRun == true)
				{
					firstRun = false;
					//creating bug
					if (stringPosition == -1)
					{
						cout << "." << endl;
						sleep(.1);
						firstRun = true;
					}
					else
					{
						textDocument.replace(stringPosition, inputTarget.length(), inputReplacement);
						stringPosition += inputReplacement.length();
						stringsReplaced++;
					}
				}
				cout << "The amount of strings replaced by the process was: " << (stringsReplaced) << endl;
				cout << "The new document looks like: /n" << textDocument << endl; 
				exit(0);
			}
			else if (childPID < 0)
			{
				cout << "Error creating child process, returning to initial prompt" << endl;	
			}

		}
		else if(inputReplacement == ":wq")
		{
			exit(0);
		}
	}

	/*

	long childPID;
	int PCvar = 10;
	cout << "1\n2\n3\n";

	childPID = fork();
	if(childPID > 0) {
		int Pvar = 20;
		PCvar = 30;
		cout << "Parent process: pid " << getpid()
			<< ", ppid " << getppid()
			<< ", child " << childPID << endl;
	} else if (childPID == 0) {
		int Cvar = 400;
		PCvar = 500;
		cout << "Child process: pid " << getpid()
			<< ", ppid " << getppid()
			<< ", child " << childPID << endl;
	} else
		cout << "Spawn error - no child process" << endl;

	cout << "4\n5\n6\n";
	exit(0);
	*/
}		
