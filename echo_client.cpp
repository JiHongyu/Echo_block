#include "CEchoClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
// Echo Client Ö÷º¯Êý
int main(int argc, char **argv)
{
	CEchoClient *echo_client;
	if (argc < 2){
		perror("usage: echo_client <IP-multicast-address> [<port#>]");
		exit(0);
	}
	else if(argc == 2){
		echo_client = new CEchoClient(argv[1], ECHOPORT);
	}
	else{
		echo_client = new CEchoClient(argv[1], argv[2]);
	}

	echo_client->startClient();
	echo_client->closeClient();
	delete echo_client;
	return 0;
}
