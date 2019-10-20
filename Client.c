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
    /*int fdSocket, res;

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdSocket < 0) {
        perror("Errore creazione socket stream.");
        exit(1);
    }

    struct sockaddr_in clientAddr;
    clientAddr.sin_port = 0;
    clientAddr.sin_family = AF_INET;

    struct hostent *localHost;
    localHost = gethostbyname("127.0.0.1");

    if(localHost == 0){
        perror("Gethostbyname fallita");
        exit(1);
    }

    bcopy(localHost->h_addr_list[0],&clientAddr.sin_addr,localHost->h_length);

    //res = bind(fdSocket,(struct sockaddr*) &clientAddr, sizeof(clientAddr));
    printf("CLIENT: Ho creato il binding con il dispositivo fisico.\n");

    if(res < 0){
        perror("Errore binding socket stream.");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_port = 4444;
    serverAddr.sin_family = AF_INET;

    struct hostent *remoteHost;
    remoteHost = gethostbyname("192.168.43.134");

    if(remoteHost == 0){
        perror("Gethostbyname fallita");
        exit(1);
    }

    bcopy(remoteHost->h_addr_list[0],&serverAddr.sin_addr,remoteHost->h_length);

    //mi devo connettere alla macchina del server creo una istanza all'IP della macchina che risiede a 
    //192.168.43.134
    res = connect(fdSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    printf("CLIENT: la connect ha restituito %d\n", res);
    printf("CLIENT: Ho creato la connessione con il server.\n");

    if(res == -1){
        perror("Errore instaurazione connessione stream.");
        exit(1);
    } else {
        printf("CLIENT: Siamo connessi con il server!");
        sleep(500);
        char *msgCliente = "Siamo finalmente connessi, forse...";
        int n = write(fdSocket, msgCliente, sizeof(msgCliente));
        printf("CLIENT: Ho inviato al server %d byte!\n", n);
        
        char msgServer[256];
        int m = read(fdSocket, msgServer, 256);
        printf("CLIENT: Ho ricevuto dal server %d byte!\n", m);

        printf("CLIENT: ricevuto dal server\n%s\n", msgServer);
    }
    close(fdSocket);
    return 0;*/
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

        read(sock, receiveMsg, sizeof(receiveMsg));
        printf("SERVER: %s\n", msgToSend);
    }
    close(sock);
    return 0; 
}
