#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include "NanStream.h"
#include "loc.h"
#include "stub.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace nans;

int main() {
	MyGumballService impl;
	GumballServiceStub stub(&impl, 8888);
	stub.run();
	return 0;
}

/*
int main() {
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddr, clientAddr;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	int reuse = 1;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);

	std::cout << "Server is listening on port 8888...\n";

	GumballMonitor* remote;
	GumballStatus s;


	int addrSize = sizeof(clientAddr);
	while (true) {
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &addrSize);
		if (clientSocket != INVALID_SOCKET) {
			std::cout << "Client connected " << clientSocket << "\n";
			int len = 0;
			char buffer[1024];
			int bytesReceived;
			while (bytesReceived = recv(clientSocket, buffer + len, sizeof(buffer) - len, 0))
			{
				len += bytesReceived;
			}
			cout << buffer << endl;
			cout << len << endl;
			BinaryStreamReader reader(buffer, len);
			GumballStatus s;
			while (reader.ReadInt32(len)) {
				reader >> s.count;
				reader >> (&s.location);
				reader >> (&s.state);
				cout << "*********" << '\n';
				cout << s.count << " " << s.location << " " << s.state << "\n";
			}

			closesocket(clientSocket);
		}
	}

	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
*/