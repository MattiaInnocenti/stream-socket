#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char msgToSend[256]; 
    char receiveMsg[256]; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(4444); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        perror("\nConnection Failed \n"); 
        return -1; 
    } 

    while((read(0, msgToSend, sizeof(msgToSend))) > 0) {
        write(sock, msgToSend, sizeof(msgToSend));
        printf("CLIENT: %s\n", msgToSend);
        bzero(msgToSend, sizeof(msgToSend));

        read(sock, receiveMsg, sizeof(receiveMsg));
        printf("SERVER: %s\n", receiveMsg);
        bzero(receiveMsg, sizeof(receiveMsg));
    }
    close(sock);
    return 0; 

}
