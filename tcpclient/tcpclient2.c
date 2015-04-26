#include "unp.h"

/*void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while(Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Writen(sockfd, sendline, strlen(sendline));
		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated permaturely");
		Fputs(recvline, stdout);
	}
}
*/

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while(Fgets(sendline, MAXLINE, fp) != NULL)
	{
		Writen(sockfd, sendline, 1);
		sleep(1);
		Write(sockfd, sendline + 1, strlen(sendline) - 1);
		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated permaturely");
		Fputs(recvline, stdout);
	}
}

int main(int argc, char const *argv[])
{
	int i, sockfd[5];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");
	for (i = 0; i < 5; ++i)
	{
		sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
		Connect(sockfd[i], (SA *) &servaddr, sizeof(servaddr));
	}

	str_cli(stdin, sockfd[0]);

	exit(0);
}
