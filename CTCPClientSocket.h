#ifndef CTCPCLIENTSOCKET_H
#define CTCPCLIENTSOCKET_H
/*
针对Linux Socket API的封装，用于TCP Client 套接字
*/
#include "CSocketADT.h"
#include <netinet/in.h>

class CTCPClientSocket:public CSocketADT
{
	public:
		//构造函数
		CTCPClientSocket(const char* ip,int port);
		//执行Socket connect()
		void setup();
		//两种关闭套接字的方法
		void closeSocket();
		void shutdownSocket(int howto);
		//获取套接字的描述符
		inline int getSocketfd(){
			return m_sockfd;
		}
	private:
		//套接字 初始化
		void initialize(const char* ip,int port);
		//封装API socket()
		int Socket(int family, int type, int protocol);
		//封装API connect()
		int Connect();
	private:
		//Socket 文件描述符
		int m_sockfd;
		//sockaddr_in 地址
		struct sockaddr_in m_sockaddr;
		
};
#endif