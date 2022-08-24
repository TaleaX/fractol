CC=cc
CFLAGS=-Wall -Wextra -Werror -Ofast
SRC_DIR=src/
SRC_NAME=main.c graphic_utils.c mandelbrot.c coloring.c parse_world_screen.c julia.c init.c bship.c
SRC=$(addprefix $(SRC_DIR),$(SRC_NAME))
SRC_OLD_DIR := src_oldmlx/
SRC_OLD := $(addprefix $(SRC_OLD_DIR),$(SRC_NAME))
OBJ=$(SRC:.c=.o)
NAME=fractol

LIB_DIR=libft/
LIBFT=$(LIB_DIR)libft.a
INC_LIB=-Iinlcude/ -I$(LIB_DIR)/
INC_SRC=-Iinlcude/ -I$(INC_DIR)/
LIBFT=$(LIB_DIR)libft.a

all: $(NAME)

%.o: %.c
	$(CC) -Imlx_new -c $< $(INC_LIB) -o $@

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) mlx_new/libmlx42.a mlx_new/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -L $(LIB_DIR) -lft

test: $(SRC)
	$(CC) $(CFLAGS) -g $< -o $@

old : $(SRC_OLD)
	$(CC) $(SRC_OLD) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	make -C $(LIB_DIR)

debug : CFLAGS += -g
debug : all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

#$(CC) $(OBJ) -Lmlx_new -lmlx42 -framework OpenGL -framework AppKit -o $(NAME)