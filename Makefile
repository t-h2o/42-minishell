#	Compilation setting

NAME	=	minishell	

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
OFLAGS	=	-fsanitize=address


#	Headers

DIR_INC	=	./headers/
HEADER	=	minishell.h


#	Sources

DIR_SRC	=	./srcs
SRCS	=	${DIR_SRC}/main.c


#	Objets

DIR_OBJ	=	./objs
OBJS	=	${addprefix ${DIR_OBJ}/, ${notdir ${SRCS:.c=.o}}}

#	Linux
ifeq ($(UNAME_S),Linux)
	@echo "It is linux os"
endif


#	Apple
ifeq ($(UNAME_S),Darwin)
	@echo "It is mac os"
endif

RM		=	rm -rf

vpath %.c ${DIR_SRC}


all : ${NAME}

${NAME}:	${OBJS}
	${CC} ${OFLAGS} ${OBJS} -o ${NAME}

${DIR_OBJ}/%.o : %.c | ${DIR_OBJ}
	${CC} ${CFLAGS} -I ${DIR_INC} -o $@ -c $^

${DIR_OBJ} :
	@mkdir -p ${DIR_OBJ}

clean:
	${RM} ${DIR_OBJ}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

norm:
	clear
	@(norminette ${DIR_INC}${HEADER} ${SRCS} | grep -v  OK\!) || true

lldb:
	gcc ${SRCS} -I${DIR_INC} -g -o ${NAME}
	lldb ${NAME}
