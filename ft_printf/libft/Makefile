# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 08:42:00 by bopopovi          #+#    #+#              #
#*   Updated: 2018/05/31 16:00:24 by bopopovi         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

############################## SRCS ############################################

# **************************************************************************** #
# Input/Output :

SRC_IO		=	ft_putchar.c ft_putstr.c ft_putnbr.c ft_putnbr_base.c \
			ft_putstr_npr.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_print_memory.c

# **************************************************************************** #
# Lists :

SRC_LST		=	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
			ft_lstiter.c ft_lstmap.c ft_lstpush.c

# **************************************************************************** #
# Memory :

SRC_MEM		=	ft_bzero.c ft_memset.c ft_memcpy.c ft_memccpy.c \
			ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
			ft_memdel.c

# **************************************************************************** #
# Strings :

SRC_STR		=	ft_islower.c ft_isupper.c ft_isalpha.c ft_isdigit.c \
			ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
			ft_toupper.c ft_tolower.c ft_strlen.c ft_strcpy.c \
			ft_strncpy.c ft_strcmp.c ft_strncmp.c ft_strcat.c \
			ft_strncat.c ft_strlcat.c ft_strrchr.c ft_strchr.c \
			ft_strchri.c ft_strstr.c ft_strnstr.c ft_itoa_base.c \
			ft_atoi.c ft_strdup.c ft_strndup.c ft_strnew.c \
			ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
			ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
			ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
			ft_itoa.c ft_issign.c ft_char_count.c ft_strappend.c \
			ft_strnappend.c

# **************************************************************************** #
# Hash :

SRC_HASH	=	ft_hashnew.c ft_hashpopkey.c ft_hashpush.c ft_hashdel.c


############################## VAR #############################################

SRCS		=	$(SRC_IO) $(SRC_LST) $(SRC_MEM) $(SRC_STR) $(SRC_HASH)

OBJS		=	$(SRCS:.c=.o)

IDIR		=	./includes

SDIR		=	./srcs

ODIR		=	./objs

INC			=	$(addprefix -I,$(IDIR)/)

SRC			=	$(addprefix $(SDIR)/, $(SRCS))

OBJ			=	$(addprefix $(ODIR)/, $(OBJS))

LFT			=	$(IDIR)/libft.h

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

############################## RULES ###########################################

all			:	$(NAME)
			@echo > /dev/null

$(NAME)		:	$(OBJ)
			@ar rcs $(NAME) $(OBJ)
			@$(CLR)
			@rm -f .cmp
			@echo $(G)[SUCCESS] $(X)


$(ODIR)/%.o	:	$(SDIR)/%.c $(LFT)
			@$(CMP)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@
			@$(CLR)
			@echo -n $@

clean		:
			@echo $(R)Cleaning $(X)the $(B)Libft $(X)files...
			@rm -f $(OBJ)
			@rm -rf $(ODIR)

fclean		:	clean
			@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all, clean, fclean, re

############################## FUN #############################################

BY			=	"\033[33;1m"
BR			=	"\033[31;1m"
BG			=	"\033[32;1m"
BB			=	"\033[34;1m"
BM			=	"\033[35;1m"
BC			=	"\033[36;1m"
BW			=	"\033[37;1m"
Y			=	"\033[33m"
R			=	"\033[31m"
G			=	"\033[32m"
B			=	"\033[34m"
KW			=	"\033[37;5m"
KR			=	"\033[31;5m"
KG			=	"\033[32;5m"
KB			=	"\033[34;5m"
X			=	"\033[0m"
UP			=	"\033[A"
CUT			=	"\033[K"
CLR			=	printf "\r                         \r"
CMP			=	if [ ! -e .cmp ]; then \
			echo $(Y)Compiling $(X)the $(B)Libft $(X)files...$(Y); \
			touch .cmp; fi
