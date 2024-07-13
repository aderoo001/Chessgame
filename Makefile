CXX = g++
CXXFLAGS = -Wall -g `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image
INCLUDES = -Igame -IgameObject -IgameEngine
TARGET = try01
SOURCES = main.cpp gameEngine/Board.cpp gameObject/Piece.cpp gameObject/Pawn.cpp gameObject/Knight.cpp gameObject/Queen.cpp gameObject/King.cpp gameObject/Bishop.cpp gameObject/Rook.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

main.o: gameEngine/Board.h gameObject/Piece.h
gameEngine/Board.o: gameEngine/Board.h gameObject/Piece.h
gameObject/Piece.o: gameObject/Piece.h
gameObject/Pawn.o: gameObject/Pawn.h gameObject/Piece.h
gameObject/Knight.o: gameObject/Knight.h gameObject/Piece.h
gameObject/King.o: gameObject/King.h gameObject/Piece.h
gameObject/Queen.o: gameObject/Queen.h gameObject/Piece.h
gameObject/Bishop.o: gameObject/Bishop.h gameObject/Piece.h
gameObject/Rook.o: gameObject/Rook.h gameObject/Piece.h

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean