CC = cc
MLXFLAGS = -L ./minilib -lmlx -Ilmlx -lXext -lX11 -lm
SRCS = 42/get_next_line/get_next_line.c  42/get_next_line/get_next_line_utils.c \
	   main.c parser.c ray.c minilib.c
# CFLAGS = -O3 -glldb  -Wall -Wextra -Werror
# CFLAGS = -g  -Wall -Wextra -Werror
CFLAGS = -g  -Wall -Wextra
# CFLAGS =  -glldb -fsanitize=address
OBJS_FOLDER = objs


OBJS = ${SRCS:%.c=$(OBJS_FOLDER)/%.o}
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS_FOLDER) $(OBJS)
	$(MAKE) -C ./42/libft
	$(CC)  $(OBJS) $(CFLAGS) $(MLXFLAGS) 42/libft/libft.a -o $(NAME)
	# $(CC)  $(OBJS) $(CFLAGS)  42/libft/libft.a -o $(NAME)

$(OBJS_FOLDER):
	mkdir -p objs/42/get_next_line

${OBJS_FOLDER}/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	# $(MAKE) clean -C 42/libft
	rm -rf $(OBJS_FOLDER)

fclean: clean
	# $(MAKE) fclean -C 42/libft
	rm -rf $(NAME)

re: fclean all
