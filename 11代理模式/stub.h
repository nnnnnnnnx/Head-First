#pragma once
#include <vector>
#include "loc.h" 
#include "NanStream.h"
#include <winsock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

struct IGumballService {
	virtual ~IGumballService() = default;

	virtual bool nextStatus(GumballStatus& status) = 0;
};


class GumballServiceProxy : public IGumballService {
public:
	GumballServiceProxy(const std::string& host, int port)
	{
		WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in addr{ AF_INET, htons((short)port), inet_addr(host.c_str()) };
		if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
			std::cerr << "Proxy connect failed\n";
			closesocket(sock); sock = INVALID_SOCKET;
		}
	}
	~GumballServiceProxy() {
		if (sock != INVALID_SOCKET) closesocket(sock);
		WSACleanup();
	}

	bool nextStatus(GumballStatus& status) override
	{
		if (!sendRequest()) return false;
		return recvResponse(status);
	}

private:
	SOCKET sock;
	bool sendRequest() {
		std::string out;
		nans::BinaryStreamWriter w(&out);
		int32_t cmd = 1;
		w << cmd;
		// flush length prefix
		w.Flush();
		return send(sock, out.data(), (int)out.size(), 0) == (int)out.size();
	}
	bool recvResponse(GumballStatus& s)
	{
		char buf[1024];
		int len = 0, ret;
		// 简化：一次性读完
		if ((ret = recv(sock, buf, sizeof(buf), 0)) <= 0) return false;
		len = ret;
		nans::BinaryStreamReader r(buf, len);
		int32_t code;
		r >> code;
		if (code != 0) return false;  // 0 = OK, 非0为结束或错误
		// 反序列化 GumballStatus
		r >> s.count;
		r >> (&s.location);
		r >> (&s.state);
		return true;
	}

};

class GumballServiceStub {
public:
	GumballServiceStub(IGumballService* impl, int port)
		:service(impl)
	{
		WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
		listenSock = socket(AF_INET, SOCK_STREAM, 0);
		int reuse = 1; setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
		sockaddr_in addr{ AF_INET, htons((short)port), INADDR_ANY };
		bind(listenSock, (sockaddr*)&addr, sizeof(addr));
		listen(listenSock, 5);
	}
	void run() {
		std::cout << "Stub listening...\n";
		while (true) {
			SOCKET client = accept(listenSock, nullptr, nullptr);
			if (client != INVALID_SOCKET) handleClient(client);
		}
	}
private:
	IGumballService* service;
	SOCKET listenSock;
	void handleClient(SOCKET client)
	{
		char buf[1024];
		int len;
		while (len = recv(client, buf, sizeof(buf), 0)) {
			if (len <= 0) { closesocket(client); return; }
			nans::BinaryStreamReader r(buf, len);
			int32_t cmd; r >> cmd;
			if (cmd == 1) {
				GumballStatus s;
				bool ok = service->nextStatus(s);
				if (!ok) goto endd;
				std::string out;
				nans::BinaryStreamWriter w(&out);
				w << (int32_t)(ok ? 0 : 1);
				if (ok) {
					w << s.count;
					w << s.location;
					w << s.state;
				}
				w.Flush();
				send(client, out.data(), (int)out.size(), 0);
			}
		}
	endd:
		closesocket(client);
	}
};

class MyGumballService : public IGumballService {
	std::vector<GumballStatus> history;
	size_t idx = 0;
public:
	MyGumballService() {
		// 假定三条预置状态
		GumballMachine gumbal("noname", 5);
		GumballStatus a = gumbal.toStatus();
		history.push_back(a);
		gumbal.insertQuarter();
		gumbal.turnCrank();
		a = gumbal.toStatus();
		history.push_back(a);
		gumbal.insertQuarter();
		gumbal.turnCrank();
		a = gumbal.toStatus();
		history.push_back(a);
	}
	bool nextStatus(GumballStatus& s) override {
		if (idx >= history.size()) return false;
		s = history[idx++];
		return true;
	}
};

