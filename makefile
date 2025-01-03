NAME = cup3d
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -g
MLX42_PATH = MLX42
LIBFT_PATH = libft
MLX42_LIB = $(MLX42_PATH)/build/libmlx42.a
LIBFT_OBJS = $(LIBFT_PATH)/libft.a

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

$(LIBFT_OBJS):
	make -C $(LIBFT_PATH)

$(MLX42_LIB):
	@if [ ! -d "$(MLX42_PATH)" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	cd MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_OBJS) $(MLX42_LIB) $(LIBS) -o $(NAME)

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
