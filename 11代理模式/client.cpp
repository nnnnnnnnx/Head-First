#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include "nanstream.h"
#include "loc.h"
#include "stub.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace nans;

int main() {
	GumballServiceProxy proxy("127.0.0.1", 8888);
	GumballStatus s;
	while (proxy.nextStatus(s)) {
		std::cout << s.count << " " << s.location << " " << s.state << "\n";
	}
}
/*
int main() {
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddr;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) != 0) {
		std::cerr << "Connection failed.\n";
		return 1;
	}

	string outbuf;
	BinaryStreamWriter writeStream(&outbuf);


	GumballMachine gumbal("noname", 5);
	gumbal.insertQuarter();
	gumbal.turnCrank();
	GumballStatus a = gumbal.toStatus();
	GumballMonitor remote(&a);
	int total_len = sizeof(a.count) + a.location.size() + a.state.size();
	writeStream << total_len;
	writeStream << a.count;
	writeStream << a.location;
	writeStream << a.state;
	cout << total_len << " " << a.count << " " << a.location << " " << a.state << endl;

	gumbal.insertQuarter();
	gumbal.turnCrank();
	a = gumbal.toStatus();
	remote.set(&a);

	total_len = sizeof(a.count) + a.location.size() + a.state.size();
	writeStream << total_len;
	writeStream << a.count;
	writeStream << a.location;
	writeStream << a.state;
	cout << total_len << " " << a.count << " " << a.location << " " << a.state << endl;

	gumbal.insertQuarter();
	gumbal.turnCrank();
	remote.set(&a);
	total_len = sizeof(a.count) + a.location.size() + a.state.size();
	writeStream << total_len;
	writeStream << a.count;
	writeStream << a.location;
	writeStream << a.state;
	cout << total_len << " " << a.count << " " << a.location << " " << a.state << endl;
	cout << outbuf << endl;
	printf("%d\n", outbuf.size());
	send(clientSocket, (char*)outbuf.c_str(), outbuf.size(), 0);

	cin.get();

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
*/