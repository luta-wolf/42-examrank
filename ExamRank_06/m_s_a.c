#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_clients {
    int     id;
    char    msg[1024];
} t_clients;

t_clients   clients[1024];
fd_set      readfds, writefds, active;
int         fdMax = 0, idNext = 0;
char        bufferRead[120000], bufferWrite[120000];

void    ftError(char *str) {
    if (str)
        write(2, str, strlen(str));
    else
        write(2, "Fatal error", strlen("Fatal error"));
    write(2, "\n", 1);
    exit(1);
}

void    sendAll(int not) {
    for(int i = 0; i <= fdMax; i++)
        if(FD_ISSET(i, &writefds) && i != not)
            send(i, bufferWrite, strlen(bufferWrite), 0);
}

int main(int ac, char **av) {
    if (ac != 2)
        ftError("Wrong number of arguments");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        ftError(NULL);

    FD_ZERO(&active);
    bzero(&clients, sizeof(clients));
    fdMax = sockfd;
    FD_SET(sockfd, &active);

    struct sockaddr_in  servaddr;
    socklen_t           len;
   	bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ftError(NULL);
    if (listen(sockfd, 10) < 0)
        ftError(NULL);

    while(1) {
        readfds = writefds = active;
        if (select(fdMax + 1, &readfds, &writefds, NULL, NULL) < 0)
            continue;
        for(int fdI = 0; fdI <= fdMax; fdI++) {
            if (FD_ISSET(fdI, &readfds) && fdI == sockfd) {
                int connfd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
                if (connfd < 0)
                    continue;
                fdMax = connfd > fdMax ? connfd : fdMax;
                clients[connfd].id = idNext++;
                FD_SET(connfd, &active);
                sprintf(bufferWrite, "server: client %d just arrived\n", clients[connfd].id);
                sendAll(connfd);
                break;
            }
            if (FD_ISSET(fdI, &readfds) && fdI != sockfd) {
                int res = recv(fdI, bufferRead, 65536, 0);
                if (res <= 0) {
                    sprintf(bufferWrite, "server: client %d just left\n", clients[fdI].id);
                    sendAll(fdI);
                    FD_CLR(fdI, &active);
                    close(fdI);
                    break;
                }
                else {
                    for (int i = 0, j = strlen(clients[fdI].msg); i < res; i++, j++) {
                        clients[fdI].msg[j] = bufferRead[i];
                        if (clients[fdI].msg[j] == '\n') {
                            clients[fdI].msg[j] = '\0';
                            sprintf(bufferWrite, "client %d: %s\n", clients[fdI].id, clients[fdI].msg);
                            sendAll(fdI);
                            bzero(&clients[fdI].msg, strlen(clients[fdI].msg));
                            j = -1;
                        }
                    }
					break;
                }
            }
        }
    }
}
