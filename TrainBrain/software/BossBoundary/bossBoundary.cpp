#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include "bossBoundary.h"

#define PORT 8081


BossBoundary::BossBoundary()
{
        std::cout << "Inititaing TCP server" << std::endl;
    
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Server has been setup\n");
}

BossBoundary::~BossBoundary(){}

// Receive
// Receives data from Boss, and returns the table number
// Returns 0 on failure
std::string BossBoundary::receive()
{
    std::memset( buffer, 0, sizeof( 1024 ) );
    valread = read( new_socket , buffer, 1024);
    printf("Received: %s\n", buffer);
    std::string s(buffer);
    return s;
}

void BossBoundary::deliveryFinnished()
{
    std::memset( buffer, 0, sizeof( 1024 ) );
    sprintf(buffer, "%s", "delivered");
    send(new_socket , buffer , strlen(buffer) , 0 );
    std::cout << "Message to BOSS has been send " << buffer << std::endl;
}