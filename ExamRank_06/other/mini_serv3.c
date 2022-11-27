#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_client {
	int		id;
	char	buf[128*1024]; // тест на 100001 символ
} t_client;
t_client clients[2048]; // мне пришло 2900 клиентов
int max = 0, next_id = 0;
fd_set active, readyR, readyW;
char bufR[128*1024], bufW[128*1024];

void err()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void send_all(int clientSock)
{
	for (int i = 0; i <= max; i++)
		if (FD_ISSET(i, &readyW) && i != clientSock)
			send(i, bufW, strlen(bufW), 0);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit (1);
	}        
	int port = atoi(argv[1]);
	(void)port;
	FD_ZERO(&active);

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
	if (serverSocket == -1) 
		err();
	max = serverSocket;
	FD_SET(serverSocket, &active);
		
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = htonl(2130706433);
	addr.sin_port = htons(port); 
	socklen_t addr_len = sizeof(addr);
  
	if ((bind(serverSocket, (const struct sockaddr *)&addr, addr_len)) != 0) {
		err();
	}
	if (listen(serverSocket, 10) != 0) {
		err();
	}
		
	while (1)
	{
		readyW = readyR = active;

		if (select(max + 1, &readyR, &readyW, 0, 0) < 0)
			continue;
		
		for (int s = 0; s <= max; s++) {
			if (FD_ISSET(s, &readyR) && s == serverSocket) {
				int clientSock = accept(s, (struct sockaddr *)&addr, &addr_len);
				if (clientSock < 0)
					continue;
				max = clientSock > max ? clientSock : max;
				clients[clientSock].id = next_id++;
				bzero(clients[clientSock].buf, 128*1024);
				FD_SET(clientSock, &active);
				sprintf(bufW, "server: client %d just arrived\n", clients[clientSock].id);
				send_all(clientSock);
				break;
			}
			if (FD_ISSET(s, &readyR) && s != serverSocket) {
				int res = recv(s, bufR, 128*1024, 0);

				// printf("res: %d\n", res);
				if (res <= 0) {
					FD_CLR(s, &active);
					sprintf(bufW, "server: client %d just left\n", clients[s].id);
					send_all(s);
					close(s);
					break;
				}
				else {
					for (int i = 0, j = strlen(clients[s].buf); i < res; i++, j++) {
						clients[s].buf[j] = bufR[i];
						clients[s].buf[j+1] = '\0';
						if (clients[s].buf[j] == '\n') {
							clients[s].buf[j] = '\0';
							sprintf(bufW, "client %d: %s\n", clients[s].id, clients[s].buf);
							send_all(s);
							bzero(clients[s].buf, strlen(clients[s].buf));
							j = -1;
						}
					}
				}
			}
		}
	}
}
