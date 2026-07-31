#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

void	fatal(void)
{
	char	*fatalErrorString = "Fatal error\n";
	int	fatalErrorStringLen = strlen(fatalErrorString);

	write(STDERR_FILENO, fatalErrorString, fatalErrorStringLen);
	exit(1);
}
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		char	*errorString = "Wrong number of arguments\n";
		write(STDERR_FILENO, errorString, strlen(errorString));
		exit(1);
	}

	// start server
	int			server_fd;
	struct sockaddr_in	addr;


	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		fatal();

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_port = htons(atoi(argv[1]));

	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		fatal();

	if (listen(server_fd, 10) < 0)
		fatal();

	// select loop
	fd_set	read_set, master_set;
	int	max_fd = server_fd;
	int	next_id = 0;

	// per-client state
	char	*recv_buf[1024];
	int	client_id[1024];
	bzero(recv_buf, sizeof(recv_buf));
	bzero(client_id, sizeof(client_id));

	FD_ZERO(&master_set);
	FD_SET(server_fd, &master_set);

	while(1)
	{
		read_set = master_set; // rebuild every iteration
		
		if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
			fatal();

		// new connection
		if (FD_ISSET(server_fd, &read_set))
		{
			int	client_fd = accept(server_fd, NULL, NULL);
			if (client_fd < 0)
				fatal();

			// store buffer
			recv_buf[client_fd] = calloc(1, 1); // start empty
			if (!recv_buf[client_fd])
				fatal();

			// store id
			client_id[client_fd] = next_id++;

			FD_SET(client_fd, &master_set);
			if (client_fd > max_fd)
				max_fd = client_fd;

			// annouce arrival
			char	msg[64];
			sprintf(msg, "server: client %d just arrived\n", client_id[client_fd]);
			for (int fd = 0; fd <= max_fd; fd++)
				if (FD_ISSET(fd, &master_set) && fd != server_fd && fd != client_fd)
					send(fd, msg, strlen(msg), 0);
		}

		// check all clients fds for incoming data
		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_set) || fd == server_fd)
				continue;

			char	tmp[4096];
			int	bytes = recv(fd, tmp, sizeof(tmp) - 1, 0);

			// disconnect
			if (bytes <= 0)
			{
				char	msg[64];
				sprintf(msg, "server: client %d just left\n", client_id[fd]);
				for (int i = 0; i <= max_fd; i++)
					if (FD_ISSET(i, &master_set) && i != server_fd && i != fd)
						send(i, msg, strlen(msg), 0);

				free(recv_buf[fd]);
				recv_buf[fd] = NULL;
				FD_CLR(fd, &master_set);
				close(fd);

				// update max_fd
				if (fd == max_fd)
					while (max_fd > server_fd && !FD_ISSET(max_fd, &master_set))
						max_fd--;
				continue;
			}

			// append to this client's buffer
			tmp[bytes] = '\0';
			char	*new_buf = realloc(recv_buf[fd], strlen(recv_buf[fd]) + bytes + 1);
			if (!new_buf)
				fatal();
			recv_buf[fd] = new_buf;
			strcat(recv_buf[fd], tmp);

			// extract complete lines and broadcast
			char	*newline;
			while ((newline = strstr(recv_buf[fd], "\n")) != NULL)
			{
				*newline = '\0'; // temporarily terminate at \n
				
				char	msg[strlen(recv_buf[fd]) + 64];
				sprintf(msg, "client %d: %s\n", client_id[fd], recv_buf[fd]);

				for (int i = 0; i <= max_fd; i++)
					if (FD_ISSET(i, &master_set) && i != server_fd && i != fd)
						send(i, msg, strlen(msg), 0);

				// shift buffer past the consumed line
				strcpy(recv_buf[fd], newline + 1);
			}
		}
	}
	return (0);
}
