NAME		=	libftprintf.a

CC			=	gcc

SDIR		=	./srcs/

ODIR		=	./objs/

IDIR		=	./includes/

LDIR		=	./libft/

LIBFT		=	$(LDIR)libft.a

SRCS		=	ft_printf.c \

OBJS		=	$(SRCS:.c=.o)

HEADERS		=	ft_printf.h

HEADER		=	$(addprefix $(IDIR), $(HEADERS))

SRC			=	$(addprefix $(SDIR), $(SRCS))

OBJ			=	$(addprefix $(ODIR), $(OBJS))

INC			=	$(addprefix -I,$(IDIR) $(LDIR)$(IDIR))

CFLAGS		=	-Wall -Wextra -Werror

all			:	$(NAME)

$(NAME)		:	$(OBJ)
			@echo "Compiling..."
			$(MAKE) -C libft
			ar rc $(NAME) $(OBJ)
			ranlib $(NAME)
			@echo "[96mft_printf [92mCompiled[0m"

$(OBJ)		:	| $(ODIR)

$(ODIR)		:
			mkdir objs

$(ODIR)%.o	:	$(SDIR)%.c $(HEADER)
			$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean		:
			$(MAKE) clean -C libft
			@echo "Cleaning the [96mft_printf [0mfiles..."
			rm -f $(OBJ)
			rm -rf $(ODIR)
			@echo "[92mDone[0m"

fclean		:	clean
			rm -f $(LDIR)libft.a
			rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re
