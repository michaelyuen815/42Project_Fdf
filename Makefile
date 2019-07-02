# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chyuen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 17:06:36 by chyuen            #+#    #+#              #
#    Updated: 2019/06/21 17:06:55 by chyuen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

DIRSRC = ./srcs/
DIRLIB = ./libft/
DIRHDER = ./includes/
DIRLIBX = ./miniLibX/

all: $(NAME)

$(NAME):
	Make -C $(DIRLIB)
	Make -C $(DIRLIBX)
	gcc -Wall -Wextra -Werror \
	-o $(NAME) \
	$(DIRSRC)*.c \
	-I $(DIRLIBX) -I $(DIRHDER) \
	-L $(DIRLIBX) -L $(DIRLIB) \
	-lmlx -lft \
	-framework OpenGL -framework AppKit

temp:
	-framework OpenGL -framework AppKit 
	
clean:
	/bin/rm -f *.o
	Make clean -C $(DIRLIB)

fclean: clean
	/bin/rm -f $(NAME)
	Make fclean -C $(DIRLIB)
	Make clean -C $(DIRLIBX)

re: fclean all
