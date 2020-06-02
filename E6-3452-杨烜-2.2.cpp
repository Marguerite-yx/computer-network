#include <WINSOCK2.H>    
#include <stdio.h>    
#pragma comment(lib,"ws2_32.lib")    
void main()    
{    
 int err;    
 WORD versionRequired;    
 WSADATA wsaData;    
 versionRequired=MAKEWORD(1,1);    
 err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息    
 if (!err)    
 {    
  printf("connected!\n");    
 }  
 else    
 {    
  printf("failed!\n");    
  return;//结束    
 }    
 SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);    
 SOCKADDR_IN clientsock_in;    
 clientsock_in.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");    
 clientsock_in.sin_family=AF_INET;    
 clientsock_in.sin_port=htons(6000);    
 //bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//注意第三个参数    
 //listen(clientSocket,5);    
 connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接    
 char receiveBuf[100];    
 recv(clientSocket,receiveBuf,101,0);    
 printf("%s\n",receiveBuf);    
 send(clientSocket,"hello,this is client",strlen("hello,this is client")+1,0); 
 system("pause");   
 closesocket(clientSocket);    
 WSACleanup();    
}