CC=gcc
CFLAGS=-g -Wall -rdynamic
OBJS=test_src.o
TARGET=yuv420_to_nv12

LDLIBS          += -lpthread

test_src.o: test_src.c

all : $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDLIBS)

