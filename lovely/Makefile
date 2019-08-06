ifeq ($(opt), mingw)
	LDFLAGS = -shared -lSDL2_image -lSDL2_ttf -lmingw32 -lSDL2main -lSDL2 -lstdc++ 
else
	LDFLAGS = -shared -lSDL2_image -lSDL2_ttf -lSDL2 -no-pie
endif

vpath %.h ./inc
vpath %.cpp ./src

CXXFLAGS = -std=c++11 -I./inc -O3 -W -Wall -Wextra -Wno-unused-parameter

TARGET_O = Application.o Widget.o Object.o
TARGET = libLovelyGUI.dll

.PHONY : all clean

all : $(TARGET)

$(TARGET) : $(TARGET_O)
	gcc -o $(TARGET) $(TARGET_O) $(LDFLAGS)

Application.o : Application.cpp Application.h Widget.h Object.h
	g++ $(CXXFLAGS) -c ./src/Application.cpp 

Widget.o : Widget.cpp Application.h Widget.h Object.h
	g++ $(CXXFLAGS) -c ./src/Widget.cpp 

Object.o : Object.cpp Application.h Widget.h Object.h
	g++ $(CXXFLAGS) -c ./src/Object.cpp 

clean :
	rm -rf $(TARGET_O)