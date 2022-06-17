#	Compilation setting

NAME	=	minishell	

DB		=	lldb
CC		=	gcc

CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g

OFLAGS	+=	-fsanitize=address
OFLAGS	+=	$(shell pkg-config --libs readline) -I $(shell pkg-config --cflags readline)


#	HEADERS

DIR_INC	=	./headers/
HEADER	=	minishell.h


#	LIBRARIES

LIB		+=	-I $(DIR_INC)


#	SOURCES

DIR_SRC	=	./srcs
SRCS	=	$(DIR_SRC)/main.c       \
			$(DIR_SRC)/build.c      \
			$(DIR_SRC)/utils.c      \
			$(DIR_SRC)/utils_free.c \
			$(DIR_SRC)/parse.c      \
			$(DIR_SRC)/split.c      \
			$(DIR_SRC)/exec.c       \
			$(DIR_SRC)/env.c        \
			$(DIR_SRC)/pwd.c        \
			$(DIR_SRC)/cd.c         \
			$(DIR_SRC)/brexit.c     \
			$(DIR_SRC)/export.c     \
			$(DIR_SRC)/line_env.c   \
			$(DIR_SRC)/line_space.c \
			$(DIR_SRC)/line_sep.c   \
			$(DIR_SRC)/setcmd.c     \
			$(DIR_SRC)/echo.c       \
			$(DIR_SRC)/signals.c    \
			$(DIR_SRC)/get_next_line.c

#	OBJETS

DIR_OBJ	=	./objs
OBJS	=	$(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf
vpath %.c $(DIR_SRC)


all : $(NAME)


$(NAME):	$(OBJS)
	$(CC) $(OFLAGS) $(OBJS) -o $(NAME)


$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(LIB) -o $@ -c $^


$(DIR_OBJ) :
	@mkdir -p $(DIR_OBJ)


clean:
	$(RM) $(DIR_OBJ)


fclean:	clean
	$(RM) $(NAME)
	$(RM) minishell.DSYM


re:		fclean all


norm:
	clear
	@(norminette $(DIR_INC)$(HEADER) $(SRCS) \
	| grep -v  OK\!) || true


# Debugger
db:	$(NAME)
	$(DB) $(NAME)
