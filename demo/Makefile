ifeq ($(opt), mingw)
	LDFLAGS = -lLovelyGUI -L../lovely -lSDL2_image -lSDL2_ttf -lmingw32 -lSDL2main -lSDL2 -lstdc++ -mwindows 
else
	LDFLAGS = -lLovelyGUI -L../lovely -lSDL2_image -lSDL2_ttf -lSDL2 -no-pie
endif

vpath %.h ./inc
vpath %.cpp ./src

CXXFLAGS = -std=c++11 -I./inc -O3 -W -Wall -Wextra -I../lovely/inc -g

TARGET_O = main.o
TARGET = application

.PHONY : all clean

all : $(TARGET)

$(TARGET) : $(TARGET_O)
	gcc -o $(TARGET) $(TARGET_O) $(LDFLAGS)

main.o : main.cpp
	g++ $(CXXFLAGS) -c main.cpp