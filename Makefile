CC	=		gcc 

SRCS	=	pipex.c pipex_utils.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	pipex

RM		=	rm -f

${NAME}:	${OBJS}
			${CC} ${SRCS} -o ${NAME}

all:		${NAME}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all