
BINARY	= crypto

IDIR	= ./header

LIBDIR	= ./lib

SRC	= ./src

SRCS	= $(SRC)/main.c\
	  $(SRC)/function.c\
	  $(SRC)/test.c\
	  $(SRC)/keygen.c\
	  $(SRC)/key.c\
	  $(SRC)/shnorr.c

OBJS	= $(SRCS:.c=.o)

HEADERS	= $(IDIR)/*

LIBS	= -lgmp\
	  -ltinycrypt

CC	= gcc

CFLAGS	= -I$(IDIR) -L$(LIBDIR)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: 	$(OBJS)
	$(CC) -o $(BINARY) $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(SRC)/*.o

fclean: clean
	rm -f $(BINARY)

re: fclean all

.PHONY:  clean fclean re
