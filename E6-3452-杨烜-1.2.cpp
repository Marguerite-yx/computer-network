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
	/* ����Windows Sockets DLL,�ɹ������ʹ��socketϵ�к��� */
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
	/* ��������ַ */
	stServerAddr.sin_family = AF_INET;
	/* �����˿� */
	stServerAddr.sin_port = htons(6000); 
	stServerAddr.sin_addr.s_addr = INADDR_ANY;
	/* �������˴���socket, ��ģʽ(TCP)*/
	uiFdSerSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* �󶨶˿ں� */
	bind(uiFdSerSocket, (struct sockaddr*)&stServerAddr, sizeof(sockaddr_in));
	/* ���������� */
	listen(uiFdSerSocket, 5);
	while(true)
	{
		printf("waiting client send msg now...\r\n");
		/* ���ܿͻ�������,��ȡ�ͻ��˵�ip��ַ */
		uiFdConnectSocket = accept(uiFdSerSocket, (SOCKADDR*)&stClientAddr, &iAddrlen);
		/* ��Ϸ�����Ϣ����IP��ַ����ת��Ϊ�ַ��� */
		sprintf(szSendbuffer, "hello,this is server", inet_ntoa(stClientAddr.sin_addr));
		/* ������Ϣ���ͻ��� */
		send(uiFdConnectSocket, "hello,this is server", strlen(szSendbuffer)+1, 0);
		/* ���տͻ�����Ϣ */
		recv(uiFdConnectSocket, szRecvbuffer, sizeof(szRecvbuffer), 0);
		printf("Received datagram from client %s->%s\n", inet_ntoa(stClientAddr.sin_addr), szRecvbuffer);
		closesocket(uiFdConnectSocket);
	}
	closesocket(uiFdSerSocket);
}