#ifndef CSOCKET_H
#define CSOCKET_H
/*
�׽��ֲ�������
initialize:��ʼ������
setup:ִ���׽��ֳ�ʼ������,����bind,listen,connect
closeSocket:�ر��׽��ֵ�һ�ַ���
shutdownSocket:�ر��׽��ֵ���һ�ַ���
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
