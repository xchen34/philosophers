NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
SRC_FILES = main.c\
	init.c\
	routine.c\
	thread.c\
	stop.c\
	utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=%.o)

all: $(NAME)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g -pthread -Iinc -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g -pthread -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re