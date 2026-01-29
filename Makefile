NAME = philo

CFLAGS = -Wall -Wextra -Werror

CC = cc 

INC = -I includes/

SRC = src/*.c

OBJ = $(SRC : .c=.o)

all: $(NAME)
$(NAME) :
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)
re: fclean all

.PHONY : all clean fclean re