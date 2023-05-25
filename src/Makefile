CC := g++
CFLAGS := -std=c++11 -Wall
LIBS := -lGL -lGLU -lglut -lglfw -lGLEW -lglad
INCLUDES := -Ipath/to/glad -Ipath/to/glfw/include -Ipath/to/glew/include -Ipath/to/glm

SRCS := main.c glad.c

all: opengl_app

opengl_app: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(INCLUDES) -o opengl_app

clean:
	rm -f opengl_app
