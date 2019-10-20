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

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
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
        printf("SERVER: Accettata connessione con il client!\n");
        
        char msgClient[256];

        while (read(fdConnect, msgClient, sizeof(msgClient)) > 0) {
            printf("SERVER: ricevuto messaggio --> %s\n", msgClient);
            write(fdConnect, msgClient, sizeof(msgClient));
            bzero(msgClient, sizeof(msgClient));
        }
        
    }
    close(fdConnect);
    close(fdSocket);
    return 0;
}
