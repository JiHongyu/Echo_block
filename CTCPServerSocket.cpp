#include"CTCPServerSocket.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

CTCPServerSocket::CTCPServerSocket(int port)
{
	initialize(NULL,port);
}

CTCPServerSocket::CTCPServerSocket(const char* ip,int port)
{
	initialize(ip,port);
}

int CTCPServerSocket::Socket(int family, int type, int protocol)
{
	int	n;

	if ( (n = socket(family, type, protocol)) < 0)
		perror("socket error");
	int reuse = 1;  
    if(setsockopt(n, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))==-1)
		perror("setsockopt error"); 
	return(n);
}

void CTCPServerSocket::Listen(int backlog)
{
	char *ptr;

		/*4can override 2nd argument with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(m_sockfd, backlog) < 0)
		perror("listen error");
}

void
CTCPServerSocket::Bind()
{
	if (bind(m_sockfd,(struct sockaddr *)&m_sockaddr, sizeof(m_sockaddr)) < 0)
		perror("bind error");
}

int
CTCPServerSocket::Accept()
{
	int	n;

again:
	if ( (n = accept(m_sockfd,NULL,NULL)) < 0) {
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			perror("accept error");
	}
	return(n);
}

void CTCPServerSocket::initialize(const char* ip,int port)
{
	m_sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	memset(&m_sockaddr, 0, sizeof(m_sockaddr));
	if (ip == NULL){
		m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else if (inet_pton(AF_INET,ip, &m_sockaddr.sin_addr) <= 0){
		perror("IP address error");
		exit(-1);
	}
	m_sockaddr.sin_family      = AF_INET;
	m_sockaddr.sin_port        = htons(port);	
}

void CTCPServerSocket::setup()
{
	Bind();
	Listen(1024);
}

void CTCPServerSocket::closeSocket()
{
	if (close(m_sockfd)==-1)
	{
		perror("close error");
	}
}

void CTCPServerSocket::shutdownSocket(int howto)
{
	if(shutdown(m_sockfd,howto)==-1)
	{
		perror("shutdown error");
	}
}

