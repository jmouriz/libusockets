#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "boilerplate.h"

static bool
handle_client (socket_t server, socket_t client)
{
	char *buffer;
	bool handled;

	if (!socket_accept (&server, &client))
	{
		return true;
	}

	buffer = (char *) malloc (sizeof (char) * 1024);

	if (!socket_receive (&client, buffer, 1024))
	{
		(void) socket_close (&client);

		free (buffer);

		return true;
	}

	if (!socket_close (&client))
	{
		free (buffer);

		return true;
	}

	printf ("Message received from client: \"%s\"\n", buffer);

	handled = strncmp (buffer, "close", 5) == 0;

	free (buffer);

	return handled;
}

int
main (int argc, char *argv[])
{
	socket_t server;
	socket_t client;

	socket_set_silent (off);
	socket_set_debug (on);

	test (socket_server_new (&server, IP, PORT, 3));

	while (!handle_client (server, client));

	test (socket_close (&server));

	return EXIT_SUCCESS;
}
