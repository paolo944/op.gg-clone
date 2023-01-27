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

$(BIN): 	obj/main.o obj/profile.o obj/request.o obj/game_history.o obj/stats.o
	gcc $(CFLAGS) $^ -o $@ -lcurl -ljansson

obj/main.o:		main.c lib/headers/profile.h 
	gcc $(CFLAGS) -c $< -o $@

obj/profile.o:	lib/profile.c lib/headers/profile.h lib/headers/request.h
	gcc $(CFLAGS) -c $< -o $@

obj/game_history.o:	lib/game_history.c lib/headers/game_history.h lib/headers/request.h
	gcc $(CFLAGS) -c $< -o $@

obj/stats.o:	lib/stats.c lib/headers/stats.h lib/headers/request.h
	gcc $(CFLAGS) -c $< -o $@

obj/request.o:	lib/request.c lib/headers/request.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BIN) bin/*.o