CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/parser.c \
      src/metrics.c \
      src/gantt.c \
      src/fcfs.c \
      src/rr.c \
      src/sjf.c \
      src/stcf.c \
      src/mlfq.c\
      src/compare.c\
      src/config.c

all:
	$(CC) $(CFLAGS) $(SRC) -o schedsim

clean:
	rm -f schedsim