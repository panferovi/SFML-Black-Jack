CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -lsfml-graphics -lsfml-system -lsfml-window
SRC = ./source/main.cpp ./source/game.cpp  ./source/interface.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = BlackJack.out

all: $(OBJ)
	$(CXX) $^ -o $(TARGET) $(CXXFLAGS)
	rm -rf ./source/*.o ./source/*.dot

.PHONY: clean
clean:
	rm -rf ./source/*.o