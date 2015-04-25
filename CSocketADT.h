#ifndef CSOCKET_H
#define CSOCKET_H
/*
套接字操作抽象
initialize:初始化数据
setup:执行套接字初始化操作,比如bind,listen,connect
closeSocket:关闭套接字的一种方法
shutdownSocket:关闭套接字的另一种方法
*/

class CSocketADT
{
	public:
	virtual void initialize(const char *ip,int port)=0;
	virtual void setup() = 0;
	virtual void closeSocket()=0;
	virtual void shutdownSocket(int howto)=0;
};
#endif
