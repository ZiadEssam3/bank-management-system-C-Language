CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/account.c src/admin.c src/client.c
OUT = bank_system

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
