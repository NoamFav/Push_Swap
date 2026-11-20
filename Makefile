NAME	= push_swap
CC		= cc
# MMD: create .d files to track headers' dependencies for .c files
# MP: in case of header change, to avoid issues if we don't do a full rebuild
CFLAGS	= -Wall -Wextra -Werror -Iincludes -MMD -MP
SRC_DIR	= src
OBJ_DIR	= obj
SRCS	= main.c \
		  stack.c \
		  ctx.c \
		  disorder.c \
		  args/parser.c \
		  args/parser_utils.c \
		  utils/ft_strcmp.c \
		  ops/op.c \
		  ops/push.c \
		  ops/swap.c \
		  ops/rotate.c \
		  ops/rrotate.c \
		  utils/ft_dprintf.c \
		  utils/ft_strlen.c \
		  utils/dprintf_helpers.c \
		  utils/dprintf_dispatch.c \
		  output/output.c \
		  sort/bubble.c \
		  sort/selection.c \
		  sort/ksort.c \
		  sort/radix.c \
		  sort/quicksort.c \
		  sort/utils.c 
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # @ prevents make to echo the command
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# "-" to not fail if the .d files don't exist yet
-include $(DEPS)

.PHONY: all clean fclean re
