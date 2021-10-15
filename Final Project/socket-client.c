#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

    // first get the arguments from the terminal which are serveradress,portnumber and text

    int counter, port_number;
    char *server_add, *text;


    if(argc!= 6)
    {
        printf("The number of given arguments are not equal to what's expected(expected 6, given %d), the input structure is:\n‫‪./socket-client‬‬ ‫‪-h‬‬ ‫‪serveraddress‬‬ ‫‪-p‬‬ ‫‪portnumber‬‬ ‫‪text‬‬",argc);
        exit(EXIT_FAILURE);
    }

    // get the value of given param
    server_add = (char *)argv[2];
    port_number = atoi(argv[4]);
    text = (char *)argv[5];

    // create a socket
    int network_socket;
    network_socket= socket(AF_INET, SOCK_STREAM, 0);
    
    // specify an address for the socket to connect
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(server_add);
    
    // connect to server 
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  
    // check if socket is connected successfully
    if (connection_status < 0)
    {
        printf("There was an error making connection to the remote socket");
    } 


    // define start and end to compute elapsed time 
    struct timespec start_time, end_time;

    // get the start time
    clock_gettime(CLOCK_BOOTTIME, &start_time);
    
    // send the message to server
    send(network_socket, text, strlen(text), 0);

    // now we send or receive some data
    char server_response[5000]={""};
    // receive message from the server
    recv(network_socket, &server_response, sizeof(server_response),0);
    // get the end clock
    clock_gettime(CLOCK_BOOTTIME, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1e9; 
    // convert ns to ms
    elapsed_time = (elapsed_time + (end_time.tv_nsec - start_time.tv_nsec)) * 1e-6;
    
    // printout received message and the elapsed time
    printf("\rreceived message from server:\n%s\nelapsed time: \t %fms\n", server_response, elapsed_time);

    // close the socket
    close(network_socket);

    return 0;
}
