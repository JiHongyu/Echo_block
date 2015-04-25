#ifndef CTCPSERVERSOCKET_H
#define CTCPSERVERSOCKET_H
/*
���Linux Socket API�ķ�װ������TCP Server �׽���
*/
#include "CSocketADT.h"
#include <netinet/in.h>

#define CLOSE 0
#define SHUTDOWN 1


class CTCPServerSocket:public CSocketADT
{
	public:
		//���캯��
		CTCPServerSocket(int port);
		CTCPServerSocket(const char* ip,int port);
		//ִ�� bind()��listen()
		void setup();
		//��װAPI accept()
		int Accept();
		//���ֹر��׽��ֵķ���
		void closeSocket();
		void shutdownSocket(int howto);
		//��ȡ�׽��ֵ�������
		inline int getSocketfd(){
			return m_sockfd;
		}
	private:
		//�׽��ֳ�ʼ��
		void initialize(const char* ip,int port);
		//��װ API socket()
		int Socket(int family, int type, int protocol);
		//��װ API listen()
		void Listen(int backlog);
		//��װ API bind()
		void Bind();
	private:
		//�׽���������
		int m_sockfd;
		//sockaddr_in ��ַ
		struct sockaddr_in m_sockaddr;
};
#endif
