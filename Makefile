CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = rsa

SRC = main.c \
      math/euclid.c \
      math/modular.c \
      math/primes.c \
      rsa_d/keygen.c \
      rsa_d/encrypt.c \
      rsa_d/decrypt.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
