CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lGL -lGLU -lglut -lglad -LDFLAGS -lglfw

TARGET = 3DScene

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) *.o
