NAME = cup3d

LIBMLX = ./MLX42

HEADERS = -I ./mlx/include -I $(LIBMLX)/include
SRCS = main.c game_function.c helper_function.c populate_data.c get_next_line.c get_next_line_utils.c input_function.c
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wunreachable-code -Ofast -g

all: libmlx $(NAME)

libmlx:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
	else \
		echo "Already have"; \
	fi
		@cd MLX42 && cmake -B build && cmake --build build -j4 \

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADER) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build
	make -C lib clean

fclean: clean
	rm -f $(NAME)
	make -C lib fclean
	rm -rf MLX42

re: fclean all

.PHONY: all clean fclean re libmlx
