NAME		=	test.out

CC			=	gcc

TNAME		=	unit_tests

TSRCS		=	unit_tests.c

OBJS		=	$(SRCS:.c=.o)

SRCS		=	main.c

LIBS		=	libftprintf.a libft/libft.a

LDIR		=	ft_printf

LIB			=	$(addprefix $(LDIR)/, $(LIBS))

IDIRS		=	includes libft/includes

INC			=	$(addprefix -I./$(LDIR)/, $(IDIRS))

CFLAGS		=	-Wall -Wextra -Werror

all			:	$(NAME)
	@echo > /dev/null

$(NAME)		:	$(SRCS)
	@$(MAKE) -C $(LDIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIB) $(INC)

test		:	$(UTEST)
	@$(MAKE) -C $(LDIR)
	@$(CC) $(DEBUG) -o $(TNAME) ft_printf/srcs/* $(TSRCS) \
		ft_printf/libft/libft.a ft_printf/libftprintf.a \
		-I./ft_printf/includes -I./ft_printf/libft/includes

clean		:
	@$(MAKE) clean -C $(LDIR)

fclean		:	clean
	@/bin/rm -f $(LIB)
	@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
