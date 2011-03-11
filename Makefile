OS = $(shell uname)

GLFLAGS = -framework GLUT -framework OpenGL
CXXFLAGS = -g -Wall 

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.h)

all: $(OBJS)
	g++ $(CXXFLAGS) $(GLFLAGS) $(OBJS) -o game

test: game
	./game
