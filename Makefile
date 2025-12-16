CC = gcc #-fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
LDFLAGS = -lpthread

SRC = src/main.c \
      src/philos.c \
      src/args.c \
      src/errors.c \
      src/utils.c \
      src/philo_actions.c \
      src/monitor.c \
      src/messg.c

OBJ = $(SRC:.c=.o)

all: philo

philo: $(OBJ)
	$(CC)  -o $@ $^ $(LDFLAGS)

%.o: %.c Makefile 
	$(CC) $(CFLAGS) -c $< -o $@


fclean: clean
	rm -f philo
clean:
	rm -f $(OBJ) philo
re: fclean all
.PHONY: all clean fclean re