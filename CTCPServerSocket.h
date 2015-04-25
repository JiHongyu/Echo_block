#ifndef CTCPSERVERSOCKET_H
#define CTCPSERVERSOCKET_H
/*
针对Linux Socket API的封装，用于TCP Server 套接字
*/
#include "CSocketADT.h"
#include <netinet/in.h>

#define CLOSE 0
#define SHUTDOWN 1


class CTCPServerSocket:public CSocketADT
{
	public:
		//构造函数
		CTCPServerSocket(int port);
		CTCPServerSocket(const char* ip,int port);
		//执行 bind()和listen()
		void setup();
		//封装API accept()
		int Accept();
		//两种关闭套接字的方法
		void closeSocket();
		void shutdownSocket(int howto);
		//获取套接字的描述符
		inline int getSocketfd(){
			return m_sockfd;
		}
	private:
		//套接字初始化
		void initialize(const char* ip,int port);
		//封装 API socket()
		int Socket(int family, int type, int protocol);
		//封装 API listen()
		void Listen(int backlog);
		//封装 API bind()
		void Bind();
	private:
		//套接字描述符
		int m_sockfd;
		//sockaddr_in 地址
		struct sockaddr_in m_sockaddr;
};
#endif
