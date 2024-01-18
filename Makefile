OBJS	= 2048.o GameLogic.o Helpers.o StringUtils.o
SOURCE	= 2048.cpp GameLogic.cpp Helpers.cpp StringUtils.cpp
HEADER	= ConstValues.h GameLogic.h Helpers.h StringUtils.h
OUT	= 2048.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

2048.o: 2048.cpp
	$(CC) $(FLAGS) 2048.cpp 

GameLogic.o: GameLogic.cpp
	$(CC) $(FLAGS) GameLogic.cpp 

Helpers.o: Helpers.cpp
	$(CC) $(FLAGS) Helpers.cpp 

StringUtils.o: StringUtils.cpp
	$(CC) $(FLAGS) StringUtils.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)