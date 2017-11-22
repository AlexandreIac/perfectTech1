##
## Makefile for Makefile in /home/alex/lib
## 
## Made by alex
## Login   <alexandre.iacona@epitech.eu>
## 
## Started on  Wed Nov 22 09:16:37 2017 alex
## Last update Wed Nov 22 10:00:09 2017 alex
##

NAME	= pam_modules.so

GCC	= gcc

CFLAGS	= -fPIC

LDFLAGS	= -lpam

SRC	= pam_modules.c

OBJS	= $(SRC:.c=.o)

%.o: %.c
	$(GCC) -c -o $@ $< $(CFLAGS)

all : $(NAME)

$(NAME): $(OBJS)
	$(GCC) -shared -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: all clean

install: re
	sudo rm -f /etc/pam.d/lib/security/pam_modules.so
	sudo mv ./pam_modules.so /etc/pam.d/lib/security/

.PHONY: all clean fclean re
