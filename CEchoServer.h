#ifndef CECHOSERVER_H
#define CECHOSERVER_H
/*
CEchoServer��,���Echo Server�������߼�.
Server������epoll�ĸ߼�IO��ѯ��������ͻ��˵�������ҵ��
*/


#define MAX_EVENTS 10
#define BUFFERSIZE 4096
#define ECHOPORT 	9999 //Ĭ�϶˿�

class CEchoIO;
class CTCPServerSocket;

class CEchoServer
{
	public: 
		//���캯��
		CEchoServer(const char *ip,int port);
		//��������
		void startServer();
		//�رշ���
		void closeServer();
		//����
		~CEchoServer();
	private:
		//Echo ҵ������
		void echoHandler(int sockfd);
		//��ʼ��
		void initialize(const char *ip,int port);
	private:
		CTCPServerSocket* m_serverSocket;//socket
		int m_epollfd;//epoll ������
		
		struct epoll_event *m_events;//epoll�¼�����
		CEchoIO* m_io;//IO������ָ��
		char m_buffer[BUFFERSIZE];//����

		bool m_isrunning;//flag,�жϷ������Ƿ���
};

#endif
