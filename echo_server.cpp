#include "CEchoServer.h"
// Echo Server ������
int main()
{
	CEchoServer echoServer((const char *)0,ECHOPORT);
	echoServer.startServer();
	return 0;
}
