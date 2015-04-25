#include "CEchoServer.h"
// Echo Server Ö÷º¯Êý
int main()
{
	CEchoServer echoServer((const char *)0,ECHOPORT);
	echoServer.startServer();
	return 0;
}
