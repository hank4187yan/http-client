CC = gcc
LD = ld
MKDIR = mkdir
RM = rm -rf
CFLAGS = -g -Wall -Wno-deprecated -fPIC -lrt -D_GNU_SOURCE -D_GLIBCXX_USE_CXX11_ABI=0

OBJ_DIR = ./obj
OUT_DIR = ./output
BIN_DIR = ../bin/

HTTP_INC_DIR = ./http
HTTP_SRC_DIR = ./http

INCLUDE = -I./ -I$(HTTP_INC_DIR)

TEST = httpclient_sf
BIN = $(TEST)

HTTP_OBJS = http.o

BIN_OBJS = main.o\
	$(HTTP_OBJS)


all: clean $(BIN)

$(BIN): $(BIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf $(BIN)
	rm -rf *.o $(HTTP_SRC_DIR)/*.o

install: all
	install $(BIN)   $(BIN_DIR)
