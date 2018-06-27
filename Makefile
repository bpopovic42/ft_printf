NAME		=	test.out

CC			=	gcc

TNAME		=	unit_tests

TSRCS		=	unit_tests.c

PTF_SRCS	=	ft_printf.c ft_printf_buffer.c ft_printf_is_fspecif.c \
			ft_printf_itoa.c ft_printf_parse_args.c ft_printf_itoa_base.c

OBJS		=	$(SRCS:.c=.o)

SRCS		=	main.c

LIBS		=	libftprintf.a libft/libft.a

LDIR		=	ft_printf

LIB			=	$(addprefix $(LDIR)/, $(LIBS))

IDIRS		=	includes libft/includes

INC			=	$(addprefix -I./$(LDIR)/, $(IDIRS))

CFLAGS		=	-Wall -Wextra -Werror

PTF_SRC		=	$(addprefix $(LDIR)/srcs/, $(PTF_SRCS))

all			:	$(NAME)
	@$(MAKE) -C $(LDIR)/libft
	@$(MAKE) -C $(LDIR)
	@echo > /dev/null

$(NAME)		:
	@$(MAKE) -C $(LDIR)/libft
	@$(MAKE) -C $(LDIR)
	@$(CC) $(DEBUG) $(CFLAGS) -o $(NAME) $(SRCS) $(LIB) $(INC)

test		:	$(TSRCS)
	@$(MAKE) -C $(LDIR)/libft
	@$(MAKE) -C $(LDIR)
	@$(CC) $(DEBUG) -o $(TNAME) ft_printf/srcs/* $(TSRCS) \
		ft_printf/libft/libft.a ft_printf/libftprintf.a \
		-I./ft_printf/includes -I./ft_printf/libft/includes

clean		:
	@$(MAKE) clean -C $(LDIR)
	@$(MAKE) clean -C $(LDIR)/libft

fclean		:	clean
	@/bin/rm -f $(LIB)
	@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
