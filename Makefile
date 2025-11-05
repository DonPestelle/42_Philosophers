CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lpthread

SRC = src/philo.c
OBJ = $(SRC:.c=.o)

all: philo

philo: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


fclean: clean
	rm -f philo
clean:
	rm -f $(OBJ) philo