NAME		:=	cub3D

CC			:=	clang
ifdef LDFLAGS
	FLAGS		:=	$(LDFLAGS) -Llibft -lft -lm -Llibmlx -lmlx -framework OpenGL -framework AppKit
else
	FLAGS		:= -Llibft -lft -lm -Llibmlx -lmlx -framework OpenGL -framework AppKit
endif
CFLAGS		:=	-Wall -Wextra -Werror
FLAGS		+=	-g

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	include

LST_SRCS	:=	parsing/check_map.c \
				parsing/error.c \
				parsing/extract_utils.c \
				parsing/extract.c \
				parsing/free.c \
				parsing/ft_utils.c \
				parsing/map2d.c \
				parsing/parse_file.c \
				parsing/parse_map.c \
				parsing/parsing.c \
				parsing/rgb.c \
				display/draw.c \
				display/key_loop.c \
				display/main.c \
				display/math.c \
				display/raycastinghv.c \
				display/raycastingutils.c \
				display/utils.c \
				display/mousendestroy.c \
				display/utils_init.c \
				
LST_OBJS	:=	$(LST_SRCS:.c=.o)
LST_INCS	:=	parsing.h \
				cub3d.h \
				keys.h \
				proto.h

SRCS		:=	$(addprefix $(DIR_SRCS)/, $(LST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/, $(LST_OBJS))
INCS		:=	$(addprefix $(DIR_INCS)/, $(LST_INCS))

ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m

# .o generation
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile libft/libft.a
	mkdir -p $(DIR_OBJS) $(DIR_OBJS)/parsing $(DIR_OBJS)/display
ifdef CPPFLAGS
	$(CC) -I $(DIR_INCS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) -I $(DIR_INCS) $(CFLAGS) -c $< -o $@
endif
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all:		libft libmlx $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(CFLAGS) -o $@
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

test:	all
	printf "$(ERASE)$(GREEN)Starting tests\n$(END)"
	./tests/parsing_test.sh

libft:
	make -C libft

libmlx:
	make -C libmlx > /dev/null

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
