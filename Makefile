##
## Makefile for Makefile in /home/alex/lib
## 
## Made by alex
## Login   <alexandre.iacona@epitech.eu>
## 
## Started on  Wed Nov 22 09:16:37 2017 alex
## Last update Wed Nov 22 09:25:39 2017 alex
##

NAME	= pam_module.so

GCC	= gcc

CFLAGS	= -W -Wall -ansi -pedantic -fPIC

LDFLAGS	= -lpam

SRC	= pam_modules.c

OBJS	= $(SRC:.c=.o)c

%.o: %.c
	$(GCC) -c -o $@ $< $(CFLAGS)

all : $(NAME)

$(NAME): $(OBJS)
	$(GCC) -shared -o $@ $(OBJS) $(LDFLAGS)
