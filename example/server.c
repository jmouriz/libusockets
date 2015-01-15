#include <unistd.h>

#include "boilerplate.h"

int
main (int argc, char *argv[])
{
	socket_t server;
	socket_t client;

	socket_set_silent (off);
	socket_set_debug (on);

	test (socket_server_new (&server, IP, PORT, 3));

	while (!socket_server_serve (&server, &client, NULL /* no handler */));

	test (socket_close (&server));

	return EXIT_SUCCESS;
}
