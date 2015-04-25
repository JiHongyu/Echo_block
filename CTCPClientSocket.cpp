#include"CTCPClientSocket.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <arpa/inet.h>

CTCPClientSocket::CTCPClientSocket(const char * ip,int port)
{
	initialize(ip,port);
}

int CTCPClientSocket::Socket(int family, int type, int protocol)
{
	int	n;

	if ( (n = socket(family, type, protocol)) < 0)
		perror("socket error");
	int reuse = 1;  
    if(setsockopt(n, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))==-1)
		perror("setsockopt error"); 
	return(n);
}

int CTCPClientSocket::Connect()
{
	return connect(m_sockfd, (struct sockaddr*) &m_sockaddr, sizeof(m_sockaddr));
}

void CTCPClientSocket::initialize(const char* ip,int port)
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

void CTCPClientSocket::setup()
{
	
	if (Connect()<0)
	{
		perror("Connection error");	
		exit(errno);
	}
}

void CTCPClientSocket::closeSocket()
{
	if (close(m_sockfd)==-1)
	{
		perror("close error");
	}
}

void CTCPClientSocket::shutdownSocket(int howto)
{
	if(shutdown(m_sockfd,howto)==-1)
	{
		perror("shutdown error");
	}
}

