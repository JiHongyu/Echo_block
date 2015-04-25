#ifndef CECHOSERVER_H
#define CECHOSERVER_H
/*
CEchoServer类,完成Echo Server的所有逻辑.
Server采用了epoll的高级IO轮询技术处理客户端的连接与业务
*/


#define MAX_EVENTS 10
#define BUFFERSIZE 4096
#define ECHOPORT 	9999 //默认端口

class CEchoIO;
class CTCPServerSocket;

class CEchoServer
{
	public: 
		//构造函数
		CEchoServer(const char *ip,int port);
		//开启服务
		void startServer();
		//关闭服务
		void closeServer();
		//析构
		~CEchoServer();
	private:
		//Echo 业务处理函数
		void echoHandler(int sockfd);
		//初始化
		void initialize(const char *ip,int port);
	private:
		CTCPServerSocket* m_serverSocket;//socket
		int m_epollfd;//epoll 描述符
		
		struct epoll_event *m_events;//epoll事件队列
		CEchoIO* m_io;//IO操作类指针
		char m_buffer[BUFFERSIZE];//缓存

		bool m_isrunning;//flag,判断服务器是否开启
};

#endif
