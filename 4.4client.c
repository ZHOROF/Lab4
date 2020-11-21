#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h> //inet_addr

int main(int argc, char*argv[])
{
	int socket_desc;

	struct sockaddr_in server;
	char message[2000], server_reply[2000];


	//Create socket
	socket_desc = socket(AF_INET,SOCK_STREAM,0);

	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("10.0.2.16");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);


	//connect to remote server

	if(connect(socket_desc,(struct sockaddr*)&server, sizeof(server))<0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	/*//Send some data
	message = "connect";
	if(send(socket_desc,message,strlen(message),0)<0)
	{
		puts("Send failed");
		return 1;
	}

	puts("Data Send\n");*/

	int num = 1;
	while(num == 1)
	{
		printf("tulis pesanan anda: ");
		fgets(message, 2000, stdin);
		send(socket_desc, message, 2000, 0);


		//Receive a reply from the server
		if(recv(socket_desc, server_reply, 2000, 0)<0)
		{
			puts("recv failed");
		}

		printf("\nReply received: %s", server_reply);
	}
	return 0;
}
