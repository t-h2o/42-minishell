#	Compilation setting

NAME	=	minishell	

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror
OFLAGS	+=	-fsanitize=address
OFLAGS	+=	-lreadline


#	HEADERS

DIR_INC	=	./headers/
HEADER	=	minishell.h

#	LIBRARIES

LIB		+=	-I $(DIR_INC)
LIB		+=	-L /usr/include/readline
LIB		+=	-lreadline

#	SOURCES

DIR_SRC	=	./srcs
SRCS	=	$(DIR_SRC)/main.c	\
			$(DIR_SRC)/build.c

#	OBJETS

DIR_OBJ	=	./objs
OBJS	=	$(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf

vpath %.c $(DIR_SRC)


all : $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OFLAGS) $(LIB) $(OBJS) -o $(NAME)
#	$(CC) $(OFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(LIB) -o $@ -c $^

$(DIR_OBJ) :
	@mkdir -p $(DIR_OBJ)

clean:
	$(RM) $(DIR_OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

norm:
	clear
	@(norminette $(DIR_INC)$(HEADER) $(SRCS) \
	| grep -v  OK\!) || true

lldb:
	gcc $(SRCS) -I$(DIR_INC) $(OFLAGS) -g -o $(NAME)
	lldb $(NAME)
