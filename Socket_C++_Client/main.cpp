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
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) 
	{
		cerr << "can not create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str, &hint.sin_addr);

	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) 
	{
		cerr << "can not connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	//Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	do 
	{
		//prompt the user for some text
		cout << "> ";
		getline(cin, userInput);
		
		if (userInput.size() > 0)  //make sure the user has typed in something
		{
			//send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				//wait for respose
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					//echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
	
	} while (userInput.size() > 0);

   //Gracefully close down everything;
   closesocket(sock);
	WSACleanup();
}