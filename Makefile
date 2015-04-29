objects1 = echo_server.o CEchoServer.o CTCPServerSocket.o CEchoIO.o
objects2 = echo_client.o CEchoClient.o CTCPClientSocket.o CEchoIO.o

all : echo_server echo_client

echo_server : $(objects1)
	g++ -g -o  echo_server $(objects1) 

echo_client : $(objects2)
	g++ -g -o  echo_client $(objects2) 
	
echo_server.o : CEchoServer.h
CEchoServer.o : CEchoServer.h CTCPServerSocket.h CEchoIO.h
CTCPServerSocket.o : CTCPServerSocket.h CSocketADT.h

echo_client.o : CEchoClient.h
CEchoClient.o : CEchoClient.h CTCPClientSocket.h CEchoIO.h
CTCPClientSocket.o : CTCPClientSocket.h CSocketADT.h

CEchoIO.o : CEchoIO.h

clean:
	rm echo_server $(objects1)
	rm echo_client $(objects2)
