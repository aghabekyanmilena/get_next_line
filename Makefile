CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c

NAME = get_next_line

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c get_next_line.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re