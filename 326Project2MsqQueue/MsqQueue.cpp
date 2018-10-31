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
    //Creating the queue with the ftok() function similar to lab msgQ_B
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
    	cout << "The queue has been created\n" <<endl;

    //string messageFromQueue;
    //string identifier;
    //string realMessage;
   
    //Declaring the message buffer just as done in the lab
	struct buf
	{
		long mtype; // required
		char message[50]; // mesg content
	};
	buf msg;	//initializes instance of buffer
	int size = sizeof(msg)-sizeof(long);

    //Using the 2 recievers to know when to exit the message queue
    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);
    cout << msg.message << endl;

    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);
    cout << msg.message << "\n"<< endl;

    cout << "All Receivers Exited, Deleting Queue now...." << endl;

    // now safe to delete message queue
    msgctl (qid, IPC_RMID, NULL);


    return 0;
}
