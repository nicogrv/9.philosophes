SHELL = /bin/bash

SRCS += main.c
SRCS += print.c

SRC_PATH += ./Philo_src/



OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./Philo_src/_Objet


HEAD_PATH += -I ./Philo_src/_Include


NAME = philo
CC = cc

CFLAGS += -Wall -Werror -Wextra
CFLAGS += -g



vpath %.c ${SRC_PATH}
vpath %.h ${HEAD_PATH}

all: ${NAME}

run: all
# @	clear
	@	./${NAME}

valgrind: all
	valgrind ./${NAME}


${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile philo.h
	@	mkdir -p ${OBJS_PATH}
	@	$(COLORCOMPIL)
	@	${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

${NAME}:  ${OBJS}
	@	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${HEAD_PATH}
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "\t$(NAME) OK" "\033[0m" "\n"


clean:
	@	echo -ne "\r\033[2K" $(YELLOW) "Cleaning\n\n"$(NC)
	@	rm -rf ${OBJS_PATH}


fclean: clean
	@	rm -f ${NAME}
	@	echo -ne "\r\033[2K" $(GREEN) "\t$(NAME) Remove\n"$(NC)"\n"




re: fclean
	@	echo -ne "\r\033[2K" $(YELLOW) "Rebuilding..."$(NC)"\n""\n"
	@	$(MAKE) -s


.PHONY: re clean fclean 

NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'

DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'


ifndef COLORCOMPIL
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		fi \
	fi
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif
