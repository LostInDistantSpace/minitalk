# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 14:09:57 by bmouhib           #+#    #+#              #
#    Updated: 2024/09/06 14:36:12 by bmouhib          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  VARIABLES                                   #
# ---------------------------------------------------------------------------- #

NAME			:=	minitalk
SERVER_NAME		:=	server
CLIENT_NAME		:=	client

# ---------------------------------- CLIENT ---------------------------------- #

SRC_CLIENT		:=	client.c	

# ---------------------------------- SERVER ---------------------------------- #

SRC_SERVER		:=	server.c

# --------------------------------- COMMANDS --------------------------------- #

CC				:=	gcc
RM				:=	rm -rf

# ----------------------------------- PATHS ---------------------------------- #

LIBFT_DIR		:=	libft/
LIBFT_NAME		:=	libft.a

LIBFT			:=	$(LIBFT_DIR)$(LIBFT_NAME)

# ----------------------------------- FLAGS -------	--------------------------- #

CFLAGS			+=	-Wall
CFLAGS			+=	-Wextra
CFLAGS			+=	-Werror
CFLAGS			+=	-g3

INCLUDES 		:= -I$(LIBFT_DIR)includes 

LIBFT_FLAGS		+=	-L$(LIBFT_DIR)
LIBFT_FLAGS		+=	-lft

MAKE_NO_PRINT	:=	--no-print-directory
MAKE_FLAGS		+=	$(MAKE_NO_PRINT)
MAKE_FLAGS		+=	-C

# ---------------------------------- STYLES ---------------------------------- #

RED				:=	"\033[0;31m\033[1m"
GREEN			:=	"\033[0;32m\033[1m"
BLUE			:=	"\033[0;34m\033[1m"
PURPLE			:=	"\033[0;35m\033[1m"
YELLOW			:=	"\033[1;33m\033[1m"
WHITE			:=	"\033[0;37m\033[1m"
NO_STYLE		:=	"\033[0m"

# ----------------------------------- ECHO ----------------------------------- #

ECHO			:=	echo

DELETION		:=	$(RED)Deletion$(NO_STYLE) of
CREATION		:=	$(GREEN)Creation$(NO_STYLE) of
TO_UPPER		:=	tr '[:lower:]' '[:upper:]'
PROJECT			:=	$(shell $(ECHO) $(NAME) | $(TO_UPPER))
PROJ_CLIENT		:=	$(shell $(ECHO) $(CLIENT_NAME) | $(TO_UPPER))
PROJ_SERVER		:=	$(shell $(ECHO) $(SERVER_NAME) | $(TO_UPPER))
OBJ_FILES		:=	$(BLUE)object files$(NO_STYLE)
DEPS_FILES		:=	$(BLUE)dependencies files$(NO_STYLE)
AND				:=	and
COMPLETE		:=	complete
PROJECT_NAME	:=	$(WHITE)$(PROJECT)$(NO_STYLE)
PROJ_NAME_CLI	:=	$(WHITE)$(PROJ_CLIENT)$(NO_STYLE)
PROJ_NAME_SERV	:=	$(WHITE)$(PROJ_SERVER)$(NO_STYLE)
NAME_FILE		:=	$(BLUE)$(NAME)$(NO_STYLE)

COMP_NAME_CLI	:=	$(ECHO) $(CREATION) $(PROJ_NAME_CLI) $(NAME_FILE) $(COMPLETE)
COMP_NAME_SERV	:=	$(ECHO) $(CREATION) $(PROJ_NAME_SERV) $(NAME_FILE) $(COMPLETE)
COMP_CLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(OBJ_FILES) $(AND) $(DEPS_FILES) $(COMPLETE)
COMP_FCLEAN		:=	$(ECHO) $(DELETION) $(PROJECT_NAME) $(NAME_FILE) $(COMPLETE)

define HELP_MSG
Usage: make [TARGET]
		all         - Build the main program
		clean       - Remove object file(s)
		fclean      - Remove object file(s) and binary file(s)
		re          - Rebuild the program
		bonus       - Build the bonus part of the program
		norm        - Run norminette checks
		debug	    - Activate debug flags
		help        - Display this help message
endef
export HELP_MSG

HELP			:=	@$(ECHO) "$$HELP_MSG"

# ---------------------------------------------------------------------------- #
#                                    RULES                                     #
# ---------------------------------------------------------------------------- #

all:				$(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME):		$(LIBFT)
					@$(CC) $(CFLAGS) $(INCLUDES) $(SRC_CLIENT) -o $(CLIENT_NAME) $(LIBFT_FLAGS)
					@$(COMP_NAME_CLI)

$(SERVER_NAME):		$(LIBFT)
					@$(CC) $(CFLAGS) $(INCLUDES) $(SRC_SERVER) -o $(SERVER_NAME) $(LIBFT_FLAGS)
					@$(COMP_NAME_SERV)

$(LIBFT):
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR)

re: fclean all

.PHONY:	 all clean fclean re

clean:
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR) clean
					@$(COMP_CLEAN)

fclean:				clean
					@$(MAKE) $(MAKE_FLAGS) $(LIBFT_DIR) fclean
					@$(RM) $(SERVER_NAME)
					@$(RM) $(CLIENT_NAME)
					@$(COMP_FCLEAN)

re:					fclean all

help:
					$(HELP)

.PHONY:				all clean fclean re help
