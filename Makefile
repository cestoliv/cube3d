NAME		:=	cube3d

CC			:=	clang
ifdef LDFLAGS
	FLAGS		:=	$(LDFLAGS) -Llibft -lft
else
	FLAGS		:= -Llibft -lft
endif
#CFLAGS		:=	-Wall -Wextra -Werror
FLAGS		+=	-g

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	include

LST_SRCS	:=	check_map.c \
				error.c \
				extract_utils.c \
				extract.c \
				free.c \
				ft_utils.c \
				main.c \
				map2d.c \
				parse_map.c \
				parsing.c \
				rgb.c
LST_OBJS	:=	$(LST_SRCS:.c=.o)
LST_INCS	:=	parsing.h

SRCS		:=	$(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/, $(LST_OBJS))
INCS		:=	$(addprefix $(DIR_INCS)/, $(LST_INCS))

ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m

# .o generation
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(DIR_SRCS)/main.c $(INCS) Makefile libft/libft.a
	mkdir -p $(DIR_OBJS)
ifdef CPPFLAGS
	$(CC) -I $(DIR_INCS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) -I $(DIR_INCS) $(CFLAGS) -c $< -o $@
endif
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all:		libft $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(CFLAGS) -o $@
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

test:	all
	printf "$(ERASE)$(GREEN)Starting tests\n$(END)"
	./tests/parsing_test.sh

libft:
	make -C libft

clean:
	rm -rf $(DIR_OBJS)
	printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	printf "libft : "
	make clean -C libft

fclean:		clean
	rm -rf $(NAME)
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	printf "libft : "
	make fclean -C libft

re:			fclean all

.PHONY:		all libft clean fclean re test
.SILENT:
