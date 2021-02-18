CC = g++
TARGET = PushBoxGame
SOURCES = CWindow.cpp \
	main.cpp \
	PushBoxMap.cpp \
	StatusMap.cpp \

LDFLAGS = -lncurses -std=c++11

all:
	$(CC) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf *.o $(TARGET)
