#ifndef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#else
#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#endif

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>

#include <proto/Messages.pb.h>
#include "proto/User.pb.h"
#include "proto/Response.pb.h"
#include "proto/Status.pb.h"

#pragma warning(disable : 4018)
#pragma warning(disable : 4146)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4305)
#pragma warning(disable : 4355)
#pragma warning(disable : 4800)
#pragma warning(disable : 4996)

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libprotobuf.lib") 
#pragma comment(lib, "libprotobuf-lite.lib") 
#pragma comment(lib, "libprotoc.lib") 
using namespace std;

int main()
{
	SOCKET uiFdClientsocket;
	WSADATA wsaData;
	com::protobuf::msg::Message mmsg;
	com::protobuf::msg::Response response;
	com::protobuf::msg::Other other;
	com::protobuf::msg::Info info;

	struct sockaddr_in stServerAddr;
	int iAddrlen = sizeof(sockaddr_in);
	char szSendbuffer[1024];
	char szRecvbuffer[1024];

	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData))
	{
		printf("Winsock init faied!\r\n");
		WSACleanup();
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 1)
	{
		printf("the socket version is error!\r\n");
		WSACleanup();
		return 0;
	}



	/* 服务器监听的端口和地址 */
	memset(&stServerAddr, 0, sizeof(stServerAddr));
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(3000);
	stServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (true)
	{

		szSendbuffer[0] = '\0';
		szRecvbuffer[0] = '\0';
		/* 创建SOCKET */
		uiFdClientsocket = socket(AF_INET, SOCK_STREAM, 0);
		/* 连接服务器 */
		connect(uiFdClientsocket, (SOCKADDR*)&stServerAddr, sizeof(sockaddr_in));

		printf("connect to server ok...\r\n");
		/* 接收服务器端数据 */
		int n;
		string sRecvStr;
		
		if ((n = recv(uiFdClientsocket, szRecvbuffer, sizeof(szRecvbuffer), 0)) > 0){
			printf("revive data from server->%s\r\nnow input msg here...`\r\n", szRecvbuffer);
			szRecvbuffer[n] = 0x00;
			sRecvStr = szRecvbuffer;
			response.ParseFromString(sRecvStr);
			cout << "Msg Type:" << response.type() << endl;
			cout << "Msg status:" << response.status() << endl;
			cout << "Msg data:" << response.data() << endl;
			
		}

		/* 向服务器端发送数据 */
		string sInfo,sMsg;
		char iStr[1024];
		(void)memset(iStr, 0x00, sizeof(iStr));
		info.set_id(1);
		scanf("%s", iStr);
		info.set_name(iStr);
		info.SerializeToString(&sInfo);
		mmsg.set_type(com::protobuf::msg::HOME);
		//mmsg.set_type(com::protobuf::msg::msgType::USER);
		mmsg.set_msgbody(sInfo);
		mmsg.SerializeToString(&sMsg);
		(void)memset(szSendbuffer, 0x00, sizeof(szSendbuffer));
		(void)memcpy(szSendbuffer, sMsg.c_str(), sMsg.size());
		send(uiFdClientsocket, szSendbuffer, sizeof(szSendbuffer) + 1, 0);

		closesocket(uiFdClientsocket);
	}
	closesocket(uiFdClientsocket);
	return 0;
}