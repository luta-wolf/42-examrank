#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int sockfd, connfd, max_fd; 
socklen_t len;
fd_set _fds, _fds_read, _fds_write;
struct sockaddr_in servaddr, cli; 
int client = 0;
int _user[65000];
char *_msg[65000];
char buffer[1025];
char send_info[50];

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void send_all(int from, char *str) {
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &_fds_write) && fd != from)
			send(fd, str, strlen(str), 0);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		write(2, "Fatal error\n", strlen("Fatal error\n"));
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 

	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		write(2, "Fatal error\n", strlen("Fatal error\n"));
		exit(1);
	} 

	if (listen(sockfd, 1024) != 0) {
		write(2, "Fatal error\n", strlen("Fatal error\n"));
		exit(1);
	}

	FD_ZERO(&_fds);
	FD_SET(sockfd, &_fds);
	max_fd = sockfd;

	while(1)
	{
		_fds_read = _fds_write = _fds;

		if (select(max_fd + 1, &_fds_read, &_fds_write, 0,0) < 0) {
			write(2, "Fatal error\n", strlen("Fatal error\n"));
			exit(1);
		}

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &_fds_read))
				continue;
			
			if (fd == sockfd)
			{
				len = sizeof(cli);
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd < 0) { 
					write(2, "Fatal error\n", strlen("Fatal error\n"));
					exit(1);
				}
				if (max_fd < connfd)
					max_fd = connfd;
				_user[connfd] = client;
				client++;
				_msg[connfd] = NULL;
				sprintf(send_info, "server: client %d just arrived\n", _user[connfd]);
				send_all(connfd, send_info);
				FD_SET(connfd, &_fds);
				break;
			}
			else
			{
				int ret = recv(fd, buffer, 1024, 0);
				if (ret <= 0)
				{
					sprintf(send_info, "server: client %d just left\n", _user[fd]);
					send_all(fd, send_info);
					close(fd);
					free(_msg[fd]);
					_msg[fd] = NULL;
					FD_CLR(fd, &_fds);
					break;
				}
				buffer[ret] = '\0';
				_msg[fd] = str_join(_msg[fd], buffer);
				char *buuu = NULL;
				while(extract_message(&_msg[fd], &buuu))
				{
					sprintf(send_info, "client %d: ", _user[fd]);
					send_all(fd, send_info);
					send_all(fd, buuu);
					free(buuu);
					buuu = NULL;
				}
			}
		}
	}
	return 0;
}