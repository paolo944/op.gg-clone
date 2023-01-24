CFLAGS = -Wall
BIN=exe

all:		$(BIN)

$(BIN): 	main.o profile.o request.o game_history.o
	gcc $(CFLAGS) $^ -o $@ -lcurl -ljansson

main.o:		main.c profile.h 
	gcc $(CFLAGS) -c main.c

profile.o:	profile.h request.h
	gcc $(CFLAGS) -c profile.c

game_history.o:	game_history.h request.h
	gcc $(CFLAGS) -c game_history.c

request.o:	request.h
	gcc $(CFLAGS) -c request.c

clean:
	$(RM) -rf $(BIN) *.o