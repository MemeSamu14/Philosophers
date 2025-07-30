NAME = philo

SRC = main.c set_data.c actions_1.c actions_2.c lock_actions.c time_actions.c dead_actions.c checks.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf 

fclean: clean
	rm -f $(NAME)

re: fclean all