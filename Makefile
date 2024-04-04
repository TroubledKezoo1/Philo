NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -ggdb#-fsanitize=thread 

SRCS =	main.c\
		utils.c\
		ft_split.c\
		initialize.c\
		free.c\
		time.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
