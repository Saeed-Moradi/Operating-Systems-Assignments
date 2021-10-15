#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void *connection_handler(void *);
int client_count = 0;
int main(int argc, char *argv[])
{   
    // first get server address and portnumber arguments from the terminal 
    int port_number;
    char *listen_address;
    int *new_socket;

    if(argc!= 5)
    {
        printf("The number of given arguments are not equal to what's expected(expected 5, given %d), the input structure is:\n‫‪./socket-server -h listenaddress -p portnumber",argc);
        exit(EXIT_FAILURE);
    }
    // get the value of given param
    listen_address = (char *)argv[2];
    port_number = atoi(argv[4]);

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // check if it has been created successfully
    if (server_socket == -1)
    {
        perror("\nCould not creat server socket\n");
        exit(EXIT_FAILURE);
    }

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port= htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(listen_address);


    // bind the socket to the specified IP and port
    if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
    {
        perror("\n[ERROR] Bind failed\n");
        exit(EXIT_FAILURE);
    }


    // listen for connection
    if(listen(server_socket,5) < 0)
    {
        perror("\n[ERROR] Failed to listen.\n");
        exit(EXIT_FAILURE);
    }

    // create an int to define the client socket
    int client_socket; 

    while(1){
        client_socket = accept(server_socket,(struct sockaddr*) &server_address, (socklen_t*)&server_address);

        if(client_socket < 0)
        {
            puts("\n[ERROR] Accept failed.\n");
            exit(EXIT_FAILURE);
        }
        client_count ++;

        printf("\n%d client(s) have been connected to this server.\n", client_count);
        
        //handle each client seperately  
        pthread_t sniffer_thread;
	new_socket = malloc(1);
	*new_socket = client_socket;
	if(pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_socket) < 0)
	{
		puts("could not create thread");
		return 1;
	}
	else{
		puts("Thread has been created successfully.");
	}
	puts("Handler assigned");
}
}

void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	
	//Send some messages to the client
	char *message = "This is the connection handler\n";
	write(sock , message, strlen(message));
	
}

