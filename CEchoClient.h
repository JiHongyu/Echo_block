#ifndef CECHOCLIENT_H
#define CECHOCLIENT_H
/*
CEchoClient��,���Echo Client�������߼�.
client������epoll�ĸ߼�IO��ѯ����ͬʱ������׼������׽��ֵ�����
*/
#define MAXBUFFERSIZE 4096
#define ECHOPORT 	9999	//Ĭ�϶˿�

class CEchoIO;
class CTCPClientSocket;

class CEchoClient
{
	public:
		//���캯��
		CEchoClient(const char*,int port);
		CEchoClient(const char*,const char* port);
		//��������,����clientҵ���߼���,ֱ�Ӱ�����startClient��
		void startClient();
		//�رշ���
		void closeClient();
		//��������
		~CEchoClient();
	private:
		//��ʼ��
		void initialize(const char*,int port);
	private:
		CTCPClientSocket *m_clientSocket;//client socket
		int m_epollfd;//epoll������
		struct epoll_event *m_events;//epoll�¼�����
		CEchoIO *m_io;//IO������ָ��
		char m_buffer[MAXBUFFERSIZE];//����
		bool m_isrunning;//flag,�ж��Ƿ�����
};
#endif