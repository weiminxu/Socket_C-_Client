#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

void main()
{
	string ipAddress = "127.0.0.1";
	int port = 54000;

	//Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int WSResult = WSAStartup(ver, &data);
	if (WSResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << WSResult << endl;
		return;
	}

	//Create Socket
	//Fill in a hint structure
	//Connect to server
	//Do-while loop to send and receive data
	//Gracefully close down everything

}