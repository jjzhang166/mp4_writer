CC = gcc
XX = g++
CFLAGS = -Wall -O -g -I../mp4v2-2.0.0/include -I../mp4v2-2.0.0/libplatform -I../mp4v2-2.0.0/libutil
TARGET = ./mp4_writer

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(XX) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)
	chmod a+x $(TARGET)

clean:
	rm -rf *.o mp4_writer