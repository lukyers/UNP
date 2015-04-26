#include "unp.h"

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
		Write(sockfd, buf, n);
	if (n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}

int main(int argc, char const *argv[])
{
	int listenfd, connfd;
	char buf[MAXLINE];
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);

	for (; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = Accept(listenfd, (SA *) &cliaddr, &clilen)) < 0)
		{
			if (errno == EINTR)
				continue;
			else 
				err_sys("accept error");
		}

		if((childpid = Fork() == 0))
		{
			Close(listenfd);
			printf("connection from %s, port %d\n", 
					Inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)),
					ntohs(cliaddr.sin_port));
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}

	return 0;
}