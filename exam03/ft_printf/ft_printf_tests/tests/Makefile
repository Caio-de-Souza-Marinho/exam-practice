NAME		= libftprintf.a
CC		= cc
RM		= rm -f
TESTFILE	= tests_ft_printf.c
TESTPROGRAM	= printf.tests
SRCDIR		= ../src/

SRCS		= ${SRCDIR}ft_printf_bonus.c \
		  ${SRCDIR}ft_printf_utils_bonus.c \
		  ${SRCDIR}ft_printf_parser_bonus.c \
		  ${SRCDIR}ft_printf_buffer_bonus.c \
		  ${SRCDIR}ft_printf_char_bonus.c \
		  ${SRCDIR}ft_printf_str_bonus.c \
		  ${SRCDIR}ft_printf_int_bonus.c

OBJS		= ${SRCS:.c=.o}

test:		fclean
			make -C ../src
			@${CC} -o ${TESTPROGRAM} -I . -I ${SRCDIR} ${TESTFILE} -L${SRCDIR} -lftprintf
			@./${TESTPROGRAM}

leakfull:
			valgrind --track-origins=yes --error-exitcode=42 --leak-check=full ./${TESTPROGRAM}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME} ${TESTPROGRAM}

re:		fclean test

.PHONY:		test leakfull clean fclean re
