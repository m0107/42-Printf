# Makefile template for a shared library in C

NAME = libftprintf.a
CC = gcc  # C compiler
CFLAGS = -Wall -Werror -Wextra -I. -I libft/. -c  # C flags
RM = rm -f   # rm command
LB_NAME =	libft.a
LIB_DIR	=	./libft


#B_SRCS = ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \

SRCS = ft_printf.c \


OBJS = $(SRCS:.c=.o)

#B_OBJS = $(B_SRCS:.c=.o)

all: ${NAME}

${LIB_DIR}/${LB_NAME}:
		${MAKE} -C $(LIB_DIR)

$(NAME): $(OBJS) ${LIB_DIR}/${LB_NAME}
	ar rcs $@ $(OBJS) 

$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

#$(B_OBJS):$(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS)

#bonus: $(OBJS) $(B_OBJS)
#	rm -f $(NAME)
#	ar rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# I use .PHONY to make sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: clean fclean all re
