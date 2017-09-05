CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = game
INCLUDES = -I"C:/SFML-2.4.2/include"
LIBS = -L"C:/Users/Maxence/Desktop/SFML-build/lib" -lsfml-graphics -lsfml-window -lsfml-system
OBJ_FILES = main.o tile.o map.o

all : $(EXEC_NAME)

clean :
		rm game.exe $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<
