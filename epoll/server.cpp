#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define MAXLINE		5
#define	OPEN_MAX	100
#define LISTENQ		20
#define	SERV_PORT	5000
#define	INFTIM		1000

void setnoblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if(opts < 0)
	{
		perror("fch=ntl error");
		exit(1);
	}
	opts = opts|O_NONBLOCK;
	if(fcntl(sock, F_SETFL, opts) < 0)
	{
		perror("fcntl(sock, F_SETFL, opts)");
		exit(1);
	}
}

int main()
{
	int i, maxi, listenfd, connfd, sockfd, epfd, nfds;
	ssize_t	n;
	char line[MAXLINE];
	socklen_t client;
	struct epoll_event ev, events[20];

	epfd = epoll_create(256);
	struct sockaddr_in	clientaddr;
	struct sockaddr_in	serveraddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

//	setnoblocking(listenfd);

	ev.data.fd = listenfd;

	ev.events = EPOLLIN|EPOLLET;
//	ev.events = EPOLLIN;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENQ);

	maxi = 0;
	client = sizeof(struct sockaddr);

	for(;;){
		nfds = epoll_wait(epfd, events, 20, 500);

		for(i = 0; i < nfds; i++)
		{
			if(events[i].data.fd = listenfd)
			{
				printf("001\n");
				connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &client);
				if(connfd < 0)
				{
					perror("accept error");
					exit(1);
				}

				char *str = inet_ntoa(clientaddr.sin_addr);
				printf("accept a connection from %s\n", str);

				ev.data.fd = connfd;

				ev.events = EPOLLIN|EPOLLET;
	//			ev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			}
			else if(events[i].events&EPOLLIN)
			{
				printf("EPOLLIN\n");
				if(sockfd = events[i].data.fd < 0)
					continue;
				if((n = read(sockfd, line, MAXLINE)) < 0)
				{
					if(errno == ECONNRESET)
					{
						close(sockfd);
						events[i].data.fd = -1;
					}else
						printf("error\n");
				}else if(n == 0)
				{
					close(sockfd);
					events[i].data.fd = -1;
				}
				line[n] = '\0';
				printf("read %s\n", line);
				
				ev.data.fd = sockfd;

				ev.events = EPOLLOUT|EPOLLET;
		//		ev.events = EPOLLOUT;
			}
			else if(events[i].events & EPOLLOUT)
			{
				printf("002\n");
				sockfd = events[i].data.fd;
				write(sockfd, line, n);
				ev.data.fd = sockfd;

				ev.events = EPOLLIN|EPOLLET;
			//	ev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}

	return 0;
}
