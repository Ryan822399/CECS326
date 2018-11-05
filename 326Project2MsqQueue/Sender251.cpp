#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "Get_Info.h"

using namespace std;

int rand();
void get_info(int, struct msgbuf *, int, long);

int main()
{	
    	//ensuring the number generated is random each time
    	srand (time(NULL));

	//boolean value to control the forever loop
	bool forever = true;

	//variable used through the program
	string outGoingMessage;

    	// declaring the message buffer
	struct buf 
	{
		long mtype; // required
		char message[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    	// Grabbing the existing queue from the other program
    	int qid = msgget(ftok(".",'u'), 0);
	
	//using the patch code to terminate Receiver 1 after kill command
	strcpy(msg.message, "251: quit");
	msg.mtype = 117;
	get_info(qid, (struct msgbuf *)&msg, size, 117);

	cout << "Sender 251 has started"<<endl;
	while(forever  == true)
	{
		//creating the random number
		int randNumber = rand();
		//preventing the message from being 251 otherwise the identifier of the recievers will get confused
		if (randNumber % 251 == 0)
		{
			//formatting to make the output look nice
			cout.width(15);
			cout << left << randNumber << " : Sended"<<endl;
			outGoingMessage = "251: " + to_string(randNumber);
			strcpy(msg.message, outGoingMessage.c_str());
			
			//Specifying the mtype of receiver 1
			msg.mtype = 117;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);	
		} 
		else
		{
			cout.width(15); 
			cout<< left << randNumber << " : Trash"<<endl;
		}
	} 
    return 0;
}
