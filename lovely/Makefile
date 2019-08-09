ifeq ($(opt), mingw)
	LDFLAGS = -shared -lSDL2_image -lSDL2_ttf -lmingw32 -lSDL2main -lSDL2 -lstdc++ 
else
	LDFLAGS = -shared -lSDL2_image -lSDL2_ttf -lSDL2 -no-pie
endif

vpath %.h ./inc
vpath %.cpp ./src

CXXFLAGS = -std=c++11 -I./inc -O3 -W -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -g

TARGET_O = Window.o Renderer.o Application.o Widget.o Object.o Spectrogram.o Timer.o Worker.o LinearLayout.o \
			Font.o Label.o Texture.o


TARGET = libLovelyGUI.dll

.PHONY : all clean

all : $(TARGET)

$(TARGET) : $(TARGET_O)
	gcc -o $(TARGET) $(TARGET_O) $(LDFLAGS)

Object.o : Object.cpp Application.h Widget.h Object.h
	g++ $(CXXFLAGS) -c ./src/Object.cpp 

Window.o : Window.cpp Window.h
	g++ $(CXXFLAGS) -c ./src/Window.cpp 

Texture.o : Texture.cpp Texture.h
	g++ $(CXXFLAGS) -c ./src/Texture.cpp 

Renderer.o : Renderer.cpp Renderer.h Window.h Texture.h
	g++ $(CXXFLAGS) -c ./src/Renderer.cpp 

Font.o : Font.cpp Font.h  Object.h Texture.h
	g++ $(CXXFLAGS) -c ./src/Font.cpp 

Application.o : Application.cpp Application.h Widget.h Object.h Window.h Renderer.h Font.h
	g++ $(CXXFLAGS) -c ./src/Application.cpp 

Worker.o : Worker.cpp Worker.h Application.h
	g++ $(CXXFLAGS) -c ./src/Worker.cpp 

Timer.o : Timer.cpp Timer.h Worker.h
	g++ $(CXXFLAGS) -c ./src/Timer.cpp 

Widget.o : Widget.cpp Application.h Widget.h Object.h Renderer.h
	g++ $(CXXFLAGS) -c ./src/Widget.cpp 

Spectrogram.o : Spectrogram.cpp Spectrogram.h Application.h Widget.h Object.h Texture.h
	g++ $(CXXFLAGS) -c ./src/Spectrogram.cpp 

LinearLayout.o : LinearLayout.cpp LinearLayout.h Application.h Widget.h Object.h
	g++ $(CXXFLAGS) -c ./src/LinearLayout.cpp 

Label.o : Label.cpp Label.h Application.h Widget.h Object.h Font.h Texture.h
	g++ $(CXXFLAGS) -c ./src/Label.cpp 

clean :
	rm -rf $(TARGET_O)