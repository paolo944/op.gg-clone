CFLAGS = -Wall
BIN=exe

all:		$(BIN)

install:
	curl http://digip.org/jansson/releases/jansson-2.13.tar.bz2 --output jansson-2.13.tar.bz2
	bunzip2 -c jansson-2.13.tar.bz2 | tar xf -
	cd jansson-2.13
	./configure
	make
	make check
	make install

$(BIN): 	main.o profile.o request.o game_history.o
	gcc $(CFLAGS) $^ -o $@ -lcurl -ljansson

main.o:		main.c profile.h 
	gcc $(CFLAGS) -c main.c

profile.o:	profile.c profile.h request.h
	gcc $(CFLAGS) -c profile.c

game_history.o:	game_history.c game_history.h request.h
	gcc $(CFLAGS) -c game_history.c

request.o:	request.c request.h
	gcc $(CFLAGS) -c request.c

clean:
	$(RM) -rf $(BIN) *.o