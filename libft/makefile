# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 16:51:40 by tdumouli          #+#    #+#              #
#    Updated: 2016/12/19 17:35:17 by tdumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra

SRCS = memset bzero memcpy memccpy memmove memchr memcmp strlen strdup strcpy \
	   strncpy strcat strncat strlcat strchr strrchr strstr strnstr strcmp \
	   strncmp atoi isalpha isdigit isalnum isascii isprint toupper tolower \
	   memalloc memdel strnew strdel strclr striter striteri strmap strmapi \
	   strequ strnequ strsub strjoin strtrim strsplit itoa putchar putstr \
	   putendl putnbr putchar_fd putstr_fd putendl_fd putnbr_fd isspace \
	   lstadd lstnew lstdel lstdelone lstiter lstmap intlen power lstfind \
	   lstaddend lstfindsize lstothernew itoabase atoibase unsignedintlen \
	   itoabaseint erreur

SRC = $(addsuffix .c, $(addprefix ft_, $(SRCS))) 

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	
anc: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	@ar r $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
