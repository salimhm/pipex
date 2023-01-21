CC	=		gcc 

SRCS	=	pipex.c pipex_utils.c child.c parent.c ft_fork.c ft_strncmp.c ft_split.c ft_errors.c ft_fork_parent.c free.c ft_strlcpy.c ft_strdup.c 

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