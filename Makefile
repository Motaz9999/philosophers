NAME = philo

INC = -I includes

CFLAGS = -Wall -Wextra -Werror -g3 $(INC)

CC = cc 

SRC = src/check_input.c src/destroy_philos.c src/error.c src/inti_philos.c src/philo.c src/time.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean : clean
	@rm -f $(NAME)
re: fclean all

.PHONY : all clean fclean re