// demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#include "proto/User.pb.h"
#include "proto/Messages.pb.h"
#include "proto/Response.pb.h"
#include "proto/Status.pb.h"
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libprotobuf.lib") 
#pragma comment(lib, "libprotoc.lib") 


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET uiFdSerSocket;
	SOCKET uiFdConnectSocket;
	WSADATA wsaData;
	com::protobuf::msg::Message mmsg;
	com::protobuf::msg::Response response;
	com::protobuf::msg::Other other;
	com::protobuf::msg::Info info;
	char szSendbuffer[1024] = "\0";
	char szRecvbuffer[1024] = "\0";
	struct sockaddr_in stServerAddr;
	struct sockaddr_in stClientAddr;

	int iAddrlen = sizeof(sockaddr_in);

	/* 调用Windows Sockets DLL,成功后才能使用socket系列函数 */
	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData))
	{


		WSACleanup();
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 1)
	{

		WSACleanup();
		return 0;

	}
	memset(&stServerAddr, 0, sizeof(stServerAddr));
	memset(&stClientAddr, 0, sizeof(stClientAddr));
	/* 服务器地址 */
	stServerAddr.sin_family = AF_INET;
	/* 监听端口 */
	stServerAddr.sin_port = htons(3000);
	stServerAddr.sin_addr.s_addr = INADDR_ANY;


	/* 服务器端创建socket, 流模式(TCP)*/
	uiFdSerSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* 绑定端口号 */
	bind(uiFdSerSocket, (struct sockaddr*)&stServerAddr, sizeof(sockaddr_in));

	/* 服务器监听 */
	listen(uiFdSerSocket, 5);


	while (true)
	{
		printf("waiting client send msg now...\r\n");

		/* 接受客户端连接,获取客户端的ip地址 */
		uiFdConnectSocket = accept(uiFdSerSocket, (SOCKADDR*)&stClientAddr, &iAddrlen);

		/* 组合发送消息，将IP地址整形转化为字符串 */
		memset(&szSendbuffer, 0x00, sizeof(szSendbuffer));
		sprintf(szSendbuffer, "Welcome %s to here!", inet_ntoa(stClientAddr.sin_addr));
		cout << "szSendbuffer:\t" << szSendbuffer << endl;
		response.set_type(com::protobuf::msg::msgType::WORK);
		response.set_status(com::protobuf::msg::statusCode::ERR);
		response.set_data(szSendbuffer);
		/* 发送消息到客户端 */
		string sendStr;
		memset(&sendStr, 0x00, sizeof(sendStr));
		//response.AppendToString(&sendStr);
		response.SerializeToString(&sendStr);
		cout << "response.SerializeToString:\t" << sendStr.c_str() << sendStr.size() << endl;
		//
		//char bufs[1024] = "\0";
		//(void)memset(bufs, 0x00, sizeof(bufs));
		//(void)memcpy(bufs, sendStr.c_str(), sendStr.size());
		send(uiFdConnectSocket, sendStr.c_str(), sendStr.size(), 0);
		//send(uiFdConnectSocket, bufs, strlen(bufs) + 1, 0);
		//char bufs[1024] = "this test code!";
		//string bufs = "this test code!";
		
		//send(uiFdConnectSocket, bufs.c_str(), bufs.size(), 4);
		/* 接收客户端消息 */
		int n;
		if ((n = recv(uiFdConnectSocket, szRecvbuffer, sizeof(szRecvbuffer), 0)) > 0){
			printf("Received datagram from client %s->%s\n", inet_ntoa(stClientAddr.sin_addr), szRecvbuffer);
			mmsg.ParseFromString(szRecvbuffer);
			cout << "Msg Type:" << mmsg.type() << endl;
			cout << "Msg String:" << mmsg.msgbody() << endl;
			info.ParseFromString(mmsg.msgbody());
			cout << "Info ID:" << info.id() << endl;
			cout << "Info NAME:" << info.name() << endl;
			
		}
		
		//closesocket(uiFdConnectSocket);
		
	}
	closesocket(uiFdSerSocket);
	return 0;
}

