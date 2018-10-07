#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	FILE *html_file;

	html_file = fopen("index.html","r");

	char html_source[2048];
	fgets(html_source,2048,html_file);

	char http_header_positive[2048] = "HTTP/1.1 200 OK \r\n\n";

	strcat(http_header_positive,html_source);

	int server_socket;

	server_socket = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8998);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket,(struct sockaddr *) &server_addr ,sizeof(server_addr));

	listen(server_socket,5);


	int client_request;

	while(1){

		client_request = accept(server_socket,NULL,NULL);
		send(client_request,http_header_positive,sizeof(http_header_positive),0);
		close(client_request);

	}
	return 0;

}
