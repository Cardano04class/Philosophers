NAME = philo

SRC = philo.c utils.c init_philo.c routine.c

OBJ = $(SRC:.c=.o)

CC = cc -pthread
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

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