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

    //Grabbing the existing queue from the other program
	int qid = msgget(ftok(".",'u'), 0);
	cout << "Queue found, reciever1 is waiting..\n" <<endl;

    //declare my message buffer 
	struct buf 
	{
		long mtype; // required
		char message[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    //main receiver loop
    while(forever == true)
    {
	//receiving the message with m.type 117
        msgrcv(qid, (struct msgbuf *)&msg, size, 117, 0);

	//storing the full message
        queMessage = msg.message;

	//storing the sender identifier
        senderIdentifier = queMessage.substr(0,3);

	//storing the real message from the que
        realMessage = queMessage.substr(5);

	//in this scenario the quit message has been received thus the receiver needs to send back a message to the que center with a specific m.type letting the senders know it is dead
        if(realMessage.compare("quit") == 0)
        {
    	    //sending the quit message out for the senders
            strcpy(msg.message, "Receiver 1 has quit");
            msg.mtype = 1;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            //sending the quit message out to the message queue
            strcpy(msg.message, "Receiver 1 Exited Successfully!");
            msg.mtype = 326;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

	    //letting the user know the program is exiting
            cout << "\nQuiting the program"<<endl;
            forever = false;
        }
	
	//if the reciever does not get a quit message, we still need to check to see if the message from 997 where we must send back acknowledgment to it
        else
        {
            if (senderIdentifier.compare("997") == 0)
            {
                cout << senderIdentifier <<"'s Message Received: "<< realMessage <<endl;
                strcpy(msg.message, "Message has been received from Receiver 1");
                msg.mtype = 1;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            }
            else
            {
                cout << senderIdentifier <<"'s Message Received: "<< realMessage <<endl;
            }
        }
    }
    return 0;
}
