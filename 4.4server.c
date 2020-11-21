#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char message[2000], client_reply[2000];
	int optval;
	socklen_t optlen = sizeof(optval);

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}


	/* Check the status for the keep alive option */
	if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0)
	{
		perror("getsockopt()");
		close(socket_desc);
		exit(EXIT_FAILURE);
	}
	printf("SO_KEEPALIVE is %s\n", (optval ? "ON":"OFF"));

	/* Set the option active */
	optval = 1;
	optlen = sizeof(optval);

	if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0)
	{
		perror("setsockopt()");
		close(socket_desc);
		exit(EXIT_FAILURE);
	}

	printf("SO_KEEPALIVE set on socket\n");



	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}

	puts("bind done");

	//Listen
	listen(socket_desc, 3);


	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	int num  = 1;
	while(num == 1)
	{
		new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

		puts("Connection accepted");



		//printf("Waiting for message from client..\n");

		recv(new_socket, client_reply, 2000, 0);
		printf("\nMenunggu Pesanan daripada CLient: %s",client_reply);

		printf("Enter message for client: ");
		fgets(message, 2000, stdin);
		send(new_socket, message, 2000, 0);
	}

	if(new_socket < 0)
	{
		perror("accept failed");
		return 1;
	}

	return 0;

}
