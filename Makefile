CFLAGS = -Wall
CFLAGS += -ljansson
CFLAGS += -lcurl

BIN=exe

all:	$(BIN)

$(BIN): main.c
	gcc $(CFLAGS) $^ -o $@

clean:
	$(RM) -rf $(BIN) *.o