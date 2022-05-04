#	Compilation setting

NAME	=	minishell	

CC		=	gcc

CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror

OFLAGS	+=	-fsanitize=address
OFLAGS	+=	-lreadline


#	HEADERS

DIR_INC	=	./headers/
HEADER	=	minishell.h


#	LIBRARIES

LIB		+=	-I $(DIR_INC)



#	SOURCES

DIR_SRC	=	./srcs
SRCS	=	$(DIR_SRC)/main.c	\
			$(DIR_SRC)/build.c	\
			$(DIR_SRC)/utils.c	\
			$(DIR_SRC)/parse.c	\
			$(DIR_SRC)/split.c	\
			$(DIR_SRC)/exec.c	\
			$(DIR_SRC)/env.c	\
			$(DIR_SRC)/pwd.c	\
			$(DIR_SRC)/brexit.c \
			$(DIR_SRC)/line_env.c	\
			$(DIR_SRC)/line_sep.c	\
			$(DIR_SRC)/setcmd.c	\
			$(DIR_SRC)/echo.c

#	OBJETS

DIR_OBJ	=	./objs
OBJS	=	$(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf


#	LINUX

ifeq ($(UNAME_S),Linux)
	LIB		+=	-L /usr/include/
endif


#	MAC OS

ifeq ($(UNAME_S),Darwin)
	OFLAGS	+=	-L $(HOME)/.brew/Cellar/readline/8.1.2
endif


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


lldb:
	gcc $(SRCS) -I$(DIR_INC) $(OFLAGS) -g -o $(NAME)
	lldb $(NAME)

