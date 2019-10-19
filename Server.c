#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fdSocket, res;

    fdSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(fdSocket < 0) {
        perror("Errore creazione socket stream.");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(4444);
    serverAddr.sin_family = AF_INET;

    int addLen = sizeof(struct sockaddr_in);

    res = bind(fdSocket,(struct sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res < 0){
        perror("Errore binding socket stream.");
        exit(1);
    }

    //Creo la lista di ascolta
    res = listen(fdSocket, 5);
    if(res < 0){
        perror("Errore listen socket stream.");
        exit(1);
    }
    printf("SERVER: Istanziato la lista delle richieste con la listen\n");

    struct sockaddr_in *remoteAddr;
    int remoteAddrLen;

    int fdConnect = accept(fdSocket, (struct sockaddr*)remoteAddr, &remoteAddrLen);

    if(fdConnect < 0){
        perror("Errore instaurazione connessione stream server.");
        exit(1);
    } else {
        printf("SERVER: Accettata connessione con il client!");
        
        char msgClient[256];
        int m = read(fdConnect, msgClient, 256);
        printf("SERVER: Ho ricevuto dal client %d byte!\n", m);

        printf("SERVER: ricevuto dal client\n%s\n", msgClient);

        char *msgServer = "Sono qua per servirti, addio!";
        int n = write(fdConnect, msgServer, sizeof(msgServer));
        printf("CLIENT: Ho inviato al server %d byte!\n", n);

    }
    close(fdConnect);
    close(fdSocket);
    return 0;
}
