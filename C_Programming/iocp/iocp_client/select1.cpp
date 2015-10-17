
#include <winsock2.h>     
#include <stdio.h>     

#define PORT  5150     

#define MSGSIZE  1024     

#pragma comment(lib, "ws2_32.lib")     

int g_iTotalConn1 = 0;
int g_iTotalConn2 = 0;

SOCKET g_CliSocketArr1[FD_SETSIZE];
SOCKET g_CliSocketArr2[FD_SETSIZE];

DWORD WINAPI WorkerThread1(LPVOID lpParam);
int CALLBACK ConditionFunc1(LPWSABUF lpCallerId, LPWSABUF lpCallerData, LPQOS lpSQOS, LPQOS lpGQOS, LPWSABUF lpCalleeId, LPWSABUF lpCalleeData, GROUP FAR * g, DWORD dwCallbackData);

DWORD WINAPI WorkerThread2(LPVOID lpParam);
int CALLBACK ConditionFunc2(LPWSABUF lpCallerId, LPWSABUF lpCallerData, LPQOS lpSQOS, LPQOS lpGQOS, LPWSABUF lpCalleeId, LPWSABUF lpCalleeData, GROUP FAR * g, DWORD dwCallbackData);


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET sListen, sClient;
	SOCKADDR_IN local, client;
	int iAddrSize = sizeof(SOCKADDR_IN);
	DWORD dwThreadId;
	// Initialize windows socket library     
	WSAStartup(0x0202, &wsaData);
	// Create listening socket     
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// Bind     

	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);
	bind(sListen, (sockaddr*)&local, sizeof(SOCKADDR_IN));

	// Listen     

	listen(sListen, 3);

	// Create worker thread     

	CreateThread(NULL, 0, WorkerThread1, NULL, 0, &dwThreadId);
	// CreateThread(NULL, 0, WorkerThread2, NULL, 0, &dwThreadId);    

	while (TRUE)
	{
		sClient = WSAAccept(sListen, (sockaddr*)&client, &iAddrSize, ConditionFunc1, 0);
		printf("1:Accepted client:%s:%d:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), g_iTotalConn1);
		g_CliSocketArr1[g_iTotalConn1++] = sClient;
		/*
		sClient = WSAAccept(sListen, (sockaddr*)&client, &iAddrSize, ConditionFunc2, 0);
		printf("2:Accepted client:%s:%d:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), g_iTotalConn2);
		g_CliSocketArr2[g_iTotalConn2++] = sClient;   */

	}
	return 0;
}

DWORD WINAPI WorkerThread1(LPVOID lpParam)
{
	int i;
	fd_set fdread;
	int ret;
	struct timeval tv = { 1, 0 };
	char szMessage[MSGSIZE];
	while (TRUE)
	{
		FD_ZERO(&fdread);   //1清空队列  
		for (i = 0; i < g_iTotalConn1; i++)
		{
			FD_SET(g_CliSocketArr1[i], &fdread);   //2将要检查的套接口加入队列  
		}

		// We only care read event     
		ret = select(0, &fdread, NULL, NULL, &tv);   //3查询满足要求的套接字，不满足要求，出队  
		if (ret == 0)
		{
			// Time expired     
			continue;
		}

		for (i = 0; i < g_iTotalConn1; i++)
		{
			if (FD_ISSET(g_CliSocketArr1[i], &fdread))    //4.是否依然在队列  
			{
				// A read event happened on g_CliSocketArr     

				ret = recv(g_CliSocketArr1[i], szMessage, MSGSIZE, 0);
				if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
				{
					// Client socket closed     
					printf("1:Client socket %d closed.\n", g_CliSocketArr1[i]);
					closesocket(g_CliSocketArr1[i]);
					printf("3:here debug %d\n", g_iTotalConn1 - 1);
					if (i < g_iTotalConn1 - 1)
					{
						//g_CliSocketArr1[i--] = g_CliSocketArr1[--g_iTotalConn1];
					}
				}
				else
				{
					// We reveived a message from client     
					szMessage[ret] = '\0';
					send(g_CliSocketArr1[i], szMessage, strlen(szMessage), 0);
				}
			}
		}
	}
}

int CALLBACK ConditionFunc1(LPWSABUF lpCallerId, LPWSABUF lpCallerData, LPQOS lpSQOS, LPQOS lpGQOS, LPWSABUF lpCalleeId, LPWSABUF lpCalleeData, GROUP FAR * g, DWORD dwCallbackData)
{
	if (g_iTotalConn1 < FD_SETSIZE)
		return CF_ACCEPT;
	else
		return CF_REJECT;
}

DWORD WINAPI WorkerThread2(LPVOID lpParam)
{
	int i;
	fd_set fdread;
	int ret;
	struct timeval tv = { 1, 0 };
	char szMessage[MSGSIZE];
	while (TRUE)
	{
		FD_ZERO(&fdread);   //1清空队列  
		for (i = 0; i < g_iTotalConn2; i++)
		{
			FD_SET(g_CliSocketArr2[i], &fdread);   //2将要检查的套接口加入队列  
		}

		// We only care read event     
		ret = select(0, &fdread, NULL, NULL, &tv);   //3查询满足要求的套接字，不满足要求，出队  
		if (ret == 0)
		{
			// Time expired     
			continue;
		}

		for (i = 0; i < g_iTotalConn2; i++)
		{
			if (FD_ISSET(g_CliSocketArr2[i], &fdread))    //4.是否依然在队列  
			{
				// A read event happened on g_CliSocketArr     

				ret = recv(g_CliSocketArr2[i], szMessage, MSGSIZE, 0);
				if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
				{
					// Client socket closed     
					printf("2:Client socket %d closed.\n", g_CliSocketArr1[i]);
					closesocket(g_CliSocketArr2[i]);
					printf("3:here debug %d\n", g_iTotalConn2 - 1);
					if (i < g_iTotalConn2 - 1)
					{
						printf("3:here debug\n");
						//g_CliSocketArr2[i--] = g_CliSocketArr2[--g_iTotalConn2];
					}
				}
				else
				{
					// We reveived a message from client     
					szMessage[ret] = '\0';
					send(g_CliSocketArr2[i], szMessage, strlen(szMessage), 0);
				}
			}
		}
	}
}

int CALLBACK ConditionFunc2(LPWSABUF lpCallerId, LPWSABUF lpCallerData, LPQOS lpSQOS, LPQOS lpGQOS, LPWSABUF lpCalleeId, LPWSABUF lpCalleeData, GROUP FAR * g, DWORD dwCallbackData)
{
	if (g_iTotalConn2 < FD_SETSIZE)
		return CF_ACCEPT;
	else
		return CF_REJECT;
}
