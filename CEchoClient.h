#ifndef CECHOCLIENT_H
#define CECHOCLIENT_H
/*
CEchoClient类,完成Echo Client的所有逻辑.
client采用了epoll的高级IO轮询技术同时侦听标准输入和套接字的输入
*/
#define MAXBUFFERSIZE 4096
#define ECHOPORT 	9999	//默认端口

class CEchoIO;
class CTCPClientSocket;

class CEchoClient
{
	public:
		//构造函数
		CEchoClient(const char*,int port);
		CEchoClient(const char*,const char* port);
		//开启服务,由于client业务逻辑简单,直接包含在startClient中
		void startClient();
		//关闭服务
		void closeClient();
		//析构函数
		~CEchoClient();
	private:
		//初始化
		void initialize(const char*,int port);
	private:
		CTCPClientSocket *m_clientSocket;//client socket
		int m_epollfd;//epoll描述符
		struct epoll_event *m_events;//epoll事件队列
		CEchoIO *m_io;//IO操作类指针
		char m_buffer[MAXBUFFERSIZE];//缓存
		bool m_isrunning;//flag,判断是否运行
};
#endif