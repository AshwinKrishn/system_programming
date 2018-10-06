#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argv, char * argc[]){

	int port;
	char ip [20];
	char server_info[] = "You are connected to Ashwin's server";
	if(argv != 3 ){
		
		printf("Usage ./tcp_server [port] [ip]\n");
		exit(0);
	}
	port = atoi(argc[1]);
	//create a socket
	int network_socket;
	network_socket = socket(AF_INET , SOCK_STREAM , 0);
	
	//provide the socket an address

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;
	//bind the socket with ip and port
	int conn_status = bind(network_socket,(struct sockaddr *)&server_address,sizeof(server_address));

	if(conn_status == -1){
		perror("bind failed");
		exit(0);
	}
	
	listen(network_socket,5);

	int client_socket = accept(network_socket,NULL,NULL);
	
	 char server_response[256];

	send(client_socket, server_info , sizeof(server_info),0);
	printf("\n\nnow receive from client ");
	recv(client_socket ,&server_response , sizeof(server_response),0 );	
	printf("\n data %s",server_response);
	close(network_socket);
	return 0;	
}
