NAME = cup3d
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -g
MLX42_PATH = MLX42
MLX42_LIB = $(MLX42_PATH)/build/libmlx42.a

SRCS = main.c \
	game_function.c \
	helper_function.c \
	populate_data.c \
	get_next_line.c \
	get_next_line_utils.c \
	input_function.c

OBJS = $(SRCS:.c=.o)

LIBS = -ldl -lglfw -pthread -lm 
INCLUDES = -I./MLX42/include -I./libft

all: $(MLX42_LIB) $(NAME)

$(MLX42_LIB):
	git clone https://github.com/codam-coding-college/MLX42.git || true
	cd MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX42_LIB) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(MLX42_PATH)/build

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX42_PATH)

re: fclean all

.PHONY: all clean fclean re