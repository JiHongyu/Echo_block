#include "CEchoServer.h"
#include "CTCPServerSocket.h"
#include "CEchoIO.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
 
CEchoServer::CEchoServer(const char *ip,int port=ECHOPORT) 
{
	initialize(ip,port);
}
void CEchoServer::initialize(const char *ip,int port)
{
	int listen_sock;
	struct epoll_event ev;
	m_serverSocket = new CTCPServerSocket(ip,port);
	m_serverSocket->setup();
	listen_sock = m_serverSocket->getSocketfd();
	m_epollfd = epoll_create1(0);
	if (m_epollfd < 0) {
   		perror("epoll_create");
		exit(EXIT_FAILURE);
	}
	//配置Server socket的读事件
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	//注册事件
	if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, listen_sock, &ev) < 0) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	m_events = new struct epoll_event[MAX_EVENTS];
	m_io = new CEchoIO;
	m_isrunning = false;
}

void CEchoServer::startServer()
{
	int nfds=0;
	int conn_sock_fd;
	struct epoll_event ev;
	m_isrunning = true;
	for (;;) {
		//epoll等待事件发生
		nfds = epoll_wait(m_epollfd, m_events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_pwait");
			exit(EXIT_FAILURE);
		}

		for (int n = 0; n < nfds; ++n) {
			if (m_events[n].data.fd == m_serverSocket->getSocketfd()) {
				//来自客户端的连接事件
				//获取客户端套接字描述符
				conn_sock_fd = m_serverSocket->Accept();
				//配置客户端业务处理事件
				ev.events = EPOLLIN|EPOLLET ;
				ev.data.fd = conn_sock_fd;
				//注册事件
				if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, conn_sock_fd,
					&ev) == -1) {
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}
			}else if(m_events[n].events&EPOLLIN){
				//来自客户端的业务逻辑事件
		       echoHandler(m_events[n].data.fd);
		   }
		}
	}
}

void CEchoServer::echoHandler(int sockfd)
{
	ssize_t		n;

again:
	while ( (n = m_io->Read(sockfd, m_buffer, BUFFERSIZE)) > 0)
		m_io->Writen(sockfd, m_buffer, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		perror("echoHandler: read error");
		
}

void CEchoServer::closeServer()
{
	close(m_epollfd);
	
	m_serverSocket->closeSocket();
}

CEchoServer::~CEchoServer()
{
	if (m_isrunning==true)
		closeServer();
	delete[] m_events;
}