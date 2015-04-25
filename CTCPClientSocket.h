#ifndef CTCPCLIENTSOCKET_H
#define CTCPCLIENTSOCKET_H
/*
���Linux Socket API�ķ�װ������TCP Client �׽���
*/
#include "CSocketADT.h"
#include <netinet/in.h>

class CTCPClientSocket:public CSocketADT
{
	public:
		//���캯��
		CTCPClientSocket(const char* ip,int port);
		//ִ��Socket connect()
		void setup();
		//���ֹر��׽��ֵķ���
		void closeSocket();
		void shutdownSocket(int howto);
		//��ȡ�׽��ֵ�������
		inline int getSocketfd(){
			return m_sockfd;
		}
	private:
		//�׽��� ��ʼ��
		void initialize(const char* ip,int port);
		//��װAPI socket()
		int Socket(int family, int type, int protocol);
		//��װAPI connect()
		int Connect();
	private:
		//Socket �ļ�������
		int m_sockfd;
		//sockaddr_in ��ַ
		struct sockaddr_in m_sockaddr;
		
};
#endif