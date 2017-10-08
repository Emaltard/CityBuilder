CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = game
INCLUDES = -I"C:/SFML/include"
LIBS = -L"C:/SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system #-mwindows
OBJ_FILES = main.o tile.o map.o

all : $(EXEC_NAME)

clean :
		rm $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o Bin/$(EXEC_NAME) $(OBJ_FILES) $(LIBS)
	$(MAKE) clean

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
