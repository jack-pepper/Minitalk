# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmalie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 09:35:38 by mmalie            #+#    #+#              #
#    Updated: 2024/11/14 09:35:45 by mmalie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################################
### Name of the file obtained after compilation ###
###################################################

EXEC_CLIENT = client
EXEC_SERVER = server

############################
### Compilation settings ###
############################

CC=cc
CFLAGS=-Wall -Wextra -Werror

####################
### Dependencies ###
####################

DEPS = ./libft/libft.h
LIBFT = ./libft/libft.a

####################
### Source files ###
####################

SRC_CLIENT = client.c
SRC_SERVER = server.c

### Object files
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

##############################################
### Default rules (compile the executable) ###
##############################################

all: $(LIBFT) $(EXEC_CLIENT) $(EXEC_SERVER)

$(LIBFT): $(DEPS)
	cd libft && make

$(EXEC_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(EXEC_CLIENT)

$(EXEC_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(OBJ_SERVER) $(LIBFT) -o $(EXEC_SERVER)

######################################
### Compile .c files into .o files ###
######################################

$(OBJ_CLIENT): $(SRC_CLIENT) $(DEPS)
	$(CC) $(CFLAGS) -c $(SRC_CLIENT) -o $(OBJ_CLIENT)

$(OBJ_SERVER): $(SRC_SERVER) $(DEPS)
	$(CC) $(CFLAGS) -c $(SRC_SERVER) -o $(OBJ_SERVER)

#	$(CC) $(CFLAGS) -c $< -o $@

#########################
### Cleaning-up rules ###
#########################

clean:
	cd libft && make clean
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	cd libft && make fclean
	rm -f $(EXEC_CLIENT) $(EXEC_SERVER)

# Rule to recompile everything (execute fclean, then re)
re: fclean all

############################################
# Those targets are not files but commands
.PHONY: all clean fclean re bonus
