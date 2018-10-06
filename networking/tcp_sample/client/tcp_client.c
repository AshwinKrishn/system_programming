#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

int main(int argv, char * argc[]){

	int port;
	char ip [20];
	char server_response[256];
	if(argv != 3 ){
		
		printf("Usage ./tcp_client [port] [ip]\n");
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
	int conn_status = connect(network_socket,(struct sockaddr *)&server_address,sizeof(server_address));

	if(conn_status == -1){
		perror("connected failed");
		exit(0);
	}
	


	recv(network_socket, &server_response , sizeof(server_response),0);

	printf("server sent : %s\n",server_response);
	memset(server_response,'\0',256);
	sprintf(server_response,"thanks from client");	
	send(network_socket,server_response,sizeof(server_response),0);
	close(network_socket);	
	return 0;
}
