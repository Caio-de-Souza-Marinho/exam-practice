#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int	extract_message(char **buf, char **msg);
char	*str_join(char *buf, char *add);
void	fatal(void);

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	int			sockfd;
	struct sockaddr_in	servaddr; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0)
		fatal();

	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal();

	if (listen(sockfd, 10) < 0)
		fatal();

	fd_set	read_set, master_set;
	int	max_fd = sockfd;
	int	next_id = 0;

	char	*recv_buf[1024];
	int	client_id[1024];
	bzero(recv_buf, sizeof(recv_buf));
	bzero(client_id, sizeof(client_id));

	FD_ZERO(&master_set);
	FD_SET(sockfd, &master_set);

	while (1)
	{
		read_set = master_set;

		if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
			fatal();
		
		// accept block
		if (FD_ISSET(sockfd, &read_set))
		{
			int	client_fd = accept(sockfd, NULL, NULL);
			if (client_fd < 0)
				fatal();

			recv_buf[client_fd] = calloc(1, 1);
			if (!recv_buf[client_fd])
				fatal();

			client_id[client_fd] = next_id++;

			FD_SET(client_fd, &master_set);

			if (client_fd > max_fd)
				max_fd = client_fd;

			char	msg[64];
			sprintf(msg, "server: client %d just arrived\n", client_id[client_fd]);
			for (int fd = 0; fd <= max_fd; fd++)
				if (FD_ISSET(fd, &master_set) && fd != sockfd && fd != client_fd)
					send(fd, msg, strlen(msg), 0);
		}

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_set) || fd == sockfd)
				continue;

			char	tmp[4096];
			int	bytes = recv(fd, tmp, sizeof(tmp) - 1, 0);

			// disconnect
			if (bytes <= 0)
			{
				char	msg[64];
				sprintf(msg, "server: client %d just left\n", client_id[fd]);
				for (int i = 0; i <= max_fd; i++)
					if (FD_ISSET(i, &master_set) && i != sockfd && i != fd)
						send(i, msg, strlen(msg), 0);

				free(recv_buf[fd]);
				recv_buf[fd] = NULL;
				FD_CLR(fd, &master_set);
				close(fd);

				if (fd == max_fd)
				{
					while (max_fd > sockfd && !FD_ISSET(max_fd, &master_set))
						max_fd--;
				}
				continue;
			}

			tmp[bytes] = '\0';
			char	*new_buf = str_join(recv_buf[fd], tmp);
			if (!new_buf)
				fatal();
			recv_buf[fd] = new_buf;

			char	*msg;
			while (extract_message(&recv_buf[fd], &msg))
			{
				char	out[strlen(msg) + 64];
				sprintf(out, "client %d: %s", client_id[fd], msg);

				for (int i = 0; i <= max_fd; i++)
					if (FD_ISSET(i, &master_set) && i != sockfd && i != fd)
						send(i, out, strlen(out), 0);
				free(msg);
			}
		}
	}
}

int	extract_message(char **buf, char **msg)
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

char	*str_join(char *buf, char *add)
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

void	fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}
