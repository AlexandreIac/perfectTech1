##
## Makefile for Makefile in /home/alex/lib
## 
## Made by alex
## Login   <alexandre.iacona@epitech.eu>
## 
## Started on  Wed Nov 22 09:16:37 2017 alex
## Last update Sun Nov 26 18:01:23 2017 alex
##

NAME	= mypam.so

GCC	= gcc

CFLAGS	= -fPIC -c -Wall -Werror

LD	= ld

SRC	= src/mypam.c

OBJS	= $(SRC:.c=.o)

%.o: %.c
	$(GCC) -o $@ $< $(CFLAGS)

all : $(NAME)

$(NAME): $(OBJS)
	$(LD) --shared -o $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

install: re
	sudo mkdir -p /lib/security/
	sudo rm -f /lib/security/$(NAME)
	sudo mv ./$(NAME) /lib/security/
	sudo ./install.sh

uninstall:
	sudo ./uninstall.sh

.PHONY: all clean fclean re
