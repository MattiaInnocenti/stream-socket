#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fdSocket, res;

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(fdSocket < 0) {
        perror("Errore creazione socket stream.");
        exit(1);
    }

    struct sockaddr_in clientAddr;
    clientAddr.sin_port = 0;
    clientAddr.sin_family = AF_INET;

    struct hostent *host;
    host = gethostbyname("127.0.0.1");

    int addLen = sizeof(struct sockaddr_in);

    if(host == 0){
        perror("Gethostbyname fallita");
        exit(1);
    }

    bcopy(host->h_addr_list[0],&clientAddr.sin_addr,host->h_length);

    res = bind(fdSocket,(struct sockaddr*) &clientAddr, sizeof(clientAddr));
    printf("CLIENT: Ho creato il binding con il dispositivo fisico.");

    if(res < 0){
        perror("Errore binding socket stream.");
        exit(1);
    }

    res = connect(fdSocket, (struct sockaddr*) &clientAddr, sizeof(clientAddr));
    if(res != -1){
        perror("Errore instaurazione connessione stream.");
        exit(1);
    } else {
        printf("CLIENT: Siamo connessi con il server!");
        
        char *msgCliente = "Siamo finalmente connessi, forse...";
        int n = write(fdSocket, msgCliente, sizeof(msgCliente));
        printf("CLIENT: Ho inviato al server %d byte!\n", n);
        
        char msgServer[256];
        int m = read(fdSocket, msgServer, 256);
        printf("CLIENT: Ho ricevuto dal server %d byte!\n", m);

        printf("CLIENT: ricevuto dal server\n%s\n", msgServer);
    }
    close(fdSocket);
    return 0;
}
