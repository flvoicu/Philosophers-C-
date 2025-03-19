NAME = philo

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

CC = gcc

RM = rm -rf

SRC = 	philo.c\
		thread.c\
		utils.c\
		init.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)	

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all
