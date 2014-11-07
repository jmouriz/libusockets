#include <stdio.h>

#include "boilerplate.h"

int
main (int argc, char *argv[])
{
	socket_t server;

	if (argc < 2)
	{
		fprintf (stderr, "Por favor, especifique el mensaje que quiere enviar al servidor.\n");

		return EXIT_FAILURE;
	}

	socket_set_silent (off);
	socket_set_debug (on);

	test (socket_new (&server, IP, PORT));

	test (socket_connect (&server));

	test (socket_send (&server, argv[1]));

	test (socket_close (&server));

	return EXIT_SUCCESS;
}
