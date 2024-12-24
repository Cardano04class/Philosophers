NAME = philo

SRC = philo.c utils.c

OBJ = $(SRC:.c=.o)

CC = cc -g -pthread
CFLAGS = -g3 -Wall -Wextra -Werror #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.SECONDARY : $(OBJ)