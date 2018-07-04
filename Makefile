NAME		=	test.out

CC			=	gcc

TNAME		=	unit_tests

TSRCS		=	unit_tests.c

OBJS		=	$(SRCS:.c=.o)

SRCS		=	main.c

LIBS		=	libftprintf.a

LDIR		=	ft_printf

LIB			=	$(addprefix $(LDIR)/, $(LIBS))

IDIRS		=	includes

INC			=	$(addprefix -I./$(LDIR)/, $(IDIRS))

CFLAGS		=	$(DEBUG)

PTF_SRC		=	$(addprefix $(LDIR)/srcs/, $(PTF_SRCS))

all			:	$(NAME)
	@echo > /dev/null

lib			:
	@$(MAKE) DEBUG=$(DEBUG) -C $(LDIR)

$(NAME)		:	$(OBJS) lib
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIB) $(INC)

test		:	$(TSRCS)
	@$(MAKE) -C $(LDIR)
	@$(CC) $(DEBUG) -o $(TNAME) ft_printf/srcs/* $(TSRCS) \
		ft_printf/libftprintf.a -I./ft_printf/includes

clean		:
	@$(MAKE) clean -C $(LDIR)

fclean		:	clean
	@/bin/rm -f $(LIB)
	@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
