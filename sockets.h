#include <sys/socket.h>
#include <resolv.h>
#include <stdbool.h>

#ifndef __SOCKETS_H__
#define __SOCKETS_H__

#define ALWAYS 1

typedef enum
{
	off = false,
	on = true
} socket_state_t;

typedef struct _socket_t
{
	struct sockaddr_in socket;
	int connection;
} socket_t;

inline void socket_set_silent (socket_state_t);
inline void socket_set_debug (socket_state_t);

bool socket_new (socket_t *, const char *, int);
bool socket_bind (socket_t *);
bool socket_listen (socket_t *, int);
bool socket_serve (socket_t *, int);
bool socket_accept (socket_t *, socket_t *);
bool socket_close (socket_t *);
bool socket_connect (socket_t *);
bool socket_send (socket_t *, char *);
bool socket_receive (socket_t *, char *, int);

bool socket_server_new (socket_t *, char *, int, int);

#endif /* __SOCKETS_H__ */
