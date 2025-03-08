BUFFER_SIZE	?= 5
CC		= cc
CFLAGS		= -D BUFFER_SIZE=${BUFFER_SIZE}
RM		= rm -f
TEST_EXEC	= gnl.tests
TEST_BONUS_EXEC	= gnl_bonus.tests
SRC_DIR		= ../src/
TEST_DIR	= ./
TEST_FILES_DIR	= ${TEST_DIR}/testfiles

SRC_FILES		= ${SRC_DIR}get_next_line.c
TEST_FILES		= ${TEST_DIR}tests_gnl_mandatory.c

#SRC_BONUS_FILES	= ${SRC_DIR}get_next_line_bonus.c ${SRC_DIR}get_next_line_utils_bonus.c
#TEST_BONUS_FILES	= ${TEST_DIR}tests_gnl_bonus.c

all: ${TEST_EXEC}

bonus:	${TEST_BONUS_EXEC}

${TEST_EXEC}:		${SRC_FILES} ${TEST_FILES}
				${CC} ${CFLAGS} ${SRC_FILES} ${TEST_FILES} -o ${TEST_EXEC}
				./${TEST_EXEC}

${TEST_BONUS_EXEC}:	${SRC_BONUS_FILES} ${TEST_BONUS_FILES}
				${CC} ${CFLAGS} ${SRC_BONUS_FILES} ${TEST_BONUS_FILES} -o ${TEST_BONUS_EXEC}
				./${TEST_BONUS_EXEC}

clean:		
			${RM} ${TEST_EXEC}
			${RM} ${TEST_BONUS_EXEC}
leakfull:
			valgrind --track-origins=yes --error-exitcode=42 --leak-check=full --quiet ./${TEST_EXEC}
leakfullbonus:
			valgrind --track-origins=yes --error-exitcode=42 --leak-check=full --quiet ./${TEST_BONUS_EXEC}
re:		clean all

.PHONY:		all bonus clean leakfull leakfullbonus re
