#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main()
{
    	//forever loop condition
	bool forever = true;

	string queMessage; //The full message to receive from the queue
    	string senderIdentifier; //sub string of the message that lets the reciever know which sender sent the message
    	string realMessage; //The actual message that is received from the message queue

	///declare my message buffer 
	struct buf
	{
		long mtype; // required
		char message[50]; // mesg content
		//bool receiverRunning; // flag to check receiver
	};
	buf msg;	//initializes instance of buffer
	int size = sizeof(msg)-sizeof(long);

	//keeping track of the amount of received messages to terminate at 5000
	int messageCount=0;
	
	//msg.receiverRunning = true;

	//Grabbing the existing queue from the other program
	int qid = msgget(ftok(".",'u'), 0);
	cout << "Queue found, reciever2 is waiting..\n" <<endl;

    //main receiver loop
    while(forever == true)
    {
	//receiving the outgoing 118 messages
        msgrcv(qid, (struct msgbuf *)&msg, size, 118, 0);

	//storing the full message 
        queMessage = msg.message;

	//storing the sender identifier such as 997 or 257
	senderIdentifier = queMessage.substr(0,3);

	//storing the real message from the que
        realMessage = queMessage.substr(5);

	//quits on the max messages recieved = 5000
	if(messageCount==5000)
	{
		//sending quit to 257
		strcpy(msg.message, "Receiver 2 has quit");
		//setting mtype to 120 b/c 257 expects mtype 120
		msg.mtype = 120;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);

		//sending Quit to 997
            	strcpy(msg.message, "Receiver 2 has quit");
		//setting mtype to 2 b/c 997 expects mtype 2
            	msg.mtype = 2;
           	msgsnd(qid, (struct msgbuf *)&msg, size, 0);

		//sending quit to queue program
		strcpy(msg.message, "Receiver 2 has quit");
		//setting mtype to 326 b/c the queue program expects that type of message
		msg.mtype = 326;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            	cout << "\nReceiver2 has received 500 messages and is quitting.."<<endl;

		//ending the receiving loop once all other programs have been notified
            	forever = false;
        }
	//Although this reciever accept messages from either 997 or 257 it must send back ack to 997
	else if(senderIdentifier.compare("997") == 0)
	{
		//incrmenting the amount of messages received until 5000
		messageCount++;
		cout << senderIdentifier <<"'s Message Received: "<< realMessage <<endl;
          	strcpy(msg.message, "Message has been received from Receiver 2");
		//mtype required by sender997
          	msg.mtype = 2;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		
		//this block of code must be here so that the sender does not get hung up on waiting for a message since sender 257 only cares about a quit message but must check everytime one is sent
		//mtype required by 257
		msg.mtype = 120;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	}
        else
        {
		//incrementing the amount of messages received until 5000
		messageCount++;
          	cout << senderIdentifier << "'s Message Received: "<<realMessage<<endl;
		//mtype required by 257
		msg.mtype = 120;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
        }
    }
    return 0;
}
