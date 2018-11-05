#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

int rand();

int main()
{
	//ensuring the number generated is random each time
    	srand (time(NULL));

	//variable used through the program
	string outGoingMessage;
	int randValue;

    	//grabbing the existing queue from the other program
    	int qid = msgget(ftok(".",'u'), 0);

	bool receiverRunning = true; //flag to check receiver status

    	//declare my message buffer and its size
	struct buf
	{
		long mtype; // required
		char message[50]; // mesg content
		
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	cout << "Sender 257 has started"<<endl;
	
	//Sender 251 will only be sending out as long as its reciever is running. 
	while(receiverRunning == true)
	{
		randValue = rand();
		if(randValue % 257 == 0)
		{
			cout << "Sended : "<< randValue <<endl;
			string m = "257: " + to_string(randValue);
			strcpy(msg.message, m.c_str());
			msg.mtype = 118;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			msgrcv(qid, (struct msgbuf *)&msg, size, 120, 0);
		}
	}
	cout << "\nReceiver 2 is no longer running, Sender257 quitting!"<<endl;
    return 0;
}
