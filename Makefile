NAME		:=	cube3d

CC			:=	clang
ifdef LDFLAGS
	FLAGS		:=	$(LDFLAGS) -lreadline -Llibft -lft
else
	FLAGS		:=	-lreadline -Llibft -lft
endif
CFLAGS		:=	-Wall -Wextra -Werror
#FLAGS		+=	-g -fsanitize=address

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	include

LST_SRCS	:=	parsing.c
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

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile libft/libft.a
	mkdir -p $(DIR_OBJS) $(DIR_OBJS)/parsing $(DIR_OBJS)/exec
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

libft:
	make -C libft

clean:
	printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	rm -rdf $(DIR_OBJS)
	printf "libft : "
	make clean -C libft

fclean:		clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	rm -rf $(NAME) checker
	printf "libft : "
	make fclean -C libft

re:			fclean all

.PHONY:		all libft clean fclean re
.SILENT:
