#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> /* socket_default_client_handler */

#include "sockets.h"
#include "boilerplate.h"

static socket_state_t silent = on;
static socket_state_t debug = off;

int (*_socket) (int, int, int) = socket;

inline void
socket_set_silent (socket_state_t state)
{
	silent = state;
}

inline void
socket_set_debug (socket_state_t state)
{
	debug = state;
}

bool
socket_new (socket_t *socket, const char *ip, int port)
{
	socket->socket.sin_family = AF_INET;
	socket->socket.sin_addr.s_addr = inet_addr (ip);
	socket->socket.sin_port = htons (port);

	socket->connection = _socket (socket->socket.sin_family, SOCK_STREAM, 0);

	final_test (socket->connection);
}

bool
socket_bind (socket_t *socket)
{
	final_test (bind (socket->connection, (struct sockaddr *) &socket->socket, sizeof (socket->socket)));
}

bool
socket_listen (socket_t *socket, int limit)
{
	final_test (listen (socket->connection, limit));
}

bool
socket_serve (socket_t *socket, int limit)
{
	if (socket_bind (socket))
	{
 		return socket_listen (socket, limit);
	}

	return false;
}

bool
socket_server_new (socket_t *socket, char *ip, int port, int limit)
{
	if (socket_new (socket, ip, port))
	{
		return socket_serve (socket, limit);
	}

	return false;
}

bool
socket_default_client_handler (char *buffer)
{
	printf ("Message received from client: \"%s\"\n", buffer);

	return strncmp (buffer, "close", 5) == 0;
}

bool
socket_server_serve (socket_t *server, socket_t *client, socket_client_handler_t handler)
{
	char *buffer;
	bool handled;

	if (!socket_accept (server, client))
	{
		return true;
	}

	buffer = (char *) malloc (sizeof (char) * 1024);

	if (!socket_receive (client, buffer, 1024))
	{
		(void) socket_close (client);

		free (buffer);

		return true;
	}

	if (!socket_close (client))
	{
		free (buffer);

		return true;
	}

	handled = handler ? handler (buffer) : socket_default_client_handler (buffer);

	free (buffer);

	return handled;
}

bool
socket_accept (socket_t *server, socket_t *client)
{
	socklen_t size = sizeof (client->socket);

	client->connection = accept (server->connection, (struct sockaddr *) &client->socket, &size);

	final_test (client->connection);
}

bool
socket_connect (socket_t *socket)
{
	final_test (connect (socket->connection, (struct sockaddr *) &socket->socket, sizeof (socket->socket)));
}

bool
socket_close (socket_t *socket)
{
	test (shutdown (socket->connection, SHUT_RD));

	final_test (close (socket->connection));
}

bool
socket_send (socket_t *socket, char *data)
{
	final_test (send (socket->connection, data, strlen (data), 0));
}

bool
socket_receive (socket_t *socket, char *buffer, int size)
{
	memset (buffer, '\0', size);

	final_test (recv (socket->connection, buffer, size, 0));
}
