# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergey <sergey@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 16:16:39 by kpsylock          #+#    #+#              #
#    Updated: 2021/06/07 22:58:13 by sergey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
COMPILER = gcc
FLAGS = -Wall -Wextra -Werror
SOURCES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
 ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
  ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
   ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c\
	ft_isthis.c ft_strsplit.c ft_strsplit_del.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_abs.c \
   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdel.c ft_lstdelone.c ft_lstadd.c \
   ft_lstiter.c ft_lstmap.c ft_strjoinfree.c ft_lltoa.c ft_ulltoa.c ft_ulltoa_base.c ft_strjoinfree2.c ft_putnstr.c \
   ft_strtol.c ft_strnchr.c ft_strsubfree.c get_next_line.c ft_strchr_pos.c ft_numlen.c ft_int_vector_copy.c \
   ft_int_vector_init.c ft_int_vector_pop_back.c ft_int_vector_push_back.c ft_int_vector_push_front.c \
   ft_int_vector_reset_and_free.c ft_void_vector_copy.c ft_void_vector_init.c \
   ft_void_vector_pop_back.c ft_void_vector_push_back.c ft_void_vector_reset_and_free.c \
   ft_void_vector_search.c ft_void_queue_free.c ft_void_queue_init.c ft_void_queue_pop_back.c ft_void_queue_push.c \
   ft_void_queue_resize.c ft_float_atoi.c \
   ft_float_vector_copy.c  ft_float_vector_reset_and_free.c \
   ft_float_vector_init.c ft_float_vector_pop_back.c ft_float_vector_push_back.c ft_float_vector_push_front.c \
   ft_uint_vector_copy.c \
   ft_uint_vector_init.c ft_uint_vector_pop_back.c ft_uint_vector_push_back.c ft_uint_vector_push_front.c \
   ft_uint_vector_reset_and_free.c 

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = ./

HEADERS = libft.h

all: $(NAME)

%.o: %.c $(HEADERS)
	@$(COMPILER) $(FLAGS) -o $@ -c $<
	@echo ".\c"

$(NAME): $(OBJECTS)
	@$(COMPILER) $(FLAGS) -I $(INCLUDES) -c $(SOURCES)
	@ar rcs $(NAME) $(OBJECTS)
	@echo "$(NAME) created"

clean:
	@rm -f $(OBJECTS)
	@echo "Libft object files deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all
