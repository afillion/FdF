LIBPATH = libft

LIB = $(LIBPATH)/libft.a

NAME = fdf

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -L libft -lft -L/usr/local/lib -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

SRC = main.c \
	  draw.c \
	  parse.c \
	  overlay.c

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB):
	make -C $(LIBPATH)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBPATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBPATH)

re: fclean all
