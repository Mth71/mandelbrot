CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -pthread -fopenmp

SRC_DIR = src
TARGET = mandelbrot

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/args.c $(SRC_DIR)/mandelbrot.c \
       $(SRC_DIR)/matriz_saida.c $(SRC_DIR)/timer.c $(SRC_DIR)/serial.c \
       $(SRC_DIR)/openmp.c $(SRC_DIR)/pthreads1.c $(SRC_DIR)/pthreads2.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.pgm times.txt

.PHONY: all clean test