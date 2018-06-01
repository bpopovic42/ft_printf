NAME		=	test.out

CC			=	gcc

OBJS		=	$(SRCS:.c=.o)

SRCS		=	main.c

LIBS		=	libftprintf.a libft/libft.a

LDIR		=	ft_printf

LIB			=	$(addprefix $(LDIR)/, $(LIBS))

IDIRS		=	includes libft/includes

INC			=	$(addprefix -I./$(LDIR)/, $(IDIRS)/)

CFLAGS		=	-Wall -Wextra -Werror

all			:	$(NAME)
			@echo > /dev/null

$(NAME)		:	$(SRCS)
			@$(MAKE) -C $(LDIR)
			@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIB) $(INC)

clean		:
			@$(MAKE) clean -C $(LDIR)

fclean		:	clean
			@/bin/rm -f $(LIB)
			@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
