# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 16:18:40 by melanieyane       #+#    #+#              #
#    Updated: 2023/11/22 17:18:13 by myanez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Dossiers

SRCDIR = SRCS
OBJDIR = objs
HDRDIR = includes


# Fichiers

SRCS = $(shell find ${SRCDIR} -name '*.c')
OBJS = ${SRCS:${SRCDIR}%.c=${OBJDIR}%.o}
HEADERS = ${HDRDIR}

# Compilation

CC = GCC
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

# Commandes

RM = rm -Rf

# Règles

${OBJDIR}/%.o : ${SRCDIR}/%.c
	@mkdir -p ${OBJDIR}
	@echo "Compiling $< into ${@F}..."
	@${CC} ${CFLAGS} -I ${HEADERS} -c $< -o $@

${NAME} : ${OBJS}
	@echo "\nCompiling philo executable..."
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "\nAll done!"
			
all : ${NAME}

# Nettoyage

clean : 
	@echo "Cleaning...\n"
	@${RM} ${OBJS}
	@${RM} ${OBJDIR}

fclean : clean
	@echo "Full cleaning...\n"
	@${RM} ${NAME}

# Autres règles

re : fclean all

.PHONY : re fclean clean all
	


