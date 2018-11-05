#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

//receives from 257 & 997
//terminates after receiving 5000 msgs
int main()
{
	int msgCount = 0;
	int limit = 5000;
	string senderIdentifier; //sub string of the message that lets the reciever know which sender sent the message
	string realMessage; //The actual message that is received from the message queue
	bool receiver2Alive = true; // flag to check receiver

	// buffer with the message contents
	struct buf
	{
		long mtype; // required
		char message[50]; // mesg content
		
	};

	buf msg;	//initializes instance of buffer
	int size = sizeof(msg) - sizeof(long);

	// Grab queue from other program
	int qid = msgget(ftok(".", 'u'), 0);
	cout << "Receiver2 has found the Queue." << endl;
	
	while (receiver2Alive)
	{
		senderIdentifier = realMessage.substr(0, 3); //gets the number of the sender (257 or 997)
		realMessage = msg.message; //message from queue
		
		if (msgCount > limit)
		{	
			// Sending quit to 257
			receiver2Alive = false;
			msg.mtype = 120;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			

			// Sending Quit to 997
			strcpy(msg.message, "Receiver 2 has Quit.");
			msg.mtype = 2;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);

			// Sending quit to Queue Center
			msg.mtype = 326;
			strcpy(msg.message, "Receiver 2 Exited Successfully!!");
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			cout << "\nQuiting Program....."<<endl;
			isAlive= false;
			
		}
		else if (msenderIdentifier.compare("997") == 0)
		{
			msgCount++;
			cout << "senderIdentifier: " << senderIdentifier << "\t Message: " << realMessage << endl;
			strcpy(msg.message, "Receiver 2 has obtained your message, Sender977.");
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);

		}

		else if (senderIdentifier.compare("257") == 0)
		{
			msgCount++;
			cout << "senderIdentifier: " << senderIdentifier << "\t Message: " << realMessage << endl;

		}
		else
		{
			//cout << "senderIdentifier is not 257 or 997" << endl;
		}
	}
} //end main
