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
			@echo > /dev/null

$(NAME)		:	$(OBJ)
			@$(CLR)
			@echo $(UP) $(CUT) $(UP)
			@$(MAKE) -C libft
			@ar rcs $(NAME) $(OBJ)
			@echo $(G)[$(LB)PRINTF $(G)COMPILED]$(X)
			@/bin/rm -f .cmp

$(ODIR)%.o	:	$(SDIR)%.c $(HEADER)
			@$(CMP)
			@$(MKODIR)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@
			@$(CLR)
			@echo -n $@

clean		:
			@$(MAKE) clean -C libft
			@echo $(R)Cleaning$(X) the $(LB)ft_printf $(X)files...
			@/bin/rm -f $(OBJ)
			@/bin/rm -rf $(ODIR)
			@echo $(UP) $(CUT) $(UP)
			@echo $(G)[$(LB)PRINTF $(G)CLEANED]$(X)

fclean		:	clean
			@/bin/rm -f $(LIBFT)
			@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		: all, clean, fclean, re

############################# FUN ##############################################

LB			=	"\033[96m"
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
CLR			=	printf "\r%40c\r" " "

MKODIR		=	if [ ! -d $(ODIR) ]; then \
			/bin/mkdir -p $(ODIR); fi

CMP			=	if [ ! -e .cmp ]; then \
			echo $(Y)Compiling $(X)the $(LB)ft_printf $(X)files...$(X); \
			touch .cmp; fi
