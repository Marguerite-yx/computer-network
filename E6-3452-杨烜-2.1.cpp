#include <WINSOCK2.H>    
#include <stdio.h>    
#pragma comment(lib,"ws2_32.lib")    
void main()    
{    
 //�����׽���    
 WORD myVersionRequest;    
 WSADATA wsaData;    
 myVersionRequest=MAKEWORD(1,1);    
 int err;    
 err=WSAStartup(myVersionRequest,&wsaData);    
 if (!err)    
 {    
  printf("connect\n");    
 }     
 else    
 {    
  //��һ�����׽���    
  printf("I cannot socket success\n!");    
  return;    
 }    
 SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���    
 //��Ҫ�󶨵Ĳ���    
 SOCKADDR_IN addr;    
 addr.sin_family=AF_INET;    
 addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//ip��ַ    
 addr.sin_port=htons(6000);//�󶨶˿�    
      
 bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//�����    
 listen(serSocket,5);//���еڶ������������ܹ����յ�����������     
 SOCKADDR_IN clientsocket;    
 int len=sizeof(SOCKADDR);    
 while (1)    
 {    
  SOCKET serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���    
  char sendBuf[100];    
       
  sprintf(sendBuf,"hello,this is server",inet_ntoa(clientsocket.sin_addr));//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������    
  send(serConn,sendBuf,strlen(sendBuf)+1,0);    
  char receiveBuf[100];//����    
  recv(serConn,receiveBuf,strlen(receiveBuf)+1,0);    
  printf("%s\n",receiveBuf);    
  closesocket(serConn);//�ر�    
 WSACleanup();//�ͷ���Դ�Ĳ���    
 }    
}