CC=gcc
FLAGS=-I. -g -ggdb -Wall -fstack-protector-all -Wstack-protector
LIBS=-L. -lsockets -fstack-protector-all

all: example/server example/client

purge: clean
	-rm -f libsockets.so example/server example/client

archive:
	-echo TODO: Make a libsockets.tar.gz archive.

package: all clean archive

source: purge archive

clean:
	-rm -f sockets.o example/server.o example/client.o

sockets.o: sockets.c sockets.h
	$(CC) -c sockets.c -o sockets.o $(FLAGS)

example/server.o: example/server.c example/boilerplate.h example/config.h
	$(CC) -c example/server.c -o example/server.o $(FLAGS)

example/client.o: example/client.c example/boilerplate.h example/config.h
	$(CC) -c example/client.c -o example/client.o $(FLAGS)

libsocket.so: sockets.o
	$(CC) --shared sockets.o -o libsockets.so

example/server: example/server.o libsocket.so
	$(CC) example/server.o -o example/server $(LIBS)

example/client: example/client.o libsocket.so
	$(CC) example/client.o -o example/client $(LIBS)
