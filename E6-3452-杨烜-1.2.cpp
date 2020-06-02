#include <stdio.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void main()
{
	SOCKET uiFdSerSocket;
	SOCKET uiFdConnectSocket;
	WSADATA wsaData;
	char szSendbuffer[1024] = "\0";
	char szRecvbuffer[1024] = "\0";
	struct sockaddr_in stServerAddr;
	struct sockaddr_in stClientAddr;
	int iAddrlen = sizeof(sockaddr_in);
	/* 调用Windows Sockets DLL,成功后才能使用socket系列函数 */
	if (0 != WSAStartup(MAKEWORD(2,1), &wsaData)) 
	{
		printf("Winsock init failed!\r\n");
		WSACleanup();
		return;
	}
	if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 1) 
	{
		printf("the socket version is error!\r\n");
		WSACleanup();
		return;
	}
	memset(&stServerAddr, 0, sizeof(stServerAddr));
	memset(&stClientAddr, 0, sizeof(stClientAddr));
	/* 服务器地址 */
	stServerAddr.sin_family = AF_INET;
	/* 监听端口 */
	stServerAddr.sin_port = htons(6000); 
	stServerAddr.sin_addr.s_addr = INADDR_ANY;
	/* 服务器端创建socket, 流模式(TCP)*/
	uiFdSerSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* 绑定端口号 */
	bind(uiFdSerSocket, (struct sockaddr*)&stServerAddr, sizeof(sockaddr_in));
	/* 服务器监听 */
	listen(uiFdSerSocket, 5);
	while(true)
	{
		printf("waiting client send msg now...\r\n");
		/* 接受客户端连接,获取客户端的ip地址 */
		uiFdConnectSocket = accept(uiFdSerSocket, (SOCKADDR*)&stClientAddr, &iAddrlen);
		/* 组合发送消息，将IP地址整形转化为字符串 */
		sprintf(szSendbuffer, "hello,this is server", inet_ntoa(stClientAddr.sin_addr));
		/* 发送消息到客户端 */
		send(uiFdConnectSocket, "hello,this is server", strlen(szSendbuffer)+1, 0);
		/* 接收客户端消息 */
		recv(uiFdConnectSocket, szRecvbuffer, sizeof(szRecvbuffer), 0);
		printf("Received datagram from client %s->%s\n", inet_ntoa(stClientAddr.sin_addr), szRecvbuffer);
		closesocket(uiFdConnectSocket);
	}
	closesocket(uiFdSerSocket);
}