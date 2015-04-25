#include "CEchoClient.h"
#include "CTCPClientSocket.h"
#include "CEchoIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <errno.h>

CEchoClient::CEchoClient(const char* ip,const char* port)
{
	initialize(ip,htons(atoi(port)));
}
CEchoClient::CEchoClient(const char *ip, int port)
{
	initialize(ip,port);
}

void CEchoClient::initialize(const char *ip,int port)
{
	int client_sock;
	struct epoll_event ev;
	m_clientSocket = new CTCPClientSocket(ip,port);
	
	client_sock = m_clientSocket->getSocketfd();
	m_epollfd = epoll_create1(0);
	if (m_epollfd < 0) {
   		perror("epoll_create");
			exit(errno);
	}
	//配置标准输入的epoll读事件
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = 0;//stdin
	//注册事件
	if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, 0, &ev) < 0) {
		perror("epoll_ctl: stdin");
		exit(EXIT_FAILURE);
	}
	//配置socket的epoll读事件
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = client_sock;
	//注册事件
	if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, client_sock, &ev) < 0) {
		perror("epoll_ctl: client_sock");
		exit(EXIT_FAILURE);
	}
	m_events = new struct epoll_event[2];
	m_io = new CEchoIO;
	m_isrunning = false;

}

void CEchoClient::startClient()
{
	int nfds = 0;
	int client_sock = m_clientSocket->getSocketfd();
	int data_size;
	int is_end = 0;
	m_clientSocket->setup();
	m_isrunning = true;
	for(;;){
		//epoll等待阻塞
		nfds = epoll_wait(m_epollfd, m_events, 2, -1);
		if (nfds == -1) {
			perror("epoll_pwait");
			exit(EXIT_FAILURE);
		}
		for(int n = 0; n < nfds; n++)
		{
			if(m_events[n].data.fd == client_sock)
				//来自socket的事件
			{
				if((data_size = 
				m_io->Read(client_sock,m_buffer,MAXBUFFERSIZE))==0)
				{
					if(is_end ==1)
						return;
					else
						perror("socket read error");
				}
				m_io->Writen(0,m_buffer,data_size);
			}
			else
				//来自标准输入的事件
			{
				if((data_size = 
				m_io->Read(0,m_buffer,MAXBUFFERSIZE))==0)
					{
						is_end = 1;
						m_clientSocket->shutdownSocket(SHUT_WR);
						m_isrunning = false;
						continue;
					}
					m_io->Writen(client_sock,m_buffer,data_size);
			}
		}
	}
	
}

void CEchoClient::closeClient()
{
	
}

CEchoClient::~CEchoClient()
{
	if (m_isrunning == true)
	{
		m_clientSocket->shutdownSocket(SHUT_WR);
	}	
	delete []m_events;
	delete m_clientSocket;
	delete m_io;
}