# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chyuen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 15:52:29 by chyuen            #+#    #+#              #
#    Updated: 2019/06/21 16:29:41 by chyuen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBNAME = libft.a

DIRLIB = ./srcs/
DIRHDER = ./includes/

all: $(LIBNAME)

$(LIBNAME):
	gcc -c $(DIRLIB)*.c -I $(DIRHDER) -Wall -Wextra -Werror
	ar rcs $(LIBNAME) *.o

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(LIBNAME)

re: fclean all