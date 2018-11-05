#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;
int rand();

int main()
{
	//Ensuring the number generated is random each time
    	srand (time(NULL));

	//boolean value to control the forever loop
	bool forever = true;

	//variables used through the program
	string messageContent;
	//int number = 0;
	int randomGeneratedNumber = 0;

	//variables to tell me when the recievers are still active
	bool receiver1Alive = true;
	bool receiver2Alive = true;

    	//grabbing the existing queue
    	int qid = msgget(ftok(".",'u'), 0);
	
    	//declaring the message buffer
	struct buf 
	{
		long mtype; // required
		char message[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	
	//Letting the user know the sender has begun
	cout << "Sender 977 has started"<<endl;

	do{			
		//generating a random number ensuring that it is not 0
		do{
			randomGeneratedNumber = rand() % INT_MAX;
			//number = randomNum;
		   }while (randomGeneratedNumber % 997 != 0);
		
		//setting the message content to the random number generated as weel as including 
		messageContent = "997: " + to_string(randomGeneratedNumber);
		
		//sending an event to all recievers
		if (receiver1Alive == true)
		{
			cout << "Sending to Receiver 1: " << messageContent;
			strcpy(msg.message, messageContent.c_str());
			
			//setting message mtype to 111
			msg.mtype = 113;

			//printing out message info
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0) << endl;

			//cout << endl;
		}
		if (receiver2Alive == true)
		{
			cout << "Sending to Receiver 2: " << messageContent;
			strcpy(msg.message, messageContent.c_str());

			//setting message mtype to 111
			msg.mtype = 111;	

			//printing out message info
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0) << endl;

			//cout << endl;
		}

		//in the senario that the revievers are alive, sender 977 must wait until it recieves messages from both revievers to continue, both these if's handles this
		if (receiver1Alive == true)
		{
			cout << "\nWaiting For Receiver 1 to receive the message" << endl;
			
			//receiving the message from receiver 1
			msgrcv(qid, (struct msgbuf *)&msg, size, 1, 0);
			messageContent = msg.message;
			
			//checking the message to see if the receiver was alive or not
			if (messageContent.compare("Receiver 1 has quit") == 0)
			{
				receiver1Alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "Message Recieved." << endl << endl;
			}
		}
		if (receiver2Alive == true)
		{
			cout << "\nWaiting For Receiver 2 to receive the message" << endl;
			
			//receiving the message from receiver 2
			msgrcv(qid, (struct msgbuf *)&msg, size, 2, 0);
			messageContent = msg.message;

			//checking the message to see if the receiver was alive or not
			if (messageContent.compare("Receiver 2 has quit") == 0)
			{
				receiver2Alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "Message Recieved." << endl << endl;
			}
		}
	//the do while loop will terminate if the random number generated is less than 100 as specified by the instructions
	} while(number > 100);

    //default return code for main
    return 0;
}
