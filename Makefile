CC=cc
CFLAGS=-Wall -Wextra -Werror
SRC_DIR=src/
SRC_NAME=main.c
SRC=$(addprefix $(SRC_DIR),$(SRC_NAME))
OBJ=$(SRC:.c=.o)
NAME=fdf

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

test: $(SRC)
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all